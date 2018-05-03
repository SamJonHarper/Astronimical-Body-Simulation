//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  ApplicationWrapper.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "ApplicationWrapper.h"
#include "PseudoFactory.h"
#include "Input.h"
#include "TableOutput.h"
#include "ApplicationBase.h"

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

ApplicationWrapper::ApplicationWrapper()
:   inp_(nullptr)
,   out_(nullptr)
,   fac_(nullptr)
,   app_(nullptr)
{
    // Create the input object
    inp_ = new Input;

    // If early exit is requested
    if(inp_->GetQuitOption())
    {
        // Exit cleanly
        delete inp_;
        inp_ = nullptr;
        throw std::exception();
    }

    // Create the output and factory objects
    out_ = new TableOutput;
    fac_ = new PseudoFactory;

    // Set input and output
    fac_->SetInput(inp_);
    fac_->SetOutput(out_);

    // Create the application object
    app_ = fac_->CreateApplication();
}

ApplicationWrapper::~ApplicationWrapper()
{
    // Free the contained objects
    delete fac_;
    delete inp_;
    delete out_;
    delete app_;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Run
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void ApplicationWrapper::Run() const
{
    // Perform the simulation
    out_->OutputBanner("Simulating...");
    app_->Run();

    // Output the results
    app_->RegisterOutput(*out_);
    out_->DoOutput();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
