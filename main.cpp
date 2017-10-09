/* Opt Over Efficient Set for Bi-Objective Mixed Integer Programs
 * Creator = Alvaro Sierra Altamiranda
 * University of South Florida*/

#include <cstdlib>
#include "Parameters.h"
#include "Extern_Parameters.h"
#include <sys/time.h>           /*This is a package for use time functions */
#include "OOES_Solver.h"
#include "OOES_Finders.h"
#include "Read_Model.h"
#include "Variables_Declaration.h"
#include "Results.h"


using namespace std;

int main(int argc, char *argv[]) {

    Enhancements_Declaration(argv[1]);
    Reading_The_Input_File(argv[2]);
    ReadModel();
    Variable_Declaration();
    Start_Time = clock();
    bool top = false;
    bool bottom;
    T_and_B_Points(top, bottom);
    if (Infeasibility == false) {
        Partial_Solutions* element1 = new Partial_Solutions;
        element1 = Set_of_Partial_Solutions.at(0);
        Partial_Solutions* element2 = new Partial_Solutions;
        element2 = Set_of_Partial_Solutions.at(1);
        Priority_Queue* element = new Priority_Queue;
        element->Assign_Element_to_Queue(element1, element2, Shape, Direction, GLB);
        Prior_Queue.push_back(element);
        Set_of_Partial_Solutions.back()->~Partial_Solutions();
        Set_of_Partial_Solutions.pop_back();
        Set_of_Partial_Solutions.back()->~Partial_Solutions();
        Set_of_Partial_Solutions.pop_back();

        while (Prior_Queue.size() && Search_Done == false) {
            Priority_Queue* element = new Priority_Queue;
            element = Prior_Queue.at(0);
            GLB = element->LBound;
            Relative_Gap = fabs(GUB - GLB) / (fabs(GUB) + Epsilon);
            Iteration_Counter += 1;

            if (Relative_Gap < Epsilon6 || GUB <= GLB + Epsilon6) {
                Search_Done = true;
            } else {
                bool Bottom_Point = false;
                bool Top_Point = true;
                Partial_Solutions* element1 = new Partial_Solutions;
                element1->Assign_Partial_Values(Bottom_Point);
                Partial_Solutions* element2 = new Partial_Solutions;
                element2->Assign_Partial_Values(Top_Point);
                Set_of_Partial_Solutions.push_back(element1);
                Set_of_Partial_Solutions.push_back(element2);
                double z11, z12, z21, z22, gap_points1, gap_points2;
                z11 = element1->ObjVal[0];
                z12 = element1->ObjVal[1];
                z21 = element2->ObjVal[0];
                z22 = element2->ObjVal[1];
                element1->fxOpt;
                element2->fxOpt;
                gap_points1 = fabs(z11 - z21);
                gap_points2 = fabs(z12 - z22);
                Prior_Queue.front()->~Priority_Queue();
                Prior_Queue.erase(Prior_Queue.begin());
                if (gap_points1 + gap_points2 < Epsilon * 2) {
                    Start_Time_Finder_Point = clock();
                    N_Finder_Point += 1;
                    LB_Finder_Point(element1);
                    End_Time_Finder_Point = clock();
                    Time_Finder_Point += (End_Time_Finder_Point - Start_Time_Finder_Point) / CLOCKS_PER_SEC;
                } else {
                    if (element->Element_Shape == false) {
                        bool sw = 0;
                        cont = 0;
                        Start_Time_Weighted_Sum = clock();
                        N_Weighted_Sum += 1;
                        while (sw == 0) {
                            Weighted_Sum_Method(element1, element2);
                            if (Set_of_Partial_Solutions.size() <= cont + 1) {
                                sw = 1;
                            } else {
                                element1 = Set_of_Partial_Solutions.at(cont);
                                element2 = Set_of_Partial_Solutions.at(cont + 1);
                            }
                        }
                        End_Time_Weighted_Sum = clock();
                        Time_Weighted_Sum += (End_Time_Weighted_Sum - Start_Time_Weighted_Sum) / CLOCKS_PER_SEC;
                        cont = 1;
                        while (cont < Set_of_Partial_Solutions.size()) {
                            element1 = Set_of_Partial_Solutions.at(cont);
                            element2 = Set_of_Partial_Solutions.at(cont - 1);
                            Priority_Queue* element4 = new Priority_Queue;
                            element4->Assign_Element_to_Queue(element2, element1, 1, element->Element_Direction, element->LBound);
                            Prior_Queue.insert(Prior_Queue.begin() + cont - 1, element4);
                            cont += 1;
                        }
                    } else {
                        Start_Time_Line_Detector = clock();
                        N_Line_Detector += 1;
                        Line_Detector(element1, element2);
                        End_Time_Line_Detector = clock();
                        Time_Line_Detector += (End_Time_Line_Detector - Start_Time_Line_Detector) / CLOCKS_PER_SEC;
                        if (Connection_Index == true) {
                            Start_Time_Finder_Line = clock();
                            N_Finder_Line += 1;
                            if (Partial_Connection == false) {
                                LB_Finder_Line(element1, element2);
                            } else {
                                Partial_Solutions* element3 = new Partial_Solutions;
                                element3->Weighted_Sum_Points(false);
                                LB_Finder_Line(element1, element3);
                                element1 = element3;
                            }
                            End_Time_Finder_Line = clock();
                            Time_Finder_Line += (End_Time_Finder_Line - Start_Time_Finder_Line) / CLOCKS_PER_SEC;
                        }
                        if (Connection_Index == false || Partial_Connection == true) {
                            Start_Time_Finder_Triangle = clock();
                            N_Finder_Triangle += 1;
                            LB_Finder_Triangle(element1, element2);
                            End_Time_Finder_Triangle = clock();
                            Time_Finder_Triangle += (End_Time_Finder_Triangle - Start_Time_Finder_Triangle) / CLOCKS_PER_SEC;
                            if (Upper_Bound_Condition == true) {
                                Partial_Solutions* element3 = new Partial_Solutions;
                                element3->Weighted_Sum_Points(true);
                                Start_Time_UB_Finder_Triangle = clock();
                                N_UB_Finder_Triangle += 1;
                                UB_Finder(element3, DMFun_Value, element1, element2, element->Element_Direction);
                                End_Time_UB_Finder_Triangle = clock();
                                Time_UB_Finder_Triangle += (End_Time_UB_Finder_Triangle - Start_Time_UB_Finder_Triangle) / CLOCKS_PER_SEC;
                            }
                        }
                    }
                }
                while (Set_of_Partial_Solutions.size()) {
                    Set_of_Partial_Solutions.back()->~Partial_Solutions();
                    Set_of_Partial_Solutions.pop_back();
                }
            }
        }
    }
    End_Time = clock();
    Output_Results();
    return 0;
}
