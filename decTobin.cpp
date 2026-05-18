#include <iostream>
#include <string>
using namespace std;

// Decimal to Binary
void decimalToBinary(int n)
{
    string binary = "";

    if(n == 0)
    {
        cout << "Binary = 0";
        return;
    }

    while(n > 0)
    {
        binary = char((n % 2) + '0') + binary;
        n = n / 2;
    }

    cout << "Binary = " << binary << endl;
}

// Binary to Decimal
void binaryToDecimal(string binary)
{
    int decimal = 0;
    int base = 1;

    for(int i = binary.length() - 1; i >= 0; i--)
    {
        if(binary[i] == '1')
        {
            decimal += base;
        }
        base = base * 2;
    }

    cout << "Decimal = " << decimal << endl;
}

int main()
{
    int choice;

    cout << "1. Decimal to Binary" << endl;
    cout << "2. Binary to Decimal" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if(choice == 1)
    {
        int num;
        cout << "Enter decimal number: ";
        cin >> num;

        decimalToBinary(num);
    }
    else if(choice == 2)
    {
        string binary;
        cout << "Enter binary number: ";
        cin >> binary;

        binaryToDecimal(binary);
    }
    else
    {
        cout << "Invalid choice";
    }

    return 0;
}