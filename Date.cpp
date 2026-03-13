/*
____________________________________________
DATE MEMBER FUNCTIONS
(Part of PHYS30762 Assignment 3)
____________________________________________
This implementation file defines member function for the "Date" class,
which checks that the date is a valid input.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
*/

#include<iostream>
#include "Date.h"


//Member function to check date is valid
bool Date::is_valid_date() const
{
    //Check if year is valid
    if(year < 1000 || year > 3000) {return false;}

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


bool Date::is_past_date() const
{
    std::time_t current_time{std::time(nullptr)}; //"current_time" of type "time_t" stores number of 
    //seconds since 1 January 1970, "nullptr" prevents unecessary storage of pointer
    std::tm* now{std::localtime(&current_time)};
    //tm is a structure holding calendar (human-readable) sec, min, hour, day of month, month of year,...
    //localtime() converts time of type "time_t" into human-readable form of type "tm"
    //"now" is a pointer to "tm" object, and we can call each element of it

    //Dereference now and call each member of its call
    int current_day{(*now).tm_mday};
    int current_month{(*now).tm_mon + 1}; //Jan = 0, Feb = 1
    int current_year{(*now).tm_year + 1900}; //year given since 1900

    //Check if input date is less than or equal to today's date
    if(year < current_year) {return true;} //any date which is in past year is in past
    if(year == current_year && month < current_month) {return true;} //any date which is in current year but in past month is in past
    if(year == current_year && month == current_month && day <= current_day) 
    {return true;} //allows for today's date

    return false;
}


//Friend function to print out date (overloading operator "<<")
std::ostream& operator<<(std::ostream &os, const Date &date)
{
    os <<date.day<<"/"<<date.month<<"/"<<date.year;

    return os;
}

