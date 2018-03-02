#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <cpr/cpr.h>
#include "workspace.h"

using namespace std;
using namespace cpr;

int main(int argc, char **argv)
{
    string workspaceID;
    map<string, string> environmentVariables;
    string environment[3] = {"CONVERSATION_USERNAME", "CONVERSATION_PASSWORD", "WORKSPACE_ID"};
    for (int i = 0; i < 3; i++)
    {
        if (getenv(environment[i].c_str()))
        {
            string char_string(getenv(environment[i].c_str()));
            environmentVariables[environment[i]] = char_string;
            cout << "Loaded " << environment[i] << " as " << environmentVariables[environment[i]] << endl;
        }
    }
    if (!environmentVariables["WORKSPACE_ID"].empty())
    {
        cout << "Fetching Workspace details" << endl;
        auto res = Get(Url{"https://gateway.watsonplatform.net/conversation/api/v1/workspaces?version=2018-02-16"}, Authentication{environmentVariables["CONVERSATION_USERNAME"], environmentVariables["CONVERSATION_PASSWORD"]});
        if (res.status_code == 400)
        {
            cout << "Unable to find the workspace ID on Watson. Don't worry creating one for you now." << endl;
            workspaceID = createWorkspace();
            if (workspaceID.empty())
            {
                cout << "Unable to create workspace on watson." << endl;
                return 0;
            }
            else
                environmentVariables["WORKSPACE_ID"] = workspaceID;
        }
    }
    else
    {
        cout << "It seems like you have forgot to set Workspace ID on your machine. Don't worry creating one for you now." << endl;
        workspaceID = createWorkspace();
        if (workspaceID.empty())
        {
            cout << "Unable to create workspace on watson." << endl;
            return 0;
        }
        else
            environmentVariables["WORKSPACE_ID"] = workspaceID;
    }
    auto res = Post(Url{"https://gateway.watsonplatform.net/authorization/api/v1/token?url=https://gateway.watsonplatform.net/conversation/api"}, Authentication{environmentVariables["CONVERSATION_USERNAME"], environmentVariables["CONVERSATION_PASSWORD"]});
    string tokenString = "CONVERSATION_TOKEN";
    if (res.status_code == 200)
    {
        cout << "User Authorized" << endl;
        setenv((const char *)(tokenString.c_str()), (res.text.c_str()), 1);
    }
    else
    {
        cout << "Unauthorized user" << endl;
        return 0;
    }
    char *accessToken = getenv((const char *)("CONVERSATION_TOKEN"));
    res = Post(Url{"https://gateway.watsonplatform.net/conversation/api/v1/workspaces?version=2018-02-16"}, Header{{"X-Watson-Authorization-Token", accessToken}, {"Content-Type", "application/json"}});
    cout << res.text << res.status_code;
    return 0;
}