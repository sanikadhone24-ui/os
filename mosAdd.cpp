#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

char M[200][5];      // Main Memory
char IR[5];          // Instruction Register
char R[5];           // General Purpose Register

int IC = 0;          // Instruction Counter
bool C = false;      // Toggle Register

ifstream fin("mosAddInput.txt");
ofstream fout("mosAddOutput.txt");

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

        // Data Card
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

    // Load Data from Location 10
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

        // ---------------- H ----------------
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
            fout << "Result = ";

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

        // ---------------- SR ----------------
        else if(IR[0]=='S' && IR[1]=='R')
        {
            strcpy(M[loc], R);
        }

        // ---------------- AD ----------------
        // New Arithmetic Instruction
        else if(IR[0]=='A' && IR[1]=='D')
        {
            int num1 = atoi(R);
            int num2 = atoi(M[loc]);

            int sum = num1 + num2;

            sprintf(R, "%04d", sum);
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
    cout << "Check mosAddOutput.txt\n";

    return 0;
}