#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

char M[400][5];     // Main Memory
char IR[5];         // Instruction Register
char R[5];          // General Purpose Register

int IC = 0;         // Instruction Counter
bool C = false;     // Toggle Register

int PTR = 0;        // Page Table Register

ifstream fin("welcome_input.txt");
ofstream fout("welcome_output.txt");

// ---------------- MOS ----------------
void MOS(string msg)
{
    fout << msg << endl;
}

// ---------------- ADDRESS MAP ----------------
int ADDRESSMAP(int VA)
{
    int p = VA / 10;       // Page Number
    int d = VA % 10;       // Offset

    char temp[5];

    strcpy(temp, M[PTR + p]);

    int frame =
        (temp[2] - '0') * 10 +
        (temp[3] - '0');

    return frame + d;
}

// ---------------- LOAD WITH PAGING ----------------
void LOAD()
{
    char line[50];

    // Page Table starts at 0
    PTR = 0;

    // Page Table Entry
    // Virtual Page 0 → Frame 10
    strcpy(M[0], "0010");

    // Program loaded into frame 10
    int m = 10;

    while(fin.getline(line, 50))
    {
        if(strncmp(line, "$AMJ", 4) == 0)
        {
            continue;
        }

        else if(strncmp(line, "$DTA", 4) == 0)
        {
            break;
        }

        else if(strncmp(line, "$END", 4) == 0)
        {
            break;
        }

        else
        {
            strcpy(M[m], line);
            m++;
        }
    }

    // Data stored directly from 50
    int dataLoc = 50;

    while(fin.getline(line, 50))
    {
        if(strncmp(line, "$END", 4) == 0)
            break;

        int k = 0;

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
    // Program starts from frame 10
    IC = 10;

    while(true)
    {
        strcpy(IR, M[IC]);

        IC++;

        // HALT
        if(IR[0] == 'H')
        {
            MOS("Program Executed Successfully");
            break;
        }

        int operand =
            (IR[2]-'0') * 10 +
            (IR[3]-'0');

        // Direct Data Address
        int RA = operand;

        // GD
        if(IR[0]=='G' && IR[1]=='D')
        {
            MOS("Data Loaded Successfully");
        }

        // PD
        else if(IR[0]=='P' && IR[1]=='D')
        {
            for(int i = RA; i < RA + 5; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    if(M[i][j] != '\0')
                        fout << M[i][j];
                }
            }

            fout << endl;
        }

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
    cout << "Check welcome_output.txt\n";

    return 0;
}