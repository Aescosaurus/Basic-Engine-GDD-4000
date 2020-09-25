#pragma once

#include "MemoryManager.h"
#include <mutex>
#include <shared_mutex>
#include <exception>

template<typename T>
class MemoryManagerTS
	:
	public Singleton<MemoryManagerTS<T>>
{
protected:
	class FreeStore
	{
	public:
		FreeStore* next = nullptr;
	};
public:
	MemoryManagerTS()
	{
		ExpandPoolSize();
	}
	~MemoryManagerTS()
	{
		CleanUp();
	}
	void* Allocate( size_t size )
	{
		if( head == nullptr ) ExpandPoolSize();

		std::lock_guard<std::mutex> guard{ mtx };
		auto* curHead = head;
		head = curHead->next;
		return( curHead );
	}
	void Free( void* ptr )
	{
		std::lock_guard<std::mutex> guard{ mtx };
		auto* curHead = ( FreeStore* )( ptr );

		curHead->next = head;
		head = curHead;
	}
	void ExpandPoolSize()
	{
		std::lock_guard<std::mutex> guard{ mtx };
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
		std::lock_guard<std::mutex> guard{ mtx };
		auto* cur = head;
		while( cur != nullptr )
		{
			delete[] cur;
			cur = cur->next;
		}
	}
private:
	FreeStore* head = nullptr;
	static constexpr int poolSize = 1000;
private:
	std::mutex mtx;
	// std::shared_lock<std::shared_mutex> lock;
};

template<typename T>
class ManagedTS
{
public:
	void* operator new( size_t size )
	{
		// todo spiffy template for get call
		return( MemoryManagerTS<T>::Get().Allocate( size ) );
	}
	void operator delete( void* ptr )
	{
		MemoryManagerTS<T>::Get().Free( ptr );
	}
};

template<typename T>
class ManagedFunTS
{
public:
	void* operator new( size_t size )
	{
		return( MemoryManagerTS<T>::Get().Allocate( size ) );
	}
	void operator delete( void* ptr )
	{
		MemoryManagerTS<T>::Get().Free( ptr );
	}
};