#include "circuit.h"
#include "circuit_desc.h"
#include "log.h"

#include <map>
#include <string>
//#include <sstream>
//#include <cstdio>

#define DEBUG
#undef DEBUG

#define EVENT_QUEUE_SIZE 128
#define SUBCYCLE_SIZE 64

CHIP_DESC( _VCC ) = 
{
	CUSTOM_CHIP_START(NULL)
	OUTPUT_PIN(1)
};

CHIP_DESC( _GND ) = 
{
	CUSTOM_CHIP_START(NULL)
	OUTPUT_PIN(1)
};

// Option to disable optimizations
// on chips where they do not perform well
CUSTOM_LOGIC( deoptimize )
{
    for(ChipLink& cl : chip->output_links)
    {
#ifdef DEBUG
        log_print("Deoptimizing {}", cl.chip->name);
#endif
        cl.chip->optimization_disabled = true;
    }
}

CHIP_DESC( _DEOPTIMIZER ) = 
{
	CUSTOM_CHIP_START(deoptimize)
	OUTPUT_PIN(1)
};



CUSTOM_LOGIC(trace) {
    auto data = (DebugTraceCustomData*)chip->custom_data;
	
	chip->inputs ^= mask;

	if(data == nullptr) return;

	if(mask == 0) return;

	uint32_t value = (chip->inputs & 1) ? 1 : 0;
    data->bit_events->emplace_back(chip->circuit->global_time, value, 0);

    if(data->bus_events) {
        auto v = value << data->bus_shift;
        auto m = 1 << data->bus_shift;
        if(data->bus_events->empty()) {
            data->bus_events->emplace_back(chip->circuit->global_time, v, m);
        } else {
            auto& back = data->bus_events->back();
            if(back.time == chip->circuit->global_time)
                back.value = (back.value & ~m) | v, back.valid_mask |= m;
            else
                data->bus_events->emplace_back(chip->circuit->global_time, (back.value & ~m) | v, back.valid_mask | m);
        }
    }
}

CHIP_DESC(_TRACE) {
    CUSTOM_CHIP_START(trace)
    INPUT_PINS(1)
};


const double Circuit::timescale = 1.0e-12; // 1 ps

class CircuitBuilder
{
private:
    typedef std::pair<Chip*, const ChipDesc*> ChipDescPair;
	typedef std::pair<uint8_t, ChipDescPair> Connection;
    typedef std::multimap<std::string, ChipDescPair>::iterator ChipMapIterator;

    std::multimap<std::string, ChipDescPair> chip_map;
    std::vector<Connection> connection_list_out, connection_list_in;

    Circuit* circuit;
    std::vector<Chip*>& chips;
	int trace_count = 0;

    void createChip(const ChipDesc* chip_desc, std::string name, void* custom, int queue_size, int subcycle_size);
    bool findConnection(const std::string& name1, uint8_t pin1, const std::string& name2, uint8_t pin2);

public:
    CircuitBuilder(Circuit* cir, std::vector<Chip*>& ch) : circuit(cir), chips(ch) { }

    void createChips(std::string prefix, const CircuitDesc* desc);
    void createSpecialChips();

	void createNets(const CircuitDesc* desc);
    void createTraces(const CircuitDesc* desc);
    
    void findConnections(std::string prefix, const CircuitDesc* desc);
    void makeAllConnections();

    const std::string getOutputInfo(const Chip* chip)
    {
        for(auto x : chip_map)
            if(x.second.first == chip)
                return std::format("{}.{}", x.first, x.second.second->output_pin);

        return std::string("unknown");
    }

    const std::string getInputInfo(const Chip* chip, int num)
    {
        for(auto x : chip_map)
            if(x.second.first == chip)
				return std::format("{}.{}", x.first, x.second.second->input_pins[num]);

        return std::string("unknown");
    }

    std::vector<DebugChip> debug_chips;
	std::vector<DebugConnection> debug_connections;
	std::vector<DebugNet> debug_nets;
};


