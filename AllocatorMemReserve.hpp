#ifndef __RESERVATION_ALLOCATOR_HPP_
#define __RESERVATION_ALLOCATOR_HPP_

#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

template <typename T, uint8_t NumReserve>
class AllocatorMemReserve {
public:
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;
	using difference_type = std::ptrdiff_t;

	template <typename U>
	struct rebind {
		using other = AllocatorMemReserve<U, NumReserve>;
	};

public:
	AllocatorMemReserve() = default;
	~AllocatorMemReserve() = default;

	template <typename U>
	AllocatorMemReserve(const AllocatorMemReserve<U, NumReserve> &) {
	}

	pointer allocate(std::size_t n) {
		if (n > NumReserve - _numIssued) {
			throw std::bad_alloc();
		}
		if (_start == nullptr) {
			_start = reinterpret_cast<pointer>(std::malloc(NumReserve * sizeof(T)));
			if (!_start) {
				throw std::bad_alloc();
			}
		}
		auto pos =  std::exchange(_numIssued, _numIssued + n);
		return _start + pos;
	}

	void deallocate(T *p, std::size_t n) {
		_numIssued -= n;
		if (_numIssued <= 0) {
			std::free(_start);
		}		
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
		p->~U();
	}
private:		
	pointer _start = nullptr;
	difference_type _numIssued = 0;	
};

#endif