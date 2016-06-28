#pragma once

namespace VFS
{
	/// This class prevents its inheritors from being copied.
	class NonCopyable
	{
	protected:
		NonCopyable() noexcept = default;
		~NonCopyable() = default;

		NonCopyable(NonCopyable&&) noexcept = default;
		NonCopyable& operator=(NonCopyable&&) noexcept = default;

	private:
		NonCopyable(const NonCopyable&) noexcept = delete;
		NonCopyable& operator=(const NonCopyable&) noexcept = delete;
	};
}
