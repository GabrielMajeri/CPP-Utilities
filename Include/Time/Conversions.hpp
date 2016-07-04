#pragma once

#include "Types.hpp"

/// Converts a duration to seconds
constexpr float asSeconds(Duration d) noexcept
{
	return std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1, 1>>>(d).count();
}

/// Converts a duration to milliseconds
constexpr float asMilliseconds(Duration d) noexcept
{
	return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(d).count();
}

/// Converts a value in seconds to a duration
constexpr Duration fromSeconds(float sec) noexcept
{
	return std::chrono::duration_cast<Duration>(std::chrono::duration<float, std::ratio<1, 1>>{ sec });
}

/// Converts a value in milliseconds to a duration
constexpr Duration fromMilliseconds(float ms) noexcept
{
	return std::chrono::duration_cast<Duration>(std::chrono::duration<float, std::milli>{ ms });
}
