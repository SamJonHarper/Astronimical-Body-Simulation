//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Scenario4.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "Scenario4.h"
#include "ParameterSun.h"
#include "ParameterVenus.h"
#include "ParameterEarth.h"
#include "ParameterMars.h"
#include "ParameterAlteredStar.h"
#include "PseudoFactory.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Scenario4::Scenario4(const PseudoFactory & fac)
{
    // System containing only Sun-Venus-Earth-Mars
    // perturbed by a passing neutron star
    AddBody(ParameterSun().name);
    AddBody(ParameterVenus().name);
    AddBody(ParameterEarth().name);
    AddBody(ParameterMars().name);
    AddBody(ParameterAlteredStar().name);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
