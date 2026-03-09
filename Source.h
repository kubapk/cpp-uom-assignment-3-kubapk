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
using std::string;

class Source
{
private:
    string type{}; //radioactive source element
    string date{}; //date of source acquisition
    double activity{}; //source activity at time of acquisition, in Bq/kg
    int identifier{}; //unique number to identify the source

public:
    //Default constructor
    Source() = default;

    //Paramterised constructor
    Source(string type_in, string date_in, double activity_in, int identifier_in) : 
    type{type_in}, date{date_in}, activity{activity_in}, identifier{identifier_in} {}

    //Destructor
    ~Source() {std::cout<<"Destroying source"<<std::endl;}

    //Setters
    void set_type(const string type_in) {type = type_in;}
    void set_date(const string date_in) {date = date_in;}
    void set_activity(const double activity_in) {activity = activity_in;}
    void set_identifier(const int identifier_in) {identifier = identifier_in;}

    //Getters
    string get_type() const {return type;}
    string get_date() const {return date;}
    double get_activity() const {return activity;}
    int get_identifier() const {return identifier;}

    //Prototyping member functions
    void print_source_data() const;
};

#endif //if source_h is already defined, everything between #ifndef and #endif is skipped