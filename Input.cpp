//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Input.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "Input.h"
#include "utility.h"
#include "lib_val.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Input::Input()
:   QuitOption_(false)
{
    // Input the method type
    MethodType_ = InputMethodType();
    if(QuitOption_) return;

    // Input scenario number
    ScenarioNumber_ = InputScenarioNumber();
    if(QuitOption_) return;

    // Input the number of years
    double Years = InputYears();
    if(QuitOption_) return;

    // Input the steps per year
    long StepsPerYear = InputStepsPerYear();
    if(QuitOption_) return;

    // Input the export option and clear the filename if not needed
    ExportFilename_ = "export.txt";
    bool NeedExport = InputExportOption();
    if(QuitOption_) return;
    if(!NeedExport) ExportFilename_.clear();

    // Compute the time step in years and the total number of steps
    TimeStep_ = 1.0/StepsPerYear;
    NumSteps_ = long(Years*StepsPerYear);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  InputMethodType
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

char Input::InputMethodType()
{
    // Show info
    ut::OutputLine("Welcome to the N-body simulation application");
    ut::OutputLine();
    ut::OutputLine("Available simulation methods:");
    ut::OutputLine("e) Euler discretization");
    ut::OutputLine("r) Runge-Kutta discretization:");

    // Input the method type
    const std::string prompt = "Method type (e, r, q - quit)";
    const char type = ut::get_char_in_range(prompt, "erq");

    // Quit on q
    if(type == 'q') QuitOption_ = true;
    return type;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  InputScenarioNumber
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

char Input::InputScenarioNumber()
{
    // Show info
    ut::OutputLine();
    ut::OutputLine("Available scenarios:");
    ut::OutputLine("1) Sun-Earth");
    ut::OutputLine("2) Sun-Venus-Earth-Mars-Jupiter");
    ut::OutputLine("3) Sun-Venus-Earth-Mars perturbed by a passing neutron star");
    ut::OutputLine("4) Sun-Venus-Earth-Mars perturbed by a passing neutron star (altered)");

    // Input the scenario number
    const std::string prompt = "Scenario (1, 2, 3, 4, q - quit)";
    const char number = ut::get_char_in_range(prompt, "1234q");

    // Quit on q
    if(number == 'q') QuitOption_ = true;
    return number;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  InputYears
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double Input::InputYears()
{
    // Show prompt
    const std::string prompt = "How many years to simulate? (q - quit)";
    bool valid = false;
    double value = 0.0;

    // Repeat until valid
    while(!valid)
    {
        // Input a string and convert to double
        std::string input = ut::GetString(prompt);
        value = lv::StringToDouble(input, valid);
        if(value <= 0) valid = false;

        // Quit on q
        if(input == "q")
        {
            valid = true;
            QuitOption_ = true;
        }
    }

    return value;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  InputStepsPerYear
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

long Input::InputStepsPerYear()
{
    // Show prompt
    const std::string prompt = "How many time steps per year? (q - quit)";
    bool valid = false;
    long value = 0;

    // Repeat until valid
    while(!valid)
    {
        // Input a string and convert to double
        std::string input = ut::GetString(prompt);
        value = lv::StringToLong(input, valid);
        if(value <= 0) valid = false;

        // Quit on q
        if(input == "q")
        {
            valid = true;
            QuitOption_ = true;
        }
    }

    return value;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  InputExportOption
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool Input::InputExportOption()
{
    // Input the export option
    const std::string prompt = "Export to " + ExportFilename_ + "? (y, n, q - quit)";
    const char flag = ut::get_char_in_range(prompt, "ynq");

    // Quit on q
    if(flag == 'q') QuitOption_ = true;
    return flag == 'y';
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
