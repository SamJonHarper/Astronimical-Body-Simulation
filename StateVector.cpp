//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  StateVector.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "StateVector.h"
#include <cmath>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Resizing
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void StateVector::Resize(long NumBodies)
{
    // Set the number of bodies
    NumBodies_ = NumBodies;

    // Number of bodies doubled for positions and velocities
    states_.resize(NumBodies*2);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Setters and getters
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void StateVector::SetPosition(long i, const std::vector<double> & P)
{
    states_[i] = P;
}

std::vector<double> StateVector::GetPosition(long i) const
{
    return states_[i];
}

void StateVector::SetVelocity(long i, const std::vector<double> & V)
{
    states_[NumBodies_ + i] = V;
}

std::vector<double> StateVector::GetVelocity(long i) const
{
    return states_[NumBodies_ + i];
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Computed values
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double StateVector::ComputeSpeed(long i) const
{
    // Get the body velocity
    const std::vector<double> v = GetVelocity(i);

    // Velocity vector magnitude
    return std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

double StateVector::ComputeSunDistance(long i) const
{
    // Get the body and Sun positions
    const std::vector<double> bp = GetPosition(i);
    const std::vector<double> sp = GetPosition(0);

    // Relative vector
    const double dx = bp[0] - sp[0];
    const double dy = bp[1] - sp[1];
    const double dz = bp[2] - sp[2];

    // Relative vector magnitude
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Overloaded operators
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

StateVector operator+(const StateVector & a, const StateVector & b)
{
    // Use the overloaded operation+=
    StateVector temp(a);
    temp += b;
    return temp;
}

StateVector operator*(double a, const StateVector & b)
{
    // Use the overloaded operation*=
    StateVector temp(b);
    temp *= a;
    return temp;
}

StateVector & StateVector::operator+=(const StateVector & a)
{
    // For each state
    for(long i = 0; i != NumBodies_*2; ++i)
    {
        // add X, Y, Z components
        states_[i][0] += a.states_[i][0];
        states_[i][1] += a.states_[i][1];
        states_[i][2] += a.states_[i][2];
    }

    return *this;
}

StateVector & StateVector::operator*=(double a)
{
    // For each state
    for(long i = 0; i != NumBodies_*2; ++i)
    {
        // scale X, Y, Z components
        states_[i][0] *= a;
        states_[i][1] *= a;
        states_[i][2] *= a;
    }

    return *this;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
