#include "function.h"


Function::Function(string a, vector<string> b)
{
    header = a;
    contents = b;

    statements = parse(0, 0).children;
}

Function::Function()
{
    //ctor
}

Function::~Function()
{
    //dtor
}

struct node Function::parse(int line, int column)
{
    int a = line;
    int b = column;

    while (a < contents.size())
    {
        while (b < contents.at(a).size())
        {
            if ((contents.at(a).size() - b >= 2) && contents.at(a).substr(b, 2) == "if")
            {
                cout << contents.at(a);
            }
            else if ((contents.at(a).size() - b >= 2) && contents.at(a).substr(b, 2) == "do")   //note: need to look for the while and ; corresponding to this do
            {
                cout << contents.at(a);
            }
            else if ((contents.at(a).size() - b >= 5) && contents.at(a).substr(b, 5) == "while")
            {
                cout << contents.at(a);
            }
            else if ((contents.at(a).size() - b >= 3) && contents.at(a).substr(b, 3) == "for")
            {
                cout << contents.at(a);
            }
            else if (contents.at(a).at(b) == ';')
            {

            }

            b++;
        }
        a++;
        b = 0;
    }
//    cout << "test" << endl;
}
