#include "Extern_Parameters.h"
#include "OOES_Solver.h"

void Weighted_Sum_Method(Partial_Solutions* emnt1, Partial_Solutions* emnt2) {
    double lambda1, lambda2;
    lambda1 = emnt1->ObjVal[1] - emnt2->ObjVal[1];
    lambda2 = emnt2->ObjVal[0] - emnt1->ObjVal[0];
    Extra_Constraints.add(obj_fun[0] >= emnt1->ObjVal[0]);
    Extra_Constraints.add(obj_fun[1] >= emnt2->ObjVal[1]);
    weighted_fun = (lambda1 * obj_fun[0])+(lambda2 * obj_fun[1]);
    objfunc = IloMinimize(env, weighted_fun);
    model.add(objfunc);
    model.add(Extra_Constraints);
    cplex.extract(model);
    if (Enhancement_5 == true) {
        for (int i = 0; i < Num_of_Variables; i++) {
            startVal.add(emnt1->VarX[i]);
        }
        cplex.addMIPStart(startVar, startVal);
    }
    cplex.setParam(IloCplex::TiLim, TimeLimit);
    cplex.setParam(IloCplex::Threads, NumThreads);
    cplex.setParam(IloCplex::EpGap, RelativeGap);
    //cplex.exportModel("Model.lp");
    cplex.setOut(env.getNullStream());
    IP_Problems += 1;
    IP_Weighted_Sum += 1;
    if (cplex.solve()) {
        Number_of_Nodes += cplex.getNnodes();
        for (int i = 0; i < 2; i++) {
            NewNDP[i] = cplex.getValue(obj_fun[i]);
        }
        for (int i = 0; i < Num_of_Variables; i++) {
            Point[i] = cplex.getValue(var_x[i]);
        }
        DMFun_Value = cplex.getValue(DM_fun);
    }
    cplex.clear();
    model.remove(objfunc);
    model.remove(Extra_Constraints);
    Extra_Constraints.clear();
    startVal.clear();
    double lambda3 = ((lambda1 * NewNDP[0])+(lambda2 * NewNDP[1])) - ((lambda1 * emnt1->ObjVal[0])+(lambda2 * emnt1->ObjVal[1]));
    double gap_line = (fabs(lambda1 * emnt1->ObjVal[0]) + fabs(lambda2 * emnt1->ObjVal[1])) * Epsilon5;
    if (lambda3 < (gap_line + Epsilon5)*(-1)) {
        Partial_Solutions* new_element = new Partial_Solutions;
        new_element->Weighted_Sum_Points(false);
        Set_of_Partial_Solutions.insert(Set_of_Partial_Solutions.begin() + cont + 1, new_element);
    } else {
        cont += 1;
    }
}

void T_and_B_Points(bool top1, bool bottom1) {
    for (int i = 0; i < 2; i++) {
        if (top1 == false) {
            bottom1 = true;
            Top_and_Bottom_Points(top1, bottom1);
            top1 = true;
            bottom1 = false;
        } else {
            Top_and_Bottom_Points(top1, bottom1);
        }
        if (Infeasibility == true) {

            break;
        }
    }
}

void Top_and_Bottom_Points(bool TopIndex, bool BottomIndex) {
    //objfunc = IloMinimize(env, DM_fun);
    objfunc = IloMinimize(env, obj_fun[TopIndex]);
    model.add(objfunc);
    cplex.extract(model);
    cplex.setParam(IloCplex::TiLim, TimeLimit);
    cplex.setParam(IloCplex::Threads, NumThreads);
    cplex.setParam(IloCplex::EpGap, RelativeGap);
    //cplex.exportModel("Model.lp");
    cplex.setOut(env.getNullStream());
    IP_Problems += 1;
    if (cplex.solve()) {
        Number_of_Nodes += cplex.getNnodes();
        double New_Constraint = cplex.getObjValue();
        for (int i = 0; i < Num_of_Variables; i++) {
            Point2[i] = cplex.getValue(var_x[i]);
        }
        cplex.clear();
        model.remove(objfunc);
        Extra_Constraints.add(obj_fun[TopIndex] <= New_Constraint + Compute_Epsilon(New_Constraint));
        objfunc = IloMinimize(env, obj_fun[BottomIndex]);
        model.add(objfunc);
        model.add(Extra_Constraints);
        cplex.extract(model);
        if (Enhancement_5 == true) {
            for (int i = 0; i < Num_of_Variables; i++) {
                startVal.add(Point2[i]);
            }
            cplex.addMIPStart(startVar, startVal);
        }
        cplex.setParam(IloCplex::TiLim, TimeLimit);
        cplex.setParam(IloCplex::Threads, NumThreads);
        cplex.setParam(IloCplex::EpGap, RelativeGap);
        //cplex.exportModel("Model.lp");
        cplex.setOut(env.getNullStream());
        IP_Problems += 1;
        if (cplex.solve()) {
            Number_of_Nodes += cplex.getNnodes();
            for (int i = 0; i < 2; i++) {
                NewNDP[i] = cplex.getValue(obj_fun[i]);
            }
            for (int i = 0; i < Num_of_Variables; i++) {
                Point[i] = cplex.getValue(var_x[i]);
            }
            DMFun_Value = cplex.getValue(DM_fun);
        }
        Partial_Solutions* element2 = new Partial_Solutions;
        element2->Weighted_Sum_Points(false);
        Set_of_Partial_Solutions.push_back(element2);
    } else {
        Infeasibility = true;
    }
    cplex.clear();
    model.remove(objfunc);
    model.remove(Extra_Constraints);
    Extra_Constraints.clear();
    startVal.clear();
}

