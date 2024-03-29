
//============================================================================
// Name        : DesignByContract.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : Declarations for design by contract in C++
//============================================================================

#ifndef INC_2_TEST_CONTRACT_DEBUG_DESIGN_BY_CONTRACT_H
#define INC_2_TEST_CONTRACT_DEBUG_DESIGN_BY_CONTRACT_H


#include <assert.h>

#define REQUIRE(assertion, what) \
	if (!(assertion)) __assert (what, __FILE__, __LINE__)

#define ENSURE(assertion, what) \
	if (!(assertion)) __assert (what, __FILE__, __LINE__)

#endif //INC_2_TEST_CONTRACT_DEBUG_DESIGN_BY_CONTRACT_H
