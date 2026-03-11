### Kuba Kane
# PHYS30762 Assignment 3 - Practising Classes

> [!NOTE]
> This program allows you to define radioactive sources with certain properties (and unique identifiers), as well as a detector with certain properties. Sources can be passed into detectors using the `detect_counts` function from the class. 


## User Guidelines
### Compilation Guidelines
The source file is `assignment-2.cpp`. This code was run on VSC using a Windows 11 device. The compilation line used was `g++ -std=c++17 assignment-3.cpp Source.cpp Detector.cpp Date.cpp -o main.exe`. The program can then be run by calling the file `main.exe`

### Class Guidelines
This guidelines are intended for a user who wishes to build their own code using the classes in this project.
Note that date format should follow the British format, DD/MM/YYYY.

## Program Reasoning
### Data validation
 - Originally tried to use "if-else" statements in the `Source` class to print out an error message if the data inputted was invalid. However, the code continued to print out the source object properties, leaving the invalid property blank.
 - Tried to overcome this using...


## Disclosure of Delegation to Generative AI
TBC

## Sources of information
The following sources were used in the research for this assignment.

[1] https://www.mirion.com/discover/knowledge-hub/articles/education/gamma-ray-efficiency-calibration-lab-experiment

[2] https://oncologymedicalphysics.com/detection-efficiency-and-dead-time/

[3] https://stackoverflow.com/questions/57025341/how-to-understand-c11-random-number-generator

[4] "Geiger counting", University of Manchester 2nd year lab script