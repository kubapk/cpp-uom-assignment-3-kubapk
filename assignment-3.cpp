/*
________________TITLE_______________________
PHYS30762 Assignment 3 - Practising Classes
____________________________________________
This C++ script...

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
Last updated on XXX XX Mar 2026
*/

#include<iostream>
#include<string>
#include<cmath>
#include "Source.h"
#include "Detector.h"

int main()
{
    try
    {
        Source s1("Na-22", "12/11/2003", 24.5, 100);
        Detector d1("Scintillator", true, 50);

        //Print out source data
        s1.print_source_data();

        //Print detector counts
        int d1_counts{d1.detect_counts(s1)};
        std::cout<<"Number of counts from detector d1 = "<<d1_counts<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}