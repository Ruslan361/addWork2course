#pragma once
#include <ostream>
#include <istream>
#include <iostream>
#include <iterator>
#include <iomanip>
#define SETW 5
template <typename T1>
class Vector;
template <typename T>
std::ostream& operator<< (std::ostream& stream, const Vector<T>& _vector);
template <typename T>
std::istream& operator>> (std::istream& stream, const Vector<T>& _vector);
template <typename T>
class Vector {
private:
	T* _array;
	size_t copacity;
	size_t size;
public:
	Vector() {
		_array = nullptr;
		size = 0;
		copacity = 0;
	}
	Vector(size_t size) {
		_array = new T[size];
		this->size = size;
		this->copacity = size;
	}
	Vector(size_t size, const T& elem) {
		_array = new T[size];
		this->size = size;
		this->copacity = size;
		std::fill(_array, _array + size, elem);
	}
	Vector(const Vector<T>& _vector);
	inline size_t getSize() const {
		return size;
	}
	Vector(Vector<T>&& _vector) noexcept {
		_array = _vector._array;
		size = _vector.size;
		copacity = _vector.copacity;
		_vector._array = nullptr;
	}
	Vector<T> operator=(Vector<T>&& _vector) noexcept {
		std::swap(_array, _vector._array);
		std::swap(size, _vector.size);
		std::swap(copacity, _vector.copacity);
		return *this;
	}
	T& at(size_t index) {
		if (index >= size)
			throw std::out_of_range(__FILE__, __FUNCTION__, __LINE__);
		return _array[index];
	}
	~Vector() {
		if (_array != nullptr)
			delete[] _array;
		//size = 0;
	}
	void push_back(const T& element);
	T& getBack() {
		return _array[size - 1];
	}
	T& getFront() {
		return _array[0];
	}
	T* begin() { return std::begin(_array); }
	void clear() { size = 0; }
	void erase(size_t index) {
		for (size_t i = index + 1; i < size; i++)
		{
			_array[i - 1] = _array[i];
		}
		size--;
	}
	void insert(size_t index, const T& elem) {
		Vector tmp(size + 1);
		for (size_t i = 0; i < index; i++)
		{
			tmp._array[i] = _array[i];
		}
		tmp._array[index] = elem;
		for (size_t i = index+1; i < tmp.size; i++)
		{
			tmp._array[i] = _array[i-1];
		}
		*this = tmp;
	}
	bool operator==(const Vector<T>& _vector) const;
	void resize(size_t size);
	bool operator!=(const Vector<T>& _vector) const;
	Vector<T>& operator-= (const Vector<T>& _vector);
	Vector<T>& operator=(const Vector<T>& _vector);
	bool operator<= (const Vector<T>& _vector) const;
	bool operator>= (const Vector<T>& _vector) const;
	bool operator< (const Vector<T>& _vector) const;
	bool operator> (const Vector<T>& _vector) const;
	Vector<T> operator+ (const Vector<T>& _vector) const;
	Vector<T> operator* (const T& scalar) const;
	Vector<T> operator- (const Vector<T>& _vecctor) const;
	Vector<T> operator/ (const T& scalar) const;
	Vector<T>& operator*= (const T& scalar);
	Vector<T>& operator+= (const Vector<T>& _vector);
	Vector<T>& operator/= (const T& scalar);
	Vector<T>& operator++();
	Vector<T> operator++(int);
	T operator* (const Vector<T>) const;
	T& operator[] (size_t index) { return _array[index]; }
	const T& operator[] (size_t index) const { return _array[index]; }
	friend std::ostream& operator<< <T>(std::ostream& stream, const Vector<T>& _vector);
	friend const Vector<T> operator/ (const T& scalar, const Vector<T>& vector);
	friend std::istream& operator>> <T> (std::istream& stream, const Vector<T>& _vector);
};

template <typename T>
std::ostream& operator<< (std::ostream& stream, const Vector<T>& _vector) {
	for (size_t i = 0; i < _vector.size; i++)
	{
		stream << std::setw(SETW) << _vector._array[i];
	}
	return stream;
}

template <typename T>
std::istream& operator>> (std::istream& stream, const Vector<T>& _vector) {
	for (size_t i = 0; i < _vector.size; i++)
	{
		stream >> _vector._array[i];
	}
	return stream;
}

template <typename T>
T Vector<T>::operator* (const Vector<T> _vector) const {
	size_t min = size < _vector.size ? size : _vector.size;
	T temp = static_cast<T>(0);
	for (size_t i = 0; i < min; i++)
	{
		temp += _array[i] * _vector._array[i];
	}
	return temp;
}

