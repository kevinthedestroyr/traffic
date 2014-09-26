/* 
 * File:   common.h
 * Author: kevin
 *
 * Created on April 29, 2014, 8:41 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#define DISALLOW_COPY_AND_ASSIGN(TYPE) \
  TYPE(const TYPE&);                   \
  TYPE& operator=(const TYPE&)

namespace {
constexpr float kMPSOverMPH = 0.44704;
constexpr float kMetersPerMile = 1609.34;
constexpr float PI = 3.14159265359;
}


#endif	/* COMMON_H */

