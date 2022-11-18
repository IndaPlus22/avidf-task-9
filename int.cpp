//
//This project has been influenced by the help and work of much wiser comrades 

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <any>
using namespace std;


//Vector to list instructions
vector<pair<string, vector<int>>> instructions;

//Registers
int registers[] = {0, 0, 0, 0};

//Functions 
//using counter and vector for order
void input(char *argv[]);
void parseInstruct(vector<vector<string>> inputInst);
void run();

//Main
int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "Wrong input, try again";
        exit(1);
    }
    input(argv);
    run();
    return 0;
}

//Reading file input
void input(char *argv[])
{
    ifstream input(argv[1]);
    if (input.is_open() && input.good())
    {
        vector<vector<string>> inputInstructions;

        string line;
        while (getline(input, line))
        {
            stringstream splitString(line);
            vector<string> result;

            bool inputOK = false;
            while (splitString.good())
            {
                string subString;
                getline(splitString, subString, ' '); 

                // Exclude empty strings
                if (subString.length() > 0)
                {
                    if (!inputOK)
                    {
                        inputInstructions.push_back(vector<string>());
                    }
                    inputOK = true;
                    result.push_back(subString);
                    inputInstructions[inputInstructions.size() - 1].push_back(subString);
                }

                //Keep empty lines for jump
                if (!inputOK)
                {
                    inputInstructions.push_back(vector<string>{"Empty"});
                }

                // "//" for comments
                if (subString.rfind("//", 0) == 0)
                break;

            }
        }
        input.close();

        parseInstruct(inputInstructions);
    }
}

void parseInstruct(vector<vector<string>> inputInstructions)
{
    bool error = false;

    //Instructions
    for (int i = 0; i < inputInstructions.size(); i++)
    {
        vector<string> instruction = inputInstructions[i];
        string instruct = instruction[0];

        //Error handling 
        if (instruct == "add" || instruct == "sub" || instruct == "set" || instruct == "jeq")
        {
            vector<int> registery;

            //Check instruct size
            if (instruction.size() != 4)
            {
                cout << "Invalid number of instructions and arguments \n";
                error = true;
            }

            // Check all registers
            for (int j = 1; j < instruction.size() - 1; j++)
            {
                if (instruction[j][0] != '#')
                {
                    cout << "Instruction missing prefix # \n";
                    error = true;
                }

                //Checks if instructions and arguments are defined
                int index = stoi(instruction[j]);
                registery.push_back(index);
                if (index < 0 || (j == 1 && index < 1) || index > 3)
                {
                    cout << "Invalid registery \n";
                    error = true;
                }

                //Remove # and space
                replace(instruction[j].begin(), instruction[j].end(), '#', ' '); 
            }

            //Push instructions
            instructions.push_back(make_pair(instruct, vector<int>{registery[0], registery[1] }));
        }

        //Jump instruct
        else if (instruct == "j")
        {
            if (instruction.size() != 2)
            {
                cout << "Number of instructions excceds limit \n";
                error = true;
            }

            int jump = stoi(instruction[1]);
            if (jump < -16 || jump > 15)
            {
                cout << "Instruction value exceeds limit \n";
                error = true;
            }

            instructions.push_back(make_pair(instruct, vector<int>{jump}));
        }

        //Special instructions
        else if (instruct == "input" || instruct == "print" || instruct == "exit")
        {
            if (instruction.size() != 1)
            {
                cout << "Arguments exceed limit \n";
                error = true;
            }

            instructions.push_back(make_pair(instruct, vector<int>{}));
        }
        else if (instruct == "empty")
        {
            instructions.push_back(make_pair(instruct, vector<int>{}));
        }
        else
        {
            cout << "Invalid command: #" << i << "\n";
            error = true;
        }
    }
}

void run()
{
    int currentline = 0;
    
    while (true)
    {
        pair<string, vector<int>> instruction = instructions[currentline];
        string instruct = instruction.first;
        vector<int> arguments = instruction.second;

        //Interpeting instructions
        if (instruct == "jeq")
        {
            //Jump one spot
            if (registers[arguments[0]] == registers[arguments[1]])
            {
            currentline += arguments[2]; 
            }
            
            //Jump two spots
            else if (arguments[2] == 0)
            currentline++; 
            
        }
        else if (instruct == "add")
        {
            registers[arguments[0]] += registers[arguments[1]];
            registers[arguments[0]] += arguments[2];
        }
        else if (instruct == "set")
        {
            registers[arguments[0]] = registers[arguments[1]];
            registers[arguments[0]] += arguments[2];
        }
        else if (instruct == "sub")
        {
            registers[arguments[0]] -= registers[arguments[1]];
            registers[arguments[0]] -= arguments[2];
        }

        else if (instruct == "j")
        currentline += arguments[0];
        
        else if (instruct == "input")
        cin >> registers[1];

        else if (instruct == "print")
        cout << registers[1] << "\n";

        else if (instruct == "exit")
        break;
        
        currentline++;
    }
}


