//#include <phoenix.hpp>
#include <nall/platform.hpp>
#include "manymouse/manymouse.h"

using namespace nall;
//using namespace phoenix;

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_opengl3.h"
//#include "imgui/imgui_impl_sdlgpu3.h"

#include <SDL3/SDL.h>
//#include <SDL3/SDL_opengl.h>

#include "GL/glew.h"

#include "circuit.h"
#include "circuit_desc.h"

#include "game_list.h"

#include "chips/input.h"
//#include "ui/audio_window.h"
//#include "ui/video_window.h"
//#include "ui/input_window.h"
//#include "ui/dipswitch_window.h"
//#include "ui/game_window.h"
//#include "ui/logo.h"

#ifdef WIN32
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "SDL3.lib")
#endif

#define DEBUG
#undef DEBUG

static const char VERSION_STRING[] = "DICE 0.9";

struct MainWindow {
	Settings settings;
	Input* input{};
	Video* video{};
	Circuit* circuit{};
	RealTimeClock real_time;

	struct UserInterfaceState {
		bool pause, throttle, fullscreen, quit;

		static UserInterfaceState getCurrent(MainWindow& main_window) {
			return { main_window.input->getKeyPressed(main_window.settings.input.ui.pause),
					 main_window.input->getKeyPressed(main_window.settings.input.ui.throttle),
					 main_window.input->getKeyPressed(main_window.settings.input.ui.fullscreen),
					 main_window.input->getKeyPressed(main_window.settings.input.ui.quit) };
		}
	};
	UserInterfaceState prev_ui_state{ false, false, false, false };

