/* 
 * File:   parse.h
 * Author: mark
 *
 * Created on 16 December 2013, 16:20
 */

#ifndef PARSE_H
#define	PARSE_H

#include "types.h"

bool strsame(const char * const a, const char * const b);
CONFIGURATION::PLATFORM_SHAPE parseShape(const char * const value);
VECTOR parseVector(const char * const value);
void parseArray3(const char * const value, float* const out);
void parseArray6(const char * const value, float * const out);
float parseFloat(const char * const value);
long parseInt(const char * const value);
long parseBool(const char * const value);

#endif	/* PARSE_H */
