#pragma once
#include <vector>
#include "Planets/SolarSystem.h"

template<class T> class Simple_Array
{
	//All Objects In Universe!
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
				if (_Ptr == nullptr) return nullptr;
				_curr_Index++;
			}
			return _Ptr->_Item;
		}
		return nullptr;
	}

	int size() const _NOEXCEPT {
		return _size;
	}

	Simple_Array()
		: _Front_Ptr{ nullptr },
		_size{ 0 }
	{ }

	~Simple_Array()
	{ }
	/*std::vector<T*> getArrayTemplates() 
	{ return m_Universe; }

	void addTemplate_TYPE(T* _item){
		m_Universe.push_back(_item);
	}*/
};

class UniverseSimulator
{
public:
	//All Objects In Universe!

	bool m_simulate;
	bool _getSimulateState() const
	{ return m_simulate; }

	
	Simple_Array<SolarSystem*> solarSystems;
	Simple_Array<vec::Vector3*> SolarPositions;

	void add_A_Thing_To_Universe(SolarSystem* _Solar_System, vec::Vector3* position){
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
		for (size_t i = 0; i < solarSystems.size(); i++)
		{
			glTranslatef(SolarPositions[i]->x, SolarPositions[i]->y, SolarPositions[i]->z);
			solarSystems[i]->Draw();
			solarSystems[i]->renderOrbits();
		}
	}

	UniverseSimulator(): m_simulate(false)
	{
			
	}

	~UniverseSimulator()
	{
		
	}
};

