/* 
 * File:   OOES_Finders.h
 * Author: amsierra
 *
 * Created on May 14, 2017, 7:48 PM
 */

#include "Extern_Parameters.h"
#ifndef OOES_FINDERS_H
#define OOES_FINDERS_H
void LB_Finder_Point(Partial_Solutions*);
void LB_Finder_Line(Partial_Solutions*, Partial_Solutions*);
void LB_Finder_Triangle(Partial_Solutions*, Partial_Solutions*);
void UB_Finder(Partial_Solutions*, double, Partial_Solutions*, Partial_Solutions*, bool);
#endif /* OOES_FINDERS_H */