Circuit::Circuit(const Settings& s, Input& i, Video& v, const CircuitDesc* desc, const CircuitDesc* extra_desc, bool enable_debugger, const char* name) 
    : settings(s), game_config(desc, name), input(i), video(v), global_time(0), queue_size(0)
{
    CircuitBuilder converter(this, chips);

    converter.createNets(desc);
    for(const SubcircuitDesc& d : desc->get_sub_circuits())
        converter.createNets(d.desc());

    // Construct special chips
    converter.createSpecialChips();

    // Find and construct all chips
    converter.createChips("", desc);

    for(const SubcircuitDesc& d : desc->get_sub_circuits())
        converter.createChips(d.prefix, d.desc());

    // Create list of connections
    converter.findConnections("", desc);

    for(const SubcircuitDesc& d : desc->get_sub_circuits())
        converter.findConnections(d.prefix, d.desc());

    if(enable_debugger) {
        debug_connections = std::move(converter.debug_connections); // before createTraces
        converter.createTraces(desc);
        if(extra_desc)
            converter.createTraces(extra_desc);
        debug_chips = std::move(converter.debug_chips);
    }

    // Make all connections
    converter.makeAllConnections();

    if(enable_debugger) {
        debug_nets = std::move(converter.debug_nets);
    }

    // Check for unconnected inputs, connect to GND
    for(int i = 2; i < chips.size(); i++)
        for(int j = 0; j < chips[i]->input_links.size(); j++)
            if(chips[i]->input_links[j].chip == NULL)
            {
                std::string name = converter.getInputInfo(chips[i], j);

                if(chips[i]->type != CUSTOM_CHIP)
                    log_print("WARNING: Unconnected input pin: {}, connecting to GND", name.c_str());
                
                chips[1]->output_links.push_back(ChipLink(chips[i], 1 << j));
                chips[i]->input_links[j] = ChipLink(chips[1], 0);
            }


    // Grab video descriptor
    if(desc->video != nullptr) video.desc = desc->video;
    else video.desc = &VideoDesc::DEFAULT;

    // Set up VCC & GND for analog
    chips[0]->analog_output = 5.0;
    chips[1]->analog_output = 0.0;

    // Grab audio descriptor
    if(desc->audio != nullptr) audio.desc = desc->audio;
    else audio.desc = nullptr;

    audio.audio_init(this);

    // Run VCC
    chips[0]->output = 1;
    for(LinkIterator it = chips[0]->output_links.begin(); it != chips[0]->output_links.end(); ++it)
		it->chip->inputs |= it->mask;

	for(int i = 2; i < chips.size(); i++)
		chips[i]->initialize();
}

void CircuitBuilder::createChip(const ChipDesc* chip_desc, std::string name, void* custom, int queue_size, int subcycle_size)
{
    std::map<uint8_t, ChipDescPair> output_pin_map;
    int chip = chips.size();

    for(const ChipDesc* d = chip_desc; !d->endOfDesc(); d++)
    {
        chips.push_back(new Chip(queue_size, subcycle_size, circuit, d, custom));
#ifdef _DEBUG
        chips.back()->name = name;
#endif

        ChipDescPair cd(chips.back(), d);
        chip_map.insert(std::pair<std::string, ChipDescPair>(name, cd));

        if(d->output_pin) output_pin_map[d->output_pin] = cd;

        #ifdef DEBUG
        log_print("chip name:{} p:{}", name, chips.back());
        #endif
    }

    // Create list of internal connections
    for(const ChipDesc* d = chip_desc; !d->endOfDesc(); d++, chip++)
        for(int i = 0; d->input_pins[i]; i++)
            if(output_pin_map.count(d->input_pins[i]))
            {
                connection_list_out.push_back(*output_pin_map.find(d->input_pins[i]));
                connection_list_in.push_back(Connection(d->input_pins[i], ChipDescPair(chips[chip], d)));
            }

    for(const ChipDesc* d = chip_desc; ;  d++) {
        if(d->endOfDesc()) {
            if(d->debug)
                debug_chips.push_back({ .name = name, .debug = d->debug });
            break;
        }
    }
}

