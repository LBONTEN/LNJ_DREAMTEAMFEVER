// file taken & possibly slightly modified from http://ansymore.uantwerpen.be/system/files/uploads/courses/SE1BAC/TicTacToe21.zip

//============================================================================
// Name        : fileHelpers.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#ifndef fileHelpers_H
#define fileHelpers_H


#include <iostream>


bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string leftFileName, const std::string rightFileName);


#endif