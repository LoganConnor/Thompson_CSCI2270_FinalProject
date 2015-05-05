# Thompson_CSCI2270_FinalProject
Final Project for CSCI2270 - Data Structures, Spring 2015, University of Colorado Boulder

Project Summary:

We made an electric car trip planner. The user chooses their electric car (from the 10 models currently on the market) and their desired starting and ending cities (from a select list of major U.S. cities). The program then outputs two possible paths: the least number of cities and the shortest distance. It lists all the cities, in order of when the user would pass through them, for both paths. For the shortest distance path, it also outputs the number of miles and how many charges the particular car model would need to get there.

How to Run:

Clone the GitHub repository to your local computer, making sure everything is in the same file, and compile Graph.cpp and main.cpp. Then run the program. It will display a menu with four options:
1. Plan a trip,
2. Print city choices,
3. Print graph,
4. Quit.
Type the number of your choosing and hit Enter. For choices 2 and 3, information will simply be displayed and the menu will be re-presented to you. For choice 1, you will be given a numbered list of the ten current electric car models on the market and prompted for the number of your car. Once you give that information, the program will prompt you for starting and ending cities and then display the information discussed in Project Summary.

Dependencies:

This program depends on three text files, which are provided in this GitHub repository. The program extracts the information from these text files without being prompted; the files just need to be in the same folder as Graph.cpp, Graph.h, and main.cpp. The three files are SuperChargerCities.txt, ElectricVehicleRanges.txt, and FinalProjectCities.txt. Also note that c++ 11 is necessary for all functionality.

System Requirements:

We ran this program on the Virtual Machine, which is a Linux system, but it can also run on Windows and Mac.

Group Members:

Emma Montross, Logan Thompson

Contributers: 

christyroney, schubydoo

Open Issues/Bugs:

Currently there are no fatal bugs in the program. A desired additional functionality would be improved exception handling so that all exceptions are handled in while loops or with try-throw-catch logic to allow for when a user puts in a bad input repeatedly.
