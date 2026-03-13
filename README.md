### Kuba Kane
# PHYS30762 Assignment 3 - Practising Classes

> [!IMPORTANT]
> ### Program summary
> This program allows you to define radioactive sources and detectors with certain properties. The sources are also given a unique identifier.
>
> The following classes are defined in this program to handle these properties:
> - **Source**: Gives the radioactive source a type, date of acquistion, specific activity (Bq/kg), mass (kg), and a unique identifier.
> - **Detector**: Gives the source detector a type, status (on or off), efficiency (in detecting a source), and a time (for which it measures).
> - **Date**: An object of this class has a day, month, and year.
>
> Sources can be passed into detectors using the `detect_counts` function from the **Detector** class, which returns how many paticles from the emitted source the detector counts. It is a random number generated from a normal distribution of the mean counts (found by mutliplying a source's specific activity with its mass as well as the detector's efficiency and measurement time). The detector's status must be ON and measurement time greater than 0 in order to produce counts. The sources specified must exist in `valid_sources.txt` (source validation file) which contains the source type and specific activity. The detectors specified must exist in `valid_detectors.txt` (detector validation file) which contains the detector type and efficiency.


## User Guidelines
### Running the program as-is
This code was run on VSC using a Windows 11 device. The compilation line used was `g++ -std=c++17 assignment-3.cpp Source.cpp Detector.cpp Date.cpp -o main.exe`. The program can then be run by calling the file `main.exe`.

### Modifying the program
The guidelines in this section are intended for a user who wishes to create their own main file using the classes defined in this program.

#### Keeping defined sources & detectors (working in main file)
When creating your own sources or detectors, they must be ones which exist in the `valid_sources.txt` or `valid_detectors.txt` files. If the data you enter does not match the data in those files, you will get an error message. Note that the source and detector types are case sensitive so must match exactly with the way they are written in the validation files. The ID is something you can choose to keep track of your sources, and you can specify it when initiating a **Source** object. The source identifier must be unique. See below for the allowed values for the source and detector. 

Source properties:
 | Property      | Limitations |
| ----------- | ----------- |
| Type      | String, spaces permitted       |
| Date of acquisition   | Date in the format `date(DD, MM, YYYY)` |
| Activity (Bq/kg) | Float greater than 0 |
| Mass (kg) | Float greater than 0kg and at most 1mg (1e-6kg) |
| Idenifier | Integer unique to a source |

Detector properties:
 | Property      | Limitations |
| ----------- | ----------- |
| Type      | String, spaces permitted      |
| Status (ON or OFF)   | true (ON) or false (OFF), must be ON to detect counts |
| Efficiency | Float greater than 0 and at most 1 |
| Measurement time (seconds) | Float, min 1 second & max 3600 seconds (1 hour) |

#### Modifying defined sources & detectors
If you wish to enable more types of sources or detectors, you must modify the sources and/or detector validation files with additional rows specifying all of the relevant properties. You can also use your own files, and modify `Source::load_valid_sources(<file_name>)` in the main file with your file name. In the source validation file you can specify the source name as well as its specific activity (Bq/kg), and in the detector validation file you can specify the detector name and its efficiency. Note that in both validation files the values must be seperated by semicolons. If this format is not followed on any given line in the file, the line will be skipped and so will not be interpretted as a valid source or detector. The files may start with a header as long as its on the first line only and starts with `#`.


## Program Limitations
While in reality the efficiency of a detector is not an intrinsic property and depends on the source and its energy, this program assumes that the efficiency is a set property of a given detector. In order to produce more realistic count values from a detector, the mean counts is mutliplied by a geometric factor which takes into account the fact that only a small part of the spherical span of particles emitted from the source are exposed to the detector's surface.

In reality a detector may be able to be left for several hours, but here the detector measurement time is limited to 1 hour so that the run time of the program when calculating the normal distribution from the mean counts is not so large. This also ensures that the mean counts value doesn't go beyond the maximum memory allocated to an integer (specifically, of type long long) in C++.

An improvement to this program could be to allow for a range of detector efficiencies.


## Program Reasoning
### Data validation
 - Originally tried to use "if-else" statements in the **Source** class to print out an error message if the data inputted was invalid. However, the code continued to print out the source object properties, leaving the invalid property blank.
 - Tried to overcome this using `stdexcept` library, which enabled arguments to be raised, which could then be printed out using `.what()` in the main code. This enabled direct print outs to be avoided in the class scripts, but still meant the code continued to be printed out.
 - This was finally overcome by putting the code under `try`, and printing out the error message defined in the class using `catch`. This meant code did not continue to execute if an error was picked up.
 - In order to validate the date input, a separate class was ceated so that the **Source** class did not become overwhelmed with validation checks, and so that it was easier to extract out the day, month and year to perform the checks. It also prevents ambiguity in formatting the date (e.g. British vs American date format, or whether year contains 2 or 4 digits).
 - A lot of errors in code came about because of using private data members when performing validation chedcks inside setters, which are set to 0 until the setter function is completed, instead of the inputted values when an object is declared in the main code (`assignment-3.cpp`).

 ### Unique source identifiers
 - To ensure unique identifiers, the `set` library was used to store all identifiers created by the user in a vector, disallowing any 2 entries to be the same.
 - `static` was also useful here, meaning if the code was re-run, the identifiers would be remembered and so duplicated idenifiers would produce an error.
 - To ensure compilation worked, the set `used_ids` needed to be initialised (with no elements) in the `Source.cpp` file.
 - A lot of errors came about because of using the private data memebers when valudating inputs receieved in setters, instead of the actual input given to the setters.

 ### File validation
 - Having `file.close()` inside of the read_line while loop caused only the first line to be read, and so file closing needed to be moved outside of the while loop.

## Disclosure of Delegation to Generative AI
TBC

## References
The following sources were used in the research for this assignment.

[1] https://www.mirion.com/discover/knowledge-hub/articles/education/gamma-ray-efficiency-calibration-lab-experiment

[2] https://oncologymedicalphysics.com/detection-efficiency-and-dead-time/

[3] https://stackoverflow.com/questions/57025341/how-to-understand-c11-random-number-generator

[4] "Geiger counting", University of Manchester 2nd year lab script

[5] https://ionactive.co.uk/resource-hub/technical-guidance/radiation-safety-data-radioactive/ionactive-radioisotope-data-resource

[6] https://en.wikipedia.org/wiki/Specific_activity

[7] https://cplusplus.com/reference/random/normal_distribution/

[8] https://uwm.edu/safety-health/wp-content/uploads/sites/405/2016/11/BLBK.pdf

[9] https://en.cppreference.com/w/c/chrono/time_t

## TO DO
- Print out map (key--value) if user asks for get_valid_sources() --> or remove function
- Move all setter code to the Source.cpp & Detector.cpp files if its too long
- Find source for detect_counts formula
- Ensure all functions defined in the class are functional - or remove them
- Detector file allows for negative value, and does not check if it matches with user inputted
- Do not allow for duplicate detectors?
- What if whitespace is put infront of source activity in file?
- Not capital senstive?
- Dates need to be defined inside Source.cpp?
- Sometimes file error lets you continue & sometimes stops the program - consistency?