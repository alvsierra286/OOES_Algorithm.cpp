/* 
 * File:   Priority_Queue.cpp
 * Author: amsierra
 * 
 * Created on April 6, 2017, 8:08 PM
 */

#include "Extern_Parameters.h"

Priority_Queue::Priority_Queue() {
    ObjVal = new double* [2];
    VarX = new double* [2];
    fxVal = new double [2];
    fxOpt = new bool [2];
    for (int i = 0; i < 2; i++) {
        ObjVal[i] = new double [2];
        VarX[i] = new double [Num_of_Variables];
        fxVal[i] = 0;
        fxOpt[i] = false;
    }
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            ObjVal[j][k] = 0;
        }
        for (int l = 0; l < Num_of_Variables; l++) {
            VarX[j][l] = 0;
        }
    }
    Element_Shape = false;
    Element_Direction = false;
    LBound = 0;
}

void Priority_Queue::Assign_Element_to_Queue(Partial_Solutions* New_element1, Partial_Solutions* New_element2, bool Shape_Ind, bool Dir_Ind, double Lower_Bound) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == 0) {
                ObjVal[i][j] = New_element1->ObjVal[j];
            } else {
                ObjVal[i][j] = New_element2->ObjVal[j];
            }
        }
        for (int k = 0; k < Num_of_Variables; k++) {
            if (i == 0) {
                VarX[i][k] = New_element1->VarX[k];
            } else {
                VarX[i][k] = New_element2->VarX[k];
            }
        }
        if (i == 0) {
            fxVal[i] = New_element1->fxVal;
            fxOpt[i] = New_element1->fxOpt;
        } else {
            fxVal[i] = New_element2->fxVal;
            fxOpt[i] = New_element2->fxOpt;
        }
    }
    Element_Shape = Shape_Ind;
    Element_Direction = Dir_Ind;
    LBound = Lower_Bound;
}

Priority_Queue::~Priority_Queue() {
    for (int m = 0; m < 2; m++) {
        delete[] ObjVal[m];
        delete[] VarX[m];
    }
    delete[] ObjVal;
    delete[] VarX;
    delete[] fxVal;
    delete[] fxOpt;
}