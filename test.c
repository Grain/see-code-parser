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

