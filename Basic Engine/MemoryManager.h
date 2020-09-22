#pragma once

#include "MonoBehavior.h"

class IMemoryManager
{
public:
	virtual void* Allocate( size_t size ) = 0;
	virtual void Free( void* ptr ) = 0;
};

class MemoryManager
	:
	public Singleton<MemoryManager>,
	public IMemoryManager
{
protected:
	class FreeStore
	{
	public:
		FreeStore* next;
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
	// void* operator new( size_t size )
	// {
	// 	return( Get().Allocate( size ) );
	// }
	// void* operator new[]( size_t size )
	// {
	// 	return( Get().Allocate( size ) );
	// }
	// void operator delete( void* ptr )
	// {
	// 	Get().Free( ptr );
	// }
	virtual void* Allocate( size_t size ) override
	{
		if( head == nullptr ) ExpandPoolSize();

		auto* curHead = head;
		head = curHead->next;
		return( curHead );
	}
	virtual void Free( void* ptr ) override
	{
		auto* curHead = ( FreeStore* )( ptr );

		curHead->next = head;
		head = curHead;
	}
	virtual void ExpandPoolSize()
	{}
	/*
	{
		// std::max
		size_t size = ( sizeof( Complex ) > sizeof( FreeStore* ) )
			? sizeof( Complexx ) : sizeof( FreeStore* );
		FreeStore* curHead = ( FreeStore* )( new char[size] );
		head = curHead;

		for( int i = 0; i< poolSize; ++i )
		{
			curHead->next = ( FreeStore* )( new char[size] );
			curHead = curHead->next;
		}

		curHead->next = nullptr;
	}
	*/
	virtual void CleanUp()
	{
		auto* next = head;
		for( ; next = head; )
		{
			head = head->next;
			delete[] next;
		}
	}
protected:
	FreeStore* head = nullptr;
};