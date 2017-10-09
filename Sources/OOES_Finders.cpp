#include "Extern_Parameters.h"
#include "OOES_Finders.h"
#include "Split_Triangle_Horizontal.h"
#include "Split_Triangle_Vertical.h"

void LB_Finder_Point(Partial_Solutions* emnt1) {
    Extra_Constraints.add(obj_fun[0] <= emnt1->ObjVal[0] + Compute_Epsilon(emnt1->ObjVal[0]));
    Extra_Constraints.add(obj_fun[1] <= emnt1->ObjVal[1] + Compute_Epsilon(emnt1->ObjVal[1]));
    objfunc = IloMinimize(env, DM_fun);
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
    IP_Finder_Point += 1;
    if (cplex.solve()) {
        if (cplex.getValue(DM_fun) < GUB) {
            Number_of_Nodes += cplex.getNnodes();
            GUB = cplex.getValue(DM_fun);
            for (int i = 0; i < Num_of_Variables; i++) {
                Opt_Point[i] = cplex.getValue(var_x[i]);
            }
            Z1 = cplex.getValue(obj_fun[0]);
            Z2 = cplex.getValue(obj_fun[1]);
            GUB_Counter = Iteration_Counter;
        }
    }
    cplex.clear();
    model.remove(objfunc);
    model.remove(Extra_Constraints);
    Extra_Constraints.clear();
    startVal.clear();
}

void LB_Finder_Line(Partial_Solutions* emnt1, Partial_Solutions* emnt2) {
    double lambda1, lambda2, lambda3;
    lambda1 = emnt1->ObjVal[1] - emnt2->ObjVal[1];
    lambda2 = emnt2->ObjVal[0] - emnt1->ObjVal[0];
    lambda3 = (lambda1 * emnt1->ObjVal[0])+(lambda2 * emnt1->ObjVal[1]);
    Extra_Constraints.add((((lambda1 * obj_fun[0])+(lambda2 * obj_fun[1])) - lambda3) <= Epsilon);
    Extra_Constraints.add(obj_fun[1] <= emnt1->ObjVal[1] + Compute_Epsilon(emnt1->ObjVal[1]));
    Extra_Constraints.add(obj_fun[0] <= emnt2->ObjVal[0] + Compute_Epsilon(emnt2->ObjVal[0]));
    objfunc = IloMinimize(env, DM_fun);
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
    IP_Finder_Line += 1;
    if (cplex.solve()) {
        Number_of_Nodes += cplex.getNnodes();
        if (cplex.getValue(DM_fun) < GUB) {
            GUB = cplex.getValue(DM_fun);
            for (int i = 0; i < Num_of_Variables; i++) {
                Opt_Point[i] = cplex.getValue(var_x[i]);
            }
            Z1 = cplex.getValue(obj_fun[0]);
            Z2 = cplex.getValue(obj_fun[1]);
            GUB_Counter = Iteration_Counter;
        }
    }
    cplex.clear();
    model.remove(objfunc);
    model.remove(Extra_Constraints);
    Extra_Constraints.clear();
    startVal.clear();
}

void LB_Finder_Triangle(Partial_Solutions* emnt1, Partial_Solutions* emnt2) {
    Extra_Constraints.add(obj_fun[0] <= emnt2->ObjVal[0] + Compute_Epsilon(emnt2->ObjVal[0]));
    Extra_Constraints.add(obj_fun[1] <= emnt1->ObjVal[1] + Compute_Epsilon(emnt1->ObjVal[1]));
    objfunc = IloMinimize(env, DM_fun);
    model.add(objfunc);
    model.add(Extra_Constraints);
    cplex.extract(model);
    if (Enhancement_5 == true) {
        for (int i = 0; i < Num_of_Variables; i++) {
            startVal.add(emnt1->VarX[i]);
            ;
        }
        cplex.addMIPStart(startVar, startVal);
    }
    cplex.setParam(IloCplex::TiLim, TimeLimit);
    cplex.setParam(IloCplex::Threads, NumThreads);
    cplex.setParam(IloCplex::EpGap, RelativeGap);
    //cplex.exportModel("Model.lp");
    cplex.setOut(env.getNullStream());
    IP_Problems += 1;
    IP_Finder_Triangle += 1;
    Upper_Bound_Condition = false;
    if (cplex.solve()) {
        Number_of_Nodes += cplex.getNnodes();
        DMFun_Value = cplex.getValue(DM_fun);
        if (DMFun_Value < GUB - Compute_Epsilon(GUB)) {
            for (int i = 0; i < 2; i++) {
                NewNDP[i] = cplex.getValue(obj_fun[i]);
            }
            for (int i = 0; i < Num_of_Variables; i++) {
                Point[i] = cplex.getValue(var_x[i]);
            }
            Upper_Bound_Condition = true;
        }
    }
    cplex.clear();
    model.remove(objfunc);
    model.remove(Extra_Constraints);
    Extra_Constraints.clear();
    startVal.clear();
}

