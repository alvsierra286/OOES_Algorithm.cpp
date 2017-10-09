/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Extern_Parameters.h"
#include "Variables_Declaration.h"

void Enhancements_Declaration(char *Enhancements_File) {
    InputFile.open(Enhancements_File);
    InputFile>>Enhancement_1;
    InputFile>>Enhancement_2;
    InputFile>>Enhancement_3;
    InputFile>>Enhancement_4;
    InputFile>>Enhancement_5;
    InputFile.close();
}

void Variable_Declaration() {
    Point = new double [Num_of_Variables];
    Point2 = new double [Num_of_Variables];
    Opt_Point = new double [Num_of_Variables];
    NewNDP = new double [2];
    Infeasibility = false;
    Shape = false;
    Direction = false;
    Search_Done = false;
    Connection_Index = false;
    Partial_Connection = false;
    IP_Problems = 0;
    IP_Finder_Point = 0;
    IP_Weighted_Sum = 0;
    IP_Finder_Line = 0;
    IP_Finder_Triangle = 0;
    IP_Line_Detector = 0;
    IP_UB_Finder_Triangle = 0;
    N_Finder_Point = 0;
    N_Weighted_Sum = 0;
    N_Finder_Line = 0;
    N_Finder_Triangle = 0;
    N_Line_Detector = 0;
    N_UB_Finder_Triangle = 0;
    Iteration_Counter = 0;
    Relative_Gap = 0;
    GUB = Positive_infinity;
    GLB = Negative_infinity;
}