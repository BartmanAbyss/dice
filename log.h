#pragma once

#include <format>      // C++20 std::format
#include <string>
#include <vector>
#include <mutex>

extern std::vector<std::string> log_lines;  // Your global log
extern std::mutex log_mutex;

template<typename... Args>
void log_print(std::format_string<Args...> fmt, Args&&... args) {
	std::string msg = std::format(fmt, std::forward<Args>(args)...);
#ifdef _WIN32
	OutputDebugStringA((msg + "\r\n").c_str());
#endif
	std::lock_guard<std::mutex> lock(log_mutex);
	log_lines.push_back(std::move(msg));
	if(log_lines.size() > 1000) {
		log_lines.erase(log_lines.begin());
	}
}