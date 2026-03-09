/*
____________________________________________
RADIOACTIVE DETECTOR MEMBER FUNCTIONS
(Part of PHYS30762 Assignment 3)
____________________________________________
This implementation file defines member function for the "Detector" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
Last updated on XXX XX Mar 2026
*/

#include<iostream>
#include<cstdlib> //to generate random numbers
#include "Source.h"
#include "Detector.h"

size_t Detector::detect_counts(const Source source_input) const
{
    if(!status) return 0; //if status is false (i.e. detector is off)

    //If detector is on:
    srand(time(0)); //change random number seed each time program is ran
    size_t random_num{1 + rand() % 100}; //random number between 1 and 100

    return random_num
}