//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  DataManager.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "DataManager.h"
#include "ParameterAU.h"
#include "ParameterMass.h"
#include "ParameterPositionX.h"
#include "ParameterPositionY.h"
#include "ParameterPositionZ.h"
#include "ParameterVelocityX.h"
#include "ParameterVelocityY.h"
#include "ParameterVelocityZ.h"
#include <fstream>
#include <stdexcept>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

DataManager::DataManager()
{
    // Open the data file with error checking
    std::ifstream stream("data.txt");
    if(!stream.is_open())
    {
        throw std::runtime_error("Cannot open file data.txt");
    }

    // Populate the map with the file data
    while(!stream.eof())
    {
        // Read the name-value pair
        std::pair<std::string, double> data;
        stream >> data.first;
        stream >> data.second;

        // Insert it into the map
        if(stream.good()) map_.insert(data);
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Getters
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double DataManager::GetValue(const std::string & name) const
{
    // Get the value for the specified name
    const MapIt p = map_.find(name);

    // Error checking
    if(p == map_.end())
        throw std::runtime_error(name + " parameter not found");

    // Return the corresponding value
    return p->second;
}

double DataManager::GetValue(const std::string & name, const std::string & subname) const
{
    // Combine the name with subname to support parameter names like "JupiterMass"
    return GetValue(name + subname);
}

double DataManager::GetMass(const std::string & name) const
{
    // Get the mass for the specified body name
    return GetValue(name, ParameterMass().name);
}

std::vector<double> DataManager::GetInitialPosition(const std::string & name) const
{
    // Get the initial position for the specified body name
    const double x = GetValue(name, ParameterPositionX().name);
    const double y = GetValue(name, ParameterPositionY().name);
    const double z = GetValue(name, ParameterPositionZ().name);

    // Get the astronomical unit
    static const double AU = GetValue(ParameterAU().name);

    // Convert metres to AU units
    std::vector<double> p(3);
    p[0] = x/AU;
    p[1] = y/AU;
    p[2] = z/AU;
    return p;
}

std::vector<double> DataManager::GetInitialVelocity(const std::string & name) const
{
    // Get the initial velocity for the specified body name
    const double x = GetValue(name, ParameterVelocityX().name);
    const double y = GetValue(name, ParameterVelocityY().name);
    const double z = GetValue(name, ParameterVelocityZ().name);

    // Get the astronomical unit
    static const double AU = GetValue(ParameterAU().name);
    static const double SecondsInYear = 3600*24*365.25;

    // Convert metres/second to AU/year
    std::vector<double> v(3);
    v[0] = x*SecondsInYear/AU;
    v[1] = y*SecondsInYear/AU;
    v[2] = z*SecondsInYear/AU;
    return v;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
