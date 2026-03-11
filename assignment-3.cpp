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
#include<vector>
#include "Source.h"
#include "Detector.h"
using std::vector;

int main()
{
    try
    {
        vector<Source> sources; //empty vector of "Source" objects

        Date date1(8, 3, 2026);
        Date date2(9, 3, 2026);
        Date date3(10, 3, 2026);

        //Add sources to vector
        sources.push_back(Source("Na-22", date1, 24.5, 10001));
        sources.push_back(Source("Cs-136", date2, 34.5, 10002));
        sources.push_back(Source("Co-92", date3, 44.5, 10003));

        //Define detector
        Detector d1("Scintillator", true, 0.1, 10);
        std::cout<<"NEW DETECTOR CREATED"<<std::endl;
        d1.print_detector_data();
        std::cout<<"\nSOURCE DATA"<<std::endl;
        
        //Print out source data and detector counts for all sources
        for(size_t i{}; i<sources.size(); i++)
        {
            sources[i].print_source_data();
            int d1_counts{d1.detect_counts(sources[i])};
            std::cout<<"Number of counts from "<<d1.get_type()<<" detector = " <<d1_counts<<"\n"<<std::endl;
        }

    }
    catch(const std::exception& e)
    {
        std::cout<<"Error: "<<e.what()<<std::endl;
        return 1;
    }

    return 0;
}