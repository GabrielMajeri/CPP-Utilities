#pragma once

#if defined _WIN32
	#define WINDOWS
#elif defined __APPLE__
	#define MACOS
#elif defined ANDROID || defined __ANDROID__
	#define ANDROID
#elif defined __linux__
	#define LINUX
#else
	#error Platform not supported.
#endif
