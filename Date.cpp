/*
____________________________________________
DATE MEMBER FUNCTIONS
(Part of PHYS30762 Assignment 3)
____________________________________________
This implementation file defines member function for the "Date" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
Last updated on XXX XX Mar 2026
*/

#include<iostream>
#include "Date.h"

bool Date::is_valid_past_date() const
{
    //Check if month is valid
    if(month < 1 || month > 12) {return false;}

    //Check day is valid
    if(day < 1 || day > 31) {return false;}

    //Check for months which have 30 days
    if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {return false;}

    //Check for leap year
    if(month == 2)
    {
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) //if year is leap year
            if(day > 29)
                return false;
        else
            if(day > 28)
                return false;
    }

    //If none of the conditions above apply:
    return true;
}


std::ostream& operator<<(std::ostream &os, const Date &date)
{
    os <<date.day<<"/"<<date.month<<"/"<<date.year;

    return os;
}

