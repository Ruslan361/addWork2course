#pragma once
#include "tvector.h"
#include "tmatrix.h"
#include <limits>
template <typename T>
struct TContainer {
public:
	T value;
	size_t row;
	size_t column;
	TContainer() {
		value = 0;
		row = 0;
		column = 0;
	}
	TContainer(const T& _value, size_t _row, size_t _column) : value(_value), row(_row), column(_column) {}
	TContainer(const TContainer& container) {
		value = container.value;
		row = container.row;
		column = container.column;
	}
	//bool operator< (const TContainer<T>& container) const {
	//	if (row < container.row) return true;
	//	if (row > container.row) return false;
	//	if (column < container.column) return true;
	//	return false;
	//}
	//bool operator> (const TContainer<T>& container) const {
	//	if (row > container.row) return true;
	//	if (row < container.row) return false;
	//	if (column > container.column) return true;
	//	return false;
	//}
	bool operator== (const TContainer<T>& container) const {
		if ((row == container.row) && (column == container.row) && (value == container.value)) return true;
		return false;
	}
};
template <typename T>
class TCoordinateList {
	Vector<TContainer<T>> data;
	size_t size;
	size_t binary_search(size_t start, size_t end, size_t row, size_t column, bool& is_contains) const;
public:
	TCoordinateList(size_t _size = 1) : data(), size(_size) {}
	TCoordinateList(const TCoordinateList& tcoordlist) : data(tcoordlist.data), size(tcoordlist.size) {}

	TCoordinateList(const TDynamicMatrix<T>& matrix) 
	{
		size = matrix.size();
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if (matrix[i][j] != 0) {
					data.push_back(TContainer<T>(matrix[i][j], i, j));
				}
			}
		}
	}
	const T& get(size_t row, size_t column) const
	{
		if ((row > size) || (column > size)) throw std::out_of_range("TCoordinateList try to get out of range value");
		if (data.getSize() == 0) return 0;
		bool is_exist = false;
		size_t pos = binary_search(0, data.getSize() - 1, row, column, is_exist);
		if (!is_exist) return (T) 0;
		return data[pos].value;
	}
	void set(const T& elem, size_t row, size_t column) 
	{
		if ((row > size) || (column > size)) throw std::out_of_range("TCoordinateList try to set out of range value");
		TContainer<T> record(elem, row, column);
		if (data.getSize() == 0) {
			data.push_back(record);
			return;
		}
		bool is_exist = false;
		size_t pos = binary_search(0, data.getSize() - 1, row, column, is_exist);
		if (is_exist)
			data[pos] = record;
		else
			data.insert(pos, record);
	}
	//сравнение
	bool operator==(const TCoordinateList& m) const noexcept;
	bool operator!=(const TCoordinateList& m) const noexcept
	{
		return !(*this == m);
	}
	// матрично-скалярные операции
	TCoordinateList operator*(const T& val) const;

	//// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v) const;
	//TCoordinateList<T> operator+(const TDynamicVector<T>& v) const;

	//// матрично-матричные операции
	//TCoordinateList operator+(const TCoordinateList& m) const;
	//TCoordinateList operator-(const TCoordinateList& m) const;
	//TCoordinateList operator*(const TCoordinateList& m) const;

	////ввод/вывод
	//friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
	//{
	//	for (size_t i = 0; i < v.sz; i++)
	//	{
	//		istr >> v.pMem[i];
	//	}
	//	return istr;
	//}
	//friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& v)
	//{
	//	for (size_t i = 0; i < v.sz; i++)
	//	{
	//		ostr << v.pMem[i] << std::endl;
	//	}
	//	return ostr;
	//}
};
template <typename T>
size_t TCoordinateList<T>::binary_search(size_t start, size_t end, size_t row, size_t column, bool& is_contains) const
{
	if (end - start < 5) {
		for (size_t i = start; i <= end; i++)
		{
			if ((data[i].row == row))
			{
				if (data[i].column == column)
				{
					is_contains = true;
					return i;
				}
				if (data[i].column > column) {
					is_contains = false;
					return i;
				}
			}
			else if (data[i].row > row)
			{
				is_contains = false;
				return i;
			}
		}
	}
	size_t middle = start / 2 + end / 2;
	if (data[middle].row == row) {
		if (data[middle].column == column)
		{
			is_contains = true;
			return middle;
		}
		if (data[middle].column > column)
			return binary_search(start, middle - 1, row, column, is_contains);
		else
			return binary_search(middle + 1, end, row, column, is_contains);
	}
	else if (data[middle].row < row)
		return binary_search(middle + 1, end, row, column, is_contains);
	else
		return binary_search(start, middle - 1, row, column, is_contains);
}

template<typename T>
bool TCoordinateList<T>::operator==(const TCoordinateList<T>& m) const noexcept
{
	if (size != m.size) return false;
	size_t sz = m.data.getSize();
	for (size_t i = 0; i < sz; i++)
	{
		if (m.data[i] != data[i])
			return false;
	}
	return true;
}

template<typename T>
inline TCoordinateList<T> TCoordinateList<T>::operator*(const T& val) const
{
	TCoordinateList<T> result(val.size);
	size_t sz = data.getSize();
	for (size_t i = 0; i < sz; i++)
	{
		result[i].value = data[i].value * val;
	}
	return result;
}

template<typename T>
inline TDynamicVector<T> TCoordinateList<T>::operator*(const TDynamicVector<T>& v) const
{
	if (size != v.size()) throw std::invalid_argument("sizes of TCoordinateList and TDynamicVector are not equal");
	size_t sz = data.getSize();
	TDynamicVector<T> result(size);
	T sum = {};
	//size_t last_row = 0;
	size_t j;
	for (size_t i = 0, j = 0; i < sz; i++)
	{
		if (data[i].row != j) {
			result[j] = sum;
			j++;
			sum = {};
		}
		sum += v[data[i].column] * data[i].value;
	}
	return result;
}
