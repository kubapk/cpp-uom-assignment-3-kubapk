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
#include <set> //to store a vector of unique numbers
#include <map> //to store key--value pairs
#include "Date.h"
using std::string;

class Source
{
private:
    string type{}; //radioactive source element
    Date date_acquisition{}; //date of source acquisition
    double activity{}; //source activity at time of acquisition, in Bq/kg
    int identifier{}; //unique number to identify the source

    static std::set<int> used_ids; //identifiers previously used
    static std::map<string, double> valid_sources; 
    //map "valid_sources" with string (source type) as key and double as value (activity)

public:
    //Default constructor
    Source() = default;

    //Paramterised constructor
    Source(string type_in, Date date_in, double activity_in, int identifier_in)
    {
        set_type_activity(type_in, activity_in);
        set_date(date_in);
        set_identifier(identifier_in);
    } 

    //Destructor
    ~Source() = default;

    //Setters
    void set_type_activity(const string type_in, const double activity_in)
    {
        auto iterator = valid_sources.find(type_in); //pointer to element in map

        if(iterator == valid_sources.end()) //if type_in does not exist in list
        //i.e. if the iterator reaches the end it has not found type_in in the map
        {
            throw std::invalid_argument(type_in+" is not a valid source type (from list).");
        }

        double expected = iterator->second; //activity value in list corrresponding to type_in
        double relative_error = std::abs(activity - expected) / expected;

        if(relative_error > 0.05) //if activity does not match source type in list up to 5% tolerance
        {
            throw std::invalid_argument("Activity "+std::to_string(activity_in)+" does not match source type " + type_in);
        }
        if(activity_in < 0)
        {
            throw std::invalid_argument("Activity "+std::to_string(activity_in)+" must be a positive number.");
        }

        type = type_in;
        activity = activity_in;

    }

    void set_date(const Date date_in)
    {
        if(!date_in.is_valid_past_date())
        {
            throw std::invalid_argument("Date is not valid. Ensure format is DD/MM/YYYY.");
        }

        date_acquisition = date_in;
    }

    void set_identifier(const int identifier_in)
    {
        if(identifier_in < 0)
        {
            throw std::invalid_argument("ID of source must be a positive number.");
        }
        if(used_ids.count(identifier_in) !=0) //returns 0 if idenifier_in appears 0 times in used_ids
        {
            throw std::invalid_argument("A source ID has been used twice.");
        }

        identifier = identifier_in;
        used_ids.insert(identifier_in);
    }

    //Getters
    string get_type() const {return type;}
    Date get_date() const {return date_acquisition;}
    double get_activity() const {return activity;}
    int get_identifier() const {return identifier;}
    static std::set<int> get_used_ids() {return used_ids;}

    //Prototyping member functions
    void print_source_data() const;
    static void load_valid_sources(const string file_name);
};

#endif //if source_h is already defined, everything between #ifndef and #endif is skipped