void CircuitBuilder::createSpecialChips()
{
    // Construct special chips
    chips.push_back(new Chip(1, 64, circuit, chip__VCC));
    chip_map.insert( std::pair<std::string, ChipDescPair>("_VCC", ChipDescPair(chips.back(), chip__VCC)) );

    chips.push_back(new Chip(1, 64, circuit, chip__GND));
    chip_map.insert( std::pair<std::string, ChipDescPair>("_GND", ChipDescPair(chips.back(), chip__GND)) );

    chips.push_back(new Chip(1, 64, circuit, chip__DEOPTIMIZER));
    chip_map.insert( std::pair<std::string, ChipDescPair>("_DEOPTIMIZER", ChipDescPair(chips.back(), chip__DEOPTIMIZER)) );

    // Create Video & Audio chips
    createChip(chip_VIDEO, "VIDEO", &circuit->video, 8, 64);
    createChip(chip_AUDIO, "AUDIO", &circuit->audio, 8, 64);
}

void CircuitBuilder::createTraces(const CircuitDesc* desc) {
    for(const auto& trace : desc->get_traces()) {
        auto debug_trace = std::make_unique<DebugTrace>(trace.name, trace.type);
        if(trace.elem_count == 1) {
			debug_trace->events.resize(1);
			auto chip_name = std::format("_TRACE_{}", trace_count);
			if(trace.elems[0].pin == 0) {
                if(auto it = std::find_if(debug_nets.begin(), debug_nets.end(), [&](const auto& n) { return n.name == trace.elems[0].chip; }); it != debug_nets.end()) {
					debug_trace->events[0].chip = it->chip;
					debug_trace->events[0].pin = it->pin;
				} else {
					log_print("WARNING: unknown net {}", trace.elems[0].chip);
				}
            } else {
                debug_trace->events[0].chip = trace.elems[0].chip;
                debug_trace->events[0].pin = trace.elems[0].pin;
            }
			auto custom_data = std::make_unique<DebugTraceCustomData>(&debug_trace->events[0].events, nullptr, 0);
			createChip(chip__TRACE, chip_name, custom_data.get(), 1, 64);
            if(!findConnection(debug_trace->events[0].chip, debug_trace->events[0].pin, chip_name, 1))
                log_print("WARNING: can't find connection");
			circuit->debug_traces_custom_data.push_back(std::move(custom_data));
			trace_count++;
        } else {
            debug_trace->events.resize(1 + trace.elem_count);
            for(int i = 0; i < trace.elem_count; i++) {
                auto chip_name = std::format("_TRACE_{}", trace_count);
				if(trace.elems[i].pin == 0) {
					if(auto it = std::find_if(debug_nets.begin(), debug_nets.end(), [&](const auto& n) { return n.name == trace.elems[i].chip; }); it != debug_nets.end()) {
						debug_trace->events[1 + i].chip = it->chip;
						debug_trace->events[1 + i].pin = it->pin;
					} else {
						log_print("WARNING: unknown net {}", trace.elems[i].chip);
					}
				} else {
					debug_trace->events[1 + i].chip = trace.elems[i].chip;
					debug_trace->events[1 + i].pin = trace.elems[i].pin;
				}
                auto custom_data = std::make_unique<DebugTraceCustomData>(&debug_trace->events[1 + i].events, &debug_trace->events[0].events, trace.elem_count - 1 - i);
                createChip(chip__TRACE, chip_name, custom_data.get(), 1, 64);
                if(!findConnection(debug_trace->events[1 + i].chip, debug_trace->events[1 + i].pin, chip_name, 1))
					log_print("WARNING: can't find connection");
                circuit->debug_traces_custom_data.push_back(std::move(custom_data));
                trace_count++;
            }
        }
        circuit->debug_traces.push_back(std::move(debug_trace));
    }
}

