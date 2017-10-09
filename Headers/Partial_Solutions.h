/* 
 * File:   Partial_Solutions.h
 * Author: amsierra
 *
 * Created on April 6, 2017, 8:39 PM
 */

#ifndef PARTIAL_SOLUTIONS_H
#define PARTIAL_SOLUTIONS_H

class Partial_Solutions {
public:
    double* ObjVal;
    double* VarX;
    double fxVal;
    bool fxOpt;
    Partial_Solutions();
    void Assign_Partial_Values(bool);
    void Weighted_Sum_Points(bool);
    Partial_Solutions(const Partial_Solutions& orig);
    virtual ~Partial_Solutions();
private:

};

#endif /* PARTIAL_SOLUTIONS_H */

