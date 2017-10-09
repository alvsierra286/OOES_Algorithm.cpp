/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Compute_Epsilon_Value.h
 * Author: amsierra
 *
 * Created on July 7, 2017, 11:36 AM
 */

#ifndef COMPUTE_EPSILON_VALUE_H
#define COMPUTE_EPSILON_VALUE_H

/*Epsilon Parameters*/
#define Epsilon 0.00001
#define Epsilon2 0.15
#define Epsilon3 0.05
#define Epsilon4 0.000001
#define Epsilon5 0.00001
#define Epsilon6 0.00001
#define Epsilon7 0.0001
#define Epsilon8 0.00002

/*CPLEX parameters*/
#define RelativeGap 1e-5
#define NumThreads 1
#define TimeLimit 86400
#define Positive_infinity 100000000
#define Negative_infinity -100000000

double Compute_Epsilon(double);
double Compute_Epsilon2(double);
double Compute_Epsilon3(double);
#endif /* COMPUTE_EPSILON_VALUE_H */

