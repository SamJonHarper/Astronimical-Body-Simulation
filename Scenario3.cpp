//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Scenario3.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "Scenario3.h"
#include "ParameterSun.h"
#include "ParameterVenus.h"
#include "ParameterEarth.h"
#include "ParameterMars.h"
#include "ParameterNeutronStar.h"
#include "PseudoFactory.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Scenario3::Scenario3(const PseudoFactory & fac)
{
    // System containing only Sun-Venus-Earth-Mars
    // perturbed by a passing neutron star
    AddBody(ParameterSun().name);
    AddBody(ParameterVenus().name);
    AddBody(ParameterEarth().name);
    AddBody(ParameterMars().name);
    AddBody(ParameterNeutronStar().name);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
