/* 
 * File:   matrix.h
 * Author: mark
 *
 * Created on 15 December 2013, 20:20
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <math.h>
#include "vector.h"

class MATRIX {
private:

	float c[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

public:

	void assign(const MATRIX& from);
	void assign(const MATRIX * const from);
	void assign(
		const float m00, const float m01, const float m02, const float m03,
		const float m04, const float m05, const float m06, const float m07,
		const float m08, const float m09, const float m10, const float m11,
		const float m12, const float m13, const float m14, const float m15);
	void assign(const VECTOR x, const VECTOR y, const VECTOR z, const VECTOR w);
	void assign(const VECTOR x, const VECTOR y, const VECTOR z);

	MATRIX();
	MATRIX(bool ident);
	MATRIX(const MATRIX& from);
	MATRIX(const MATRIX * const from);
	MATRIX(const float m00, const float m01, const float m02, const float m03,
		const float m04, const float m05, const float m06, const float m07,
		const float m08, const float m09, const float m10, const float m11,
		const float m12, const float m13, const float m14, const float m15);
	MATRIX(const VECTOR x, const VECTOR y, const VECTOR z, const VECTOR w);
	MATRIX(const VECTOR x, const VECTOR y, const VECTOR z);

	float& operator () (int row, int col);
	VECTOR& operator () (int col);
	float operator () (int row, int col) const;
	VECTOR operator () (int col) const;
	float& operator [] (int idx);
	operator float const * () const;

	static MATRIX zero();
	static MATRIX identity();

	static MATRIX translation(const VECTOR x);
	static MATRIX translation(const float x, const float y, const float z);

	static MATRIX scale(const VECTOR x);
	static MATRIX scale(const float x);
	static MATRIX scale(const float x, const float y, const float z);

	static MATRIX rotationX(const float angle);
	static MATRIX rotationY(const float angle);
	static MATRIX rotationZ(const float angle);
	static MATRIX rotation(const VECTOR axis, const float angle);
	static MATRIX rotation(const float yaw, const float pitch, const float roll);

	MATRIX& operator +=(const MATRIX operand);
	MATRIX& operator -=(const MATRIX operand);
	MATRIX& operator *=(const MATRIX operand);
	MATRIX& operator *=(const float factor);
	MATRIX& operator /=(const float factor);

	MATRIX operator +() const;
	MATRIX operator -() const;
	MATRIX operator *(const MATRIX operand) const;
	VECTOR operator *(const VECTOR operand) const;
	MATRIX operator *(const float factor) const;
	MATRIX operator /(const float factor) const;

	MATRIX hadamard(const MATRIX& operand) const;
};

MATRIX operator *(const float factor, const MATRIX& operand);

#endif	/* MATRIX_H */
