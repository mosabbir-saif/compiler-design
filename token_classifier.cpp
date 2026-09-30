#include <bits/stdc++.h>
using namespace std;

// Function to check Identifier
bool isIdentifier(string str)
{
    // First character must be alphabet or underscore
    if (!(isalpha(str[0]) || str[0] == '_'))
        return false;

    // Remaining characters can be alphabet, digit, or underscore
    for (int i = 1; i < str.length(); i++)
    {
        if (!(isalnum(str[i]) || str[i] == '_'))
            return false;
    }

    return true;
}

// Function to check Constant (integer or floating point)
bool isConstant(string str)
{
    bool hasDecimal = false;

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
        {
            if (hasDecimal)
                return false; // more than one decimal point

            hasDecimal = true;
        }
        else if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

// Function to check Operator
bool isOperator(string str)
{
    vector<string> ops = {
        "+", "-", "*", "/", "%", "=",
        "==", "!=", "<", ">", "<=", ">=",
        "&&", "||", "!", "++", "--",
        "+=", "-=", "*=", "/="
    };

    for (string op : ops)
    {
        if (str == op)
            return true;
    }

    return false;
}

int main()
{
    string input;

    cout << "Enter a token: ";
    cin >> input;

    if (isIdentifier(input))
    {
        cout << input << " is an Identifier" << endl;
    }
    else if (isConstant(input))
    {
        cout << input << " is a Constant" << endl;
    }
    else if (isOperator(input))
    {
        cout << input << " is an Operator" << endl;
    }
    else
    {
        cout << input << " is Invalid" << endl;
    }

    return 0;
}