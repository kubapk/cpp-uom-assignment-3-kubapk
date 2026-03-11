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
#include "Source.h"

void Source::print_source_data() const
{
    std::cout<<"Source: [type, date, activity, identifier] = ["<<type<<", "<<date_acquisition<<", "<<activity<<", "<<identifier<<"]"<<std::endl;
    return;
}

std::set<int> Source::used_ids; //empty set of used IDs created
//otherwise used_ids is initialised in class but not declared outside of it
//and so cannot be used for checking IDs