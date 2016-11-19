#pragma once

#include "COMInterface.hpp"

#include <cassert>
#include <utility>

#ifndef _WIN64
	#error This files is meant to be included only in Windows builds.
#endif

using GUID = _GUID;

struct IUnknown
{
public:
	virtual long QueryInterface(const GUID& interfaceID, void** object) = 0;
	virtual unsigned long AddRef() = 0;
	virtual unsigned long Release() = 0;
};

template <typename I>
struct RemoveIUnknown : public I
{
private:
	virtual long QueryInterface(const GUID& interfaceID, void** object) = 0;
	virtual unsigned long AddRef() = 0;
	virtual unsigned long Release() = 0;
};


template <typename I>
COMInterface<I>::COMInterface() noexcept = default;

template <typename I>
COMInterface<I>::~COMInterface()
{
	if (ptr)
		release();
}

template <typename I>
COMInterface<I>::COMInterface(const COMInterface& other) noexcept
{
	*this = other;
}

template <typename I>
COMInterface<I>& COMInterface<I>::operator=(const COMInterface& other) noexcept
{
	if (this == &rhs)
		return *this;

	if (ptr)
		release();

	ptr = rhs.ptr;

	if (ptr)
		addRef();

	return *this;
}

template <typename I>
COMInterface<I>::COMInterface(COMInterface&& other) noexcept
{
	*this = std::move(other);
}
	
template <typename I>
COMInterface<I>& COMInterface<I>::operator=(COMInterface&& rhs) noexcept
{
	if (this == &rhs)
		return *this;

	if (ptr)
		release();

	ptr = std::exchange(rhs.ptr, nullptr);

	return *this;
}

template <typename I>
I** COMInterface<I>::getAddress() noexcept
{
	return &ptr;
}

template <typename I>
I* const* COMInterface<I>::getAddress() const noexcept
{
	return &ptr;
}

template <typename I>
template <typename U>
void COMInterface<I>::as(COMInterface<U>& other) noexcept
{
	assert(ptr);

	ptr->QueryInterface(other.getUUID(), reinterpret_cast<void**>(&other.ptr));
}


template <typename I>
template <typename U>
COMInterface<U> COMInterface<I>::as() noexcept
{
	assert(ptr);

	COMInterface<U> result;

	as(result);

	return result;
}

template <typename I>
auto* COMInterface<I>::operator->() noexcept
{
	assert(ptr);
	return reinterpret_cast<RemoveIUnknown*>(ptr);
}

template <typename I>
const auto* COMInterface<I>::operator->() const noexcept
{
	assert(ptr);
	return reinterpret_cast<RemoveIUnknown*>(ptr);
}

template <typename I>
auto& COMInterface<I>::operator*() noexcept
{
	assert(ptr);
	return *reinterpret_cast<RemoveIUnknown*>(ptr);
}

template <typename I>
const auto& COMInterface<I>::operator*() const noexcept
{
	assert(ptr);
	return *reinterpret_cast<RemoveIUnknown*>(ptr);
}

template <typename I>
void swap(COMInterface<I>& lhs, COMInterface<I>& rhs) noexcept
{
	using std::swap;

	swap(lhs.ptr, rhs.ptr);
}

template <typename I>
constexpr static auto COMInterface<I>::getUUID() noexcept
{
	return __uuidof(I);
}

template <typename I>
void COMInterface<I>::addRef() noexcept
{
	assert(ptr);

	reinterpret_cast<IUnknown*>(ptr)->AddRef();
}

template <typename I>
void COMInterface<I>::release() noexcept
{
	assert(ptr);

	reinterpret_cast<IUnknown*>(ptr)->Release();
	ptr = nullptr;
}

