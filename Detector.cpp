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
#include<fstream> //for files
#include "Source.h"
#include "Detector.h"


//Member function to produce random detector counts
int Detector::detect_counts(const Source& source_input) const
{
    if(!status) return 0; //if status is false (i.e. detector is off)

    //If detector is on:
    static std::random_device rdm; //generates varying (random) seed "rdm" for random number
    static std::mt19937 gen(rdm()); //Mersenne Twister random number generator created random number "gen" 
    //using the seed "rdm"
    //static ensures that if the function is called again, it generates a new seed following the sequence
    //of rdm, instead of using the first seed each time the function is called

    double geometry_factor{1e-6}; //Radioactive sources emit radiation isotropically, this takes into account
    //fraction of detector area to surface area of a sphere
    double activity{source_input.get_activity()}; //gets activity from source
    double mass{source_input.get_mass()}; //gets mass from source
    double mean_counts{activity * mass * efficiency * geometry_factor * measurement_time}; //assuming even distribution over time

    std::normal_distribution<double> dist(mean_counts, std::sqrt(mean_counts)); 
    //creates Poisson distribution with expected value = mean_counts and generates integer results
    //around that mean

    return dist(gen); //random number produced following Poisson distribution - fluctuations around mean
}


//Member function to print out detector data
void Detector::print_detector_data() const
{
    std::cout<<"Detector: [type, status, efficiency, measurement time (s), ] = "
    "["<<type<<", "<<status<<", "<<efficiency<<", "<<measurement_time<<"]"<<std::endl;

    return;
}


//Create empty map ready to store data from "valid_detectors" file
std::map<string, double> Detector::valid_detectors;


//Member function to load in valid detectors from file
void Detector::load_valid_detectors(const string detector_file_name)
{
    std::ifstream read_file(detector_file_name);

    string detector_type;
    double detector_efficiency;

    while(read_file >> detector_type >> detector_efficiency)
    //read_file is sent to detector type (the first thing it reads)
    //2nd thing read_file reads is then sent to detector_efficiency
    {
        valid_detectors[detector_type] = detector_efficiency;
        //sets detector_type to be key and detector_efficiency to be value
    }
}