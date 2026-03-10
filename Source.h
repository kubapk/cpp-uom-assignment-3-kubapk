/*
____________________________________________
RADIOACTIVE SOURCE CLASS
(Part of PHYS30762 Assignment 3)
____________________________________________
This header file defines a class for a radioactive source.

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
#include <stdexcept> //to report errors
#include "Date.h"
using std::string;

class Source
{
private:
    string type{}; //radioactive source element
    string date_acquisition{}; //date of source acquisition
    double activity{}; //source activity at time of acquisition, in Bq/kg
    int identifier{}; //unique number to identify the source

public:
    //Default constructor
    Source() = default;

    //Paramterised constructor
    Source(string type_in, string date_in, double activity_in, int identifier_in)
    {
        set_type(type_in);
        set_date(date_in);
        set_activity(activity_in);
        set_identifier(identifier_in);
    } 

    //Destructor
    ~Source() {std::cout<<"Destroying source"<<std::endl;}

    //Setters
    void set_type(const string type_in) 
    {
        if(!(type_in == "Na-22" || type_in == "Cs-136" || type_in == "Co-92"))
        {
            throw std::invalid_argument("Source type must be either Na-22, Cs-136, or Co-92.");
        }

        type = type_in;
    
    }
    void set_date(const string date_in) {date_acquisition = date_in;}

    void set_activity(const double activity_in)
    {
        if(activity_in < 0)
        {
            throw std::invalid_argument("Activity must be a positive number.");
        }

        activity = activity_in;
    
    }

    void set_identifier(const int identifier_in)
    {
        if(identifier_in < 0)
        {
            throw std::invalid_argument("ID of source must be a positive number.");
        }

        identifier = identifier_in;
    
    }

    //Getters
    string get_type() const {return type;}
    string get_date() const {return date_acquisition;}
    double get_activity() const {return activity;}
    int get_identifier() const {return identifier;}

    //Prototyping member functions
    void print_source_data() const;
};

#endif //if source_h is already defined, everything between #ifndef and #endif is skipped