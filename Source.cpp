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
#include "Date.h"
using std::string;


//SETTERS
//Setter for type and activity
void Source::set_type_activity(const string type_in, const double activity_in)
{
    auto iterator = valid_sources.find(type_in); //pointer to element in map

    if(iterator == valid_sources.end()) //if type_in does not exist in source validation file
    //i.e. if the iterator reaches the end it has not found type_in in the map
    {
        throw std::invalid_argument(type_in+" is not a valid source type (from source validation file).");
    }

    double expected = iterator->second; //activity value in source validation file corrresponding to type_in
    double relative_error = std::abs(activity_in - expected) / expected;

    if(relative_error > 0.05) //if activity does not match source type in source validation file up to 5% tolerance
    {
        throw std::invalid_argument("Activity "+std::to_string(activity_in)+"Bq/kg does not match source type "+type_in+
        ", as specified in source validation file.");
    }

    type = type_in;
    activity = activity_in;
}


//Setter for date
void Source::set_date(const Date date_in)
{
    if(!date_in.is_valid_date())
    {
        throw std::invalid_argument("Date is not valid for "+type+" source. Ensure format is DD/MM/YYYY.");
    }
    if(!date_in.is_past_date())
    {
        throw std::invalid_argument("Date for "+type+" source is in the future. Ensure acquisition date is not in the future.");
    }

    date_acquisition = date_in;
}


//Setter for identifier
void Source::set_identifier(const int identifier_in)
{
    if(identifier_in < 0)
    {
        throw std::invalid_argument("Source ID must be a positive number.");
    }
    if(used_ids.count(identifier_in) !=0) //count returns 0 if idenifier_in appears 0 times in used_ids
    {
        throw std::invalid_argument("The source ID "+std::to_string(identifier_in)+" has been used more than once.");
    }

    identifier = identifier_in;
    used_ids.insert(identifier_in);
}


//Setter for mass
void Source::set_mass(const double mass_in)
{
    if(mass_in == 0)
    {
        throw std::invalid_argument(type+" source mass cannot be 0kg.");
    }
    if(mass_in < 0 || mass_in > 1e-6) //if mass is less than/equal to 0 or greater than 1mg
    {
        throw std::invalid_argument("The mass "+std::to_string(mass_in)+"kg for "+type+" source is invalid." 
        " Mass must be between 0 and 1mg (1e-6 kg).");
    }
    mass = mass_in;
}


//MEMBER FUNCTIONS
//Member function to print source data
void Source::print_source_data() const
{
    std::cout<<"Source: [type, date (DD/MM/YYYY), activity (Bq/kg), identifier, mass (kg)] = ["<<
        type<<", "<<date_acquisition<<", "<<activity<<", "<<identifier<<", "<<mass<<"]"<<std::endl;
    return;
}


//Create empty set of used IDs and valid sources
std::set<int> Source::used_ids;
//otherwise used_ids is initialised in class but not declared outside of it
std::map<string, double> Source::valid_sources;


//Member function to load valid sources into map
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