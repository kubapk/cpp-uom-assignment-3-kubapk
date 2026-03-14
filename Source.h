/*
____________________________________________
RADIOACTIVE SOURCE CLASS
(Part of PHYS30762 Assignment 3)
____________________________________________
This header file defines a class for a radioactive source.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
*/

//Include gaurd
#ifndef SOURCE_H
#define SOURCE_H

#include<iostream>
#include<string>
#include<cmath>
#include<stdexcept> //to report errors
#include<set> //to store a vector of unique numbers
#include<map> //to store key--value pairs
#include "Date.h"
using std::string;

class Source
{
private:
    string type{}; //radioactive source element
    Date date_acquisition{}; //date of source acquisition
    double activity{}; //source activity at time of acquisition, in Bq/kg
    double mass{}; //mass of source element used, in kg
    int identifier{}; //unique number to identify the source

    static std::set<int> used_ids; //identifiers previously used
    static std::map<string, double> valid_sources; 
    //map "valid_sources" with string (source type) as key and double as value (activity)

public:
    //Default constructor
    Source() = default;

    //Paramterised constructor
    Source(string type_in, Date date_in, double activity_in, int identifier_in, double mass_in)
    {
        set_type_activity(type_in, activity_in);
        set_date(date_in);
        set_identifier(identifier_in);
        set_mass(mass_in);
    } 

    //Destructor
    ~Source() = default;

    //Setters
    void set_type_activity(const string type_in, const double activity_in);
    void set_date(const Date date_in);
    void set_identifier(const int identifier_in);
    void set_mass(const double mass_in);

    //Getters
    string get_type() const {return type;}
    Date get_date() const {return date_acquisition;}
    double get_activity() const {return activity;}
    int get_identifier() const {return identifier;}
    double get_mass() const {return mass;}

    //Prototyping member functions
    void print_source_data() const;
    static void load_valid_sources(const string& source_file_name); //file name passed by reference
};

#endif //if source_h is already defined, everything between #ifndef and #endif is skipped