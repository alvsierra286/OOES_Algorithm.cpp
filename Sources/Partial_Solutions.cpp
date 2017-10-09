/* 
 * File:   Partial_Solutions.cpp
 * Author: amsierra
 * 
 * Created on April 6, 2017, 8:39 PM
 */

#include "Extern_Parameters.h"

Partial_Solutions::Partial_Solutions() {
    ObjVal = new double [2];
    VarX = new double [Num_of_Variables];
    fxVal = 0;
    fxOpt = false;
    for (int i = 0; i < 2; i++) {
        ObjVal[i] = 0;
    }
    for (int j = 0; j < Num_of_Variables; j++) {
        VarX[j] = 0;
    }
}

void Partial_Solutions::Assign_Partial_Values(bool Point_Index) {
    for (int i = 0; i < 2; i++) {
        ObjVal[i] = Prior_Queue.at(0)->ObjVal[Point_Index][i];
    }
    for (int j = 0; j < Num_of_Variables; j++) {
        VarX[j] = Prior_Queue.at(0)->VarX[Point_Index][j];
    }
    fxVal = Prior_Queue.at(0)->fxVal[Point_Index];
    fxOpt = Prior_Queue.at(0)->fxOpt[Point_Index];
}

void Partial_Solutions::Weighted_Sum_Points(bool fx_Opt) {
    for (int i = 0; i < 2; i++) {
        ObjVal[i] = NewNDP[i];
    }
    for (int k = 0; k < Num_of_Variables; k++) {
        VarX[k] = Point[k];
    }
    fxVal = DMFun_Value;
    fxOpt = fx_Opt;
}

Partial_Solutions::~Partial_Solutions() {
    delete[] ObjVal;
    delete[] VarX;
}

