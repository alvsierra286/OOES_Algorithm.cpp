/* 
 * File:   Parameters.h
 * Author: amsierra
 *
 * Created on April 6, 2017, 9:09 PM
 */

#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <ilcplex/ilocplex.h>   /*This is a package for using CPLEX in C++ */
#include <iostream>             /*This is a package for reading/writing from/in screen in C++ */
#include<fstream>              /*This is a package for reading/writing files C++ */
#include <vector>               /*This is a package for creating dynamic lists */
#include "Priority_Queue.h"
#include "Partial_Solutions.h"

/*C++ Variables Declaration*/
bool Shape, Direction, Connection_Index, Partial_Connection, Infeasibility, Search_Done, Upper_Bound_Condition;
bool Enhancement_1, Enhancement_2, Enhancement_3, Enhancement_4, Enhancement_5;
int Num_of_Variables, Num_of_Int_Var, Num_of_Bool_Var, Num_of_Cont_Var, Num_of_Const, Num_of_Less_Const, cont;
int IP_Problems, IP_Finder_Point, IP_Weighted_Sum, IP_Finder_Line, IP_Finder_Triangle, IP_Line_Detector, IP_UB_Finder_Triangle;
int Iteration_Counter, GUB_Counter, N_Finder_Point, N_Weighted_Sum, N_Finder_Line, N_Finder_Triangle, N_Line_Detector, N_UB_Finder_Triangle;
int Number_of_Nodes(0);
double Relative_Gap;
double Start_Time(0), End_Time(0), GLB, GUB, Z1, Z2;
double Start_Time_Finder_Point(0), End_Time_Finder_Point(0);
double Start_Time_Weighted_Sum(0), End_Time_Weighted_Sum(0);
double Start_Time_Line_Detector(0), End_Time_Line_Detector(0);
double Start_Time_Finder_Line(0), End_Time_Finder_Line(0);
double Start_Time_Finder_Triangle(0), End_Time_Finder_Triangle(0);
double Start_Time_UB_Finder_Triangle(0), End_Time_UB_Finder_Triangle(0);
double Time_Finder_Point(0), Time_Weighted_Sum(0), Time_Line_Detector(0), Time_Finder_Line(0), Time_Finder_Triangle(0), Time_UB_Finder_Triangle(0);
double* DMFun_Coeff;
double* Point;
double* Point2;
double* NewNDP;
double DMFun_Value;
double* RHS;
double* Opt_Point;
double** Obj_Coeff;
double** Const_Coeff;

std::vector <Partial_Solutions*>Set_of_Partial_Solutions;
std::vector <Priority_Queue*>Prior_Queue;

/*Functions to read/write Input/Output files*/
std::ifstream InputFile;
std::ofstream OutputFile;
std::ofstream OutputFile2;
std::ofstream OutputFile3;

/*CPLEX Variables Declaration*/
ILOSTLBEGIN
typedef IloArray<IloNumVarArray> NumVar2DArray;
IloEnv env;
IloModel model(env);
IloCplex cplex(model);
IloObjective objfunc;
IloRangeArray Extra_Constraints(env);
IloNumVarArray var_x;
IloExpr Expr(env);
IloExprArray Extra_Model(env);
IloExprArray obj_fun(env);
IloExprArray obj_fun2(env);
IloExpr DM_fun(env);
IloExpr weighted_fun(env);
IloNumVarArray startVar(env);
IloNumVarArray startVar2(env);
IloNumArray startVal(env);

#endif /* PARAMETERS_H */

