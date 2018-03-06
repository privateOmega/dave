#include "dave.h"
#include "config.h"

static bool run;
json environmentVariables;

void Dave::load_config()
{
    string fileName = "../../daveConfig.json";
    environmentVariables = read_config_file(fileName);
}

void Dave::get_input()
{
    string input;
    getline(cin, input);
    cout << endl;
    if (!input.compare("quit"))
    {
        run = false;
        return;
    }
    json text = {
        {"input", {{"text", input}}}};
    string jsonString = text.dump();
    string conversationAccessToken = environmentVariables["CONVERSATION_ACCESS_TOKEN"],
           workspaceId = environmentVariables["CONVERSATION_WORKSPACE_ID"];
    string link = "https://gateway.watsonplatform.net/conversation/api/v1/workspaces/" + workspaceId + "/message?version=2018-02-16";
    auto res = Post(Url{link}, Body{jsonString}, Header{{"X-Watson-Authorization-Token", conversationAccessToken}, {"Content-Type", "application/json"}});
    if (res.status_code == 200)
    {
        json j = json::parse(res.text);
        for (json::iterator it = j["output"]["text"].begin(); it != j["output"]["text"].end(); ++it)
        {
            cout << "Dave: " << *it << endl;
        }
    }
    else
        cout << "Please try again." << endl;
}

int main(int argc, char **argv)
{
    run = true;
    Dave dave;
    dave.load_config();
    try
    {
        cout << "Enter 'quit' to exit." << endl;
        while (run)
        {
            cout << "You: ";
            dave.get_input();
            dave.print_response();
        }
    }
    catch (...)
    {
        cout << "Dave has stopped due to unknown reasons" << endl;
    }
    cout << "The conversation has ended." << endl;
    return 0;
}
