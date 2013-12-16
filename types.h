/* 
 * File:   types.h
 * Author: mark
 *
 * Created on 16 December 2013, 01:40
 */

#ifndef TYPES_H
#define	TYPES_H

#include "vector.h"
#include "matrix.h"

const double PI = 3.141592653589793238462;

/*
 * Lengths are dimensionless, so I arbitrarily choose to use values in
 * millimetres
 */

/* A strut */
class STRUT {
public:

	STRUT()
	{
	}

	/* Offset of motor from centre */
	VECTOR motor_offset = VECTOR::zero();

	/* Angle of motor arm from base plane */
	float motor_angle = 0;

	/* Tangent to ellipse, at the motor_offset point */
	VECTOR tangent = VECTOR::zero();

	/* Normal to ellipse, at the motor_offset point */
	VECTOR normal = VECTOR::zero();

	/* 
	 * Offset of bases of strut from centres (accounting for rotary arm on
	 * base)
	 */
	VECTOR base_offset = VECTOR::zero();
	VECTOR platform_offset = VECTOR::zero();

	/* 
	 * Half the minor dimensions of the strut at each end, for display
	 * purposes
	 */
	VECTOR base_halfwidth = VECTOR::zero();
	VECTOR base_halfdepth = VECTOR::zero();
	VECTOR platform_halfwidth = VECTOR::zero();
	VECTOR platform_halfdepth = VECTOR::zero();

	/* Length of the strut */
	float length = 250;

	/*
	 * Stores positions of each end of the strut, relative to centre of base
	 * platform
	 */
	VECTOR p[2] = { VECTOR::zero(), VECTOR::zero() };

	/* Nonzero if this strut could not be solved */
	float error = 0;
};

/* Platform configuration objective */
class CONFIGURATION {
public:

	CONFIGURATION(int struts) :
	struts(struts),
	s(new STRUT[struts])
	{
	}

	~CONFIGURATION()
	{
		delete [] s;
	}

	/* pitch/yaw/roll/x/y/z must follow appear in that order in memory: */

	/* Platform rotation relative to base plane */
	float pitch = 0.3, yaw = 0.2, roll = 0;

	/* Platform centre displacement from base centre */
	VECTOR platform_displacement = { 0, 200, 0 };

	/* Number of struts */
	const int struts;

	/* Length of strut */
	float strut_length = 250;

	/* Arm length / wheel radius between strut and motor */
	/* Wheels are displayed as ellipses to illustrate the angles better */
	float strut_arm = 10;

	/* Smaller dimensions of strut, for display purposes only*/
	float strut_w = 3;
	float strut_d = 2;

	/* Wheel / arm thickness */
	float wheel_thickness = 10;

	/* Base geometry: plane size, thickness */
	float base_rx = 150;
	float base_ry = 150;
	float base_thickness = 10;

	/* Platform geometry: plane size, thickness */
	float platform_rx = 100;
	float platform_ry = 100;
	float platform_thickness = 10;

	/* Ellipse, polygon with vertex attachment, polygon with edge attachment */
	enum PLATFORM_SHAPE {
		ELLIPSE, POLYVERTEX, POLYEDGE
	};

	/* Major and minor axes base */
	VECTOR base[2] = {
		VECTOR::unitX(),
		VECTOR::unitY()
	};

	/* Is the base a polygon?  Or an ellipse? */
	PLATFORM_SHAPE base_polygon = POLYEDGE;

	/* Major and minor axes platform */
	VECTOR platform[2] = {
		VECTOR::unitX(),
		VECTOR::unitY()
	};

	/* Is the platform a polygon?  Or an ellipse? */
	PLATFORM_SHAPE platform_polygon = POLYEDGE;

	/* Struts */
	STRUT * const s;
	STRUT & operator [] (int index)
	{
		return this->s[index];
	}

	void configure();
	void solve();
	void solve(int strut);
	float epsilon();
	bool optimise(
		const float pitch_freedom,
		const float yaw_freedom,
		const float roll_freedom,
		const VECTOR displacement_freedom,
		const float jumpscale = 0.1,
		const int iterations = 100);
	/* yaw/pitch/roll/x/y/z */
	bool optimise(const float * const freedom,
		const float jumpscale = 0.1,
		const int iterations = 100,
		const float delta = 0.1);
private:
	void setParams(const float* const x);
	void getParams(float* const x);
	void gradient(const float* const x, float * const grad, const float delta = 0.1);
};

CONFIGURATION demo_configuration();

#endif	/* TYPES_H */
