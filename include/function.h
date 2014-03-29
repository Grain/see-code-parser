#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <list>
#include <iostream>
#include <string>

using namespace std;

class Function
{
    public:
        Function(string, vector<string>);
        Function();
        virtual ~Function();
    protected:
    private:
        struct node parse(int, int);

        string header;
        vector<string> contents;

        struct node
        {
            string statement;
            list<struct node> children;
            int amountChildren;
        };

        list<struct node> statements;
};

#endif // FUNCTION_H
