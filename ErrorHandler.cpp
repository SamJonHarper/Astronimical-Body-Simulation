//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  ErrorHandler.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "ErrorHandler.h"
#include "utility.h"
#include <iostream>

void ErrorHandler::HandleRunTimeError(const std::runtime_error & e) const
{
    std::cout << "Error caught:  " << e.what() << std::endl;
}

void ErrorHandler::HandleUnknownError() const
{
    std::cout << "Unknown error caught" << std::endl;
}

long ErrorHandler::PauseAndReturn() const
{
    return ut::PauseAndReturn();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
