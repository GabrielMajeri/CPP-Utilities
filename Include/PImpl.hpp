#pragma once

/// This template class represents the pointer-to-implementation (PImpl) idiom.
/// This can be used to hide private members and separate platform specific implementations.
///
/// Remember to include PImpl.inl in the source file.
template <typename T>
class PImpl
{
public:
	/// Constructs an empty implementation.
	PImpl(decltype(nullptr)) noexcept;

	/// Constructs a new implementation from some arguments.
	/// T must be constructible from Ts.
	template <typename... Ts>
	PImpl(Ts&&... values);

	/// Destroys the implementation, if any.
	~PImpl();

	/// Delete the copy ctor and copy assignment operator. 
	PImpl(const PImpl&) noexcept = delete;
	PImpl& operator=(const PImpl&) noexcept = delete;
		
	/// Implementations can be moved. Moving sets this implementation to null.
	PImpl(PImpl&& other) noexcept;
	PImpl& operator=(PImpl&& rhs) noexcept;

	/// Creates a new implementation. If this already owns an implementation, it is deleted first.
	template <typename... Ts>
	void create(Ts&&... values);

	/// Accessors.
	auto* operator->() noexcept;
	const auto* operator->() const noexcept;

	auto& operator*() noexcept;
	const auto& operator*() const noexcept;

private:
	T* ptr{ nullptr };
};

/// Disallow PImpl to pointers or references.

template <typename T>
class PImpl<T*>;

template <typename T>
class PImpl<T&>;
