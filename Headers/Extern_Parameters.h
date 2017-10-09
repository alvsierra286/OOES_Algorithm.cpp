/* 
 * File:   Extern_Parameters.h
 * Author: amsierra
 *
 * Created on April 6, 2017, 9:15 PM
 */

#ifndef EXTERN_PARAMETERS_H
#define EXTERN_PARAMETERS_H
#include <ilcplex/ilocplex.h>   /*This is a package for using CPLEX in C++ */
#include <iostream>             /*This is a package for reading/writing from/in screen in C++ */
#include<fstream>              /*This is a package for reading/writing files C++ */
#include <vector>               /*This is a package for creating dynamic lists */
#include "Priority_Queue.h"
#include "Partial_Solutions.h"
#include "Compute_Epsilon_Value.h"
#include <cmath>


extern int Num_of_Variables, Num_of_Int_Var, Num_of_Bool_Var, Num_of_Cont_Var, Num_of_Const, Num_of_Less_Const, cont;
extern int IP_Problems, IP_Finder_Point, IP_Weighted_Sum, IP_Finder_Line, IP_Finder_Triangle, IP_Line_Detector, IP_UB_Finder_Triangle;
extern int Iteration_Counter, GUB_Counter, N_Finder_Point, N_Weighted_Sum, N_Finder_Line, N_Finder_Triangle, N_Line_Detector, N_UB_Finder_Triangle;
extern int Number_of_Nodes;
extern double Relative_Gap;
extern double* DMFun_Coeff;
extern double* Point;
extern double* Point2;
extern double* NewNDP;
extern double** Obj_Coeff;
extern double** Const_Coeff;
extern double* RHS;
extern double* Opt_Point;
extern double DMFun_Value, GLB, GUB, Z1, Z2;
extern double Start_Time, End_Time;
extern double Start_Time_Finder_Point, End_Time_Finder_Point;
extern double Start_Time_Weighted_Sum, End_Time_Weighted_Sum;
extern double Start_Time_Line_Detector, End_Time_Line_Detector;
extern double Start_Time_Finder_Line, End_Time_Finder_Line;
extern double Start_Time_Finder_Triangle, End_Time_Finder_Triangle;
extern double Start_Time_UB_Finder_Triangle, End_Time_UB_Finder_Triangle;
extern double Time_Finder_Point, Time_Weighted_Sum, Time_Line_Detector, Time_Finder_Line, Time_Finder_Triangle, Time_UB_Finder_Triangle;
extern bool Shape, Direction, Connection_Index, Partial_Connection, Infeasibility, Search_Done, Upper_Bound_Condition;
extern bool Enhancement_1, Enhancement_2, Enhancement_3, Enhancement_4, Enhancement_5;

extern std::vector <Partial_Solutions*>Set_of_Partial_Solutions;
extern std::vector <Priority_Queue*>Prior_Queue;

extern std::ifstream InputFile;
extern std::ofstream OutputFile;
extern std::ofstream OutputFile2;
extern std::ofstream OutputFile3;

ILOSTLBEGIN
typedef IloArray<IloNumVarArray> NumVar2DArray;
extern IloEnv env;
extern IloModel model;
extern IloCplex cplex;
extern IloObjective objfunc;
extern IloRangeArray Extra_Constraints;
extern IloNumVarArray var_x;
extern IloExpr Expr;
extern IloExprArray Extra_Model;
extern IloExprArray obj_fun;
extern IloExprArray obj_fun2;
extern IloExpr DM_fun;
extern IloExpr weighted_fun;
extern IloNumVarArray startVar;
extern IloNumVarArray startVar2;
extern IloNumArray startVal;

#endif /* EXTERN_PARAMETERS_H */

