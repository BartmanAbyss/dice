#ifdef NALL_STRING_INTERNAL_HPP

#include <filesystem>

namespace nall {

	std::filesystem::path activepath() {
		std::filesystem::path result;
#if defined(PLATFORM_WINDOWS)
		wchar_t path[PATH_MAX] = L"";
		auto unused = _wgetcwd(path, PATH_MAX);
		result = path;
#else
		char path[PATH_MAX] = "";
		auto unused = getcwd(path, PATH_MAX);
		result = path;
#endif
		if(result.empty()) result = ".";
		return result;
	}

	std::filesystem::path realpath(const std::string& name) {
		std::filesystem::path result;
#if defined(PLATFORM_WINDOWS)
		wchar_t path[PATH_MAX] = L"";
		if(_wfullpath(path, utf16_t(name.c_str()), PATH_MAX)) result = path;
		result = path;
#else
		char path[PATH_MAX] = "";
		if(::realpath(name, path)) result = path;
#endif
		if(result.empty()) result = activepath() / name;
		return result;
	}

	// /home/username/
	// c:/users/username/
	std::filesystem::path userpath() {
		std::filesystem::path result;
#if defined(PLATFORM_WINDOWS)
		wchar_t path[PATH_MAX] = L"";
		SHGetFolderPathW(nullptr, CSIDL_PROFILE | CSIDL_FLAG_CREATE, nullptr, 0, path);
		result = path;
#else
		struct passwd* userinfo = getpwuid(getuid());
		result = userinfo->pw_dir;
#endif
		if(result.empty()) result = ".";
		return result;
	}

	// /home/username/.config/
	// c:/users/username/appdata/roaming/
	std::filesystem::path configpath() {
		std::filesystem::path result;
#if defined(PLATFORM_WINDOWS)
		wchar_t path[PATH_MAX] = L"";
		SHGetFolderPathW(nullptr, CSIDL_APPDATA | CSIDL_FLAG_CREATE, nullptr, 0, path);
		result = std::filesystem::path(path);
#elif defined(PLATFORM_OSX)
		result = userpath() / "Library/Application Support/";
#else
		result = userpath() / ".config/";
#endif
		return result;
	}

	std::filesystem::path sharedpath() {
		std::filesystem::path result;
#if defined(PLATFORM_WINDOWS)
		wchar_t path[PATH_MAX] = L"";
		SHGetFolderPathW(nullptr, CSIDL_COMMON_APPDATA | CSIDL_FLAG_CREATE, nullptr, 0, path);
		result = path;
#elif defined(PLATFORM_OSX)
		result = "/Library/Application Support/";
#else
		result = "/usr/share/";
#endif
		if(result.empty()) result = ".";
		return result;
	}

	std::filesystem::path temppath() {
#if defined(PLATFORM_WINDOWS)
		wchar_t path[PATH_MAX] = L"";
		GetTempPathW(PATH_MAX, path);
		return path;
#else
		return "/tmp/";
#endif
	}

}

#endif
