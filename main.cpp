//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "ApplicationWrapper.h"
#include "ErrorHandler.h"
#include "utility.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  main
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main(int argc, char *argv[])
{
    ErrorHandler handler;

    try
    {
        // Run the app repeatedly
        do
        {
            ApplicationWrapper app;
            app.Run();
        }
        while(ut::do_again());
    }
    catch(const std::runtime_error & e)
    {
        // Handle runtime errors
        handler.HandleRunTimeError(e);
    }
    catch(const std::exception&)
    {
        // Handle early exit
        return 0;
    }
    catch(...)
    {
        // Handle other errors
        handler.HandleUnknownError();
    }

    return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
