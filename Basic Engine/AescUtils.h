#pragma once

#include <algorithm>
#include <functional>

namespace aesc
{
	template<typename Container,typename Pred>
	void remove_erase_if( Container& container,Pred pred )
	{
		const auto new_end = std::remove_if( container.begin(),container.end(),pred );
		container.erase( new_end,container.end() );
	}

	template<typename T>
	T sign( T val )
	{
		return( val / abs( val ) );
	}

	template<typename T>
	bool check_coll( const T& a,const T& b,float rad )
	{
		return( ( a - b ).GetLengthSq() < rad * rad );
	}
}