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
    //Initiate 1 source and 1 detector
    /*
    Source s1{};
    try
    {
        Source s1("Na-221", "12/11/2003", 24.5, 100);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    */

    Source s1("Na-221", "12/11/2003", 24.5, 100);
    Detector d1("Scintillator", true, 50);

    //Print out source data
    s1.print_source_data();

    //Print detector counts
    int d1_counts{d1.detect_counts(s1)};
    std::cout<<"Number of counts from detector d1 = "<<d1_counts<<std::endl;

    return 0;
}