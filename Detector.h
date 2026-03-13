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
    void set_type_efficiency(const string type_in, const double efficiency_in)
    {
        auto iterator = valid_detectors.find(type_in); //pointer to inputted element in map

        if(iterator == valid_detectors.end()) //if type_in does not exist in detector validation file
        //i.e. if the iterator reaches the end it has not found type_in in the map
        {
            throw std::invalid_argument(type_in+" is not a valid detector type (from detector validation file).");
        }

        double expected = iterator->second; //returns efficiency value in detector validation file corrresponding 
        //to type_in
        double relative_error = std::abs(efficiency_in - expected) / expected; //finds percentage difference in
        //inputted efficiency and corresponding efficiency in the file

        if(efficiency_in < 0 || efficiency_in > 1) //disallows efficiency not in [0, 1], even if in detector 
        //validation file
        {
            throw std::invalid_argument("Efficiency for detector "+type_in+" is not between 0 and 1. Efficiency must be"
            "between 0 and 1 inclusive.");
        }
        if(relative_error > 0.05) //if efficiency_in does not match detector type in detector validation file up to 5% tolerance
        {
            throw std::invalid_argument("Efficiency "+std::to_string(efficiency_in)+" does not match detector type "+type_in+
            ", as specified in detector validation file.");
        }

        type = type_in;
        efficiency = efficiency_in;
    }

    void set_status(const bool status_in) {status = status_in;}

    void set_measurement_time(const double measurement_time_in)
    {
        if(!status) //works as long as status is set before measurement_time
        {
            throw std::invalid_argument("Cannot set measurement time for "+type+" detector whose status if OFF.");
        }

        if(measurement_time_in < 1 || measurement_time_in > 3600)
        {
            throw std::invalid_argument("Detector measurement time must be between 1 and 3600 seconds (1 hour).");
        }

        measurement_time = measurement_time_in;
    }

    //Getters
    string get_type() const {return type;}
    bool get_status() const {return status;}
    double get_efficiency() const {return efficiency;}
    double get_measurement_time() const {return measurement_time;}

    //Prototyping member functions
    long long detect_counts(const Source& source_in) const; //type allows for larger number of counts
    void print_detector_data() const;
    static void load_valid_detectors(const string& detector_file_name);
};

#endif //if detector_h is already defined, everything between #ifndef and #endif is skipped