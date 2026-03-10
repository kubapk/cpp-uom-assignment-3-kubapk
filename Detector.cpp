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
#include<random> //to generate random numbers
#include "Source.h"
#include "Detector.h"

int Detector::detect_counts(const Source source_input) const
{
    if(!status) return 0; //if status is false (i.e. detector is off)

    //If detector is on:
    static std::random_device rdm; //generates varying (random) seed "rdm" for random number
    static std::mt19937 gen(rdm()); //Mersenne Twister random number generator created random number "gen" 
    //using the seed "rdm"
    //static ensures that if the function is called again, it generates a new seed following the sequence
    //of rdm, instead of using the first seed each time the function is called

    double activity{source_input.get_activity()}; //gets activity from source
    double mean_counts{activity * efficiency * measurement_time}; //assuming even distribution over time

    std::poisson_distribution<int> dist(mean_counts); 
    //creates Poisson distribution with expected value = mean_counts and generates integer results
    //around that mean

    return dist(gen); //random number produced following Poisson distribution - fluctuations around mean
}