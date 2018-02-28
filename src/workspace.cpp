#include "workspace.h"

using namespace std;
using namespace cpr;

string createWorkspace()
{
    map<string, string> environmentVariables;
    ifstream inputFile;
    stringstream strStream;
    inputFile.open("workspace.json");
    strStream << inputFile.rdbuf();
    string jsonStr = strStream.str();
    string environment[3] = {"CONVERSATION_USERNAME", "CONVERSATION_PASSWORD", "WORKSPACE_ID"};
    for (int i = 0; i < 3; i++)
    {
        if (getenv(environment[i].c_str()))
        {
            string char_string(getenv(environment[i].c_str()));
            environmentVariables[environment[i]] = char_string;
            cout << "Loaded " << environment[i] << " as " << environmentVariables[environment[i]] << endl;
        }
        else
            cout << environment[i] << " doesn't exist" << endl;
    }
    auto r = Post(Url{"https://gateway.watsonplatform.net/conversation/api/v1/workspaces?version=2018-02-16"},
                  Authentication{environmentVariables["CONVERSATION_USERNAME"], environmentVariables["CONVERSATION_PASSWORD"]},
                  Body{jsonStr.c_str()});
    cout << r.text << r.status_code;
    if (r.status_code == 200)
        return r.text;
    else
        return "";
}