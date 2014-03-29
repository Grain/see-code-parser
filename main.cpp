#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include "function.h"

//COMMENTED OUT { } WILL MESS THIS UP

using namespace std;

vector<string> readFile(char * filename)
{
    ifstream input;

    input.open(filename);
    vector<string> file;

    if (input.is_open() == false)
    {
        //error opening
    }
    else    //read the entire file
    {
        string line;

        while (getline(input, line) != NULL)
        {
            if (line.size() > 0 && line[0] == '#')
            {
                //ignore line
            }
            else if (line.size() == 0)
            {
                //ignore
            }
            else
            {
                for (unsigned int i = 0; i < line.size(); ++i)  //if the entire line is whitespace don't put in vector
                {
                    if (isspace(line.at(i)) == false)
                    {
                        file.push_back(line);
                        break;
                    }
                }
            }
        }

        input.close();

//        for (unsigned int i = 0; i < file.size(); ++i)
//        {
//            cout << file.at(i) << endl;
//        }
    }

    return file;
}

vector<Function> makeFunctions(vector<string> fileContents)
{
    vector<Function> functions;

    int prevPos[] = {0, -1};    //where the previous loop read up to
                                //the -1 is so the next time it starts at 0,0

    int startPos[] = {0, 0};
    int stopPos[] = {0, 0};
    bool searching = false; //inside a function and looking for close bracket?
    int level;

    for (unsigned int a = 0; a < fileContents.size(); ++a)
    {
        for (unsigned int b = 0; b < fileContents.at(a).size(); ++b)
        {
            if (searching == true)
            {
                if (fileContents.at(a).at(b) == '{')
                {
                    level++;
                }
                else if (fileContents.at(a).at(b) == '}')
                {
                    level--;
                }

                if (level == 0) //close bracket for function found
                {
                    //check for semicolon after }
                    //if found then this is a union/struct, not a function. abort mission
                    searching = false;
                    stopPos[0] = a;
                    stopPos[1] = b;
                    //make new function
//                    cout << startPos[0] << " " << startPos[1] << endl;
//                    cout << stopPos[0] << " " << stopPos[1] << endl;
//                    cout << "function found" << endl;
                    if (startPos[0] == 0 && startPos[1] == 0) //the first char of file is curly bracket
                    {

                    }
                    else
                    {
                        //function "name" is prevPos to StartPos
                        string functionHeader;
                        for (int a = prevPos[0]; a <= startPos[0]; ++a) //make function header string
                        {
                            if (a == prevPos[0])    //first line
                            {
                                functionHeader.append(fileContents.at(a), prevPos[1] + 1, string::npos);
                            }
                            else if (a == startPos[0])      //last line
                            {
                                functionHeader.append(fileContents.at(a), 0, startPos[1]);
                            }
                            else        //lines in the middle, so can append the entire line
                            {
                                functionHeader.append(fileContents.at(a));
                            }
                        }

//                        cout << functionHeader << endl;

                        vector<string> functionContents;

                        for (int a = startPos[0]; a <= stopPos[0]; ++a) //make function contents vector
                        {
                            if (a == startPos[0])   //first line
                            {
                                string temp = fileContents.at(a).substr(startPos[1] + 1);
                                if (startPos[0] == stopPos[0])
                                {
                                    temp = fileContents.at(a).substr(startPos[1] + 1, stopPos[1] - (startPos[1] + 1));
                                }
                                if (temp.size() > 0)
                                {
                                    for (unsigned int i = 0; i < temp.size(); ++i)  //if the entire line is whitespace don't put in vector
                                    {
                                        if (isspace(temp.at(i)) == false)
                                        {
                                            functionContents.push_back(temp);
                                            break;
                                        }
                                    }
                                }
                            }
                            else if (a == stopPos[0])   //last line
                            {
                                if (stopPos[1] == 0)
                                {
                                    //} is first char of line, so don't need to add anything
                                }
                                else
                                {
                                    string temp = fileContents.at(a).substr(0, stopPos[1]);
                                    if (temp.size() > 0)
                                    {
                                        for (unsigned int i = 0; i < temp.size(); ++i)  //if the entire line is whitespace don't put in vector
                                        {
                                            if (isspace(temp.at(i)) == false)
                                            {
                                                functionContents.push_back(temp);
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                functionContents.push_back(fileContents.at(a));
                            }
                        }

//                        for (unsigned int i = 0; i < functionContents.size(); ++i)
//                        {
//                            cout << functionContents.at(i) << endl;
//                        }

                        Function temp(functionHeader, functionContents);
                        functions.push_back(temp);
                    }

                    prevPos[0] = stopPos[0];
                    prevPos[1] = stopPos[1];
                }
            }
            else
            {
                if (fileContents.at(a).at(b) == '{')    //open bracket for function found
                {
                    searching = true;
                    level = 1;
                    startPos[0] = a;
                    startPos[1] = b;
                }
                else if (fileContents.at(a).at(b) == ';')
                {
                    prevPos[0] = a;
                    prevPos[1] = b;
                }
            }
        }
    }

    return functions;
}

vector<string> removeComments(vector<string> fileContents)
{
    for (unsigned int a = 0; a < fileContents.size(); ++a)
    {
        for (unsigned int b = 0; b < fileContents.at(a).size() - 1; ++b)
        {
            if (fileContents.at(a).at(b) == '/' && fileContents.at(a).at(b + 1) == '/')
            {
                if (b == 0)
                    fileContents.erase(fileContents.begin() + a);
                else
                    fileContents.at(a).erase(b);
            }
        }
    }

    for (unsigned int a = 0; a < fileContents.size(); ++a)
    {
        for (unsigned int b = 0; b < fileContents.at(a).size() - 1; ++b)
        {
            if (fileContents.at(a).at(b) == '/' && fileContents.at(a).at(b + 1) == '*') //found start
            {
                for (unsigned int c = a; c < fileContents.size(); ++c)
                {
                    for (unsigned int d = b + 2; d < fileContents.at(c).size() - 1; ++d)
                    {
                        if (fileContents.at(c).at(d) == '*' && fileContents.at(c).at(d + 1) == '/') //found end
                        {
                            if (b != 0)
                                fileContents.at(a).erase(fileContents.at(a).begin() + b, fileContents.at(a).end());
                            if (a != c)
                            {
                                if (d + 2 != fileContents.at(c).size())
                                    fileContents.at(c).erase(fileContents.at(c).begin() + d, fileContents.at(c).end());
                                if (b == 0 && d + 2 == fileContents.at(c).size())
                                    fileContents.erase(fileContents.begin() + a, fileContents.begin() + c);
                                else if (b == 0)
                                    fileContents.erase(fileContents.begin() + a, fileContents.begin() + c - 1);
                                else if (d + 2 == fileContents.at(c).size())
                                    fileContents.erase(fileContents.begin() + a + 1, fileContents.begin() + c);
                                fileContents.erase(fileContents.begin() + a + 1, fileContents.begin() + c - 1);
                            }
                            goto outside;
                        }
                    }
                }
            }
            outside:;
        }
    }

    return fileContents;
}

int main(int argc, char* argv[])
{
    vector<string> fileContents;
    vector<Function> functions;

    if (argc > 1)
    {
        fileContents = readFile(argv[1]);
        if (fileContents.empty() == true)
        {
            cout << "Error opening file" << endl;
            return 0;
        }
    }
    else
    {
        //error: no file provided
        cout << "Must provide a c source file as an argument" << endl;
        return 0;
    }
    fileContents = removeComments(fileContents);
    functions = makeFunctions(fileContents);

    for (unsigned int i = 0; i < functions.size(); ++i)
    {
        stringstream temp;
        temp << "file" << i;
        functions.at(i).outputFile(temp.str());
    }
}
