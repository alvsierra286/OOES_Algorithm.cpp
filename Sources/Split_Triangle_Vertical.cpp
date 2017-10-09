#include "Extern_Parameters.h"
#include "Split_Triangle_Vertical.h"

void Splitting_Triangle_Vertical(Partial_Solutions* emnt1, Partial_Solutions* emnt2, double Bound_Half, Partial_Solutions* emnt3) {
    bool Infeasible_Index = false;
    bool Enh_1_Condition = false;
    bool fx_Condition = false;
    double Partial_DMValue(0), Partial_DMValue1(Positive_infinity), Partial_DMValue2(Positive_infinity), DMValue1(0), DMValue2(0);
    double Diff_Point_Proof[2][2];
    double z11, z12, z21, z22, gap_points1, gap_points2;
    Partial_Solutions* element1 = new Partial_Solutions;
    Partial_Solutions* element2 = new Partial_Solutions;
    Extra_Constraints.add(obj_fun[0] <= Bound_Half);
    objfunc = IloMinimize(env, obj_fun[1]);
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
    IP_UB_Finder_Triangle += 1;
    if (cplex.solve()) {
        Number_of_Nodes += cplex.getNnodes();
        for (int i = 0; i < 2; i++) {
            NewNDP[i] = cplex.getValue(obj_fun[i]);
        }
        for (int i = 0; i < Num_of_Variables; i++) {
            Point[i] = cplex.getValue(var_x[i]);
        }
        DMFun_Value = cplex.getValue(DM_fun);
        if (Enhancement_1 == true) {
            if (fabs(NewNDP[1] - emnt1->ObjVal[1]) < fabs(emnt1->ObjVal[1]) * Epsilon) {
                Enh_1_Condition = true;
                for (int i = 0; i < 2; i++) {
                    NewNDP[i] = emnt1->ObjVal[i];
                }
                for (int i = 0; i < Num_of_Variables; i++) {
                    Point[i] = emnt1->VarX[i];
                }
                DMFun_Value = emnt1->fxVal;
                fx_Condition = emnt1->fxOpt;
            }
        }
    } else {
        Infeasible_Index = true;
    }
    cplex.clear();
    model.remove(objfunc);
    model.remove(Extra_Constraints);
    Extra_Constraints.clear();
    startVal.clear();

    if (Enh_1_Condition == false && Infeasible_Index == false) {
        Extra_Constraints.add(obj_fun[1] <= NewNDP[1] + Compute_Epsilon(NewNDP[1]));
        objfunc = IloMinimize(env, obj_fun[0]);
        model.add(objfunc);
        model.add(Extra_Constraints);
        cplex.extract(model);
        if (Enhancement_5 == true) {
            for (int i = 0; i < Num_of_Variables; i++) {
                startVal.add(Point[i]);
            }
            cplex.addMIPStart(startVar, startVal);
        }
        cplex.setParam(IloCplex::TiLim, TimeLimit);
        cplex.setParam(IloCplex::Threads, NumThreads);
        cplex.setParam(IloCplex::EpGap, RelativeGap);
        //cplex.exportModel("Model.lp");
        cplex.setOut(env.getNullStream());
        IP_Problems += 1;
        IP_UB_Finder_Triangle += 1;
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
    }
    if (Infeasible_Index == false && fx_Condition == false) {
        Extra_Constraints.add(obj_fun[0] <= NewNDP[0] + Compute_Epsilon(NewNDP[0]));
        Extra_Constraints.add(obj_fun[1] <= NewNDP[1] + Compute_Epsilon(NewNDP[1]));
        objfunc = IloMinimize(env, DM_fun);
        model.add(objfunc);
        model.add(Extra_Constraints);
        cplex.extract(model);
        if (Enhancement_5 == true) {
            for (int i = 0; i < Num_of_Variables; i++) {
                startVal.add(Point[i]);
            }
            cplex.addMIPStart(startVar, startVal);
        }
        cplex.setParam(IloCplex::TiLim, TimeLimit);
        cplex.setParam(IloCplex::Threads, NumThreads);
        cplex.setParam(IloCplex::EpGap, RelativeGap);
        //cplex.exportModel("Model.lp");
        cplex.setOut(env.getNullStream());
        IP_Problems += 1;
        IP_UB_Finder_Triangle += 1;
        if (cplex.solve()) {
            Number_of_Nodes += cplex.getNnodes();
            for (int i = 0; i < 2; i++) {
                NewNDP[i] = cplex.getValue(obj_fun[i]);
            }
            for (int i = 0; i < Num_of_Variables; i++) {
                Point[i] = cplex.getValue(var_x[i]);
            }
            DMFun_Value = cplex.getValue(DM_fun);
            Partial_DMValue1 = DMFun_Value;
            if (DMFun_Value < GUB) {
                GUB = DMFun_Value;
                for (int i = 0; i < Num_of_Variables; i++) {
                    Opt_Point[i] = cplex.getValue(var_x[i]);
                }
                Z1 = NewNDP[0];
                Z2 = NewNDP[1];
                GUB_Counter = Iteration_Counter;
            }
        }
        cplex.clear();
        model.remove(objfunc);
        model.remove(Extra_Constraints);
        Extra_Constraints.clear();
        startVal.clear();
    }

    if (Enhancement_2 == true && Infeasible_Index == false) {
        int x = 0;
        int sw = 0;
        while (x < Prior_Queue.size() && sw == 0) {
            double Value1 = fabs(NewNDP[0] - Prior_Queue.at(x)->ObjVal[1][0]);
            double Value2 = fabs(NewNDP[1] - Prior_Queue.at(x)->ObjVal[1][1]);
            if (Value1 < fabs(Prior_Queue.at(x)->ObjVal[1][0] * Epsilon) && Value2 < fabs(Prior_Queue.at(x)->ObjVal[1][1] * Epsilon)) {
                for (int j = 0; j < 2; j++) {
                    Prior_Queue.at(x)->ObjVal[1][j] = NewNDP[j];
                }
                for (int k = 0; k < Num_of_Variables; k++) {
                    Prior_Queue.at(x)->VarX[1][k] = Point[k];
                }
                Prior_Queue.at(x)->fxVal[1] = DMFun_Value;
                Prior_Queue.at(x)->fxOpt[1] = true;
                sw += 1;
            }
            x += 1;
        }
    }

    z11 = emnt1->ObjVal[0];
    z12 = emnt1->ObjVal[1];
    z21 = NewNDP[0];
    z22 = NewNDP[1];
    gap_points1 = fabs(z11 - z21);
    gap_points2 = fabs(z12 - z22);
    if (emnt3->ObjVal[0] <= emnt1->ObjVal[1] && emnt3->ObjVal[0] <= NewNDP[0]) {
        DMValue2 = emnt3->fxVal;
    } else {
        if (gap_points1 + gap_points2 > Epsilon * 2 * z11) {
            Extra_Constraints.add(obj_fun[1] <= emnt1->ObjVal[1] + Compute_Epsilon(emnt1->ObjVal[1]));
            Extra_Constraints.add(obj_fun[0] <= NewNDP[0] + Compute_Epsilon(NewNDP[0]));
            objfunc = IloMinimize(env, DM_fun);
            model.add(objfunc);
            model.add(Extra_Constraints);
            cplex.extract(model);
            if (Enhancement_5 == true) {
                for (int i = 0; i < Num_of_Variables; i++) {
                    startVal.add(Point[i]);
                }
                cplex.addMIPStart(startVar, startVal);
            }
            cplex.setParam(IloCplex::TiLim, TimeLimit);
            cplex.setParam(IloCplex::Threads, NumThreads);
            cplex.setParam(IloCplex::EpGap, RelativeGap);
            //cplex.exportModel("Model.lp");
            cplex.setOut(env.getNullStream());
            IP_Problems += 1;
            IP_UB_Finder_Triangle += 1;
            if (cplex.solve()) {
                Number_of_Nodes += cplex.getNnodes();
                DMValue2 = cplex.getValue(DM_fun);
            }
            cplex.clear();
            model.remove(objfunc);
            model.remove(Extra_Constraints);
            Extra_Constraints.clear();
            startVal.clear();
        } else {
            DMValue2 = DMFun_Value;
        }
    }
    element1->Weighted_Sum_Points(true);
    Enh_1_Condition = false;
    fx_Condition = false;

    if (Infeasible_Index == false) {
        double Inverse_Slope(0), Obj_Value(0);
        if (fabs(emnt1->ObjVal[0] - NewNDP[0]) > Epsilon && fabs(emnt1->ObjVal[1] - NewNDP[1]) > Epsilon) {
            Inverse_Slope = (emnt1->ObjVal[0] - NewNDP[0]) / (emnt1->ObjVal[1] - NewNDP[1]);
            Obj_Value = Inverse_Slope * (NewNDP[1]-((2 * (Compute_Epsilon3(NewNDP[1])))) - NewNDP[1]);
            Obj_Value += NewNDP[0];
        } else {
            Obj_Value = Negative_infinity;
        }
        if (Obj_Value < Bound_Half - Epsilon) {
            Extra_Constraints.add(obj_fun[1] <= (NewNDP[1] - Compute_Epsilon2(NewNDP[1])));
            Extra_Constraints.add(obj_fun[0] >= Bound_Half);
            objfunc = IloMinimize(env, obj_fun[0]);
            model.add(objfunc);
            model.add(Extra_Constraints);
            cplex.extract(model);
            if (Enhancement_5 == true) {
                for (int i = 0; i < Num_of_Variables; i++) {
                    startVal.add(emnt2->VarX[i]);
                }
                cplex.addMIPStart(startVar, startVal);
            }
            cplex.setParam(IloCplex::TiLim, TimeLimit);
            cplex.setParam(IloCplex::Threads, NumThreads);
            cplex.setParam(IloCplex::EpGap, RelativeGap);
            //cplex.exportModel("Model.lp");
            cplex.setOut(env.getNullStream());
            IP_Problems += 1;
            IP_UB_Finder_Triangle += 1;
            if (cplex.solve()) {
                Number_of_Nodes += cplex.getNnodes();
                for (int i = 0; i < 2; i++) {
                    NewNDP[i] = cplex.getValue(obj_fun[i]);
                }
                for (int i = 0; i < Num_of_Variables; i++) {
                    Point[i] = cplex.getValue(var_x[i]);
                }
                DMFun_Value = cplex.getValue(DM_fun);
                if (Enhancement_1 == true) {
                    if (fabs(NewNDP[0] - emnt2->ObjVal[0]) < fabs(emnt2->ObjVal[0]) * Epsilon) {
                        Enh_1_Condition = true;
                        for (int i = 0; i < 2; i++) {
                            NewNDP[i] = emnt2->ObjVal[i];
                        }
                        for (int i = 0; i < Num_of_Variables; i++) {
                            Point[i] = emnt2->VarX[i];
                        }
                        DMFun_Value = emnt2->fxVal;
                        fx_Condition = emnt2->fxOpt;
                    }
                }
            } else {
                Infeasible_Index = true;
            }
            cplex.clear();
            model.remove(objfunc);
            model.remove(Extra_Constraints);
            Extra_Constraints.clear();
            startVal.clear();

            if (Enh_1_Condition == false && Infeasible_Index == false) {
                Extra_Constraints.add(obj_fun[0] <= NewNDP[0] + Compute_Epsilon(NewNDP[0]));
                objfunc = IloMinimize(env, obj_fun[1]);
                model.add(objfunc);
                model.add(Extra_Constraints);
                cplex.extract(model);
                if (Enhancement_5 == true) {
                    for (int i = 0; i < Num_of_Variables; i++) {
                        startVal.add(Point[i]);
                    }
                    cplex.addMIPStart(startVar, startVal);
                }
                cplex.setParam(IloCplex::TiLim, TimeLimit);
                cplex.setParam(IloCplex::Threads, NumThreads);
                cplex.setParam(IloCplex::EpGap, RelativeGap);
                //cplex.exportModel("Model.lp");
                cplex.setOut(env.getNullStream());
                IP_Problems += 1;
                IP_UB_Finder_Triangle += 1;
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
            }

            if (Infeasible_Index == false && fx_Condition == false) {
                Extra_Constraints.add(obj_fun[0] <= NewNDP[0] + Compute_Epsilon(NewNDP[0]));
                Extra_Constraints.add(obj_fun[1] <= NewNDP[1] + Compute_Epsilon(NewNDP[1]));
                objfunc = IloMinimize(env, DM_fun);
                model.add(objfunc);
                model.add(Extra_Constraints);
                cplex.extract(model);
                if (Enhancement_5 == true) {
                    for (int i = 0; i < Num_of_Variables; i++) {
                        startVal.add(Point[i]);
                    }
                    cplex.addMIPStart(startVar, startVal);
                }
                cplex.setParam(IloCplex::TiLim, TimeLimit);
                cplex.setParam(IloCplex::Threads, NumThreads);
                cplex.setParam(IloCplex::EpGap, RelativeGap);
                //cplex.exportModel("Model.lp");
                cplex.setOut(env.getNullStream());
                IP_Problems += 1;
                IP_UB_Finder_Triangle += 1;
                if (cplex.solve()) {
                    Number_of_Nodes += cplex.getNnodes();
                    for (int i = 0; i < 2; i++) {
                        NewNDP[i] = cplex.getValue(obj_fun[i]);
                    }
                    for (int i = 0; i < Num_of_Variables; i++) {
                        Point[i] = cplex.getValue(var_x[i]);
                    }
                    DMFun_Value = cplex.getValue(DM_fun);
                    Partial_DMValue2 = DMFun_Value;
                    if (DMFun_Value < GUB) {
                        GUB = DMFun_Value;
                        for (int i = 0; i < Num_of_Variables; i++) {
                            Opt_Point[i] = Point[i];
                        }
                        Z1 = NewNDP[0];
                        Z2 = NewNDP[1];
                        GUB_Counter = Iteration_Counter;
                    }
                }
                cplex.clear();
                model.remove(objfunc);
                model.remove(Extra_Constraints);
                Extra_Constraints.clear();
                startVal.clear();
            }
            if (Enhancement_2 == true && Infeasible_Index == false) {
                int x = 0;
                int sw = 0;
                while (x < Prior_Queue.size() && sw == 0) {
                    double Value1 = fabs(NewNDP[0] - Prior_Queue.at(x)->ObjVal[0][0]);
                    double Value2 = fabs(NewNDP[1] - Prior_Queue.at(x)->ObjVal[0][1]);
                    if (Value1 < fabs(Prior_Queue.at(x)->ObjVal[0][0] * Epsilon) && Value2 < fabs(Prior_Queue.at(x)->ObjVal[0][1] * Epsilon)) {
                        for (int j = 0; j < 2; j++) {
                            Prior_Queue.at(x)->ObjVal[0][j] = NewNDP[j];
                        }
                        for (int k = 0; k < Num_of_Variables; k++) {
                            Prior_Queue.at(x)->VarX[0][k] = Point[k];
                        }
                        Prior_Queue.at(x)->fxOpt[0] = true;
                        Prior_Queue.at(x)->fxVal[0] = DMFun_Value;
                        sw += 1;
                    }
                    x += 1;
                }
            }
        }

        z11 = emnt2->ObjVal[0];
        z12 = emnt2->ObjVal[1];
        z21 = NewNDP[0];
        z22 = NewNDP[1];
        gap_points1 = fabs(z11 - z21);
        gap_points2 = fabs(z12 - z22);
        if (emnt3->ObjVal[0] <= emnt2->ObjVal[0] && emnt3->ObjVal[1] <= NewNDP[1]) {
            DMValue1 = emnt3->fxVal;
        } else {
            if (gap_points1 + gap_points2 > Epsilon * 2 * z11) {
                Extra_Constraints.add(obj_fun[0] <= emnt2->ObjVal[0] + Compute_Epsilon(emnt2->ObjVal[0]));
                Extra_Constraints.add(obj_fun[1] <= NewNDP[1] + Compute_Epsilon(NewNDP[1]));
                objfunc = IloMinimize(env, DM_fun);
                model.add(objfunc);
                model.add(Extra_Constraints);
                cplex.extract(model);
                if (Enhancement_5 == true) {
                    for (int i = 0; i < Num_of_Variables; i++) {
                        startVal.add(Point[i]);
                    }
                    cplex.addMIPStart(startVar, startVal);
                }
                cplex.setParam(IloCplex::TiLim, TimeLimit);
                cplex.setParam(IloCplex::Threads, NumThreads);
                cplex.setParam(IloCplex::EpGap, RelativeGap);
                //cplex.exportModel("Model.lp");
                cplex.setOut(env.getNullStream());
                IP_Problems += 1;
                IP_UB_Finder_Triangle += 1;
                if (cplex.solve()) {
                    Number_of_Nodes += cplex.getNnodes();
                    DMValue1 = cplex.getValue(DM_fun);
                }
                cplex.clear();
                model.remove(objfunc);
                model.remove(Extra_Constraints);
                Extra_Constraints.clear();
                startVal.clear();
            } else {
                DMValue1 = DMFun_Value;
            }
        }
        element2->Weighted_Sum_Points(true);
        if (DMValue2 < GUB - Compute_Epsilon(GUB)) {
            int x = 0;
            Diff_Point_Proof[0][0] = fabs(emnt1->ObjVal[0] - element1->ObjVal[0]) / (fabs(element1->ObjVal[0]));
            Diff_Point_Proof[0][1] = fabs(emnt1->ObjVal[1] - element1->ObjVal[1]) / (fabs(element1->ObjVal[1]));
            if (Diff_Point_Proof[0][0] > Epsilon7 && Diff_Point_Proof[0][1] > Epsilon7) {
                Priority_Queue* emnt3 = new Priority_Queue;
                emnt3->Assign_Element_to_Queue(emnt1, element1, false, true, DMValue2);
                if (Prior_Queue.size() > 0) {
                    while (DMValue2 > Prior_Queue.at(x)->LBound) {
                        x += 1;
                        if (x == Prior_Queue.size()) {
                            break;
                        }
                    }
                    Prior_Queue.insert(Prior_Queue.begin() + x, (emnt3));
                    x += 1;
                } else {
                    Prior_Queue.push_back(emnt3);
                }
            }
        }
        if (DMValue1 < GUB - Compute_Epsilon(GUB)) {
            Diff_Point_Proof[1][0] = fabs(emnt2->ObjVal[0] - element2->ObjVal[0]) / (fabs(element2->ObjVal[0]));
            Diff_Point_Proof[1][1] = fabs(emnt2->ObjVal[1] - element2->ObjVal[1]) / (fabs(element2->ObjVal[1]));
            int x = 0;
            if (Diff_Point_Proof[1][0] > Epsilon7 && Diff_Point_Proof[1][1] > Epsilon7) {
                Priority_Queue* emnt4 = new Priority_Queue;
                emnt4->Assign_Element_to_Queue(element2, emnt2, false, true, DMValue1);
                if (Prior_Queue.size() > 0) {
                    while (DMValue1 > Prior_Queue.at(x)->LBound) {
                        x += 1;
                        if (x == Prior_Queue.size()) {
                            break;
                        }
                    }
                    Prior_Queue.insert(Prior_Queue.begin() + x, (emnt4));
                } else {
                    Prior_Queue.push_back(emnt4);
                }
            }
        }
    }
}
