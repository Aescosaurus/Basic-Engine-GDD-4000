#pragma once

#include <cmath>

template<typename T>
class Vec2_
{
public:
	constexpr Vec2_( T x,T y )
		:
		x( x ),
		y( y )
	{}
	
	template<typename U>
	constexpr Vec2_( const Vec2_<U>& convert )
		:
		Vec2( T( convert.x ),T( convert.y ) )
	{}

	virtual Vec2_& operator+=( const Vec2_& rhs )
	{
		x += rhs.x;
		y += rhs.y;

		return( *this );
	}
	virtual Vec2_ operator+( const Vec2_& rhs ) const
	{
		auto temp = *this;
		temp += rhs;
		return( temp );
	}
	virtual Vec2_& operator-=( const Vec2_& rhs )
	{
		x -= rhs.x;
		y -= rhs.y;

		return( *this );
	}
	virtual Vec2_ operator-( const Vec2_& rhs ) const
	{
		auto temp = *this;
		temp -= rhs;
		return( temp );
	}
	virtual Vec2_& operator*=( float rhs )
	{
		x *= rhs;
		y *= rhs;

		return( *this );
	}
	virtual Vec2_ operator*( T rhs ) const
	{
		auto temp = *this;
		temp *= rhs;
		return( temp );
	}
	virtual Vec2_& operator/=( T rhs )
	{
		x /= rhs;
		y /= rhs;

		return( *this );
	}
	virtual Vec2_ operator/( T rhs ) const
	{
		auto temp = *this;
		temp /= rhs;
		return( temp );
	}

	virtual Vec2_ Dot( const Vec2_& rhs ) const
	{
		auto temp = *this;

		temp.x *= rhs.x;
		temp.y *= rhs.y;

		return( temp );
	}

	virtual T GetLengthSq() const
	{
		return( x * x + y * y );
	}
	virtual T GetLength() const
	{
		return( sqrt( GetLengthSq() ) );
	}

	virtual Vec2_ Normalize()
	{
		const auto len = GetLength();
		if( len == T( 0.0 ) )
		{
			return( *this );
		}
		return( *this / len );
	}
	virtual Vec2_ GetNormalized() const
	{
		auto temp = this;
		temp.Normalize();
		return( temp );
	}
public:
	T x;
	T y;
};