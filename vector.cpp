#include "vector.h"
#include <math.h>

	float& VECTOR::operator [] (const int index)
	{
		return this->c[index];
	}

	float& VECTOR::operator () (const int index)
	{
		return this->c[index];
	}

	VECTOR VECTOR::zero()
	{
		return VECTOR(0, 0, 0);
	}

	VECTOR VECTOR::unitX()
	{
		return VECTOR(1, 0, 0);
	}

	VECTOR VECTOR::unitY()
	{
		return VECTOR(0, 1, 0);
	}

	VECTOR VECTOR::unitZ()
	{
		return VECTOR(0, 0, 1);
	}

	void VECTOR::assign(const float x, const float y, const float z)
	{
		(*this)[0] = x;
		(*this)[1] = y;
		(*this)[2] = z;
	}

	void VECTOR::assign(const VECTOR& from)
	{
		(*this)[0] = from[0];
		(*this)[1] = from[1];
		(*this)[2] = from[2];
	}

	void VECTOR::assign(const VECTOR * const from)
	{
		(*this)[0] = (*from)[0];
		(*this)[1] = (*from)[1];
		(*this)[2] = (* from)[2];
	}

	VECTOR::VECTOR(const VECTOR& from)
	{
		this->assign(from);
	}

	VECTOR::VECTOR(const VECTOR * const from)
	{
		this->assign(from);
	}

	VECTOR::VECTOR()
	{
		this->assign(0, 0, 0);
	}

	VECTOR::VECTOR(const float x, const float y, const float z)
	{
		this->assign(x, y, z);
	}

	VECTOR& VECTOR::operator +=(const VECTOR& operand)
	{
		for (int i = 0; i < 3; i++)
			(*this)[i] += operand[i];
		return *this;
	}

	VECTOR& VECTOR::operator -=(const VECTOR& operand)
	{
		for (int i = 0; i < 3; i++)
			(*this)[i] -= operand[i];
		return *this;
	}

	VECTOR& VECTOR::operator *=(const float factor)
	{
		for (int i = 0; i < 3; i++)
			(*this)[i] *= factor;
		return *this;
	}

	VECTOR& VECTOR::operator /=(const float factor)
	{
		for (int i = 0; i < 3; i++)
			(*this)[i] /= factor;
		return *this;
	}

	float VECTOR::dot(const VECTOR& operand) const
	{
		float result = 0;
		for (int i = 0; i < 3; i++)
			result += (*this)[i] * operand[i];
		return result;
	}

	float VECTOR::dotSelf() const
	{
		float result = 0;
		for (int i = 0; i < 3; i++)
			result += (*this)[i] * (*this)[i];
		return result;
	}

	float VECTOR::length() const
	{
		return sqrt(this->dotSelf());
	}

	float VECTOR::normalise()
	{
		float len = this->length();
		if (len == 0)
			return 0;
		for (int i = 0; i < 3; i++)
			(*this)[i] /= len;
		return len;
	}

	float VECTOR::normalise(const float length)
	{
		float len = this->length();
		if (len == 0 || length == 0)
			return 0;
		len = length / len;
		for (int i = 0; i < 3; i++)
			(*this)[i] *= len;
		return len;
	}

	VECTOR VECTOR::asUnit() const
	{
		VECTOR result(this);
		result.normalise();
		return result;
	}

	VECTOR VECTOR::asUnit(const float length) const
	{
		VECTOR result(this);
		result.normalise(length);
		return result;
	}

	VECTOR::operator const float*() const
	{
		return this->c;
	}

	VECTOR VECTOR::operator +(const VECTOR& operand) const
	{
		VECTOR result(this);
		result += operand;
		return result;
	}

	VECTOR VECTOR::operator -(const VECTOR& operand) const
	{
		VECTOR result(this);
		result -= operand;
		return result;
	}

	float VECTOR::operator |(const VECTOR& operand) const
	{
		return this->dot(operand);
	}

	VECTOR VECTOR::operator *(const VECTOR& operand) const
	{
		VECTOR result(
			(*this)[1] * operand[2] - (*this)[2] * operand[1],
			(*this)[2] * operand[0] - (*this)[0] * operand[2],
			(*this)[0] * operand[1] - (*this)[1] * operand[0]);
		return result;
	}

	VECTOR VECTOR::operator *(float factor) const
	{
		VECTOR result(this);
		result *= factor;
		return result;
	}

	VECTOR VECTOR::operator /(float factor) const
	{
		VECTOR result(this);
		result /= factor;
		return result;
	}

	VECTOR VECTOR::operator +() const
	{
		VECTOR result(this);
		return result;
	}

	VECTOR VECTOR::operator -() const
	{
		VECTOR result(this);
		result *= -1;
		return result;
	}

	VECTOR VECTOR::operator =(const VECTOR& source)
	{
		this->assign(source);
	}

	float* VECTOR::quat(const float w)
	{
		(*this)[3] = w;
		return(float*) this;
	}

	VECTOR VECTOR::hadamard(const VECTOR& operand)
	{
		VECTOR result(this);
		for (int i = 0; i < 3; i++)
			result[i] *= operand[i];
		return result;
	}

VECTOR operator *(const float factor, const VECTOR& operand)
{
	return operand * factor;
}
