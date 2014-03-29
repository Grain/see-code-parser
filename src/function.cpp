#include "function.h"


Function::Function(string a, vector<string> b)
{
    header = a;

    for (unsigned int i = 0; i < b.size(); ++i)
    {
        b.at(i) = trim(b.at(i));
        contents.append(b.at(i));
    }

    statements = parse(0, contents.size() - 1);
    statements.statement = header;

//    printNode(statements);
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
//    unsigned int a = line;
//    unsigned int b = column;
//
//    struct node value;
//
//    while (a < contents.size())
//    {
//        while (b < contents.at(a).size())
//        {
//            if ((contents.at(a).size() - b >= 2) && contents.at(a).substr(b, 2) == "if")
//            {
//                // which comes first, { or ;, and where is it
//
//                unsigned int j = a;
//                unsigned int k = b;
//
//                int result = isStatement(&j, &k);
//
//                string ifStatement;
//                string statement;
//
//                //figure out which part is the if statement header
//                int level = 0;
//                while (a < contents.size())
//                {
//                    while (b < contents.at(a).size())
//                    {
//                        ifStatement.push_back(contents.at(a).at(b));
//
//                        if (contents.at(a).at(b) == '(')
//                        {
//                            level++;
//                        }
//                        else if (contents.at(a).at(b) == ')')
//                        {
//                            level--;
//                            if (level == 0)
//                            {
//                                goto outside;
//                            }
//                        }
//                        b++;
//                    }
//                    a++;
//                    b = 0;
//                }
//                outside:
//
//                cout << ifStatement << endl;
//
//
//
////                if (result == 1)    //only 1 statement for hte if, no {}
////                {
////                    if (b + 1 >= contents.at(a).size())
////                    {
////                        statement = getStatement(a + 1, 0, j, k);
////                    }
////                    else
////                    {
////                        statement = getStatement(a, b + 1, j, k);
////                    }
////
////                    struct node childNode;
////                    childNode.statement = statement;
////
////                    struct node newNode;
////                    newNode.statement = ifStatement;
////                    newNode.children.push_back(childNode);
////
////                    if (k + 1 >= contents.at(j).size())
////                    {
////                        line = j + 1;
////                        column = 0;
////                    }
////                    else
////                    {
////                        line = j;
////                        column = k + 1;
////                    }
////                    a = j;
////                    b = k;
////
////                    value.children.push_back(newNode);
////                }
////                else if (result == 0)   //{
////                {
////                    struct node inside;
////
////                    if (k + 1 >= contents.at(j).size())
////                    {
////                        inside = parse(j + 1, 0);
////                    }
////                    else
////                    {
////                        inside = parse(j, k + 1);
////                    }
////
////                    inside.statement = ifStatement;
////                    value.children.push_back(inside);
//////                    printNode(inside);
////
////                    level = 1;
////
//////                    while (a < contents.size()) //go to the end of the if statement block (to the outside })
//////                    {
//////                        while (b < contents.at(a).size())
//////                        {
//////                            if (contents.at(a).at(b) == '{')
//////                            {
//////                                level++;
//////                            }
//////                            else if (contents.at(a).at(b) == '}')
//////                            {
//////                                level--;
//////                                if (level == 0)
//////                                {
//////                                    goto outside2;
//////                                }
//////                            }
//////                            b++;
//////                        }
//////                        a++;
//////                        b = 0;
//////                    }
//////                    outside2:
////
////                    if (b + 1 >= contents.at(a).size())
////                    {
////                        line = a + 1;
////                        column = 0;
////                    }
////                    else
////                    {
////                        line = a;
////                        column = b + 1;
////                    }
////                }
////                else    //reached end
////                {
////
////                }
//            }
//            else if ((contents.at(a).size() - b >= 5) && contents.at(a).substr(b, 5) == "while")
//            {
//            }
//            else if ((contents.at(a).size() - b >= 3) && contents.at(a).substr(b, 3) == "for")
//            {
//            }
//            else if (contents.at(a).at(b) == ';')   //individual statement
//            {
//                struct node newNode;
//                newNode.statement = getStatement(line, column, a, b);
//
//                if (b + 1 >= contents.at(a).size())
//                {
//                    line = a + 1;
//                    column = 0;
//                }
//                else
//                {
//                    line = a;
//                    column = b + 1;
//                }
//
//                value.children.push_back(newNode);
//            }
//            else if (contents.at(a).at(b) == '}')
//            {
////                level--;
////                if (level == 0) //finished
////                {
////                    if (b + 1 >= contents.at(a).size())
////                    {
////                        a++;
////                        b = 0;
////                    }
////                    else
////                    {
////                        b++;
////                    }
////
////                    return parse(a, b);
////                }
//
//                //finished
////                return value;
//            }
//
//            b++;
//        }
//        a++;
//        b = 0;
//    }
//
//    //finished
//    return value;

//    cout << "test" << endl;
}

string Function::getStatement(unsigned int startLine, unsigned int startColumn, unsigned int stopLine, unsigned int stopColumn)
{
    string statement;
    statement.append(trim(contents.at(startLine).substr(startColumn)));
//    cout << contents.at(startLine) << endl;
    for (int i = startLine + 1; i < stopLine; ++i)
    {
        statement.append(trim(contents.at(i)));
    }
    if (startLine != stopLine)
    {
        statement.append(trim(contents.at(stopLine).substr(0, stopColumn)));
    }

    return statement;
}

// 1 == TRUE, 0 == FALSE, -1 == reached end of file without finding either ; or {
int Function::isStatement(unsigned int * a, unsigned int * b)
{
    for (unsigned int j = *a; j < contents.size(); ++j)
    {
        for (unsigned int k = *b; k < contents.at(j).size(); ++k)
        {
            if (contents.at(j).at(k) == '{')
            {
                *a = j;
                *b = k;
                return 0;
            }
            else if (contents.at(j).at(k) == ';')
            {
                *a = j;
                *b = k;
                return 1;
            }
        }
    }
    return -1;
}

void Function::printNode(struct node current)
{
    cout << current.statement << endl;

    for (unsigned int i = 0; i < current.children.size(); ++i)
    {
        if (current.children.at(i).children.size() != 0)
        {
            printNode(current.children.at(i));
        }
        else
        {
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
