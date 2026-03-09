/*
____________________________________________
DATE INPUT VALIDATION CLASS
(Part of PHYS30762 Assignment 3)
____________________________________________
This header file defines a class to check that a date object produces a valid
date.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
Last updated on XXX XX Mar 2026
*/

class Date
{
private:
    int day{};
    int month{};
    int year{};

public:
    //Default constructor
    Date() = default;

    //Paramterised constructor
    Date(int d, int m, int y) : day{d}, month{m}, year{y} {}

    //Destructor
    ~Date() = default;

    //Setter
    void set_date(const int d, const int m, const int y) 
    {
        day = d;
        month = m;
        year = y;
    }

    //Getters
    int get_day() const {return day;}
    int get_month() const {return month;}
    int get_year() const {return year;}

    //Prototyping member functions
    bool is_valid_past_date() const;

};