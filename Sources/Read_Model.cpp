#include "Extern_Parameters.h"
#include "Read_Model.h"

void Reading_The_Input_File(char *Input_File) {
    InputFile.open(Input_File);
    /*Assignation of parameters in the Input file to C++ variables*/
    InputFile>>Num_of_Variables;
    InputFile>>Num_of_Cont_Var;
    InputFile>>Num_of_Int_Var;
    Num_of_Bool_Var = Num_of_Variables - Num_of_Cont_Var - Num_of_Int_Var;
    InputFile>>Num_of_Const;
    InputFile>>Num_of_Less_Const;
    Const_Coeff[19][19];
    Obj_Coeff = new double* [2];
    for (int i = 0; i < 2; i++) {
        Obj_Coeff[i] = new double [Num_of_Variables];
        for (int j = 0; j < Num_of_Variables; j++) {
            InputFile >> Obj_Coeff[i][j];
        }
    }
    Const_Coeff = new double* [Num_of_Const];
    for (int i = 0; i < Num_of_Const; i++) {
        Const_Coeff[i] = new double [Num_of_Variables];
        for (int j = 0; j < Num_of_Variables; j++) {
            InputFile >> Const_Coeff[i][j];
        }
    }
    RHS = new double [Num_of_Const];
    for (int i = 0; i < Num_of_Const; i++) {
        InputFile >> RHS[i];
    }
    DMFun_Coeff = new double [Num_of_Variables];
    for (int i = 0; i < Num_of_Variables; i++) {
        InputFile >> DMFun_Coeff[i];
    }
    InputFile.close();
}

void ReadModel() {

    /*Creation of CPLEX variables of the model*/
    char VarName[25];
    var_x = IloNumVarArray(env, Num_of_Variables + Num_of_Cont_Var);
    for (int i = 0; i < Num_of_Variables + Num_of_Cont_Var; i++) {
        sprintf(VarName, "x%d", i + 1);
        if (i < Num_of_Cont_Var) {
            var_x[i] = IloNumVar(env, 0.0, Positive_infinity, ILOFLOAT, VarName);
        } else if (i < Num_of_Cont_Var + Num_of_Int_Var) {
            var_x[i] = IloNumVar(env, 0.0, Positive_infinity, ILOINT, VarName);
        } else if (i < Num_of_Variables) {
            var_x[i] = IloNumVar(env, 0.0, 1, ILOBOOL, VarName);
        } else {
            var_x[i] = IloNumVar(env, 0.0, Positive_infinity, ILOFLOAT, VarName);
        }
    }

    /*Creation of CPLEX less or equal constraints of the model*/
    Extra_Model.clear();
    Extra_Model = IloExprArray(env, Num_of_Const);

    for (int j = 0; j < Num_of_Less_Const; j++) {
        Expr.clear();
        Extra_Model[j] = IloExpr(env);
        for (int k = 0; k < Num_of_Variables; k++) {
            Expr += (Const_Coeff[j][k] * var_x[k]);
            if (k < Num_of_Cont_Var) {
                Extra_Model[j] += (Const_Coeff[j][k] * var_x[k + Num_of_Variables]);
            } else {
                Extra_Model[j] += (Const_Coeff[j][k] * var_x[k]);
            }
        }
        model.add(Expr <= RHS[j]);
    }

    /*Creation of CPLEX equality constraints of the model*/
    for (int l = 0; l < Num_of_Const - Num_of_Less_Const; l++) {
        Expr.clear();
        Extra_Model[l + Num_of_Less_Const] = IloExpr(env);
        for (int m = 0; m < Num_of_Variables; m++) {
            Expr += (Const_Coeff[l + Num_of_Less_Const][m] * var_x[m]);
            if (m < Num_of_Cont_Var) {
                Extra_Model[l + Num_of_Less_Const] += (Const_Coeff[l + Num_of_Less_Const][m] * var_x[m + Num_of_Variables]);
            } else {
                Extra_Model[l + Num_of_Less_Const] += (Const_Coeff[l + Num_of_Less_Const][m] * var_x[m]);
            }
        }
        model.add(Expr == RHS[l + Num_of_Less_Const]);
    }

    /*Creation of CPLEX objectives of the model*/
    obj_fun.clear();
    obj_fun = IloExprArray(env, 2);
    for (int n = 0; n < 2; n++) {
        obj_fun[n] = IloExpr(env);
        for (int o = 0; o < Num_of_Variables; o++) {
            obj_fun[n] += (Obj_Coeff[n][o] * var_x[o]);
        }
    }
    DM_fun.clear();
    for (int o = 0; o < Num_of_Variables; o++) {
        DM_fun += (DMFun_Coeff[o] * var_x[o]);
    }
    obj_fun2.clear();
    obj_fun2 = IloExprArray(env, 2);
    for (int n = 0; n < 2; n++) {
        obj_fun2[n] = IloExpr(env);
        for (int o = 0; o < Num_of_Variables; o++) {
            if (o < Num_of_Cont_Var) {
                obj_fun2[n] += (Obj_Coeff[n][o] * var_x[o + Num_of_Variables]);
            } else {
                obj_fun2[n] += (Obj_Coeff[n][o] * var_x[o]);
            }
        }
    }
    for (int i = 0; i < Num_of_Variables; i++) {
        startVar.add(var_x[i]);
        startVar2.add(var_x[i]);
    }
    for (int i = 0; i < Num_of_Cont_Var; i++) {
        startVar2.add(var_x[i + Num_of_Variables]);
    }
    Extra_Constraints.clear();
    startVal.clear();
}
