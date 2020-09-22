#pragma once

#include "Vec2.h"

template<typename T>
class Vec3_
	:
	public Vec3_<T>
{
public:
	Vec3_( T x,T y,T z )
		:
		x( x ),
		y( y ),
		z( z )
	{}

	Vec3_( const Vec3_& v,T z )
		:
		Vec3_( v.x,v.y,z )
	{}

	template<typename U>
	Vec3_( const Vec3_<U>& convert )
		:
		Vec3_( T( convert.x ),T( convert.y ),T( convert.z ) )
	{}

	operator Vec2_() const
	{
		return( Vec2_{ x,y } );
	}

	Vec3_& operator+=( const Vec3_& rhs ) override 
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return( *this );
	}
	Vec3_ operator+( const Vec3_& rhs ) const override
	{
		auto temp = *this;
		temp += rhs;
		return( temp );
	}
	Vec3_& operator-=( const Vec3_& rhs ) override
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return( *this );
	}
	Vec3_ operator-( const Vec3_& rhs ) const override
	{
		auto temp = *this;
		temp -= rhs;
		return( temp );
	}
	Vec3_& operator*=( float rhs ) override
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return( *this );
	}
	Vec3_ operator*( T rhs ) const override
	{
		auto temp = *this;
		temp *= rhs;
		return( temp );
	}
	Vec3_& operator/=( T rhs ) override
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;

		return( *this );
	}
	Vec3_ operator/( T rhs ) const override
	{
		auto temp = *this;
		temp /= rhs;
		return( temp );
	}

	Vec3_ Dot( const Vec3_& rhs ) const override
	{
		auto temp = *this;

		temp.x *= rhs.x;
		temp.y *= rhs.y;
		temp.z *= rhs.z;

		return( temp );
	}
	Vec3_ Cross( const Vec3_& rhs ) const
	{
		return( Vec3_{ y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x } );
	}

	T GetLengthSq() const override
	{
		return( x * x + y * y + z * z );
	}
	T GetLength() const override
	{
		return( sqrt( GetLengthSq() ) );
	}

	Vec3_ Normalize() override
	{
		const auto len = GetLength();
		if( len == T( 0.0 ) )
		{
			return( *this );
		}
		return( *this / len );
	}
	Vec3_ GetNormalized() const override
	{
		auto temp = this;
		temp.Normalize();
		return( temp );
	}
public:
	T z;
};