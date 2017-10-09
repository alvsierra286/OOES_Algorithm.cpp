/* 
 * File:   Priority_Queue.h
 * Author: amsierra
 *
 * Created on April 6, 2017, 8:08 PM
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "Partial_Solutions.h"

class Priority_Queue {
public:
    double** ObjVal;
    double** VarX;
    double* fxVal;
    bool* fxOpt;
    bool Element_Shape;
    bool Element_Direction;
    double LBound;
    Priority_Queue();
    void Assign_Element_to_Queue(Partial_Solutions*, Partial_Solutions*, bool, bool, double);
    Priority_Queue(const Priority_Queue& orig);
    virtual ~Priority_Queue();
private:

};

#endif /* PRIORITY_QUEUE_H */
