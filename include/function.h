#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Function
{
    public:
        Function(string, vector<string>);
        Function();
        virtual ~Function();
    protected:
    private:
        struct node
        {
            string statement;
            vector<struct node> children;
        };

        struct node parse(unsigned int, unsigned int);
        void printNode(struct node, int);
        string trim(string);

        string header;
        string contents;
        struct node statements;
};

#endif // FUNCTION_H
