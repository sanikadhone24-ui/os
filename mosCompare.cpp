#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

char M[200][5];      // Main Memory
char IR[5];          // Instruction Register
char R[5];           // General Purpose Register

int IC = 0;          // Instruction Counter
bool C = false;      // Toggle Register

ifstream fin("compare_input.txt");
ofstream fout("compare_output.txt");

// ---------------- MOS ----------------
void MOS(string msg)
{
    fout << msg << endl;
}

// ---------------- LOAD ----------------
void LOAD()
{
    char line[40];
    int m = 0;

    while(fin.getline(line, 40))
    {
        // Start of Program
        if(strncmp(line, "$AMJ", 4) == 0)
        {
            continue;
        }

        // Data Begins
        else if(strncmp(line, "$DTA", 4) == 0)
        {
            break;
        }

        // End
        else if(strncmp(line, "$END", 4) == 0)
        {
            break;
        }

        // Load Instructions
        else
        {
            strcpy(M[m], line);
            m++;
        }
    }

    // Load Data into Memory from Block 10
    int dataLoc = 10;

    while(fin.getline(line, 40))
    {
        if(strncmp(line, "$END", 4) == 0)
            break;

        strcpy(M[dataLoc], line);

        dataLoc++;
    }
}

// ---------------- EXECUTE ----------------
void EXECUTE()
{
    while(true)
    {
        strcpy(IR, M[IC]);

        IC++;

        // ---------------- HALT ----------------
        if(IR[0] == 'H')
        {
            MOS("Program Executed Successfully");
            break;
        }

        int loc =
            (IR[2]-'0') * 10 +
            (IR[3]-'0');

        // ---------------- GD ----------------
        if(IR[0]=='G' && IR[1]=='D')
        {
            MOS("Data Loaded Successfully");
        }

        // ---------------- PD ----------------
        else if(IR[0]=='P' && IR[1]=='D')
        {
            for(int j = 0; j < 4; j++)
            {
                if(M[loc][j] != '\0')
                    fout << M[loc][j];
            }

            fout << endl;
        }

        // ---------------- LR ----------------
        else if(IR[0]=='L' && IR[1]=='R')
        {
            strcpy(R, M[loc]);
        }

        // ---------------- CR ----------------
        else if(IR[0]=='C' && IR[1]=='R')
        {
            if(strcmp(R, M[loc]) == 0)
                C = true;
            else
                C = false;
        }

        // ---------------- BT ----------------
        else if(IR[0]=='B' && IR[1]=='T')
        {
            if(C == true)
                IC = loc;
        }

        // ---------------- ERROR ----------------
        else
        {
            MOS("Operation Code Error");
            break;
        }
    }
}

// ---------------- MAIN ----------------
int main()
{
    LOAD();

    EXECUTE();

    fin.close();
    fout.close();

    cout << "Execution Completed\n";
    cout << "Check compareOutput.txt\n";

    return 0;
}