void Line_Detector(Partial_Solutions* emnt1, Partial_Solutions* emnt2) {
    double Int_Variables_Gap(0), Equal_Variables_Gap(0), lambda1, lambda2, lambda3;
    int Num_Equal_Variables(0);
    bool sw = false;
    Connection_Index = false;
    Partial_Connection = false;
    if (Enhancement_3 == true) {
        for (int i = 0; i < Num_of_Variables - Num_of_Cont_Var; i++) {
            Int_Variables_Gap += fabs(emnt1->VarX[i + Num_of_Cont_Var] - emnt2->VarX[i + Num_of_Cont_Var]);
        }
        if (Int_Variables_Gap <= Epsilon) {
            Connection_Index = true;
            sw = true;
        }
    }
    if (Enhancement_4 == true && Connection_Index == false) {
        for (int i = 0; i < Num_of_Variables - Num_of_Cont_Var; i++) {
            if (fabs(emnt1->VarX[i + Num_of_Cont_Var] - emnt2->VarX[i + Num_of_Cont_Var]) <= Epsilon) {
                Num_Equal_Variables += 1;
            }
        }
        Equal_Variables_Gap = double(Num_Equal_Variables) / (double(Num_of_Variables - Num_of_Cont_Var));
        if (Equal_Variables_Gap < (1 - Epsilon3)) {
            sw = true;
        }
    }
    if (sw == false) {
        lambda1 = emnt1->ObjVal[1] - emnt2->ObjVal[1];
        lambda2 = emnt2->ObjVal[0] - emnt1->ObjVal[0];
        lambda3 = (lambda1 * emnt1->ObjVal[0])+(lambda2 * emnt1->ObjVal[1]);
        Extra_Constraints.add(obj_fun[0] <= emnt1->ObjVal[0] + Compute_Epsilon(emnt1->ObjVal[0]));
        Extra_Constraints.add(obj_fun[1] <= emnt1->ObjVal[1] + Compute_Epsilon(emnt1->ObjVal[1]));
        Extra_Constraints.add((((lambda1 * obj_fun2[0])+(lambda2 * obj_fun2[1])) - lambda3) <= Epsilon);
        for (int i = 0; i < Num_of_Const; i++) {
            if (i < Num_of_Less_Const) {
                Extra_Constraints.add(Extra_Model[i] <= RHS[i]);
            } else {
                Extra_Constraints.add(Extra_Model[i] == RHS[i]);
            }
        }
        objfunc = IloMaximize(env, obj_fun2[0]);
        model.add(objfunc);
        model.add(Extra_Constraints);
        cplex.extract(model);
        if (Enhancement_5 == true) {
            for (int i = 0; i < Num_of_Variables + Num_of_Cont_Var; i++) {
                if (i < Num_of_Variables) {
                    startVal.add(emnt1->VarX[i]);
                } else {
                    startVal.add(emnt1->VarX[i - Num_of_Variables]);
                }
            }
            cplex.addMIPStart(startVar2, startVal);
        }
        cplex.setParam(IloCplex::TiLim, TimeLimit);
        cplex.setParam(IloCplex::Threads, NumThreads);
        cplex.setParam(IloCplex::EpGap, RelativeGap);
        //cplex.exportModel("Model.lp");
        cplex.setOut(env.getNullStream());
        IP_Problems += 1;
        IP_Line_Detector += 1;
        if (cplex.solve()) {
            Number_of_Nodes += cplex.getNnodes();
            int x = 0;
            for (int i = 0; i < 2; i++) {
                NewNDP[i] = cplex.getValue(obj_fun2[i]);
            }
            for (int i = 0; i < Num_of_Variables; i++) {
                if (i < Num_of_Cont_Var) {
                    Point[i] = cplex.getValue(var_x[i + Num_of_Variables]);
                } else {
                    Point[i] = cplex.getValue(var_x[i]);
                }
            }
            DMFun_Value = cplex.getValue(DM_fun);
            if (NewNDP[0] >= emnt2->ObjVal[0] - Compute_Epsilon3(emnt2->ObjVal[0])) {
                Connection_Index = true;
            } else if (NewNDP[0] > emnt1->ObjVal[0] + Compute_Epsilon3(emnt1->ObjVal[0])) {
                Connection_Index = true;
                Partial_Connection = true;
            }
        }
        cplex.clear();
        model.remove(objfunc);
        model.remove(Extra_Constraints);
        Extra_Constraints.clear();
        startVal.clear();
    }
}