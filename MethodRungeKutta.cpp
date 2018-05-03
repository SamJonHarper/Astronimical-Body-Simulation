//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  MethodRungeKutta.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "MethodRungeKutta.h"
#include "PseudoFactory.h"
#include "StateVector.h"
#include "ScenarioBase.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

MethodRungeKutta::MethodRungeKutta(const PseudoFactory & fac)
:   h_(fac.GetTimeStep())
{
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Step
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void MethodRungeKutta::Step(const ScenarioBase & scenario, StateVector & y)
{
    // Constants
    static const double c6 = 1.0/6;
    static const double c3 = 1.0/3;

    // Runge-Kutta discretization
    // there are no partial time increments
    // because gravity doesn't explicitly depend on time
    const StateVector d1 = h_*scenario.ComputeF(y);
    const StateVector d2 = h_*scenario.ComputeF(y + 0.5*d1);
    const StateVector d3 = h_*scenario.ComputeF(y + 0.5*d2);
    const StateVector d4 = h_*scenario.ComputeF(y + d3);
    y += c6*d1 + c3*d2 + c3*d3 + c6*d4;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
