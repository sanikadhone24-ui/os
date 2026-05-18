#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

char M[200][5];      // Main Memory
char IR[5];          // Instruction Register
char R[5];           // General Purpose Register

int IC = 0;          // Instruction Counter
bool C = false;      // Toggle Register

ifstream fin("hello_input.txt");
ofstream fout("hello_output.txt");

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
            m = 0;
        }

        // Start of Data
        else if(strncmp(line, "$DTA", 4) == 0)
        {
            break;
        }

        // End
        else if(strncmp(line, "$END", 4) == 0)
        {
            break;
        }

        // Store Instructions
        else
        {
            strcpy(M[m], line);
            m++;
        }
    }

    // Load Data into Memory from Location 10
    int dataLoc = 10;

    while(fin.getline(line, 40))
    {
        if(strncmp(line, "$END", 4) == 0)
            break;

        int k = 0;
        int start = dataLoc;

        while(line[k] != '\0')
        {
            for(int j = 0; j < 4; j++)
            {
                if(line[k] != '\0')
                {
                    M[dataLoc][j] = line[k];
                    k++;
                }
                else
                {
                    M[dataLoc][j] = '\0';
                }
            }

            dataLoc++;
        }
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

        // ---------------- VALIDATE OPCODE ----------------
        if(
            !(IR[0]=='G' && IR[1]=='D') &&
            !(IR[0]=='P' && IR[1]=='D') &&
            !(IR[0]=='L' && IR[1]=='R') &&
            !(IR[0]=='S' && IR[1]=='R') &&
            !(IR[0]=='C' && IR[1]=='R') &&
            !(IR[0]=='B' && IR[1]=='T')
          )
        {
            MOS("Operation Code Error");
            break;
        }

        // ---------------- VALIDATE OPERAND ----------------
        if(!(isdigit(IR[2]) && isdigit(IR[3])))
        {
            MOS("Operand Error");
            break;
        }

        int loc = (IR[2]-'0')*10 + (IR[3]-'0');

        // ---------------- GD ----------------
        if(IR[0]=='G' && IR[1]=='D')
        {
            MOS("Data Loaded Successfully");
        }

        // ---------------- PD ----------------
        else if(IR[0]=='P' && IR[1]=='D')
        {
            for(int i = loc; i < loc + 10; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(M[i][j] != '\0')
                        fout << M[i][j];
                }
            }

            fout << endl;
        }

        // ---------------- LR ----------------
        else if(IR[0]=='L' && IR[1]=='R')
        {
            strcpy(R, M[loc]);
        }

        // ---------------- SR ----------------
        else if(IR[0]=='S' && IR[1]=='R')
        {
            strcpy(M[loc], R);
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
    }
}

// ---------------- MAIN ----------------
int main()
{
    LOAD();

    EXECUTE();

    fin.close();
    fout.close();

    cout << "Execution Completed.\n";
    cout << "Check hello_output.txt file\n";

    return 0;
}