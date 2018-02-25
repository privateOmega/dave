#include <iostream>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

int main()
{
    map<string, string> environmentVariables;
    string environment[9] = {"CONVERSATION_USERNAME", "CONVERSATION_PASSWORD", "WORKSPACE_ID", "DISCOVERY_USERNAME", "DISCOVERY_PASSWORD", "DISCOVERY_ENVIRONMENT_ID", "DISCOVERY_COLLECTION_ID", "NATURAL_LANGUAGE_UNDERSTANDING_USERNAME", "NATURAL_LANGUAGE_UNDERSTANDING_PASSWORD"};
    for (int i = 0; i < 9; i++)
    {
        if (getenv(environment[i].c_str()))
        {
            string char_string(getenv(environment[i].c_str()));
            environmentVariables[environment[i]] = char_string;
            cout << "Variable = " << environment[i] << ", Value= " << environmentVariables[environment[i]] << endl;
        }
        else
            cout << environment[i] << " doesn't exist" << endl;
    }
    return 0;
}