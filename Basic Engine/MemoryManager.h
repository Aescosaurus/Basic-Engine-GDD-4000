#pragma once

#include "Singleton.h"
#include "MonoBehavior.h"
#include <algorithm>

class IMemoryManager
{
public:
	virtual void* Allocate( size_t size ) = 0;
	virtual void Free( void* ptr ) = 0;
};

template<typename T>
class MemoryManager
	:
	public MonoBehavior,
	public Singleton<MemoryManager<T>>,
	public IMemoryManager
{
protected:
	class FreeStore
	{
	public:
		FreeStore* next = nullptr;
	};
public:
	MemoryManager()
	{
		ExpandPoolSize();
	}
	~MemoryManager()
	{
		CleanUp();
	}
	void* Allocate( size_t size ) override
	{
		if( head == nullptr ) ExpandPoolSize();

		auto* curHead = head;
		head = curHead->next;
		return( curHead );
	}
	void Free( void* ptr ) override
	{
		auto* curHead = ( FreeStore* )( ptr );

		curHead->next = head;
		head = curHead;
	}
	void ExpandPoolSize()
	{
		const auto size = sizeof( FreeStore* );
		auto* curHead = ( FreeStore* )( new char[size] );
		head = curHead;

		for( int i = 0; i < poolSize; ++i )
		{
			curHead->next = ( FreeStore* )( new char[size] );
			curHead = curHead->next;
		}
	}
	void CleanUp()
	{
		auto* cur = head;
		while( cur != nullptr )
		{
			delete[] cur;
			cur = cur->next;
		}
	}
protected:
	FreeStore* head = nullptr;
	static constexpr int poolSize = 1000;
};

template<typename T>
class Managed
{
public:
	void* operator new( size_t size )
	{
		return( MemoryManager<T>::Get().Allocate( size ) );
	}
	void operator delete( void* ptr )
	{
		MemoryManager<T>::Get().Free( ptr );
	}
};