void CircuitBuilder::createChips(std::string prefix, const CircuitDesc* desc)
{
    // Create map of simulator optimization hints
    std::map<std::string, OptimizationHintDesc> hint_list;
    for(const OptimizationHintDesc& hint : desc->get_hints())
    {
        log_print("Hinting {}", hint.chip);
        hint_list[hint.chip] = hint;
    }

    // Find and construct all chips
    //std::map<const ChipDesc*, Chip*> desc_map; // Doesn't work with custom chips, TODO: fix
    for(const ChipInstance& instance : desc->get_chips())
    {
        //std::map<const ChipDesc*, Chip*> desc_map;
        
        int queue_size = EVENT_QUEUE_SIZE;
        int subcycle_size = SUBCYCLE_SIZE;
        
        if(hint_list.find(instance.name) != hint_list.end())
        {
            queue_size = hint_list[instance.name].queue_size;
            subcycle_size = hint_list[instance.name].subcycle_size;
        }

        createChip(instance.chip, prefix + instance.name, (void*)instance.custom_data, queue_size, subcycle_size);
    }
}

void CircuitBuilder::createNets(const CircuitDesc* desc) {
    for(const NetDesc& n : desc->get_nets())
        debug_nets.push_back({ .name = n.name, .chip = n.chip, .pin = n.pin });
}

void CircuitBuilder::findConnections(std::string prefix, const CircuitDesc* desc)
{
    // Create list of connections
    for(ConnectionDesc c : desc->get_connections())
    {
        if(c.pin1 == 0) {
			if(auto it = std::find_if(debug_nets.begin(), debug_nets.end(), [&](const auto& n) { return n.name == c.name1; }); it != debug_nets.end()) {
                c.name1 = it->chip.c_str();
                c.pin1 = it->pin;
            } else {
				log_print("WARNING: unknown net {}", c.name1);
            }
        }
		if(c.pin2 == 0) {
			if(auto it = std::find_if(debug_nets.begin(), debug_nets.end(), [&](const auto& n) { return n.name == c.name2; }); it != debug_nets.end()) {
				c.name2 = it->chip.c_str();
				c.pin2 = it->pin;
			} else {
				log_print("WARNING: unknown net {}", c.name2);
			}
		}

        // Try appending prefix to both signals first
        if(findConnection(prefix + c.name1, c.pin1, prefix + c.name2, c.pin2)) continue;
        
        if(prefix.size() != 0)
        {
            // Try appending prefix to 1 signal only 
            if(findConnection(prefix + c.name1, c.pin1, c.name2, c.pin2)) continue;
            if(findConnection(c.name1, c.pin1, prefix + c.name2, c.pin2)) continue;

            // Try without prefix, but only if 1 of the signals already has prefix appended
            if((prefix.compare(0, prefix.size(), c.name1) == 0 ||
                prefix.compare(0, prefix.size(), c.name2) == 0) &&
                findConnection(c.name1, c.pin1, c.name2, c.pin2)) continue;
        }
        
        // No connection found
        log_print("WARNING: Invalid connection: {}({}.{} -> {}.{})", prefix, c.name1, c.pin1, c.name2, c.pin2);
    }
}

bool CircuitBuilder::findConnection(const std::string& name1, uint8_t pin1, const std::string& name2, uint8_t pin2)
{
    ChipMapIterator it1, it2;
    std::pair<ChipMapIterator, ChipMapIterator> range1, range2;

    range1 = chip_map.equal_range(name1);
    range2 = chip_map.equal_range(name2);

    // Find output pin
    bool connected = false;
    for(it1 = range1.first; it1 != range1.second; ++it1)
        if(it1->second.second->output_pin == pin1)
        {
            for(it2 = range2.first; it2 != range2.second; ++it2)
                for(int i = 0; it2->second.second->input_pins[i]; i++)
                    if(it2->second.second->input_pins[i] == pin2)
                    {
                        if(std::find(connection_list_in.begin(), connection_list_in.end(), Connection(pin2, it2->second)) != connection_list_in.end())
                        {
                            log_print("WARNING: Attempted multiple connections to input: {}.{}", name2, pin2);
                        }
                        //else
                        {
                            connected = true;
                            connection_list_out.push_back(Connection(pin1, it1->second));
                            connection_list_in.push_back(Connection(pin2, it2->second));
                            debug_connections.push_back({ .outChip = name1, .outPin = pin1, .inChip = name2, .inPin = pin2 });
                        }
                    }
            break;
        }

    for(it2 = range2.first; it2 != range2.second; ++it2)
        if(it2->second.second->output_pin == pin2)
        {
            for(it1 = range1.first; it1 != range1.second; ++it1)
                for(int i = 0; it1->second.second->input_pins[i]; i++)
                    if(it1->second.second->input_pins[i] == pin1)
                    {
                        if(std::find(connection_list_in.begin(), connection_list_in.end(), Connection(pin1, it1->second)) != connection_list_in.end())
                        {
                            log_print("WARNING: Attempted multiple connections to input: {}.{}", name1, pin1);
                        }
                        //else
                        {
                            connected = true;
                            connection_list_out.push_back(Connection(pin2, it2->second));
                            connection_list_in.push_back(Connection(pin1, it1->second));
							debug_connections.push_back({ .outChip = name2, .outPin = pin2, .inChip = name1, .inPin = pin1 });
                        }
                    }
            break;
        }

    return connected;
}



