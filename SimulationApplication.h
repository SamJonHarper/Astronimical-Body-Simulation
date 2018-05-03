//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  SimulationApplication.h
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef SimulationApplicationH
#define SimulationApplicationH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "ApplicationBase.h"
#include "StateVector.h"
#include <string>

class PseudoFactory;
class ScenarioBase;
class MethodBase;

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  class SimulationApplication
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class SimulationApplication : public ApplicationBase
{
    public:
        SimulationApplication(const PseudoFactory & fac);
        ~SimulationApplication();

        void Run();
        void RegisterOutput(TableOutput & out) const;

    private:
        ScenarioBase * scenario_;
        MethodBase * method_;

        double TimeStep_;               // Simulation time step
        long NumSteps_;                 // Number of simulation steps

        std::string ExportFilename_;    // Filename for exporting

        StateVector StartState_;        // State before simulation
        StateVector EndState_;          // State after simulation
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
