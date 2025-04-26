#pragma once
#include <iostream>
#include "Array.h"

template <typename Elem>
class Sequence
{
private:
	size_t _default_capacity = 5;
	size_t _size;
	Array<Elem> *  _allocator;
public:
	Sequence(const size_t capacity) : _size(0), _allocator(new Array<Elem>(capacity)) {}

	~Sequence() { delete _allocator; }

	size_t capacity() const { return _allocator->size(); }

	size_t size() const { return _size; }

	bool empty() const { return _size == 0; }

	bool full() const { return _size == capacity(); }

	bool has(const Elem& elem)
	{
		for (size_t i = 0; i < _size; ++i)
			if ((*_allocator)[i] == elem)
				return true;
		return false;
	}

	Sequence& clear()
	{
		_size = 0;
		return *this;
	}

	const Elem& operator[](const size_t index) const
	{
		if (index >= _size) throw std::out_of_range("Index out of range");
		return (*_allocator)[index];
	}

	Elem& operator[](const size_t index)
	{
		if (index >= _size) throw std::out_of_range("Index out of range");
		return (*_allocator)[index];
	}

	Sequence& add(const Elem& elem)
	{
		return insertAt(_size, elem);
	}

	Sequence& insert(const size_t index, const Elem& elem)
	{
		if (index > _size) throw std::out_of_range("Index out of range");
		return insertAt(index, elem);
	}

	Sequence& remove(const size_t index)
	{
		if (index >= _size) throw std::out_of_range("Index out of range");

		for (size_t i = index + 1; i < _size; ++i)
			(*_allocator)[i - 1] = (*_allocator)[i];
		--_size;

		return *this;
	}

	Sequence& cut()
	{
		if (empty()) throw std::out_of_range("Trying to operate an empty sequence");
		--_size;
		return *this;
	}

private:
	void enlarge(const size_t times = 1)
	{
		const size_t new_capacity = _default_capacity * times + capacity();
		Array<Elem>* new_alloc = new Array<Elem>(new_capacity);

		for (size_t i = 0; i < _size; ++i)
			(*new_alloc)[i] = (*_allocator)[i];
		delete _allocator;

		_allocator = new_alloc;
	}

	Sequence& insertAt(const size_t index, const Elem& elem)
	{
		if (full()) enlarge();

		for (size_t i = _size; i > index; --i)
			(*_allocator)[i] = (*_allocator)[i - 1];

		(*_allocator)[index] = elem;
		++_size;
		return *this;
	}

	Sequence(const Sequence&) = delete;
	Sequence& operator=(const Sequence&) = delete;
	Sequence(Sequence&&) = delete;
	Sequence& operator=(Sequence&&) = delete;
};

template <typename Elem>
std::ostream& operator<<(std::ostream& out, const Sequence<Elem>& sequence)
{
	char sep = '\0';
	out << '[';
	for (size_t i = 0; i < sequence.size(); ++i)
	{
		out << sep << sequence[i];
		sep = ',';
	}
	out << ']' << " Sequence size: " << sequence.size() << ", capacity: " << sequence.capacity();
	return out;
}