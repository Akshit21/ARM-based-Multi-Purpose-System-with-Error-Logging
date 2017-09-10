/*
 * profiler.h
 *
 *  Created on: Dec 7, 2016
 *      Author: Akshit
 */

#ifndef INCLUDES_PROFILER_H_
#define INCLUDES_PROFILER_H_

#include "MKL25Z4.h"
#include "log.h"

#define MOD_VAL 65535
#define T1CLK  	21

void start(void);
void end(void);
void profiler(void);
void profile_BBB(void);





#endif /* INCLUDES_PROFILER_H_ */
