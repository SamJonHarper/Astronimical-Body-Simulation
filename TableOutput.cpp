//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  TableOutput.cpp
//  Assignment 2 - 1422827
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "TableOutput.h"
#include "utility.h"
#include <iostream>
#include <iomanip>
#include <sstream>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Registration
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void TableOutput::RegisterOutput(long row, long column, const std::string & text)
{
    // Add the mapping from (row, column) to text
    const Cell cell = std::make_pair(row, column);
    map_[cell] = text;
}

void TableOutput::RegisterOutput(long row, long column, double value)
{
    // Register the value converted to text
    std::ostringstream ss;
    ss << std::setprecision(4) << value;
    RegisterOutput(row, column, ss.str());
}

void TableOutput::RegisterOutput(long row, long lcolumn, const std::string & label,
                                           long vcolumn, double value)
{
    // Register the label at (row, lcolumn) and value at (row, vcolumn)
    RegisterOutput(row, lcolumn, label);
    RegisterOutput(row, vcolumn, value);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Output
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void TableOutput::DoOutput() const
{
    // Previous row
    long prow = 0;

    // For each registered entry
    for(MapIt k = map_.begin(); k != map_.end(); ++k)
    {
        // Table cell position
        const Cell cell = k->first;
        const long row = cell.first;
        const long column = cell.second;

        // Go to the next line if different row from the previous
        if(row != prow) std::cout << std::endl;

        // Output with padding, smaller for the first column
        const long width = (column == 1) ? 7 : 12;
        std::cout << std::setw(width) << k->second;

        // Update the previous row
        prow = row;
    }

    std::cout << std::endl;
}

void TableOutput::OutputBanner(const std::string & text) const
{
    ut::OutputLine(text);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  End Of File
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
