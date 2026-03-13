/*
________________TITLE_______________________
PHYS30762 Assignment 3 - Practising Classes
____________________________________________
This C++ script initialises 3 types of sources using the Source class, and 
also intialises 1 detector from the Detector class. It then uses the 
detect_counts member function of Detector class to find number of counts
detected by the detector for each of the 3 sources.

Created by Kuba Kane (ID: 11019699)
Created on Mon 9 Mar 2026
*/

#include<iostream>
#include<vector>
#include "Source.h"
#include "Detector.h"
using std::vector;

int main()
{
    try
    {
        //Print line to show program is starting
        std::cout<<"\n----------------------------------------------"<<std::endl;

        //Load in the files with valid sources & detectors into the maps
        Source::load_valid_sources("valid_sources.txt");
        Detector::load_valid_detectors("valid_detectors.txt");

        //Create empty vector of "Source" objects
        vector<Source> sources; 

        Date date1(8, 3, 2026);
        Date date2(9, 3, 2026);
        Date date3(12, 3, 2026);

        //Add sources to vector
        sources.push_back(Source("Na-22", date1, 2.31e17, 10003, 1e-6));
        sources.push_back(Source("F-18", date2, 3.52e21, 10002, 1e-9));
        sources.push_back(Source("Co-92", date3, 4.2e16, 10004, 1e-9));

        //Define detector
        Detector d1("Ionisation Chamber", true, 0.15, 10);
        std::cout<<"NEW DETECTOR CREATED"<<std::endl;
        d1.print_detector_data();
        std::cout<<"\nSOURCE DATA"<<std::endl;
        
        //Print out source data and detector counts for all sources
        for(size_t i{}; i<sources.size(); i++)
        {
            sources[i].print_source_data();

            long long d1_counts{d1.detect_counts(sources[i])};
            std::cout<<"Number of counts from "<<d1.get_type()<<" detector in "
            <<d1.get_measurement_time()<<"s = " <<d1_counts<<"\n"<<std::endl;
        }

        //Print line to show program has ended
        std::cout<<"----------------------------------------------\n"<<std::endl;

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;

        //Print line to show program has ended
        std::cout<<"----------------------------------------------\n"<<std::endl;
        return 1;
    }

    return 0;
}