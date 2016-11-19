#pragma once

#include <cassert>
#include <type_traits>
#include <utility>

#include "PImpl.hpp"

template <typename T>
PImpl<T>::PImpl(decltype(nullptr)) noexcept
{
}

template<typename T>
template<typename... Ts>
inline PImpl<T>::PImpl(Ts&&... values)
{
	create(std::forward<Ts>(values)...);
}

template<typename T>
PImpl<T>::~PImpl()
{
	static_assert(sizeof(T) > 0, "T is an incomplete type! Define it before using PImpl.");

	if (ptr)
		delete ptr;
}

template<typename T>
inline PImpl<T>::PImpl(PImpl&& other) noexcept
{
	*this = std::move(other);
}

template<typename T>
inline PImpl<T>& PImpl<T>::operator=(PImpl&& rhs) noexcept
{
	ptr = std::exchange(rhs.ptr, nullptr);

	return *this;
}

template<typename T>
template<typename... Ts>
inline void PImpl<T>::create(Ts&&... values)
{
	static_assert(std::is_constructible_v<T, Ts...>, "Cannot construct T from the given values!");

	if (ptr != nullptr)
		delete ptr;

	ptr = new T{ std::forward<Ts>(values)... };
}

/// This class is used to hide the constructors and destructors of the implementation.
/// This forces users of PImpl to only call constructors and destructors of this class.
template <typename T>
struct HideImplementation
	: public T
{
private:
	HideImplementation() = default;
	~HideImplementation() = default;
};

template<typename T>
inline auto* PImpl<T>::operator->() noexcept
{
	assert(ptr);
	return reinterpret_cast<HideImplementation<T>*>(ptr);
}

template<typename T>
inline const auto* PImpl<T>::operator->() const noexcept
{
	assert(ptr);
	return reinterpret_cast<HideImplementation<const T>*>(ptr);
}

template<typename T>
inline auto& PImpl<T>::operator*() noexcept
{
	assert(ptr);
	return *reinterpret_cast<HideImplementation<T>*>(ptr);
}

template<typename T>
inline const auto& PImpl<T>::operator*() const noexcept
{
	assert(ptr);
	return *reinterpret_cast<HideImplementation<const T>*>(ptr);
}
