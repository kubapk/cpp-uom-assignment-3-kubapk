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
#include<limits> //to check for maximum variable memory in compiler
#include<string>
#include<sstream> //string stream for reading in lines
#include "Source.h"
#include "Detector.h"
using std::string;


//Member function to produce random detector counts
long long Detector::detect_counts(const Source& source_input) const
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

    if(mean_counts > std::numeric_limits<long long>::max())
    {
        throw std::invalid_argument("Detector cannot generate counts as value is too large to be stored. Ensure detector and source properties"
        " are physically reasonable.");
    }


    std::normal_distribution<double> dist(mean_counts, std::sqrt(mean_counts)); 
    //creates Poisson distribution with expected value = mean_counts and generates integer results
    //around that mean
    //dist is of type double so must be cast to int (long long to allow for longer ints)

    return static_cast<long long>(dist(gen)); //random number produced following normal distribution - fluctuations around mean
}


//Member function to print out detector data
void Detector::print_detector_data() const
{
    std::cout<<"Detector: [type, status, efficiency, measurement time (s)] = "
    "["<<type<<", "<<status<<", "<<efficiency<<", "<<measurement_time<<"]"<<std::endl;

    return;
}


//Create empty map ready to store data from "valid_detectors" file
std::map<string, double> Detector::valid_detectors;


//Member function to load in valid detectors from file
void Detector::load_valid_detectors(const string& detector_file_name)
{
    //Read in detector validation file
    std::ifstream read_file(detector_file_name);

    //Check if file opened correctly
    if(!read_file.good())
    {
        throw std::runtime_error("Detector validation file '"+detector_file_name+"' could not be opened.");
    }

    string line; //string to read in one line from the data file

    while (getline(read_file, line)) //While getline(source, destination) is true, i.e. there is a line to be read
    {
        std::stringstream ss(line); //create string stream called ss and initialise it with "line", i.e. first line in file

        string detector_type;
        string detector_efficiency_str; //later converted to int
        string extra;

        //Try to read detector type & efficiency with semicolon separation
        //getline(input stream, string to put date int, delimiter character)
        if(!getline(ss, detector_type, ';') || !getline(ss, detector_efficiency_str))
        {
            std::cout << "TYPE: {" << detector_type << "} "
            << "EFF: {" << detector_efficiency_str << "}\n";

            std::cerr<<"  The line {"<<line<<"} in detector validation file is incorrectly formatted."<<std::endl;
            continue; //skip rest of current iteration and move to the next one (ignore line)
        }

        double detector_efficiency{std::stod(detector_efficiency_str)}; //convert efficiency into double
        valid_detectors[detector_type] = detector_efficiency;

        //Check no extra characters in file
        if(!(ss >> detector_efficiency) || (ss >> extra))
        {
            std::cerr << "Invalid efficiency in line {" << line << "}.\n";
            continue;
        }


        //Check efficiency range is valid
        if(detector_efficiency < 0 || detector_efficiency > 1) //disallows efficiency not in [0, 1]
        {
            throw std::invalid_argument("Efficiency in line {"+line+"} of detector validation file is not between 0 and 1. Efficiency must be"
            "between 0 and 1 inclusive."); //does not allow program to continue
        }
    }

}