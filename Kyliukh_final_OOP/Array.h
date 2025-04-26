#pragma once
#include <stdexcept>

template <typename Elem>
class Array
{
private: 
	Elem* const _data;
	size_t _size;

public:
	Array(size_t size) : _data(new Elem[size]), _size(size) {}

	~Array()
	{
		if (_data == nullptr) return;
		delete[] _data;
	}

	Elem& operator[](const size_t index)
	{
		if (index >= _size) throw std::out_of_range("Index out of range");
		return _data[index];
	}

	const Elem& operator[](const size_t index) const
	{
		if (index >= _size) throw std::out_of_range("Index out of range");
		return _data[index];
	}

	const size_t size() const
	{
		return _size;
	}

private:
	Array(const Array&) = delete;
	Array& operator=(const Array&) = delete;
	Array(Array&&) = delete;
	Array& operator=(Array&&) = delete;
};

