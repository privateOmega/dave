#include "config.h"

using namespace std;
using namespace cpr;
using json = nlohmann::json;

json j;

void get_access_token()
{
    string conversationUsername = j["CONVERSATION_USERNAME"],
           conversationPassword = j["CONVERSATION_PASSWORD"],
           discoveryUsername = j["DISCOVERY_USERNAME"],
           discoveryPassword = j["DISCOVERY_PASSWORD"];
    if (!(conversationUsername.empty() || conversationPassword.empty()))
    {
        auto res = Post(Url{"https://gateway.watsonplatform.net/authorization/api/v1/token?url=https://gateway.watsonplatform.net/conversation/api"}, Authentication{conversationUsername, conversationPassword});
        if (res.status_code == 200)
        {
            j["CONVERSATION_ACCESS_TOKEN"] = res.text;
        }
        else
        {
            cout << "User unauthorized for CONVERSATION." << endl;
            exit(1);
        }
    }
    if (!(discoveryUsername.empty() || discoveryPassword.empty()))
    {
        // TO-DO change discovery URL
        auto res = Post(Url{"https://gateway.watsonplatform.net/authorization/api/v1/token?url=https://gateway.watsonplatform.net/discovery/api"}, Authentication{discoveryUsername, discoveryPassword});
        if (res.status_code == 200)
        {
            j["DISCOVERY_ACCESS_TOKEN"] = res.text;
        }
        else
        {
            cout << "User unauthorized for DISCOVERY." << endl;
            exit(1);
        }
    }
};

void create_workspace()
{
    ifstream inputFile("../config/workspace.json");
    json workspace = json::parse(inputFile);
    string conversationAccessToken = j["CONVERSATION_ACCESS_TOKEN"];
    auto res = Post(Url{"https://gateway.watsonplatform.net/conversation/api/v1/workspaces?version=2018-02-16"}, Body{workspace.dump()}, Header{{"X-Watson-Authorization-Token", conversationAccessToken}, {"Content-Type", "application/json"}});
    if (res.status_code == 201)
    {
        json response = json::parse(res.text);
        cout << "Workspace created." << endl;
        j["CONVERSATION_WORKSPACE_ID"] = response["workspace_id"];
    }
    else
    {
        cout << "Unable to create workspace." << endl;
        exit(1);
    }
};

json read_config_file(string fileName)
{
    ifstream inputFile(fileName);
    j = json::parse(inputFile);
    get_access_token();
    string workspaceId = j["CONVERSATION_WORKSPACE_ID"],
           environmentId = j["DISCOVERY_ENVIRONMENT_ID"],
           collectionId = j["DISCOVERY_COLLECTION_ID"];
    if (workspaceId.empty())
        create_workspace();
    // TO-DO Add code to create environment and collection if unable to find
    return j;
}