void UB_Finder(Partial_Solutions* emnt4, double DM_Fun_Value, Partial_Solutions* emnt5, Partial_Solutions* emnt6, bool Dir_Index) {
    double point_difference11 = fabs(emnt6->ObjVal[0] - emnt4->ObjVal[0]);
    double point_difference12 = fabs(emnt5->ObjVal[1] - emnt4->ObjVal[1]);
    double point_difference21 = (emnt6->ObjVal[0] - emnt5->ObjVal[0]) * Epsilon2;
    double point_difference22 = (emnt5->ObjVal[1] - emnt6->ObjVal[1]) * Epsilon2;
    double DMValue1(0), DMValue2(0);
    if (point_difference11 > point_difference21 && point_difference12 > point_difference22) {
        Extra_Constraints.add(obj_fun[0] <= emnt4->ObjVal[0] + Compute_Epsilon(emnt4->ObjVal[0]));
        Extra_Constraints.add(obj_fun[1] <= emnt4->ObjVal[1] + Compute_Epsilon(emnt4->ObjVal[1]));
        objfunc = IloMinimize(env, obj_fun[0] + obj_fun[1]);
        model.add(objfunc);
        model.add(Extra_Constraints);
        cplex.extract(model);
        if (Enhancement_5 == true) {
            for (int i = 0; i < Num_of_Variables; i++) {
                startVal.add(emnt4->VarX[i]);
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
            cplex.clear();
            model.remove(objfunc);
            model.remove(Extra_Constraints);
            Extra_Constraints.clear();
            startVal.clear();

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
        }
        cplex.clear();
        model.remove(objfunc);
        model.remove(Extra_Constraints);
        Extra_Constraints.clear();
        startVal.clear();

        double z11, z12, z21, z22, gap_points1, gap_points2;
        z11 = emnt4->ObjVal[0];
        z12 = emnt4->ObjVal[1];
        z21 = NewNDP[0];
        z22 = NewNDP[1];
        gap_points1 = fabs(z11 - z21);
        gap_points2 = fabs(z12 - z22);
        if (gap_points1 > Compute_Epsilon(emnt4->ObjVal[0]) || gap_points2 > Compute_Epsilon(emnt4->ObjVal[1])) {
            Extra_Constraints.add(obj_fun[0] <= emnt6->ObjVal[0] + Compute_Epsilon(emnt6->ObjVal[0]));
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

            Extra_Constraints.add(obj_fun[1] <= emnt5->ObjVal[1] + Compute_Epsilon(emnt5->ObjVal[1]));
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
            DMValue1 = DM_Fun_Value;
            DMValue2 = DM_Fun_Value;
        }
        Priority_Queue* emnt7 = new Priority_Queue;
        Priority_Queue* emnt8 = new Priority_Queue;
        Partial_Solutions* emnt9 = new Partial_Solutions;
        emnt9->Weighted_Sum_Points(true);

        if (DMValue1 < DMFun_Value) {
            if (Prior_Queue.size() > 0) {
                int x = 0;
                while (DMValue1 > Prior_Queue.at(x)->LBound) {
                    x += 1;
                    if (x == Prior_Queue.size()) {
                        break;
                    }
                }
                emnt8->Assign_Element_to_Queue(emnt9, emnt6, false, Dir_Index, DMValue1);
                Prior_Queue.insert(Prior_Queue.begin() + x, (emnt8));
            } else {
                emnt8->Assign_Element_to_Queue(emnt9, emnt6, false, Dir_Index, DMValue1);
                Prior_Queue.push_back(emnt8);
            }
        }
        if (DMValue2 < DMFun_Value) {
            if (Prior_Queue.size() > 0) {
                int x = 0;
                while (DMValue2 > Prior_Queue.at(x)->LBound) {
                    x += 1;
                    if (x == Prior_Queue.size()) {
                        break;
                    }
                }
                emnt7->Assign_Element_to_Queue(emnt5, emnt9, false, Dir_Index, DMValue2);
                Prior_Queue.insert(Prior_Queue.begin() + x, (emnt7));
            } else {
                emnt7->Assign_Element_to_Queue(emnt5, emnt9, false, Dir_Index, DMValue2);
                Prior_Queue.push_back(emnt7);
            }
        }
    } else {
        if (Dir_Index == false) {
            Splitting_Triangle_Horizontal(emnt5, emnt6, (emnt5->ObjVal[1] + emnt6->ObjVal[1]) / 2, emnt4);
        } else {
            Splitting_Triangle_Vertical(emnt5, emnt6, (emnt5->ObjVal[0] + emnt6->ObjVal[0]) / 2, emnt4);
        }
    }
}