	MainWindow(SDL_Window* window) {
		// Load config file
		auto config_path = configpath() / "dice";
		std::filesystem::create_directories(config_path);
		settings.filename = (config_path / "settings.cfg").string();
		settings.load();
		/*
				onClose = &Application::quit;

				// Game menu
				game_menu.setText("Game");

				new_game_item.setText("New Game...");
				new_game_item.onActivate = [&] { game_window.create(geometry().position()); };
				game_window.cancel_button.onActivate = [&] { game_window.setModal(false); game_window.setVisible(false); };

				game_window.start_button.onActivate = [&]
				{
					GameDesc& g = game_list[game_window.game_view.selection()];
					if(circuit) delete circuit;
					circuit = new Circuit(settings, *input, *video, g.desc, g.command_line);
					game_window.setModal(false);
					game_window.setVisible(false);
					onSize();
				};

				game_menu.append(new_game_item);

				end_game_item.setText("End Game");
				end_game_item.onActivate = [&]
				{
					if(circuit)
					{
						delete circuit;
						circuit = nullptr;
					}
					onSize();
				};
				game_menu.append(end_game_item);

				game_menu.append(game_sep[0]);
				pause_item.setText("Pause");
				pause_item.onToggle = [&] { settings.pause = pause_item.checked(); };
				throttle_item.setText("Throttle");
				throttle_item.setChecked(true);
				throttle_item.onToggle = [&]
				{
					settings.throttle = throttle_item.checked();
					if(settings.throttle && circuit) // Adjust rtc
					{
						uint64_t emu_time = circuit->global_time * 1000000.0 * Circuit::timescale;
						circuit->rtc += int64_t(circuit->rtc.get_usecs()) - emu_time;
					}
				};
				game_menu.append(pause_item, throttle_item);

				game_menu.append(game_sep[1]);
				exit_item.setText("Exit");
				exit_item.onActivate = onClose;
				game_menu.append(exit_item);

				append(game_menu);

				// Settings menu
				settings_menu.setText("Settings");

				audio_item.setText("Audio Settings...");
				settings_menu.append(audio_item);
				audio_item.onActivate = [&] { audio_window.create(geometry().position()); };
				audio_window.onClose = audio_window.exit_button.onActivate = [&]
				{
					mute_item.setChecked(settings.audio.mute);
					audio_window.setModal(false);
					audio_window.setVisible(false);
					if(circuit) circuit->audio.toggle_mute();
				};
				mute_item.setText("Mute Audio");
				mute_item.setChecked(settings.audio.mute);
				mute_item.onToggle = [&]
				{
					settings.audio.mute = mute_item.checked();
					if(circuit) circuit->audio.toggle_mute();
				};

				settings_menu.append(mute_item);
				settings_menu.append(settings_sep[0]);

				video_item.setText("Video Settings...");
				video_item.onActivate = [&] { video_window.create(geometry().position()); };
				status_visible_item.setText("Status Bar Visible");
				status_visible_item.setChecked(settings.video.status_visible);
				status_visible_item.onToggle = [&]
				{
					settings.video.status_visible = status_visible_item.checked();
					setStatusVisible(settings.video.status_visible);
				};
				fullscreen_item.setText("Fullscreen");
				fullscreen_item.onToggle = [&] { toggleFullscreen(fullscreen_item.checked()); };
				settings_menu.append(video_item, status_visible_item, fullscreen_item);

				settings_menu.append(settings_sep[1]);
				input_item.setText("Configure Inputs...");
				input_item.onActivate = [&] { input_window.create(geometry().position()); };
				input_window.onClose = [&]
				{
					if(input_window.active_selector) input_window.active_selector->assign(KeyAssignment::None);
					input_window.setModal(false);
					input_window.setVisible(false);
				};
				input_window.exit_button.onActivate = [&]
				{
					if(input_window.active_selector)
						input_window.active_selector->assign(KeyAssignment::None);
					else
					{
						input_window.setModal(false);
						input_window.setVisible(false);
					}
				};

				settings_menu.append(input_item);

				dipswitch_item.setText("Configure DIP Switches...");
				dipswitch_item.onActivate = [&]
				{
					int selection = 0;
					if(circuit) for(int i = 0; i < dipswitch_window.game_configs.size(); i++)
					{
						if(circuit->game_config == dipswitch_window.game_configs[i])
						{
							selection = i;
							break;
						}
					}
					dipswitch_window.create(geometry().position(), selection);
				};
				dipswitch_window.onClose = dipswitch_window.exit_button.onActivate = [&]
				{
					dipswitch_window.game_configs[dipswitch_window.current_config].save();
					dipswitch_window.setModal(false);
					dipswitch_window.setVisible(false);
				};
				settings_menu.append(settings_sep[2]);
				settings_menu.append(dipswitch_item);

				append(settings_menu);

				setStatusVisible(settings.video.status_visible);

				setBackgroundColor({0, 0, 0});
				layout.setMargin(0);
				viewport = new Viewport();
				layout.append(*viewport, {~0, ~0});
				append(layout);
		*/
		// Initialize SDL, input, etc.
		settings.num_mice = ManyMouse_Init();

		input = new Input();
		video = new Video();
		/*
				onSize = [&] {

					if((signed)geometry().height < 0 || (signed)geometry().width < 0)
						return;

					video->video_init(geometry().width, geometry().height, settings.video);

					if(circuit == nullptr)
					{
						drawLogo();
					}

					viewport->setFocused();
				};

				setTitle(VERSION_STRING);
				setFrameGeometry({(Desktop::workspace().width - 640) / 2, (Desktop::workspace().height - 480) / 2, 640, 480});
				setMenuVisible();
				setVisible();

				onSize();
		*/
	}

	~MainWindow() {
		settings.save();
		if(circuit) delete circuit;
		delete video;
		delete input;
	}

	void toggleFullscreen(bool fullscreen) {
		settings.fullscreen = fullscreen;
		/*
				fullscreen_item.setChecked(fullscreen);
				setStatusVisible(!fullscreen && settings.video.status_visible);
				setMenuVisible(!fullscreen);
				setFullScreen(fullscreen);
		*/
		video->show_cursor(!fullscreen);
		//       onSize();
	}

