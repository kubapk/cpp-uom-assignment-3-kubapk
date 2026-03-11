### Kuba Kane
# PHYS30762 Assignment 3 - Practising Classes

> [!IMPORTANT]
> ### PROGRAM SUMMARY
> This program allows you to define radioactive sources with certain properties (and unique identifiers), as well as a detector with certain properties. Sources can be passed into detectors using the `detect_counts` function from the class, which gives a random source count generated from a Poisson distribution of the properties of the source.
>
> The classes defined in this program are:
> - `Source`: Gives the radioactive source a type, date of acquistion, activity (Bq/kg), and a unique identifier.
> - `Detector`: Gives the source detector a type, status (on or off), efficiency (in detecting a source), and a time (for which it measures).
> - `Date`: Allows objects contain a day, month and year printed in the format DD/MM/YYYY.


## User Guidelines
### Compilation Guidelines
This code was run on VSC using a Windows 11 device. The compilation line used was `g++ -std=c++17 assignment-3.cpp Source.cpp Detector.cpp Date.cpp -o main.exe`. The program can then be run by calling the file `main.exe`.

### Class Guidelines
This guidelines are intended for a user who wishes to build their own code using the classes in this project.
Note that date format should follow the British format, DD/MM/YYYY.
When creating your own sources or detectors, they must be ones which exist in the valid_sources or valid_detector files. If the data you enter does not match the data in those files, you will get an error message. The ID is something you can choose to keep track of your sources. If you wish to enable more types of sources or detectors, you must modify the valid_sources or valid_detectors files with additional rows specifying all of the relevant properties.

## Program Reasoning
### Data validation
 - Originally tried to use "if-else" statements in the `Source` class to print out an error message if the data inputted was invalid. However, the code continued to print out the source object properties, leaving the invalid property blank.
 - Tried to overcome this using `stdexcept` library, which enabled arguments to be raised, which could then be printed out using `.what()` in the main code. This enabled direct print outs to be avoided in the class scripts, but still meant the code continued to be printed out.
 - This was finally overcome by putting the code under `try`, and printing out the error message defined in the class using `catch`. This meant code did not continue to execute if an error was picked up.
 - In order to validate the date input, a separate class was ceated so that the `Source` class did not become overwhelmed with validation checks, and so that it was easier to extract out the day, month and year to perform the checks. It also prevents ambiguity in formatting the date (e.g. British vs American date format, or whether year contains 2 or 4 digits).

 ### Unique source identifiers
 - To ensure unique identifiers, the `set` library was used to store all identifiers created by the user in a vector, disallowing any 2 entries to be the same.
 - `static` was also useful here, meaning if the code was re-run, the identifiers would be remembered and so duplicated idenifiers would produce an error.
 - To ensure compilation worked, the set `used_ids` needed to be initialised (with no elements) in the `Source.cpp` file.



## Disclosure of Delegation to Generative AI
TBC

## Sources of information
The following sources were used in the research for this assignment.

[1] https://www.mirion.com/discover/knowledge-hub/articles/education/gamma-ray-efficiency-calibration-lab-experiment

[2] https://oncologymedicalphysics.com/detection-efficiency-and-dead-time/

[3] https://stackoverflow.com/questions/57025341/how-to-understand-c11-random-number-generator

[4] "Geiger counting", University of Manchester 2nd year lab script

[5] https://ionactive.co.uk/resource-hub/technical-guidance/radiation-safety-data-radioactive/ionactive-radioisotope-data-resource

[6] https://en.wikipedia.org/wiki/Specific_activity