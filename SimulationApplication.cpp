//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  SimulationApplication.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "SimulationApplication.h"
#include "PseudoFactory.h"
#include "ScenarioBase.h"
#include "MethodBase.h"
#include "Export.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

SimulationApplication::SimulationApplication(const PseudoFactory & fac)
:   TimeStep_(fac.GetTimeStep())
,   NumSteps_(fac.GetNumSteps())
,   ExportFilename_(fac.GetExportFilename())
{
    scenario_ = fac.CreateScenario();
    method_ = fac.CreateMethod();
}

SimulationApplication::~SimulationApplication()
{
    delete scenario_;
    delete method_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Run
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SimulationApplication::Run()
{
    // If the filename was supplied, the export is needed
    const bool NeedExport = !ExportFilename_.empty();

    // Create an Export object if needed
    Export * exp = NeedExport ? new Export(ExportFilename_) : nullptr;

    // Create the start state and store it for later output
    StateVector state = scenario_->CreateY();
    StartState_ = state;

    // Simulate for a specified number steps
    for(long i = 0; i != NumSteps_; ++i)
    {
        // If export is needed
        if(exp)
        {
            // Register the state for export
            const double year = i*TimeStep_;
            scenario_->RegisterExport(*exp, state, year);

            // Write at once to avoid clogging memory with huge data
            const bool NeedHeader = (i == 0);
            exp->DoExport(NeedHeader);
        }

        // Use the specified method for a simulation step
        method_->Step(*scenario_, state);
    }

    // Store the end state for later output
    EndState_ = state;

    // Destroy the Export object (if created) to close its file
    delete exp;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  RegisterOutput
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SimulationApplication::RegisterOutput(TableOutput & out) const
{
    // Start and end year
    const double StartYear = 0;
    const double EndYear = TimeStep_*NumSteps_;

    // Register start and end states
    long line = 0;
    scenario_->RegisterOutput(out, line, StartState_, StartYear);
    scenario_->RegisterOutput(out, line, EndState_, EndYear);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
