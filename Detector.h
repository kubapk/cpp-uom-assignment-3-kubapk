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
    double efficiency{}; //efficiency of detector (0 - 1)
    double measurement_time{}; //time detector is on

public:
    //Default constructor
    Detector() = default;

    //Paramterised constructor
    Detector(string type_in, bool status_in, double efficiency_in, double measurement_time_in)
    {
        set_type(type_in);
        set_status(status_in);
        set_efficiency(efficiency_in);
        set_measurement_time(measurement_time_in);
    }

    //Destructor
    ~Detector() {std::cout<<"Destroying detector"<<std::endl;}

    //Setters
    void set_type(const string type_in)
    {
        if(!(type_in == "Scintillator" || type_in == "Geiger" || type_in == "Germanium detector"))
        {
            throw std::invalid_argument("Detector type must be either Scintillator, Geiger, or Germanium detector.");
        }

        type = type_in;
    
    }

    void set_status(const bool status_in) {status = status_in;}

    void set_efficiency(const double efficiency_in) 
    {
        if(efficiency_in < 0 || efficiency_in > 1)
        {
            throw std::invalid_argument("Efficiency must be between 0 and 1.");
        }

        efficiency = efficiency_in;
    }

    void set_measurement_time(const double measurement_time_in)
    {
        if(measurement_time_in < 0)
        {
            throw std::invalid_argument("Detector measurement time must be positive.");
        }

        measurement_time = measurement_time_in;
    }

    //Getters
    string get_type() const {return type;}
    bool get_status() const {return status;}
    double get_efficiency() const {return efficiency;}
    double get_measurement_time() const {return measurement_time;}

    //Prototyping member functions
    int detect_counts(const Source source_in) const;
};

#endif //if detector_h is already defined, everything between #ifndef and #endif is skipped