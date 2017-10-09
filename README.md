# OOES_Algorithm.cpp
An Exact Algorithm to optimize a Linear Function Over the Set of Efficient Solutions for BOMILP

This is a criterion space search for optimizing a linear function over the set of efficient solutions of bi-objective mixed integer linear programs.

The following problem classes are supported:

    i. Objectives:   2 linear objectives.
    ii. Constraints:  0 or more linear (both inequality and equality) constraints.
    iii. Variables:
        a. Binary
        b. Integer variables
        c. Continous variables
        d. Any combination between previous types of variables.

A bi-objective mixed integer linear instance can be provided as an input file using the following format:

Problem example:

![Images](/Images/Example.jpg)
![Images](/Images/Obj_fun_example.jpg)

Description of the input file:

![Images](/Images/Input File.jpg)
