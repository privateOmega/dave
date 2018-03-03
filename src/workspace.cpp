#include "workspace.h"

using namespace std;
using namespace cpr;

string createWorkspace()
{
    map<string, string> environmentVariables;
    ifstream inputFile;
    ofstream jsonFile;
    jsonFile.open("file.json");
    stringstream strStream;
    inputFile.open("workspace.json");
    strStream << inputFile.rdbuf();
    string jsonStr = strStream.str();
    const char *jsonString = jsonStr.c_str();
    string environment[2] = {"CONVERSATION_USERNAME", "CONVERSATION_PASSWORD"};
    for (int i = 0; i < 2; i++)
    {
        if (getenv(environment[i].c_str()))
        {
            string char_string(getenv(environment[i].c_str()));
            environmentVariables[environment[i]] = char_string;
            cout << "Loaded " << environment[i] << " as " << environmentVariables[environment[i]] << endl;
        }
        else
        {
            cout << "Missing Credential " << environment[i] << endl;
            return "";
        }
    }
    auto res = Post(Url{"https://gateway.watsonplatform.net/authorization/api/v1/token?url=https://gateway.watsonplatform.net/conversation/api"}, Authentication{environmentVariables["CONVERSATION_USERNAME"], environmentVariables["CONVERSATION_PASSWORD"]});
    string tokenString = "CONVERSATION_TOKEN";
    // tokenString += res.text;
    // char *token = (char *)(tokenString.c_str());
    if (res.status_code == 200)
    {
        cout << "User Authorized" << endl;
        setenv((const char *)(tokenString.c_str()), (res.text.c_str()), 1);
    }
    else
        return "";
    char *accessToken = getenv((const char *)("CONVERSATION_TOKEN"));
    res = Post(Url{"https://gateway.watsonplatform.net/conversation/api/v1/workspaces?version=2018-02-16"}, Body{jsonString}, Header{{"X-Watson-Authorization-Token", accessToken}, {"Content-Type", "application/json"}});
    if (res.status_code == 201)
    {
        jsonFile << res.text;
        return res.text;
    }
    else
        return "";
}