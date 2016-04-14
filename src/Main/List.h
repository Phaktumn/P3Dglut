#define  LIST_H
#include <cstdlib>
#include <iostream>
#ifdef LIST_H
#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#pragma once

#define TRUE  1
#define FALSE 0

template<class T> class Node
{
public:
	T _Item;
	Node* _Next;
};


template<class T> class List
{
	Node<T>* _Front_Ptr;
	int _size;
public:

	void push_back(T _value)
	{
		if (_Front_Ptr == nullptr) {
			_Front_Ptr = (Node<T>*)(malloc(sizeof(Node<T>)));
			_Front_Ptr->_Item = _value;
			_Front_Ptr->_Next = nullptr;
			_size++;
		}
		else {
			Node<T>* _Prev_Ptr = _Front_Ptr;
			Node<T>* _Ptr = _Front_Ptr;

			while (_Ptr != nullptr)
			{
				_Prev_Ptr = _Ptr;
				_Ptr = _Ptr->_Next;
			}
			_Ptr = (Node<T>*)malloc(sizeof(Node<T>));
			_Prev_Ptr->_Next = _Ptr;
			_Ptr->_Item = _value;
			_Ptr->_Next = nullptr;
			_size++;
		}
	}

	T operator [](int _Index) const
	{
		if (_Index >= _size){
			std::cout << ERROR << std::endl;
			exit(1);
		}
		int _curr_Index = 0;
		Node<T>* _Ptr = _Front_Ptr;
		if (_Ptr != nullptr) {
			while (_curr_Index < _Index) {
				_Ptr = _Ptr->_Next;
				//Break Loop and force return statement
				if (_Ptr == nullptr) break;
				_curr_Index++;
			}
			return _Ptr->_Item;
		}
		//Getting some error when trying to return nullPtr 
		//Eg: List<Vector3>  (note no pointer) RETURN ERROR
		return {};
	}

	void addAt(unsigned int _Index, T _data)
	{
		int _curr_Index = 1;
		Node<T>* _Ptr = _Front_Ptr;
		Node<T>* _last_Ptr = _Front_Ptr;
		if (_Index == 1) {
			_Front_Ptr->_Next = _last_Ptr;
			_Front_Ptr->_Item = _data;
		}
		else {
			Node<T>* _New_Data_;
			while (_Ptr != nullptr) {
				_curr_Index++;
				_last_Ptr = _Ptr;
				_Ptr = _Ptr->_Next;
				if (_curr_Index == _Index)
					break;
			}
			_New_Data_ = (Node<T>*)(malloc(sizeof(Node<T>)));
			_New_Data_->_Item = _data;
			_New_Data_->_Next = _Ptr;
			_last_Ptr->_Next = _New_Data_;
		}
		_size++;
	}

	void removeAt(unsigned int _Index)
	{
		unsigned short int _curr_Index = 1;
		Node<T>* _Ptr = _Front_Ptr;
		//Remove The first Node
		if (_Index == 1) {
			_Front_Ptr = _Ptr->_Next;
			free(_Ptr);
			_size--;
		}

		else {
			Node<T>* _last_Ptr = _Front_Ptr;
			while (_Ptr != nullptr) {
				_curr_Index++;
				_last_Ptr = _Ptr;
				_Ptr = _Ptr->_Next;
				if (_curr_Index == _Index) {
					_size--;
					break;
				}
			}
			_last_Ptr->_Next = _Ptr->_Next;
			free(_Ptr);
		}
	}

	void Clear()
	{
		Node<T>* _Ptr = _Front_Ptr;
		Node<T>* _aux__Ptr = _Front_Ptr;
		while (_aux__Ptr != nullptr) {
			_aux__Ptr = _Ptr->_Next;
			free(_Ptr);
			_size--;
		}
	}

	T front()
	{
		if (_Front_Ptr == nullptr) return NULL;
		return _Front_Ptr->_Item;
	}

	T back()
	{
		Node<T>* _Ptr = _Front_Ptr;
		while (_Ptr != nullptr) {
			if (_Ptr->_Next == nullptr)
				break;
			_Ptr = _Ptr->_Next;
		}
		return _Ptr->_Item;
	}

	unsigned int isEmpty() const
	{
		if (size() == 0) return TRUE;
		return FALSE;
	}

	int size() const _NOEXCEPT {
		return _size;
	}

	List()
		: _Front_Ptr{ nullptr },
		_size{ 0 }
	{ }

	~List()
	{ }
};

#endif
