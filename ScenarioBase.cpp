//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  ScenarioBase.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "ScenarioBase.h"
#include "StateVector.h"
#include "ParameterG.h"
#include "DataManager.h"
#include "TableOutput.h"
#include "Export.h"
#include <cmath>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Adding bodies to the scenario
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void ScenarioBase::AddBody(const std::string & name)
{
    // Add the body name
    names_.push_back(name);

    // Get and add the body mass
    const double mass = DataManager::Instance().GetMass(name);
    masses_.push_back(mass);

    // Update the number of bodies
    ++NumBodies_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Initial state
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

StateVector ScenarioBase::CreateY() const
{
    // Create and resize the state vector
    StateVector y;
    y.Resize(NumBodies_);

    // For each body
    for(long i = 0; i != NumBodies_; ++i)
    {
        // Get the initial position and velocity
        const std::vector<double> p = DataManager::Instance().GetInitialPosition(names_[i]);
        const std::vector<double> v = DataManager::Instance().GetInitialVelocity(names_[i]);

        // Set the position and velocity in the state vector
        y.SetPosition(i, p);
        y.SetVelocity(i, v);
    }

    return y;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  State vector derivative function
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

StateVector ScenarioBase::ComputeF(const StateVector & y) const
{
    // Create and resize the state vector
    StateVector f;
    f.Resize(NumBodies_);

    // For each body
    for(long i = 0; i != NumBodies_; ++i)
    {
        // Get the velocity and compute the acceleration
        const std::vector<double> v = y.GetVelocity(i);
        const std::vector<double> a = ComputeAcceleration(y, i);

        // Set the velocity and acceleration in the state vector
        f.SetPosition(i, v);
        f.SetVelocity(i, a);
    }

    return f;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Acceleration due to gravity acting on body i
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

std::vector<double> ScenarioBase::ComputeAcceleration(const StateVector & y, long i) const
{
    // Gravitational constant
    static const double G = DataManager::Instance().GetValue(ParameterG().name);

    // Position of body i, cached for performance
    const std::vector<double> Pi = y.GetPosition(i);
    const double xi = Pi[0];
    const double yi = Pi[1];
    const double zi = Pi[2];

    // Acceleration components, initially zero
    double ax = 0;
    double ay = 0;
    double az = 0;

    // For each body
    for(long k = 0; k != NumBodies_; ++k)
    {
        // Ignore itself
        if(k != i)
        {
            // Position of body k
            const std::vector<double> Pk = y.GetPosition(k);

            // Direction vector from body i to body k
            const double dx = Pk[0] - xi;
            const double dy = Pk[1] - yi;
            const double dz = Pk[2] - zi;

            // Distance between the bodies
            const double d = std::sqrt(dx*dx + dy*dy + dz*dz);

            // Acceleration formula
            const double c = masses_[k]/(d*d*d);
            ax += c*dx;
            ay += c*dy;
            az += c*dz;
        }
    }

    // Acceleration multiplied by G outside the loop for performance
    return std::vector<double>({G*ax, G*ay, G*az});
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  RegisterOutput
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void ScenarioBase::RegisterOutput(TableOutput & out, long & line,
                                  const StateVector & state, double year) const
{
    // Register the table header
    if(year == 0.0)
    {
        // Register the Year and Variable text
        out.RegisterOutput(line, 0, "Year");
        out.RegisterOutput(line, 1, "Var");

        // Register the body names
        for(long i = 0; i != NumBodies_; ++i)
            out.RegisterOutput(line, 2 + i, names_[i]);
    }

    // Register the Year value
    out.RegisterOutput(line + 1, 0, year);

    // Register empty strings for the remaining Year column
    for(long row = line + 2; row != line + 9; ++row)
        out.RegisterOutput(row, 0, "");

    // For each body
    for(long i = 0; i != NumBodies_; ++i)
    {
        // Get the body position, velocity, speed and distance from the Sun
        const std::vector<double> p = state.GetPosition(i);
        const std::vector<double> v = state.GetVelocity(i);
        const double speed = state.ComputeSpeed(i);
        const double distance = state.ComputeSunDistance(i);

        // Register the body values at consecutive rows
        long row = line;
        out.RegisterOutput(++row, 1, "Pos X", 2 + i, p[0]);
        out.RegisterOutput(++row, 1, "Pos Y", 2 + i, p[1]);
        out.RegisterOutput(++row, 1, "Pos Z", 2 + i, p[2]);
        out.RegisterOutput(++row, 1, "Vel X", 2 + i, v[0]);
        out.RegisterOutput(++row, 1, "Vel Y", 2 + i, v[1]);
        out.RegisterOutput(++row, 1, "Vel Z", 2 + i, v[2]);
        out.RegisterOutput(++row, 1, "Speed", 2 + i, speed);
        out.RegisterOutput(++row, 1, "SDist", 2 + i, distance);
    }

    // Register an empty line at the end
    out.RegisterOutput(line + 9, 0, "");

    // Update the output line
    line += 10;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  RegisterExport
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void ScenarioBase::RegisterExport(Export & exp, const StateVector & state,
                                  double year) const
{
    // Register the year
    long column = 0;
    exp.RegisterExport(column, "Year", year);

    // For each body
    for(long i = 0; i != NumBodies_; ++i)
    {
        // Get the body name and position
        const std::string name = names_[i];
        const std::vector<double> pos = state.GetPosition(i);

        // Register the position components at consecutive columns
        exp.RegisterExport(++column, name + " Pos X", pos[0]);
        exp.RegisterExport(++column, name + " Pos Y", pos[1]);
        exp.RegisterExport(++column, name + " Pos Z", pos[2]);
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
