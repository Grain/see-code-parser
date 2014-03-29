#include "function.h"


Function::Function(string a, vector<string> b)
{
    header = a;

    for (unsigned int i = 0; i < b.size(); ++i)
    {
        b.at(i) = trim(b.at(i));
        contents.append(b.at(i));
    }

    statements = parse(0, contents.size());
    statements.statement = header;

    printNode(statements, 1);
}

Function::Function()
{
    //ctor
}

Function::~Function()
{
    //dtor
}

struct Function::node Function::parse(unsigned int start, unsigned int stop)
{
    struct node value;
    int processedUpTo = start;

    for (unsigned int a = start; a < stop; ++a)
    {
        int controlFlow = 0;

        if (a + 2 <= stop && contents.at(a) == 'i' && contents.at(a + 1) == 'f')    //if
        {
            controlFlow = 2;
        }
        else if (a + 3 <= stop && contents.at(a) == 'f' && contents.at(a + 1) == 'o' && contents.at(a + 2) == 'r')  //for
        {
            controlFlow = 3;
        }
        else if (a + 5 <= stop && contents.at(a) == 'w' && contents.at(a + 1) == 'h' && contents.at(a + 2) == 'i' && contents.at(a + 3 == 'l' && contents.at(a + 4) == 'e')) //while
        {
            controlFlow = 4;
        }

        if (controlFlow != 0)
        {
            string flowStatement;
            int level = 0;
            while (a < stop)        //get the flow control header (eg. if (soemthing) or for (i = 0;;))
            {
                flowStatement.push_back(contents.at(a));

                if (contents.at(a) == '(')
                    level++;
                else if (contents.at(a) == ')')
                {
                    level--;
                    if (level == 0)
                    {
                        break;
                        controlFlow = 0;
                    }
                }

                a++;
            }

//            cout << flowStatement << endl;

            int controlStart = a;
            int controlEnd;
            bool blockFound = false;

            while (a < stop)    //get the size of the curly brackets block, if it exists
            {
                if (contents.at(a) == ';' && blockFound == false)   //no open curly bracket, just one statement
                {
                    controlEnd = a;
                    string statement = contents.substr(controlStart + 1, controlEnd - controlStart);

                    struct node child;
                    child.statement = statement;

                    struct node newNode;
                    newNode.statement = flowStatement;
                    newNode.children.push_back(child);

                    value.children.push_back(newNode);

                    controlFlow = 0;
                    processedUpTo = a + 1;
                    break;
                }
                else if (contents.at(a) == '{')
                {
                    if (level == 0)
                    {
                        controlStart = a;
                    }
                    level++;
                    blockFound = true;
                }
                else if (contents.at(a) == '}') //found the end of the curly brackets
                {
                    level--;
                    if (level == 0)
                    {
                        controlEnd = a;

                        struct node newNode = parse(controlStart + 1, controlEnd);
                        newNode.statement = flowStatement;

                        value.children.push_back(newNode);

                        controlFlow = 0;
                        processedUpTo = a + 1;
                        break;
                    }
                }

                a++;
            }
        }
        else    //no control flow here! just regular statements probably
        {
            if (contents.at(a) == ';')
            {
                string statement = contents.substr(processedUpTo, a - processedUpTo + 1);
//                cout << statement << endl;

                struct node newNode;
                newNode.statement = statement;

                value.children.push_back(newNode);

                processedUpTo = a + 1;
            }
        }
    }

    return value;
}

void Function::printNode(struct node current, int level)
{
    for (int i = 1; i < level; ++i)
        cout << '\t';
    cout << current.statement << endl;

    for (unsigned int i = 0; i < current.children.size(); ++i)
    {
        if (current.children.at(i).children.size() != 0)
        {
            printNode(current.children.at(i), level + 1);
        }
        else
        {
            for (int i = 0; i < level; ++i)
                cout << '\t';
            cout << current.children.at(i).statement << endl;
        }
    }
}

string Function::trim(string input)
{
   size_t p = input.find_first_not_of(" \n\r\t");
   input.erase(0, p);

   p = input.find_last_not_of(" \n\r\t");
   if (string::npos != p)
      input.erase(p + 1);
    return input;
}
