/*
____________________________________________
RADIOACTIVE SOURCE MEMBER FUNCTIONS
(Part of PHYS30762 Assignment 3)
____________________________________________
This implementation file defines member function for the "Source" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
Last updated on XXX XX Mar 2026
*/

#include<iostream>
#include<fstream> //for files
#include "Source.h"

void Source::print_source_data() const
{
    std::cout<<"Source: [type, date (DD/MM/YYYY), activity (Bq/kg), identifier] = ["<<
        type<<", "<<date_acquisition<<", "<<activity<<", "<<identifier<<"]"<<std::endl;
    return;
}

std::set<int> Source::used_ids; //empty set of used IDs created
//otherwise used_ids is initialised in class but not declared outside of it
//and so cannot be used for checking IDs

std::map<string, double> Source::valid_sources;
//empty map called "valid_sources" is created

void Source::load_valid_sources(const string file_name)
{
    std::ifstream read_file(file_name);

    string source_type;
    double source_activity;

    while(read_file >> source_type >> source_activity)
    //read_file is sent to source type (the first thing it reads)
    //2nd thing read_file reads is then sent to source_activity
    {
        valid_sources[source_type] = source_activity;
        //sets source_type to be index and source_activity to be value
    }
}