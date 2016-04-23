#pragma once
#ifndef REFERENCECOUNTER_H
#define REFERENCECOUNTER_H

class ReferenceCounter
{
public:
	virtual ~ReferenceCounter()
	{
	}

	ReferenceCounter() :
		m_refCount(1) {}

	int GetReferenceCount() const{ return m_refCount; }
	void AddReference() { m_refCount++; }
	bool RemoveReference() { m_refCount--; return m_refCount == 0; }
protected:
private:
	int m_refCount;
};

#endif