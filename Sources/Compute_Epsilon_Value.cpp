#include "Compute_Epsilon_Value.h"
#include <cmath>

double Compute_Epsilon(double Epsilon_Coefficient) {
    double Var_Epsilon(Epsilon4);
    Var_Epsilon += fabs(Epsilon_Coefficient) * Epsilon4;
    return Var_Epsilon;
}
double Compute_Epsilon2(double Epsilon_Coefficient) {
    double Var_Epsilon(Epsilon8);
    Var_Epsilon += fabs(Epsilon_Coefficient) * Epsilon8;
    return Var_Epsilon;
}
double Compute_Epsilon3(double Epsilon_Coefficient) {
    double Var_Epsilon(Epsilon);
    Var_Epsilon += fabs(Epsilon_Coefficient) * Epsilon;
    return Var_Epsilon;
}