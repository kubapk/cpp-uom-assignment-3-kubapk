/*
____________________________________________
RADIOACTIVE DETECTOR CLASS
(Part of PHYS30762 Assignment 3)
____________________________________________
This header file defines a class for a radioactive detector.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
Last updated on XXX XX Mar 2026
*/

//Include gaurd
#ifndef SOURCE_H
#define SOURCE_H

#include<iostream>
#include<string>
#include<cmath>
using std::string;

class Source
{
private:
    string type{}; //type of detector being used
    bool status{}; //whether detector is on or off
    size_t counts{}; //number of counts detected from source

public:
    //
};

#endif //if detector_h is already defined, everything between #ifndef and #endif is skipped