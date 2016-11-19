# C++ Utilities
 Useful tools and utilities. Most of these files are free standing but files that are in the same folder may rely on each other.

# Prerequisites
 All / most of these files require at least a C++14 compiler, and only use the Standard Library. They are designed to be platform agnostic.

# Contents
* **PImpl** - the pointer-to-implementation idiom, used as a compilation firewall and for stable ABIs.
* **COMInterface** - represents a Component Object Model interface pointer, similar to ATL's CComPtr or WRL's ComPtr. **This class does not include any platform headers, so it does not suffer from Windows.h bloat.**
* **NonCopyable** - similar to *boost::noncopyable*, but it uses C++11's = delete syntax.
* **Platform Detection** - it checks for some macros to determine the platform and defines some unified macros (WINDOWS, LINUX, MAC)
* **Timer / Clock** - similar to SFML's Clock class, but uses C++11's `<chrono>` library. It also determines and uses the highest resolution monotonic clock available on the target platform.
* **Hybrid Graphics support** - if you build an app with the file HybridGraphics.cpp, it will force systems with NVIDIA Optimus / AMD Power Xpress to use the dedicate graphics card.

# Licence
 The code in this repo can be considered public domain, being licensed under the [Unlicense](http://unlicense.org/).
