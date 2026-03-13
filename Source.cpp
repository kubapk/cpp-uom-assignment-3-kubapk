/*
____________________________________________
RADIOACTIVE SOURCE MEMBER FUNCTIONS
(Part of PHYS30762 Assignment 3)
____________________________________________
This implementation file defines member function for the "Source" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
*/

#include<iostream>
#include<fstream> //for files
#include<sstream> //string stream
#include<string>
#include "Source.h"
using std::string;


//Member function to print source data
void Source::print_source_data() const
{
    std::cout<<"Source: [type, date (DD/MM/YYYY), activity (Bq/kg), identifier, mass (kg)] = ["<<
        type<<", "<<date_acquisition<<", "<<activity<<", "<<identifier<<", "<<mass<<"]"<<std::endl;
    return;
}

std::set<int> Source::used_ids; //empty set of used IDs created
//otherwise used_ids is initialised in class but not declared outside of it
//and so cannot be used for checking IDs

std::map<string, double> Source::valid_sources;
//empty map called "valid_sources" is created

void Source::load_valid_sources(const string& source_file_name)
{
    std::ifstream read_file(source_file_name);

    //Check if file opened correctly
    if(!read_file.good())
    {
        throw std::runtime_error("Source validation file '"+source_file_name+"' could not be opened");
    }

    string line; //read in line from data file

    while(std::getline(read_file, line))
    {
        //Ignore blank lines or header lines
        if(line.empty() || line[0] == '#') {continue;}

        //Create string stream and variables to assign data read by stream
        std::stringstream ss(line);
        string source_type;
        string source_activity_str;

        //Try to read source type & activity with semicolon separation
        if(!std::getline(ss, source_type, ';') || !std::getline(ss, source_activity_str))
        {
            std::cerr<<"Source validation file error: The line {"<<line<<"} is incorrectly formatted."
            " Line will not contribute to valid sources."<<std::endl;
            continue; 
        }

        //Ignore lines with blank source_type
        if(source_type.empty())
        {
            std::cerr<<"Source validation file error: The line {"<<line<<"} contains a blank source type."
            " Line will not contriute to valid sources."<<std::endl;
            continue; 
        }


        //Ignore extra characters after source_activity
        string extra;
        double source_activity; //converts activity to double
        std::stringstream activity_stream(source_activity_str); //create new stream to check after activity
        if(!(activity_stream >> source_activity) || (activity_stream >> extra))
        //returns true if it cannot extract double from source_activity, or if it can extract more characters after 
        //reading activity
        {
            std::cerr<<"Source validation file error: Extra characters found in line {"<<line<<"}."
            " Line will not contribute to valid sources."<<std::endl;
            continue;
        }

        //Add file line to map (type is key and activity is value)
        valid_sources[source_type] = source_activity;

        //Check activity range is valid
        if(source_activity <= 0 ) //disallows non-positive activity
        {
            throw std::invalid_argument("Activity in line {"+line+"} of source validation file is invalid. Activity must be"
            " greater than 0."); //does not allow program to continue
        }
    }

    read_file.close();
}