#pragma once

template<typename T>
class Vec3_
{
public:
	Vec3_()
		:
		Vec3_( T( 0.0 ),T( 0.0 ),T( 0.0 ) )
	{}
	Vec3_( T x,T y,T z )
		:
		x( x ),
		y( y ),
		z( z )
	{}

	template<typename U>
	Vec3_( const Vec3_<U>& convert )
		:
		Vec3_( T( convert.x ),T( convert.y ),T( convert.z ) )
	{}

	Vec3_& operator+=( const Vec3_& rhs )
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return( *this );
	}
	constexpr Vec3_ operator+( const Vec3_& rhs ) const
	{
		auto temp = *this;
		temp += rhs;
		return( temp );
	}
	Vec3_& operator-=( const Vec3_& rhs )
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return( *this );
	}
	constexpr Vec3_ operator-( const Vec3_& rhs ) const
	{
		auto temp = *this;
		temp -= rhs;
		return( temp );
	}
	Vec3_& operator*=( float rhs )
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;

		return( *this );
	}
	constexpr Vec3_ operator*( T rhs ) const
	{
		auto temp = *this;
		temp *= rhs;
		return( temp );
	}
	Vec3_& operator/=( T rhs )
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;

		return( *this );
	}
	constexpr Vec3_ operator/( T rhs ) const
	{
		auto temp = *this;
		temp /= rhs;
		return( temp );
	}

	Vec3_ Dot( const Vec3_& rhs ) const
	{
		auto temp = *this;

		temp.x *= rhs.x;
		temp.y *= rhs.y;
		temp.z *= rhs.z;

		return( temp );
	}
	Vec3_ Cross( const Vec3_& rhs ) const
	{
		return( Vec3_{
			this->y * rhs.z - this->z * rhs.y,
			this->z * rhs.x - this->x * rhs.z,
			this->x * rhs.y - this->y * rhs.x } );
	}

	T GetLengthSq() const
	{
		return( this->x * this->x + this->y * this->y + z * z );
	}
	T GetLength() const
	{
		return( sqrt( GetLengthSq() ) );
	}

	Vec3_ Normalize()
	{
		const auto len = GetLength();
		if( len == T( 0.0 ) )
		{
			return( *this );
		}
		return( *this / len );
	}
	Vec3_ GetNormalized() const
	{
		auto temp = this;
		temp.Normalize();
		return( temp );
	}
public:
	T x;
	T y;
	T z;
};

typedef Vec3_<float> Vec3;
typedef Vec3_<int> Vei3;