//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  PseudoFactory.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "PseudoFactory.h"

#include "Input.h"

#include "Scenario2.h"
#include "Scenario1.h"
#include "Scenario3.h"
#include "Scenario4.h"

#include "MethodEuler.h"
#include "MethodRungeKutta.h"

#include "SimulationApplication.h"

#include <stdexcept>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Getters
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double PseudoFactory::GetTimeStep() const
{
    return inp_->GetTimeStep();
}

long PseudoFactory::GetNumSteps() const
{
    return inp_->GetNumSteps();
}

std::string PseudoFactory::GetExportFilename() const
{
    return inp_->GetExportFilename();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  CreateScenario
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

ScenarioBase * PseudoFactory::CreateScenario() const
{
    const char ScenarioNumber = inp_->GetScenarioNumber();

    // Create the Scenario based on its number
    switch(ScenarioNumber)
    {
        case '1': return new Scenario1(*this); break;
        case '2': return new Scenario2(*this); break;
        case '3': return new Scenario3(*this); break;
        case '4': return new Scenario4(*this); break;
        default: throw std::runtime_error("PseudoFactory::CreateScenario: Bad character");
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  CreateMethod
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

MethodBase * PseudoFactory::CreateMethod() const
{
    const char MethodType = inp_->GetMethodType();

    // Create the Method based on its type
    switch(MethodType)
    {
        case 'e': return new MethodEuler(*this); break;
        case 'r': return new MethodRungeKutta(*this); break;
        default: throw std::runtime_error("PseudoFactory::CreateMethod: Bad character");
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  CreateApplication
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

ApplicationBase * PseudoFactory::CreateApplication() const
{
    return new SimulationApplication(*this);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
