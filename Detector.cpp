/*
____________________________________________
RADIOACTIVE DETECTOR MEMBER FUNCTIONS
(Part of PHYS30762 Assignment 3)
____________________________________________
This implementation file defines member function for the "Detector" class.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
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


//SETTERS
//Setter for type and efficiency
void Detector::set_type_efficiency(const string type_in, const double efficiency_in)
{
    auto iterator = valid_detectors.find(type_in); //pointer to inputted element in map

    if(iterator == valid_detectors.end()) //if type_in does not exist in detector validation file
    //i.e. if the iterator reaches the end it has not found type_in in the map
    {
        throw std::invalid_argument(type_in+" is not a valid detector type (from detector validation file).");
    }

    //Check efficiency matches detector efficiency
    double expected = iterator->second; //returns efficiency value in detector validation file corrresponding 
    //to type_in
    double relative_error = std::abs(efficiency_in - expected) / expected; //finds percentage difference in
    //inputted efficiency and corresponding efficiency in the file
    if(relative_error > 0.05) //if efficiency_in does not match detector type in detector validation file up to 5% tolerance
    {
        throw std::invalid_argument("Efficiency "+std::to_string(efficiency_in)+" does not match the efficiency for the "+type_in+
        " detector, as specified in detector validation file.");
    }

    type = type_in;
    efficiency = efficiency_in;
}


//Setter for measurement time
void Detector::set_measurement_time(const double measurement_time_in)
{
    if(!status) //works as long as status is set before measurement_time
    {
        throw std::invalid_argument("Cannot set measurement time for "+type+" detector whose status if OFF.");
    }

    if(measurement_time_in < 1 || measurement_time_in > 3600)
    {
        throw std::invalid_argument("Measurement time for "+type+" detector is invalid. Must be between 1 and 3600 seconds (1 hour).");
    }

    measurement_time = measurement_time_in;
}


//MEMBER FUNCTIONS
//Member function to produce random detector counts
long long Detector::detect_counts(const Source& source_input) const
{
    if(!status) return 0; //if status is false (i.e. detector is off)

    //If detector is on:
    static std::random_device rdm; //generates varying (random) seed "rdm" for random number
    static std::mt19937 gen(rdm()); //Mersenne Twister random number generator creates random number "gen" 
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
        throw std::invalid_argument("Detector cannot generate counts as value is too large to be stored."
        "Ensure detector and source properties are physically reasonable.");
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
    std::cout<<"Detector: [type, status (0=off, 1=on), efficiency, measurement time (s)] = "
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

    while(std::getline(read_file, line)) //While getline(source, destination) is true, i.e. there is a line to be read
    {
        //Ignore blank lines or header lines
        if(line.empty() || line[0] == '#') {continue;}

        std::stringstream ss(line); //create string stream called ss and initialise it with "line", i.e. first line in file
        string detector_type;
        string detector_efficiency_str; //string to use in string stream

        //Try to read detector type & efficiency with semicolon separation
        if(!std::getline(ss, detector_type, ';') || !std::getline(ss, detector_efficiency_str))
        {
            std::cerr<<"Detector validation file error: The line {"<<line<<"} is incorrectly formatted."
            " Line will not contribute to valid detectors."<<std::endl;
            continue; //skip rest of current iteration and move to the next one (ignore line)
        }

        //Ignore lines with blank dector_type
        if(detector_type.empty())
        {
            std::cerr<<"Detector validation file error: The line {"<<line<<"} contains a blank detector type."
            " Line will not contriute to valid detectors."<<std::endl;
            continue; 
        }

        //Ignore lines with extra characters after detector_efficiency
        string extra;
        double detector_efficiency; //converts efficiency to double

        std::stringstream efficiency_stream(detector_efficiency_str); //create new stream to check after efficiency
        if(!(efficiency_stream >> detector_efficiency) || (efficiency_stream >> extra))
        //returns true if it cannot extract double from detector_efficiency, or if it can extract more characters after 
        //reading efficiency
        {
            std::cerr<<"Detector validation file error: Invalid characters found in line {"<<line<<"}."
            " Line will not contribute to valid detectors."<<std::endl;
            continue;
        }

        //Add file line to map if it passes the if statements above
        valid_detectors[detector_type] = detector_efficiency;

        //Check efficiency range is valid
        if(detector_efficiency <= 0 || detector_efficiency > 1) //disallows efficiency not in (0, 1]
        {
            throw std::invalid_argument("Efficiency in line {"+line+"} of detector validation file is invalid. Efficiency must be"
            " greater than 0 and at most 1."); //does not allow program to continue
        }
    }

    read_file.close();
}