	void drawLogo() {
		/*        glViewport(0, 0, geometry().width, geometry().height);

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0.0, geometry().width, geometry().height, 0.0, -1.0, 1.0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glClearColor(0,0,0,0);
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

				glEnable(GL_TEXTURE_2D);

				glBindTexture(GL_TEXTURE_2D, 0);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

				unsigned logo_width = logo_data[0x12];
				unsigned logo_height = logo_data[0x16];
				int logo_x = (geometry().width - logo_width*4) / 2;
				int logo_y = (geometry().height - logo_height*4) / 2;

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, logo_width, logo_height, 0, GL_RGB, GL_UNSIGNED_BYTE, &logo_data[0x36]);

				glBindTexture (GL_TEXTURE_2D, 0);
				glBegin(GL_QUADS);
					glColor3f(1.0, 1.0, 1.0);
					glTexCoord2f(0.0, 1.0);
					glVertex3f(logo_x + 0.0, logo_y + 0.0, 0.0);
					glTexCoord2f(1.0, 1.0);
					glVertex3f(logo_x + logo_width*4, logo_y + 0.0, 0.0);
					glTexCoord2f(1.0, 0.0);
					glVertex3f(logo_x + logo_width*4, logo_y + logo_height*4, 0.0);
					glTexCoord2f(0.0, 0.0);
					glVertex3f(logo_x + 0.0, logo_y + logo_height*4, 0.0);
				glEnd();

				video->swap_buffers();*/
	}

	void run() {
		input->poll_input();

		if(circuit && !settings.pause) {
			video->activate();
			circuit->run(2.5e-3 / Circuit::timescale); // Run 2.5 ms
			video->deactivate();
			//circuit->run(100.0e-6 / Circuit::timescale); // Run 100 us

			uint64_t emu_time = circuit->global_time * 1000000.0 * Circuit::timescale;

			// Make sure real time is at least mostly caught up
			if(settings.throttle)
				while(circuit->rtc.get_usecs() + 50000 < emu_time);

			// If real time is too far ahead, adjust timer
			if(circuit->rtc.get_usecs() > emu_time + 100000)
				circuit->rtc += (circuit->rtc.get_usecs() - emu_time - 100000);

			if(real_time.get_usecs() > 1'000'000) {
				//                setStatusText({"FPS: ", circuit->video.frame_count});
				circuit->video.frame_count = 0;
				real_time += 1'000'000;
			}

			//if(emu_time > 1.56e6) onClose();
		} else {
			SDL_Delay(10);
			//          if(settings.pause && statusText() != "Paused") setStatusText("Paused");
			//          else if(!settings.pause && statusText() != VERSION_STRING) setStatusText(VERSION_STRING);
			//          if(circuit == nullptr && (focused() || video_window.focused())) drawLogo();
		}
		/*
				if(input_window.active_selector)
				{
					auto key_state = Keyboard::state();

					for(unsigned i = 0; i < key_state.size(); i++)
						if(key_state[i]) input_window.active_selector->assign({KeyAssignment::KEYBOARD, i});

					//Check Joystick Events
					SDL_Event event;
					while(SDL_PollEvent(&event))
					{
						switch(event.type)
						{
						case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
							input_window.active_selector->assign({KeyAssignment::JOYSTICK_BUTTON, event.jbutton.button, (unsigned)event.jbutton.which});
							break;
						case SDL_EVENT_JOYSTICK_AXIS_MOTION:
							if(!input_window.active_selector->allow_joystick) break;
							if(abs(event.jaxis.value) > 8192)
							{
								unsigned axis = (event.jaxis.axis << 1) | (event.jaxis.value > 0);
								input_window.active_selector->assign({KeyAssignment::JOYSTICK_AXIS, axis, (unsigned)event.jaxis.which});
							}
						default:
							break;
						}
					}
				}
				else // Handle user interface inputs

				{
					UserInterfaceState ui_state = UserInterfaceState::getCurrent(*this);

					// Don't update ui inputs while main window is in the background
					if(focused())
					{
						if(ui_state.quit && !prev_ui_state.quit)
						{
							onClose();
						}
						if(ui_state.pause && !prev_ui_state.pause)
						{
							settings.pause = !settings.pause;
							pause_item.setChecked(settings.pause);
						}
						if(ui_state.fullscreen && !prev_ui_state.fullscreen)
						{
							fullscreen_item.setChecked(!settings.fullscreen);
							fullscreen_item.onToggle();
						}
						if(ui_state.throttle && !prev_ui_state.throttle)
						{
							throttle_item.setChecked(!settings.throttle);
							throttle_item.onToggle();
						}
					}

					prev_ui_state = ui_state;
				}
		*/
	}
};

