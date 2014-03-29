#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include "function.h"

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

        for (unsigned int i = 0; i < file.size(); ++i)
        {
            cout << file.at(i) << endl;
        }
    }

    return file;
}

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        vector<string> fileContents = readFile(argv[1]);
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


}
