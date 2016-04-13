#ifndef __cplusplus
#error A C++ compiler is required!
#endif

#pragma once
#include "Planets/SolarSystem.h"
#include "LoadBMP.h"
#include "Planets/Universe.h"

template<class T> class List
{
	typedef struct Node{
		T _Item;
		Node* _Next;
	};

	Node* _Front_Ptr;
	int _size;
public:

	void push_back(T _value)
	{
		if(_Front_Ptr == nullptr) {
			_Front_Ptr = (Node*)(malloc(sizeof(Node)));
			_Front_Ptr->_Item = _value;
			_Front_Ptr->_Next = nullptr;
			_size++;
 		}
		else {
			Node* _Prev_Ptr = _Front_Ptr;
			Node* _Ptr = _Front_Ptr;

			while (_Ptr != nullptr)
			{
				_Prev_Ptr = _Ptr;
				_Ptr = _Ptr->_Next;
			}

			_Ptr = (Node*)malloc(sizeof(Node));
			_Prev_Ptr->_Next = _Ptr;
			_Ptr->_Item = _value;
			_Ptr->_Next = nullptr;
			_size++;
		}
	}

	T operator [](int _Index)
	{
		int _curr_Index = 0;
		Node* _Ptr = _Front_Ptr;
		if(_Ptr != nullptr) {
			while (_curr_Index < _Index){
				_Ptr = _Ptr->_Next;
				//Getting some error when trying to return nullPtr and T = int
				if (_Ptr == nullptr) return nullptr;
				_curr_Index++;
			}
			return _Ptr->_Item;
		}
		//Getting some error when trying to return nullPtr and T = int
		return nullptr;
	}

	void addAt(unsigned int _Index, T _data)
	{
		int _curr_Index = 1;
		Node* _Ptr = _Front_Ptr;
		Node* _last_Ptr = _Front_Ptr;
		if(_Index == 1){
			_Front_Ptr->_Next = _last_Ptr;
			_Front_Ptr->_Item = _data;
		}
		else {
			Node* _New_Data_;
			while (_Ptr != nullptr) {
				_curr_Index++;
				_last_Ptr = _Ptr;
				_Ptr = _Ptr->_Next;
				if (_curr_Index == _Index)
					break;
			}
			_New_Data_ = (Node*)(malloc(sizeof(Node)));
			_New_Data_->_Item = _data;
			_New_Data_->_Next = _Ptr;
			_last_Ptr->_Next = _New_Data_;	
		}
		_size++;
	}

	void removeAt(unsigned int _Index)
	{
		unsigned short int _curr_Index = 1;
		Node* _Ptr = _Front_Ptr;
		//Remove The first Node
		if (_Index == 1) {
			_Front_Ptr = _Ptr->_Next;
			free(_Ptr);
			_size--;
		}

		else {
			Node* _last_Ptr = _Front_Ptr;
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
		Node* _Ptr = _Front_Ptr;
		Node* _aux__Ptr = _Front_Ptr;
		while (_aux__Ptr != nullptr){
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
		Node* _Ptr = _Front_Ptr;
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

class UniverseSimulator
{
public:
	//All Objects In Universe!

	bool m_simulate;
	bool _getSimulateState() const
	{ return m_simulate; }

	GLuint m_Universetexture;
	GLuint m_list;
	List<SolarSystem*> solarSystems;
	List<vec::Vector3*> SolarPositions;

	void load_Universe()
	{
		m_Universetexture = _loadBMP("Textures/stars.bmp");

		m_list = glGenLists(1);
		glNewList(m_list, GL_COMPILE);	
		glDisable(GL_DEPTH);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(0);
		glScalef(10000, 10000, 10000);
		Universe::drawQuads();
		glDepthMask(1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH);
		glEndList();
	}

	void add_SolarSystem(SolarSystem* _Solar_System, vec::Vector3* position){
		SolarPositions.push_back(position);
		solarSystems.push_back(_Solar_System);
	}

	void addPlanet_to_SolarSystem(const std::string& _solarSistemName, Planet* _planetToAdd){
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			if(solarSystems[i]->getName() == _solarSistemName) {
				solarSystems[i]->addPlanet(_planetToAdd);
			}
		}
	}

	void simulate(float deltaTime)
	{
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			solarSystems[i]->Simulate(deltaTime);
		}
	}
	
	void draw()
	{
		drawUniverse();
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			glTranslatef(SolarPositions[i]->x, SolarPositions[i]->y, SolarPositions[i]->z);
			solarSystems[i]->Draw();
			solarSystems[i]->renderOrbits();
		}
	}

	UniverseSimulator(): m_simulate(false)
	{
		load_Universe();
	}

	~UniverseSimulator()
	{
		
	}

	void drawUniverse() const
	{
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_Universetexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glPushMatrix();
		glCallList(m_list);
		glPopMatrix();
	}
};

