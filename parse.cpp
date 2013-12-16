#include "parse.h"
#include "types.h"
#include <iostream>
#include <string.h>

using namespace std;

bool strsame(const char * const a, const char * const b)
{
	return !strcmp(a, b);
}

CONFIGURATION::PLATFORM_SHAPE parseShape(const char * const value)
{
	if (strsame(value, "ellipse"))
		return CONFIGURATION::PLATFORM_SHAPE::ELLIPSE;
	else if (strsame(value, "polygon vertex"))
		return CONFIGURATION::PLATFORM_SHAPE::POLYVERTEX;
	else if (strsame(value, "polygon edge"))
		return CONFIGURATION::PLATFORM_SHAPE::POLYEDGE;
	else {
		cerr << "Unknown platform shape: " << value << endl;
		return CONFIGURATION::PLATFORM_SHAPE::ELLIPSE;
	}
}

VECTOR parseVector(const char * const value)
{
	float x, y, z;
	int c = sscanf(value, "%f,%*[ \t]%f,%*[ \t]%f", &x, &y, &z);
	if (c != 3) {
		cerr << "Invalid vector value: " << value << endl;
		return VECTOR::zero();
	}
	return VECTOR(x, y, z);
}

void parseArray3(const char * const value, float* const out)
{
	int c = sscanf(value,
		"%f,%*[ \t]%f,%*[ \t]%f",
		out + 0, out + 1, out + 2);
	if (c != 3) {
		cerr << "Invalid vector value: " << value << endl;
		for (int i = 0; i < 3; i++)
			out[i] = 0;
	}
}

void parseArray6(const char * const value, float * const out)
{
	int c = sscanf(value,
		"%f,%*[ \t]%f,%*[ \t]%f,%*[ \t]%f,%*[ \t]%f,%*[ \t]%f",
		out + 0, out + 1, out + 2, out + 3, out + 4, out + 5);
	if (c != 6) {
		cerr << "Invalid vector value: " << value << endl;
		for (int i = 0; i < 6; i++)
			out[i] = 0;
	}
}

float parseFloat(const char * const value)
{
	errno = 0;
	float ret = strtof(value, 0);
	if (errno) {
		cerr << "Invalid decimal value: " << value << endl;
		return 0;
	}
	return ret;
}

long parseInt(const char * const value)
{
	errno = 0;
	long ret = strtol(value, 0, 10);
	if (errno) {
		cerr << "Invalid integer value: " << value << endl;
		return 0;
	}
	return ret;
}

long parseBool(const char * const value)
{
	if (
		strsame(value, "enabled") ||
		strsame(value, "true") ||
		strsame(value, "1") ||
		strsame(value, "yes") ||
		strsame(value, "on"))
		return true;
	else if (
		strsame(value, "disabled") ||
		strsame(value, "false") ||
		strsame(value, "0") ||
		strsame(value, "no") ||
		strsame(value, "off"))
		return true;
	else {
		cerr << "Invalid boolean value: " << value << endl;
		return false;
	}
}

