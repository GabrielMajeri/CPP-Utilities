#pragma once

#include <chrono>
#include <type_traits>

namespace Internal
{
	// Try to use the high resolution clock if it's monotonic or fall back to
	// steady_clock if not.
	using ClockT = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock, std::chrono::steady_clock>;
}

/// Duration represents a difference between 2 time points.
using Duration = Internal::ClockT::duration;

/// A point in time, expressed as number of ticks from the start of the clock's epoch.
using TimePoint = Internal::ClockT::time_point;
