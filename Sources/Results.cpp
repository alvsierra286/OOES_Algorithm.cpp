#include "Extern_Parameters.h"
#include "Results.h"

void Output_Results() {
    OutputFile.open("Output.txt");
    if (Infeasibility == false) {
        OutputFile << "Running_Time: " << (End_Time - Start_Time) / CLOCKS_PER_SEC << "  #IPs: " << IP_Problems << "\n";
        OutputFile << "Time_Finder_Point: " << Time_Finder_Point << "  #IPs_Finder_Point: " << IP_Finder_Point << " Number_Finder_Point: " << N_Finder_Point << "\n";
        OutputFile << "Time_Weighted_Sum: " << Time_Weighted_Sum << "  #IPs_Weighted_Sum: " << IP_Weighted_Sum << " Number_Weighted_Sum: " << N_Weighted_Sum << "\n";
        OutputFile << "Time_Line_Detector: " << Time_Line_Detector << "  #IPs_Line_Detector: " << IP_Line_Detector << " Number_Line_Detector: " << N_Line_Detector << "\n";
        OutputFile << "Time_Finder_Line: " << Time_Finder_Line << "  #IPs_Finder_Line: " << IP_Finder_Line << " Number_Finder_Line: " << N_Finder_Line << "\n";
        OutputFile << "Time_Finder_Triangle: " << Time_Finder_Triangle << "  #IPs_Finder_Triangle: " << IP_Finder_Triangle << " Number_Finder_Triangle: " << N_Finder_Triangle << "\n";
        OutputFile << "Time_UB_Finder_Triangle: " << Time_UB_Finder_Triangle << "  #IPs_UB_Finder_Triangle: " << IP_UB_Finder_Triangle << " Number_UB_Finder_Triangle: " << N_UB_Finder_Triangle << "\n";

        GLB = GUB;
        Relative_Gap = 0;
        Iteration_Counter += 1;
        OutputFile << "GLB= " << GLB << " GUB= " << GUB << " f(x)= " << GUB << "\n";
        OutputFile << "Z1= " << Z1 << " Z2= " << Z2 << "\n";
        OutputFile << "Average_Number_of_Nodes= " << Number_of_Nodes/IP_Problems;
    }
    /* We are done with Output File, so we close it.  */
    OutputFile.close();

}