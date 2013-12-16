#include "vector.h"
#include "matrix.h"
#include <math.h>

void MATRIX::assign(const MATRIX& from)
{
	for (int i = 0; i < 16; i++)
		this->c[i] = from[i];
}

void MATRIX::assign(const MATRIX * const from)
{
	for (int i = 0; i < 16; i++)
		this->c[i] = from->c[i];
}

void MATRIX::assign(
	const float m00, const float m01, const float m02, const float m03,
	const float m04, const float m05, const float m06, const float m07,
	const float m08, const float m09, const float m10, const float m11,
	const float m12, const float m13, const float m14, const float m15)
{
	this->c[0] = m00;
	this->c[1] = m01;
	this->c[2] = m02;
	this->c[3] = m03;
	this->c[4] = m04;
	this->c[5] = m05;
	this->c[6] = m06;
	this->c[7] = m07;
	this->c[8] = m08;
	this->c[9] = m09;
	this->c[10] = m10;
	this->c[11] = m11;
	this->c[12] = m12;
	this->c[13] = m13;
	this->c[14] = m14;
	this->c[15] = m15;
}

void MATRIX::assign(const VECTOR x, const VECTOR y, const VECTOR z, const VECTOR w)
{
	assign(x[0], x[1], x[2], 0, y[0], y[1], y[2], 0, z[0], z[1], z[2], 0, w[0], w[1], w[2], 1);
}

void MATRIX::assign(const VECTOR x, const VECTOR y, const VECTOR z)
{
	assign(x[0], x[1], x[2], 0, y[0], y[1], y[2], 0, z[0], z[1], z[2], 0, 0, 0, 0, 1);
}

MATRIX::MATRIX()
{
	//this->zero();
}

