# Public-transport-platform-oop
Implementation of a public transport platform, using object oriented paradigm and a graph as a data structure.

**Implementation**

To implement the public transport platform in an object-oriented way, we first created classes for BusStation and BusLine. These classes contain all the methods related to getting and adding information to a BusStation and/or BusLine.

To implement the entire platform, which includes both BusStations and BusLines and their connections, we implemented a class called Graph. The Graph class is essentially a map, where each element of the map contains a pointer to a new BusStation, and a list of all the BusLines that stop at that BusStation. We implemented methods in the Graph class for getting and setting specific new information.

We also implemented separate classes for loading, finding paths, and printing the platform, as we have a number of different implementations of these functionalities that we wanted to keep in the same place.

The class QuestionPlatform is derived from the Graph class and has pointers to the classes with specific load, find path, and print algorithms implemented for the QuestionPlatform.

We implemented exception handling using try-catch blocks and created custom exception classes.

The class LoadStrategies contains methods for loading data. There are two different methods: one for loading station data and one for loading bus line data. This class also contains methods for parsing the string.

The class PrintStrategies contains methods for printing data. There are two different methods: one for printing station data and one for printing bus line data.

The class PathStrategies contains methods for finding different paths between two different stations. There are three different versions implemented: one to search for all the paths between two stations, one to search for the path with the minimum number of stations, and one to search for the path with the minimum number of bus lines.
