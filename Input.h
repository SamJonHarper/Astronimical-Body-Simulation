//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Input.h
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef InputH
#define InputH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <string>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  class Input
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

class Input
{
    public:
        Input();

        char GetMethodType() const {return MethodType_;}
        char GetScenarioNumber() const {return ScenarioNumber_;}

        double GetTimeStep() const {return TimeStep_;}
        long GetNumSteps() const {return NumSteps_;}

        std::string GetExportFilename() const {return ExportFilename_;}
        bool GetQuitOption() const {return QuitOption_;}

    private:
        char InputMethodType();
        char InputScenarioNumber();
        double InputYears();
        long InputStepsPerYear();
        bool InputExportOption();

        char MethodType_;               // Method type
        char ScenarioNumber_;           // Scenario number

        double TimeStep_;               // Simulation time step
        long NumSteps_;                 // Number of simulation steps

        std::string ExportFilename_;    // Filename for exporting
        bool QuitOption_;               // Early exit
};

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