void CircuitBuilder::makeAllConnections()
{
    // Delete all chips w/ unconnected outputs
    bool removed;
    do 
    { 
        removed = false;
        for(std::vector<Chip*>::iterator it = chips.begin(); it != chips.end(); ++it)
        {
            // Skip custom chips
            if((*it)->type == CUSTOM_CHIP) continue;
            
            bool found = false;
            for(std::vector<Connection>::iterator it2 = connection_list_out.begin(); it2 != connection_list_out.end(); ++it2)
                if(*it == it2->second.first)
                {
                    found = true;
                    break;
                }
    
            if(!found)
            {
                log_print("Removing unused chip {}", getOutputInfo(*it));
                removed = true;
                
                // Remove all connections to this chip
                for(int i = 0; i < connection_list_in.size(); i++)
                    if(*it == connection_list_in[i].second.first)
                    {
                        connection_list_in.erase(connection_list_in.begin() + i);
                        connection_list_out.erase(connection_list_out.begin() + i);
                        i--;
                    }
                
                if((*it)->type == BASIC_CHIP)
                    delete[] (*it)->lut;
 
                delete *it;
                it = chips.erase(it) - 1;
            }
        }
    } while(removed);

    // Make all connections
    for(int i = 0; i < connection_list_out.size(); i++)
    {
        Chip* c_out          = connection_list_out[i].second.first;
        Chip* c_in           = connection_list_in[i].second.first;
        const ChipDesc* desc = connection_list_in[i].second.second;
        uint8_t pin          = connection_list_in[i].first;
        
        c_out->connect(c_in, desc, pin);

        if(c_out->output_links.size() > 64) 
        {
            std::string name = getOutputInfo(c_out);

            if(name != "_VCC.1" && name != "_GND.1")
                log_print("ERROR: Maximum output connection limit reached, chip:{}, cout:{}", name, c_out->output_links.size());
        }
    }
}

Circuit::~Circuit()
{
    for(std::vector<Chip*>::iterator it = chips.begin(); it != chips.end(); ++it)
    {
        if((*it)->type == BASIC_CHIP)
            delete[] (*it)->lut;

        delete *it;
    }
}

uint64_t Circuit::queue_push(Chip* chip, uint64_t delay)
{
    int i;
	QueueEntry qe(global_time + delay, chip);

    queue_size++;

    for(i = queue_size; i > 1 && queue[i >> 1].time > qe.time; i >>= 1)
        queue[i] = queue[i >> 1];

    queue[i] = qe;

	return qe.time;
}


void Circuit::queue_pop()
{
    QueueEntry qe = queue[queue_size];

	int i = 1;
    queue_size--;

    while((i << 1) < (queue_size + 1))
    {
        int child = (i << 1);

        if(child + 1 < queue_size + 1 && queue[child + 1].time < queue[child].time)
            child++;

        if(qe.time <= queue[child].time)
            break;

        queue[i] = queue[child];
        i = child;
    }

    queue[i] = qe;
}

void Circuit::run(int64_t run_time)
{
    while(run_time > 0)
	{        
        if(queue_size)
        {
            run_time -= queue[1].time - global_time;
		    global_time = queue[1].time;
        }
        else
		{
			global_time += run_time;	
			return;
		}

		if(global_time == queue[1].chip->pending_event)
		{	
			queue[1].chip->update_output();
		}
        queue_pop();
	}
}