static std::filesystem::path app_path;

const std::filesystem::path& application_path() {
	return app_path;
}

#undef main

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw)
#define argc __argc
#define argv __argv
#else
int main(int argc, char** argv)
#endif
{
	// Setup SDL
	// [If using SDL_MAIN_USE_CALLBACKS: all code below until the main loop starts would likely be your SDL_AppInit() function]
	if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_AUDIO)) {
		printf("Error: SDL_Init(): %s\n", SDL_GetError());
		return 1;
	}
/*
	// Create GPU Device
	SDL_GPUDevice* gpu_device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_METALLIB, false, nullptr);
	if(gpu_device == nullptr) {
		printf("Error: SDL_CreateGPUDevice(): %s\n", SDL_GetError());
		return 1;
	}

	// Create SDL window graphics context
	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
	SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL3+SDL_GPU example", (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
	if(window == nullptr) {
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return 1;
	}
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window);

	// Claim window for GPU Device
	if(!SDL_ClaimWindowForGPUDevice(gpu_device, window)) {
		printf("Error: SDL_ClaimWindowForGPUDevice(): %s\n", SDL_GetError());
		return 1;
	}
	SDL_SetGPUSwapchainParameters(gpu_device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);
*/

#if defined(__APPLE__)
	// GL 3.2 Core + GLSL 150
	const char* glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	// Create window with graphics context
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
	SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
	SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
	if(window == nullptr) {
		printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
		return 1;
	}
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	if(gl_context == nullptr) {
		printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
		return 1;
	}

	SDL_GL_MakeCurrent(window, gl_context);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window);

	glewInit();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

// Sort the game list
std::sort(game_list, game_list + game_list_size);

//auto main_window = new MainWindow(gpu_device);
auto main_window = new MainWindow(window);

// Init main_window path/window for ROM loader
app_path = realpath(argv[0]).parent_path();

// Seed random number generator
srand(time(NULL));

if(argc > 1) {
	bool start_fullscreen = true;

	// Parse options
	for(int i = 2; i < argc; i++)
		if(strcmp(argv[i], "-window") == 0) start_fullscreen = false;

	for(const GameDesc& g : game_list) {
		if(strcmp(argv[1], g.command_line) == 0) {
			main_window->toggleFullscreen(start_fullscreen);
			main_window->circuit = new Circuit(main_window->settings, *main_window->input, *main_window->video, g.desc, g.command_line);
		}
	}
}

// after circuit
int width, height;
SDL_GetWindowSizeInPixels(window, &width, &height);
main_window->video->video_init(width, height, main_window->settings.video); // TEST

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

	// Setup Platform/Renderer backends
