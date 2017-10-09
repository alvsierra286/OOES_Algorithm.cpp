/* 
 * File:   OOES_Solver.h
 * Author: amsierra
 *
 * Created on April 12, 2017, 8:34 PM
 */
#include "Extern_Parameters.h"
#ifndef OOES_SOLVER_H
#define OOES_SOLVER_H
void Weighted_Sum_Method(Partial_Solutions*, Partial_Solutions*);
void T_and_B_Points(bool, bool);
void Top_and_Bottom_Points(bool, bool);
void Line_Detector(Partial_Solutions*, Partial_Solutions*);
#endif /* OOES_SOLVER_H */

