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
    Source s1("Na-22", "09/03/2026", 24.5, 100);
    Detector d1("Scintillator", false, 50);

    int d1_counts{d1.detect_counts(s1)};

    std::cout<<"Number of counts from detector d1 = "<<d1_counts<<std::endl;

    return 0;
}