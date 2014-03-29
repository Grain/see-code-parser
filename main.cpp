#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream input;

    if (argc > 1)
    {
        input.open(argv[1]);
        if (input.is_open() == false)
        {
            //error opening
            return 0;
        }
        else
        {
            string line;
            int next;

            while ((next = input.peek()) != EOF)
            {
                if (next == '#')
                {
                    //ignore line
                    getline(input, line);
                }
                else if (next == '\n')
                {
                    //ignore line
                    getline(input, line);
                }
                else
                {
                    getline(input, line);
                    cout << line << endl;
                }
            }
        }
    }
    else
    {
        //error: no file provided
        return 0;
    }

//    cout << "Hello world!" << endl;
//    return 0;
}
