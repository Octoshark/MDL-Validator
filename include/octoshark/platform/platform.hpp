/* Copyright Octoshark Studios, All rights reserved. */

#ifndef platform_hpp
#define platform_hpp

namespace octoshark
{
	namespace platform
	{
#ifdef _WIN32
		constexpr auto EXT_EXECUTABLE = ".exe";
		constexpr auto EXT_MODULE = ".dll";
#endif

#ifdef __linux__
		constexpr auto EXT_EXECUTABLE = "";
		constexpr auto EXT_MODULE = ".so";
#endif

#ifdef __APPLE__
		constexpr auto EXT_EXECUTABLE = ""; // .app?
		constexpr auto EXT_MODULE = ".dylib";
#endif
	}
}

#endif // platform_hpp