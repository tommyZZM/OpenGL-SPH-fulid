#pragma once

#include <stdlib.h>
#include <cmath>
#include "tommyglF2/Plug/tommyVector3.h"

template <class T>
class Vector3
{
public:
	Vector3()
	{
		set(T(), T(), T());
	}

	Vector3(T new_x, T new_y, T new_z)
	{
		set(new_x, new_y, new_z);
	}

	explicit Vector3(T value)
	{
		set(value, value, value);
	}

	void set(T new_x, T new_y, T new_z)
	{
		x() = new_x;
		y() = new_y;
		z() = new_z;
	}

	T& x(){return _c[0];}
	T& y(){return _c[1];}
	T& z(){return _c[2];}

	T x() const{return _c[0];}
	T y() const{return _c[1];}
	T z() const{return _c[2];}

	void operator=(T value)
	{
		set(value, value, value);
	}

	void operator+=(const Vector3& other)
	{
		set(x() + ((T)other.x()), y() + ((T)other.y()), z() + ((T)other.z()));
	}

	void operator-=(const Vector3& other)
	{
		set(x() - ((T)other.x()), y() - ((T)other.y()), z() - ((T)other.z()));
	}

	template <class U>
	void operator*=(U factor)
	{
		T f = (T)factor;
		set(x() * f, y() * f, z() * f);
	}

	template <class U>
	void operator/=(U factor)
	{
		T f = (T)factor;
		set(x() / f, y() / f, z() / f);
	}

	T lengthSquared() const
	{
		return x()*x() + y()*y() + z()*z();
	}

	T length() const
	{
		return std::sqrt( lengthSquared() );
	}

	void normalize()
	{
		operator/=(length());
	}

	void invert()
	{
		x() = -x();
		y() = -y();
		z() = -z();
	}

	operator const T*() const
	{
		return _c;
	}

	template <class U>
	Vector3<U> convert() const
	{
		return Vector3<U>(static_cast<U>(x()), static_cast<U>(y()), static_cast<U>(z()));
	}

	inline T min_component( const Vector3& v )
	{
		if( v.x() < v.y() )
			return ( v.x() < v.z() ) ? v.x() : v.z();
		else
			return ( v.y() < v.z() ) ? v.y() : v.z();
	}

	inline T max_component( const Vector3& v )
	{
		if( v.x() > v.y() )
			return ( v.x() > v.z() ) ? v.x() : v.z();
		else
			return ( v.y() > v.z() ) ? v.y() : v.z();
	}

	inline void cross_product( const Vector3& v )
	{
		T a = y() * v.z() - z() * v.y();
		T b = z() * v.x() - x() * v.z();
		T c = x() * v.y() - y() * v.x();
		x() = a;
		y() = b;
		z() = c;
	}

	inline static Vector3 cross_product( const Vector3& u, const Vector3& v )
	{
		T a = u.y() * v.z() - u.z() * v.y();
		T b = u.z() * v.x() - u.x() * v.z();
		T c = u.x() * v.y() - u.y() * v.x();
		return Vector3<T>( a, b, c );
	}

	inline T dot_product( const Vector3& v )
	{
		return x() * v.x() + y() * v.y() + z() * v.z();
	}

	inline static T dot_product( const Vector3& u, const Vector3& v )
	{
		return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
	}

private:
	T _c[3];

public:
	static const double _PI;
	static const double _HALF_PI;
	static const double _QUATER_PI;
	static const double _RAD_TO_DEG;
	static const double _DEG_TO_RAD;
};

template <class T>
const double Vector3<T>::_PI = 3.1415926535897932384626433832795;

template <class T>
const double Vector3<T>::_HALF_PI = Vector3<T>::_PI / 2.0;

template <class T>
const double Vector3<T>::_QUATER_PI = Vector3<T>::_PI / 4.0;

template <class T>
const double Vector3<T>::_RAD_TO_DEG = 180.0 / Vector3<T>::_PI;

template <class T>
const double Vector3<T>::_DEG_TO_RAD = Vector3<T>::_PI / 180.0;

template <class T>
inline const Vector3<T> operator+(const Vector3<T>& one, const Vector3<T>& two)
{
	return Vector3<T>(one.x() + two.x(), one.y() + two.y(), one.z() + two.z());
}
template <class T>
inline const Vector3<T> operator-(const Vector3<T>& one, const Vector3<T>& two)
{
	return Vector3<T>(one.x() - two.x(), one.y() - two.y(), one.z() - two.z());
}
template <class T>
inline const Vector3<T> operator-(const Vector3<T>& one)
{
	return Vector3<T>(-one.x(), -one.y(), -one.z());
}
template <class T, class U>
inline const Vector3<T> operator*(const Vector3<T>& one, U factor)
{
	T f = (T)factor;
	return Vector3<T>(one.x() * f, one.y() * f, one.z() * f);
}
template <class T, class U>
inline const Vector3<T> operator*(U factor, const Vector3<T>& one)
{
	T f = (T)factor;
	return Vector3<T>(one.x() * f, one.y() * f, one.z() * f);
}
template <class T, class U>
inline const Vector3<T> operator/(const Vector3<T>& one, U factor)
{
	T f = (T)factor;
	return Vector3<T>(one.x() / f, one.y() / f, one.z() / f);
}

template <class T>
inline T operator*(const Vector3<T>& one, const Vector3<T>& two){ //dotproduct
	return one.x()*two.x() + one.y()*two.y() + one.z()*two.z();
}
template <class T>
inline T boundedDot(const Vector3<T>& one, const Vector3<T>& two)
{
	T dot = one * two;
	if (dot < 0)
		return 0;
	if (dot > 1)
		return 1;
	return dot;
}
template <class T>
inline Vector3<T> operator%(const Vector3<T>& one, const Vector3<T> two){ //crossproduct
	return Vector3<T>(one.y()*two.z() - one.z()*two.y(), one.z()*two.x() - one.x()*two.z(), 
		one.x()*two.y() - one.y()*two.x());
}

template <class T>
inline Vector3<T> normalize(const Vector3<T>& vec){return vec / vec.length();}

template <class T>
inline bool operator==(const Vector3<T>& one, const Vector3<T>& two)
{
	return one.x() == two.x() and one.y() == two.y() and one.z() == two.z();
}
template <class T>
inline bool operator!=(const Vector3<T>& one, const Vector3<T>& two)
{
	return !(one == two);
}

typedef Vector3<double> Vector3d;
typedef Vector3<double> Vector3f;
typedef Vector3<int> Vector3i;
typedef Vector3<size_t> Vector3u;


template <class T>
inline T random()
{
	return ( ( (T)rand() ) / RAND_MAX );
}
#define rndf random<double>


