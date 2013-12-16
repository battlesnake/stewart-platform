/* 
 * File:   vector.h
 * Author: mark
 *
 * Created on 14 December 2013, 22:19
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include <math.h>

class VECTOR {
private:
	float c[4] = { 0, 0, 0, 0 };
public:

	float& operator [] (const int index);
	float& operator () (const int index);

	static VECTOR zero();
	static VECTOR unitX();
	static VECTOR unitY();
	static VECTOR unitZ();

	void assign(const float x, const float y, const float z);
	void assign(const VECTOR& from);
	void assign(const VECTOR * const from);

	VECTOR(const VECTOR& from);
	VECTOR(const VECTOR * const from);
	VECTOR();
	VECTOR(const float x, const float y, const float z);

	VECTOR& operator +=(const VECTOR& operand);
	VECTOR& operator -=(const VECTOR& operand);
	VECTOR& operator *=(const float factor);
	VECTOR& operator /=(const float factor);

	float dot(const VECTOR& operand) const;
	float dotSelf() const;

	float length() const;

	float normalise();
	float normalise(const float length);

	VECTOR asUnit() const;
	VECTOR asUnit(const float length) const;

	operator const float*() const;
	VECTOR operator +(const VECTOR& operand) const;
	VECTOR operator -(const VECTOR& operand) const;
	float operator |(const VECTOR& operand) const;
	VECTOR operator *(const VECTOR& operand) const;
	VECTOR operator *(float factor) const;
	VECTOR operator /(float factor) const;
	VECTOR operator +() const;
	VECTOR operator -() const;
	VECTOR operator =(const VECTOR& source);

	float* quat(const float w);
	VECTOR hadamard(const VECTOR& operand);
};

VECTOR operator *(const float factor, const VECTOR& operand);

#endif	/* VECTOR_H */

