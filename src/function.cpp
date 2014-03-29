#include "function.h"


Function::Function(string a, vector<string> b)
{
    header = a;

    for (unsigned int i = 0; i < b.size(); ++i)
    {
        b.at(i) = trim(b.at(i));
        contents.append(b.at(i));
//        cout << b.at(i) << endl;
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

void Function::outputFile(string filename)
{
    ofstream output(filename);
    if (output.is_open() == true)
    {
        output << "var code = {\"type\":\"function\", \"code\":\"";
        output << addBackslashes(statements.statement);
        output << "\", \"inner\":[";
        output << printList(statements.children);
        output << "]};";

        output.close();
    }
    else
    {
        //error
    }
}


struct Function::node Function::parse(unsigned int start, unsigned int stop)
{
    struct node value;
    int processedUpTo = start;

    for (unsigned int a = start; a < stop; ++a)
    {
        int controlFlow = 0;
        bool isDo = false;

        if (a + 2 <= stop && contents.at(a) == 'i' && contents.at(a + 1) == 'f')    //if
        {
            controlFlow = 2;
        }
        else if (a + 2 <= stop && contents.at(a) == 'd' && contents.at(a + 1) == 'o')    //do
        {
            isDo = true;
        }
        else if (a + 3 <= stop && contents.at(a) == 'f' && contents.at(a + 1) == 'o' && contents.at(a + 2) == 'r')  //for
        {
            controlFlow = 3;
        }
        else if (a + 7 <= stop && contents.at(a) == 'e' && contents.at(a + 1) == 'l' && contents.at(a + 2) == 's' && contents.at(a + 3) == 'e' && contents.at(a + 4) == ' ' && contents.at(a + 5) == 'i' && contents.at(a + 6) == 'f')  //else if
        {
            controlFlow = 6;
        }
        else if (a + 4 <= stop && contents.at(a) == 'e' && contents.at(a + 1) == 'l' && contents.at(a + 2) == 's' && contents.at(a + 3) == 'e')  //else
        {
            controlFlow = 12;
        }
        else if (a + 5 <= stop && contents.at(a) == 'w' && contents.at(a + 1) == 'h' && contents.at(a + 2) == 'i' && contents.at(a + 3 == 'l' && contents.at(a + 4) == 'e')) //while
        {
            controlFlow = 4;
        }

        if (controlFlow != 0)
        {
            string flowStatement;
            int level = 0;
            if (controlFlow == 12)   //else
            {
                flowStatement = "else";
            }
            else
            {
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
        else if (isDo)  //do while loop!    //similar to the other flow controls, except you have to get flow header at end
        {
            a++;    //since we didn't process header like the other flow controls

            string flowStatement;
            int level = 0;

            int controlStart = a;
            int controlEnd;
            bool blockFound = false;
            struct node newNode;

            while (a < stop)    //get the size of the curly brackets block, if it exists
            {
                if (contents.at(a) == ';' && blockFound == false)   //no open curly bracket, just one statement
                {
                    controlEnd = a;
                    string statement = trim(contents.substr(controlStart + 1, controlEnd - controlStart));

                    struct node child;
                    child.statement = statement;


//                    newNode.statement = flowStatement;
                    newNode.children.push_back(child);

//                    value.children.push_back(newNode);

//                    controlFlow = 0;
//                    processedUpTo = a + 1;
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

                        newNode = parse(controlStart + 1, controlEnd);
//                        newNode.statement = flowStatement;

//                        value.children.push_back(newNode);

//                        controlFlow = 0;
//                        processedUpTo = a + 1;
                        break;
                    }
                }

                a++;
            }

            a++;

            while (a < stop)        //get the flow control header (eg. while (1);)
            {
                flowStatement.push_back(contents.at(a));

                if (contents.at(a) == ';')
                {
                    flowStatement = "do " + trim(flowStatement);
//                    cout << flowStatement << endl;
                    newNode.statement = flowStatement;
                    value.children.push_back(newNode);
                    //do stuff
                    break;
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


string Function::printList(vector<struct node> sequence)    //to JSON
{
    string output;

    for (unsigned int i = 0; i < sequence.size(); ++i)
    {
        output.append("{");
        if (sequence.at(i).children.size() > 0)
        {
            string type;
            if (sequence.at(i).statement.at(0) == 'i')
                type = "if";
            else if (sequence.at(i).statement.at(0) == 'f')
                type = "for";
            else if (sequence.at(i).statement.at(0) == 'w')
                type = "while";
            else if (sequence.at(i).statement.at(0) == 'd')
                type = "do";
            else if (sequence.at(i).statement.at(0) == 'e' && sequence.at(i).statement.size() > 6)
                type = "else if";
            else if (sequence.at(i).statement.at(0) == 'e')
                type = "else";
            output.append("\"type\":\"");
            output.append(type);
            output.append("\", \"code\":\"");
            output.append(addBackslashes(sequence.at(i).statement));
            output.append("\", \"inner\":[");
            output.append(printList(sequence.at(i).children));
            output.append("]");
        }
        else
        {
            output.append("\"type\":\"statement\", \"code\":\"");
            output.append(addBackslashes(sequence.at(i).statement));
            output.append("\", \"inner\":[]");
        }

        output.append("},");
    }

    output.erase(output.end() - 1, output.end());

    return output;
}

void Function::printNode(struct node current, int level)    //just for testing and stuff
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

string Function::addBackslashes(string input)
{
    for (unsigned int i = 0; i < input.size(); ++i)
    {
        if (input.at(i) == '\\' || input.at(i) == '\"' || input.at(i) == '\'')
        {
            input.insert(input.begin() + i, '\\');
            i++;
        }
    }

    return input;
}
