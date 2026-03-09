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
#ifndef DETECTOR_H
#define DETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include "Source.h"
using std::string;

class Detector
{
private:
    string type{}; //type of detector being used
    bool status{}; //whether detector is on or off (true = on)
    size_t counts{}; //number of counts detected from source

public:
    //Default constructor
    Detector() = default;

    //Paramterised constructor
    Detector(string type_in, bool status_in, size_t counts_in) : 
    type{type_in}, status{status_in}, counts{counts_in} {}

    //Destructor
    ~Detector() {std::cout<<"Destroying detector"<<std::endl;}

    //Setters
    void set_type(const string type_in) {type = type_in;}
    void set_status(const bool status_in) {status = status_in;}
    void set_counts(const size_t counts_in) {counts = counts_in;}

    //Getters
    string get_type() const {return type;}
    bool get_status() const {return status;}
    int get_counts() const {return counts;}

    //Prototyping member functions
    int detect_counts(const Source source_in) const;
};

#endif //if detector_h is already defined, everything between #ifndef and #endif is skipped