MATRIX::MATRIX(bool ident)
{
	if (ident)
		this->assign(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	else
		this->assign(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

MATRIX::MATRIX(const MATRIX& from)
{
	this->assign(from);
}

MATRIX::MATRIX(const MATRIX * const from)
{
	this->assign(from);
}

MATRIX::MATRIX(const float m00, const float m01, const float m02, const float m03,
	const float m04, const float m05, const float m06, const float m07,
	const float m08, const float m09, const float m10, const float m11,
	const float m12, const float m13, const float m14, const float m15)
{
	this->assign(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
}

MATRIX::MATRIX(const VECTOR x, const VECTOR y, const VECTOR z, const VECTOR w)
{
	this->assign(x, y, z, w);
}

MATRIX::MATRIX(const VECTOR x, const VECTOR y, const VECTOR z)
{
	this->assign(x, y, z);
}

float& MATRIX::operator () (int row, int col)
{
	return this->c[col * 4 + row];
}

VECTOR& MATRIX::operator () (int col)
{
	return(VECTOR&) this->c[col * 4];
}

float MATRIX::operator () (int row, int col) const
{
	return this->c[col * 4 + row];
}

VECTOR MATRIX::operator () (int col) const
{
	return *(VECTOR*) & this->c[col * 4];
}

float& MATRIX::operator [] (int idx)
{
	return this->c[idx];
}

MATRIX::operator float const * () const
{
	return this->c;
}

MATRIX MATRIX::zero()
{
	return MATRIX(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

MATRIX MATRIX::identity()
{
	return MATRIX(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

MATRIX MATRIX::translation(const VECTOR x)
{
	return MATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x[0], x[1], x[2], 1);
}

MATRIX MATRIX::translation(const float x, const float y, const float z)
{
	return MATRIX(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1);
}

MATRIX MATRIX::scale(const VECTOR x)
{
	return MATRIX(
		x[0], 0, 0, 0,
		0, x[1], 0, 0,
		0, 0, x[2], 0,
		0, 0, 0, 1);
}

MATRIX MATRIX::scale(const float x)
{
	return MATRIX(
		x, 0, 0, 0,
		0, x, 0, 0,
		0, 0, x, 0,
		0, 0, 0, 1);
}

MATRIX MATRIX::scale(const float x, const float y, const float z)
{
	return MATRIX(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

MATRIX MATRIX::rotationX(const float angle)
{
	float cs, sn;
	sincosf(angle, &sn, &cs);
	return MATRIX(
		1, 0, 0, 0,
		0, cs, sn, 0,
		0, -sn, cs, 0,
		0, 0, 0, 1);
}

MATRIX MATRIX::rotationY(const float angle)
{
	float cs, sn;
	sincosf(angle, &sn, &cs);
	return MATRIX(
		cs, 0, -sn, 0,
		0, 1, 0, 0,
		sn, 0, cs, 0,
		0, 0, 0, 1);
}

MATRIX MATRIX::rotationZ(const float angle)
{
	float cs, sn;
	sincosf(angle, &sn, &cs);
	return MATRIX(
		cs, sn, 0, 0,
		-sn, cs, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}

MATRIX MATRIX::rotation(const VECTOR axis, const float angle)
{
	float c, s;
	sincosf(angle, &s, &c);
	float C = 1 - c;
	float x = axis[0], y = axis[1], z = axis[2];
	return MATRIX(
		x * x * C + c, y * x * C + z*s, z * x * C - y*s, 0,
		x * y * C - z*s, y * y * C + c, z * y * C + x*s, 0,
		x * z * C + y*s, y * z * C - x*s, z * z * C + c, 0,
		0, 0, 0, 1);
}

MATRIX MATRIX::rotation(const float yaw, const float pitch, const float roll)
{
	return MATRIX::rotationZ(roll) * MATRIX::rotationY(pitch) * MATRIX::rotationX(yaw);
}

MATRIX& MATRIX::operator +=(const MATRIX operand)
{
	for (int i = 0; i < 16; i++)
		(*this)[i] += operand[i];
	return *this;
}

MATRIX& MATRIX::operator -=(const MATRIX operand)
{
	for (int i = 0; i < 16; i++)
		(*this)[i] -= operand[i];
	return *this;
}

MATRIX& MATRIX::operator *=(const MATRIX operand)
{
	this->assign(*this * operand);
	return *this;
}

MATRIX& MATRIX::operator *=(const float factor)
{
	for (int i = 0; i < 16; i++)
		(*this)[i] *= factor;
}

MATRIX& MATRIX::operator /=(const float factor)
{
	for (int i = 0; i < 16; i++)
		(*this)[i] /= factor;
	return *this;
}

MATRIX MATRIX::operator +() const
{
	MATRIX result(this);
	return result;
}

MATRIX MATRIX::operator -() const
{
	MATRIX result;
	for (int i = 0; i < 16; i++)
		result[i] = -(*this)[i];
	return result;
}

MATRIX MATRIX::operator *(const MATRIX operand) const
{
	MATRIX result;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			float sum = 0;
			for (int k = 0; k < 4; k++)
				sum += (*this)(i, k) * operand(k, j);
			result(i, j) = sum;
		}
	return result;
}

VECTOR MATRIX::operator *(const VECTOR operand) const
{
	VECTOR result;
	for (int i = 0; i < 4; i++) {
		float sum = 0;
		for (int k = 0; k < 4; k++)
			sum += (*this)(i, k) * operand[k];
		result[i] = sum;
	}
	return result;
}

MATRIX MATRIX::operator *(const float factor) const
{
	MATRIX result(this);
	result *= factor;
	return result;
}

MATRIX MATRIX::operator /(const float factor) const
{
	MATRIX result(this);
	result /= factor;
	return result;
}

MATRIX MATRIX::hadamard(const MATRIX& operand) const
{
	MATRIX result(this);
	for (int i = 0; i < 16; i++)
		result[i] *= operand[i];
	return result;
}

MATRIX operator *(const float factor, const MATRIX& operand)
{
	return operand * factor;
}
