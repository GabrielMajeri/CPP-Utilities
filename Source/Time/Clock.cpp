#include "Time/Clock.hpp"

namespace Internal
{
	static ClockT clock;
}

Clock::Clock() noexcept
	: start{ Internal::clock.now() }
{
}

Clock::Clock(const TimePoint& start) noexcept
	: start{ start }
{
}

Duration Clock::getElapsedTime() const noexcept
{
	return Internal::clock.now() - start;
}

Duration Clock::restart() noexcept
{
	TimePoint originalStart = start;
	start = Internal::clock.now();
	return start - originalStart;
}

TimePoint Clock::now() noexcept
{
	return Internal::clock.now();
}