/*	ImGui_ImplSDL3_InitForSDLGPU(window);
	ImGui_ImplSDLGPU3_InitInfo init_info = {};
	init_info.Device = gpu_device;
	init_info.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(gpu_device, window);
	init_info.MSAASamples = SDL_GPU_SAMPLECOUNT_1;                      // Only used in multi-viewports mode.
	init_info.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;  // Only used in multi-viewports mode.
	init_info.PresentMode = SDL_GPU_PRESENTMODE_VSYNC;
	ImGui_ImplSDLGPU3_Init(&init_info);
*/
// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);


	// Load Fonts
	// - If fonts are not explicitly loaded, Dear ImGui will call AddFontDefault() to select an embedded font: either AddFontDefaultVector() or AddFontDefaultBitmap().
	//   This selection is based on (style.FontSizeBase * style.FontScaleMain * style.FontScaleDpi) reaching a small threshold.
	// - You can load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - If a file cannot be loaded, AddFont functions will return a nullptr. Please handle those errors in your code (e.g. use an assertion, display an error and quit).
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use FreeType for higher quality font rendering.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//style.FontSizeBase = 20.0f;
	//io.Fonts->AddFontDefaultVector();
	//io.Fonts->AddFontDefaultBitmap();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
	//IM_ASSERT(font != nullptr);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.00f);

	// Main loop
	bool done = false;
	while(!done) {
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		// [If using SDL_MAIN_USE_CALLBACKS: call ImGui_ImplSDL3_ProcessEvent() from your SDL_AppEvent() function]
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			ImGui_ImplSDL3_ProcessEvent(&event);
			if(event.type == SDL_EVENT_QUIT)
				done = true;
			if(event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
				done = true;
			if(event.type == SDL_EVENT_WINDOW_RESIZED && event.window.windowID == SDL_GetWindowID(window))
				main_window->video->video_init(event.window.data1, event.window.data2, main_window->settings.video);
		}

		main_window->run();

		// [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppIterate() function]
		if(SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
			SDL_Delay(10);
			continue;
		}

		// Start the Dear ImGui frame
//		ImGui_ImplSDLGPU3_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();

		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if(show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if(ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if(show_another_window) {
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if(ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		ImVec2 size(io.DisplaySize);
		ImVec2 origin(0, 0);
/*
		// Keep aspect ratio
		bool horizontal = true;
		if(main_window->video->desc->orientation == ROTATE_90 || main_window->video->desc->orientation == ROTATE_270)
			horizontal = false;

		if(main_window->settings.video.keep_aspect) {
			if(horizontal) {
				if(size.x > 4 * size.y / 3) {
					origin.x = (size.x - 4 * size.y / 3) / 2;
					size.x = 4 * size.y / 3;
				} else if(size.y > 3 * size.x / 4) {
					origin.y = (size.y - 3 * size.x / 4) / 2;
					size.y = 3 * size.x / 4;
				}
			} else { // vertical
				if(size.x > 3 * size.y / 4) {
					origin.x = (size.x - 3 * size.y / 4) / 2;
					size.x = 3 * size.y / 4;
				} else if(size.y > 4 * size.x / 3) {
					origin.y = (size.y - 4 * size.x / 3) / 2;
					size.y = 4 * size.x / 3;
				}
			}
		}

		const auto& data = main_window->video->get_data();
		auto draw_list = ImGui::GetBackgroundDrawList();
		if(data.scanline_time && data.v_size) {
			//draw_list->AddRectFilled(origin, ImVec2(origin.x + size.x, origin.y + size.y), IM_COL32_BLACK);
			switch(main_window->video->desc->orientation) {
			case ROTATE_0:
				for(const auto& pixel : data.pixels)
					draw_list->AddRectFilled(ImVec2(origin.x + pixel.start_time * size.x / data.scanline_time, origin.y + pixel.v_pos * size.y / data.v_size), ImVec2(origin.x + pixel.end_time * size.x / data.scanline_time + 1, origin.y + (pixel.v_pos + 1) * size.y / data.v_size), pixel.color);
				break;
			case ROTATE_90:
				for(const auto& pixel : data.pixels)
					draw_list->AddRectFilled(ImVec2(origin.x + size.x - pixel.v_pos * size.x / data.v_size, origin.y + pixel.start_time * size.y / data.scanline_time), ImVec2(origin.x + size.x - (pixel.v_pos + 1) * size.x / data.v_size, origin.y + pixel.end_time * size.y / data.scanline_time + 1), pixel.color);
				break;
			case ROTATE_180:
				break;
			case ROTATE_270:
				break;
			}
		}
*/
		// Rendering
		ImGui::Render();
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		if(main_window->video->get_output()) {
			// Emulator
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, 1, 1, 0, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glDisable(GL_DEPTH_TEST);  // No depth for fullscreen quad
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, main_window->video->get_output());  // FBO color attachment

			glColor3f(1.0f, 1.0f, 1.0f);  // White tint

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(1, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(1, 1);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 1);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		}

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);

/*
		ImDrawData draw_data = *ImGui::GetDrawData();
		const bool is_minimized = (draw_data.DisplaySize.x <= 0.0f || draw_data.DisplaySize.y <= 0.0f);

		SDL_GPUCommandBuffer* command_buffer = SDL_AcquireGPUCommandBuffer(gpu_device); // Acquire a GPU command buffer

		SDL_GPUTexture* swapchain_texture;
		SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer, window, &swapchain_texture, nullptr, nullptr); // Acquire a swapchain texture

		if(swapchain_texture != nullptr && !is_minimized) {
			// This is mandatory: call ImGui_ImplSDLGPU3_PrepareDrawData() to upload the vertex/index buffer!
			ImGui_ImplSDLGPU3_PrepareDrawData(&draw_data, command_buffer);

			// Setup and start a render pass
			SDL_GPUColorTargetInfo target_info = {};
			target_info.texture = swapchain_texture;
			target_info.clear_color = SDL_FColor{ clear_color.x, clear_color.y, clear_color.z, clear_color.w };
			target_info.load_op = SDL_GPU_LOADOP_CLEAR;
			target_info.store_op = SDL_GPU_STOREOP_STORE;
			target_info.mip_level = 0;
			target_info.layer_or_depth_plane = 0;
			target_info.cycle = false;
			SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(command_buffer, &target_info, 1, nullptr);

			// Render ImGui
			ImGui_ImplSDLGPU3_RenderDrawData(&draw_data, command_buffer, render_pass);

			SDL_EndGPURenderPass(render_pass);
		}

		// Submit the command buffer
		SDL_SubmitGPUCommandBuffer(command_buffer);
*/
	}

	delete main_window;

	// Cleanup
	// [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppQuit() function]
//	SDL_WaitForGPUIdle(gpu_device);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
//	ImGui_ImplSDLGPU3_Shutdown();
	ImGui::DestroyContext();
/*
	SDL_ReleaseWindowFromGPUDevice(gpu_device, window);
	SDL_DestroyGPUDevice(gpu_device);
*/
	SDL_GL_DestroyContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;

#ifdef DEBUG
	printf("chip size:%d\n", sizeof(Chip));
	if(main_window.circuit) printf("chips: %d\n", main_window.circuit->chips.size());
	uint64_t total_event_count = 0;
	uint64_t total_loop_count[8] = { 0 };
	for(int i = 0; main_window.circuit && i < main_window.circuit->chips.size(); i++) {
		total_event_count += main_window.circuit->chips[i]->total_event_count;
		printf("%p LUT=%llx, event_count=%lld, act_count=%lld, state=%d act_out:%d cyc_time:%lld act_time:%lld, max_cyc:%lld max_sub:%lld\n",
			main_window.circuit->chips[i],
			(uint32_t)main_window.circuit->chips[i]->lut_data,
			main_window.circuit->chips[i]->total_event_count,
			main_window.circuit->chips[i]->activation_count,
			main_window.circuit->chips[i]->state,
			main_window.circuit->chips[i]->active_outputs,
			main_window.circuit->chips[i]->cycle_time,
			main_window.circuit->chips[i]->activation_time,
			main_window.circuit->chips[i]->max_cycle_length,
			main_window.circuit->chips[i]->max_subcycle_length);
		main_window.circuit->chips[i]->print_input_events();
		main_window.circuit->chips[i]->print_output_events();
		for(int j = 0; j < 8; j++) {
			printf("loop_count%d:%lld, ", j, main_window.circuit->chips[i]->loop_count[j]);
			total_loop_count[j] += main_window.circuit->chips[i]->loop_count[j];
		}
		printf("\n");
	}
	printf("total event count:%lld\n", total_event_count);
	for(int j = 0; j < 8; j++) {
		printf("total_loop_count%d:%lld, ", j, total_loop_count[j]);
	}
	printf("\n");
#endif

	return 0;
}

