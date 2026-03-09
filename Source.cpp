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
    std::cout<<"Source: [type, date, activity, identifier] = ["<<type<<", "<<date<<", "<<activity<<", "<<identifier<<"]"<<std::endl;
    return;
}