template <typename T>
Vector<T>::Vector<T>(const Vector<T>& _vector) {
	this->copacity = _vector.copacity;
	this->size = _vector.size;
	this->_array = new T[copacity];
	std::copy( _vector._array, _vector._array + _vector.size, _array);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& _vector) {
	if (_array != nullptr) {
		delete[] _array;
	}
	size = _vector.size;
	copacity = _vector.size;
	_array = new T[size];
	for (size_t i = 0; i < size; i++)
	{
		_array[i] = _vector._array[i];
	}
	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+ (const Vector<T>& _vector) const {
	size_t max = size > _vector.size ? size : _vector.size;
	size_t min = size < _vector.size ? size : _vector.size;
	Vector<T> temp(max);
	size_t i;
	for (i = 0; i < min; i++)
	{
		temp._array[i] = _array[i] + _vector._array[i];
	}
	for (; i < size; i++)
	{
		temp._array[i] = _array[i];
	}
	for (; i < _vector.size; i++)
	{
		temp._array[i] = _vector._array[i];
	}
	return temp;
}

template <typename T>
Vector<T>& Vector<T>::operator+= (const Vector<T>& _vector) {
	*this = *this + _vector;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-= (const Vector<T>& _vector) {
	*this = *this - _vector;
	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator- (const Vector<T>& _vector) const {
	size_t max = size > _vector.size ? size : _vector.size;
	size_t min = size < _vector.size ? size : _vector.size;
	Vector<T> temp(max);
	for (size_t i = 0; i < min; i++)
	{
		temp._array[i] = _array[i] - _vector._array[i];
	}
	for (size_t i = 0; i < size; i++)
	{
		temp._array[i] = _array[i];
	}
	for (size_t i = 0; i < _vector.size; i++)
	{
		temp._array[i] = _vector._array[i];
	}
	return temp;
}

template <typename T>
Vector<T> Vector<T>::operator* (const T& scalar) const {
	Vector<T> temp(size);
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = _array[i] * scalar;
	}
	return temp;
}
template <typename T>
Vector<T> operator* (const T& scalar, const Vector<T> right) {
	return right * scalar;
}

template <typename T>
Vector<T> Vector<T>::operator/ (const T& scalar) const {
	Vector<T> temp(size);
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = _array[i] / scalar;
	}
	return temp;
}

template <typename T>
Vector<T> operator/ (const T& scalar, const Vector<T>& _vector) {
	Vector<T> temp(_vector.size);
	for (size_t i = 0; i < _vector.size; i++)
	{
		temp[i] = scalar / _vector._array[i];
	}
	return temp;
}

template <typename T>
Vector<T>& Vector<T>::operator*= (const T& scalar) {
	*this = *this * scalar;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator/= (const T& scalar) {
	*this = *this / scalar;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator++() {
	for (size_t i = 0; i < size; i++)
	{
		++_array[i];
	}
	return *this;
}

template <typename T>
Vector<T> Vector<T>::operator++(int) {
	Vector<T> temp(*this);
	for (size_t i = 0; i < size; i++)
	{
		_array[i]++;
	}
	return temp;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& _vector) const {
	if (size != _vector.size)
		return false;
	for (size_t i = 0; i < size; i++)
	{
		if (_array[i] != _vector._array[i])
			return false;
	}
	return true;
}
template <typename T>
bool Vector<T>::operator!=(const Vector<T>& _vector) const {
	return !(*this == _vector);
}

template <typename T>
void Vector<T>::resize(size_t size) {
	if (copacity <= size) {
		Vector<T> temp(*this);
		if (_array != nullptr) {
			delete[] _array;
		}
		this->copacity = size * 2;
		_array = new T[copacity];
		size_t min = this->size < size ? this->size : size;
		std::copy(temp._array, temp._array + min, _array);
	}
	this->size = size;
}

template <typename T>
bool Vector<T>::operator<= (const Vector<T>& _vector) const {
	return !(*this > _vector);
}

template <typename T>
bool Vector<T>::operator>= (const Vector<T>& _vector) const {
	return !(*this < _vector);
}

template <typename T>
bool Vector<T>::operator< (const Vector<T>& _vector) const {
	if (size > _vector.size)
		return false;
	if (size < _vector.size)
		return true;
	for (size_t i = 0; i < size; i++)
	{
		if (_array[i] < _vector._array[i])
			return true;
		else if (_array[i] > _vector._array[i])
			return false;
	}
	return false;
}

template <typename T>
bool Vector<T>::operator> (const Vector<T>& _vector) const {
	if (size > _vector.size)
		return true;
	if (size < _vector.size)
		return false;
	for (size_t i = 0; i < size; i++)
	{
		if (_array[i] > _vector._array[i])
			return true;
		else if (_array[i] < _vector._array[i])
			return false;
	}
	return false;
}

template <typename T>
void Vector<T>::push_back(const T& element) {
	resize(size + 1);
	getBack() = element;
}