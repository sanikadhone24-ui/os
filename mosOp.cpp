// MOS Program for Opcode Error and Operand Error
// Main Memory = 200 Words
// Block Size = 10 Words
// Program already loaded in memory

#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

char M[200][4];      // Main Memory
char IR[4];          // Instruction Register
char R[4];           // General Register
int IC;              // Instruction Counter
bool C = false;      // Toggle Register

ifstream fin("input.txt");
ofstream fout("output.txt");

void LOAD();
void EXECUTE();
void TERMINATE(string);

int main()
{
    LOAD();
    EXECUTE();

    fin.close();
    fout.close();

    cout << "Program Executed Successfully\n";
    cout << "Check output.txt\n";

    return 0;
}

void LOAD()
{
    char line[40];
    int m = 0;

    while(fin.getline(line,40))
    {
        // Skip control cards
        if(strncmp(line,"$AMJ",4)==0)
        {
            continue;
        }

        else if(strncmp(line,"$DTA",4)==0)
        {
            break;
        }

        else if(strncmp(line,"$END",4)==0)
        {
            break;
        }

        else
        {
            int k = 0;

            while(line[k] != '\0')
            {
                for(int j=0;j<4;j++)
                {
                    if(line[k] != '\0')
                        M[m][j] = line[k++];
                    else
                        M[m][j] = ' ';
                }
                m++;
            }
        }
    }
}

void EXECUTE()
{
    IC = 0;

    while(true)
    {
        // Load instruction into IR
        for(int i=0;i<4;i++)
        {
            IR[i] = M[IC][i];
        }

        IC++;

        char opcode[3];

        opcode[0] = IR[0];
        opcode[1] = IR[1];
        opcode[2] = '\0';

        // Halt
        if(IR[0] == 'H')
        {
            TERMINATE("NO ERROR");
            break;
        }

        // Opcode Check
        bool validOpcode = false;

        if(strcmp(opcode,"GD")==0 ||
           strcmp(opcode,"PD")==0 ||
           strcmp(opcode,"LR")==0 ||
           strcmp(opcode,"SR")==0 ||
           strcmp(opcode,"CR")==0 ||
           strcmp(opcode,"BT")==0)
        {
            validOpcode = true;
        }

        if(validOpcode == false)
        {
            TERMINATE("OPCODE ERROR");
            break;
        }

        // Operand Check
        if(IR[2]<'0' || IR[2]>'9' ||
           IR[3]<'0' || IR[3]>'9')
        {
            TERMINATE("OPERAND ERROR");
            break;
        }

        int addr = (IR[2]-'0')*10 + (IR[3]-'0');

        // Execute Instructions

        if(strcmp(opcode,"LR")==0)
        {
            for(int i=0;i<4;i++)
            {
                R[i] = M[addr][i];
            }
        }

        else if(strcmp(opcode,"SR")==0)
        {
            for(int i=0;i<4;i++)
            {
                M[addr][i] = R[i];
            }
        }

        else if(strcmp(opcode,"CR")==0)
        {
            C = true;

            for(int i=0;i<4;i++)
            {
                if(R[i] != M[addr][i])
                {
                    C = false;
                    break;
                }
            }
        }

        else if(strcmp(opcode,"BT")==0)
        {
            if(C == true)
            {
                IC = addr;
            }
        }

        else if(strcmp(opcode,"GD")==0)
        {
            // Dummy instruction
        }

        else if(strcmp(opcode,"PD")==0)
        {
            // Dummy instruction
        }
    }
}

void TERMINATE(string error)
{
    fout << "PROGRAM TERMINATED" << endl;
    fout << error << endl;
}