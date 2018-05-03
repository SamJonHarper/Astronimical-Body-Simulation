//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Export.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "Export.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Constructor
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

Export::Export(const std::string & filename)
{
    // Open the file for exporting
    stream.open(filename.c_str());

    // Error checking
    if(!stream.is_open())
        throw std::runtime_error("Cannot open file " + filename);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Registration
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Export::RegisterExport(long column, const std::string & label, double value)
{
    // Register the column label
    LabelMap_[column] = label;

    // Register the value converted to text
    std::ostringstream ss;
    ss << value;
    ValueMap_[column] = ss.str();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Export
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Export::DoExport(bool NeedHeader)
{
    // Export column labels at the start
    if(NeedHeader)
    {
        // For each registered entry
        for(MapIt k = LabelMap_.begin(); k != LabelMap_.end(); ++k)
        {
            // Export the registered label with padding
            stream << std::setw(20) << k->second;
        }

        stream << std::endl;
    }

    // For each registered entry
    for(MapIt k = ValueMap_.begin(); k != ValueMap_.end(); ++k)
    {
        // Export the registered value with padding
        stream << std::setw(20) << k->second;
    }

    stream << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
