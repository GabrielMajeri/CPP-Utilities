#pragma once

#include "Types.hpp"
#include "Conversions.hpp"

class Clock final
{
public:
	/// Constructs and starts the clock
	Clock() noexcept;
	
	/// Constructs a clock as if it was started at the given time
	Clock(const TimePoint& start) noexcept;

	/// Gets how much time has passed since the clock was (re)started
	Duration getElapsedTime() const noexcept;

	/// Restarts the clock and returns how much time passed since the last (re)start
	Duration restart() noexcept;

	/// Returns the current time
	static TimePoint now() noexcept;

private:
	/// The start time of this clock
	TimePoint start;
};
