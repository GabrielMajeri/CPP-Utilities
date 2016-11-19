#pragma once

/// This class represents a pointer to a COM interface. All interfaces must inherit
/// from IUnknown.
///
/// Remember to include "COMInterface.inl" in the source files for classes use this class template!
template <typename I>
class COMInterface final
{
public:
	COMInterface() noexcept;
	~COMInterface();

	COMInterface(const COMInterface& other) noexcept;
	COMInterface& operator=(const COMInterface& rhs) noexcept;

	COMInterface(COMInterface&& other) noexcept;
	COMInterface& operator=(COMInterface&& rhs) noexcept;

	I** getAddress() noexcept;
		
	I* const* getAddress() const noexcept;

	/// If interface is not supported, other is set to nullptr.
	template <typename U>
	void as(COMInterface<U>& other) noexcept;

	/// If interface is not supported, returned interface is set to nullptr.
	template <typename U>
	COMInterface<U> as() noexcept;

	constexpr static auto getUUID() noexcept;

	auto* operator->() noexcept;
	const auto* operator->() const noexcept;

	auto& operator*() noexcept;
	const auto& operator*() const noexcept;

	friend void swap(COMInterface& lhs, COMInterface& rhs) noexcept;

private:
	I* ptr{ nullptr };

	template <typename U>
	friend class COMInterface;

	void addRef() noexcept;
	void release() noexcept;
};

template <typename I>
class COMInterface<I*>;

template <typename I>
class COMInterface<I&>;
