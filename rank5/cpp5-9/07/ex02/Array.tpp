/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 23:25:53 by davigome          #+#    #+#             */
/*   Updated: 2025/06/25 19:43:28 by davigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
template<typename T>
Array<T>::Array(): _array(NULL), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _array(new T[n]()) , _size(n)
{
	
}

template <typename T>
Array<T>::Array(const Array<T> &other) : _array(NULL), _size(other._size)
{
	_array = new T[_size];
	for (unsigned int i = 0; i < _size; ++i)
		_array[i] = other._array[i];
}

template<typename T>
Array<T> &Array<T>::operator=(const Array<T> &other)
{
	if (this != &other)
	{
		delete[] _array;
		_size = other._size;
		_array = new T[_size];
		for (unsigned int i = 0; i < _size; ++i)
			_array[i] = other._array[i];
	}
	return *this;
}

template <typename T>
Array<T>::~Array(){
	delete[] _array;
}

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Index out of bonds");
	return _array[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Index out of bounds");
	return _array[index];
}

template <typename T>
unsigned int Array<T>::size() const{
	return _size;
}