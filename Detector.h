/*
____________________________________________
RADIOACTIVE DETECTOR CLASS
(Part of PHYS30762 Assignment 3)
____________________________________________
This header file defines a class for a radioactive detector.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
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
    double measurement_time{}; //time detector is on, seconds

    static std::map<string, double> valid_detectors; 
    //map "valid_detectors" with string (detector type) as key and double as value (detector efficiency)

public:
    //Default constructor
    Detector() = default;

    //Paramterised constructor
    Detector(string type_in, bool status_in, double efficiency_in, double measurement_time_in)
    {
        set_type_efficiency(type_in, efficiency_in);
        set_status(status_in);
        set_measurement_time(measurement_time_in);
    }

    //Destructor
    ~Detector() = default;

    //Setters
    void set_type_efficiency(const string type_in, const double efficiency_in);
    void set_status(const bool status_in) {status = status_in;}
    void set_measurement_time(const double measurement_time_in);

    //Getters
    string get_type() const {return type;}
    bool get_status() const {return status;}
    double get_efficiency() const {return efficiency;}
    double get_measurement_time() const {return measurement_time;}

    //Prototyping member functions
    long long detect_counts(const Source& source_in) const; //type allows for larger number of counts
    void print_detector_data() const;
};

#endif //if detector_h is already defined, everything between #ifndef and #endif is skipped