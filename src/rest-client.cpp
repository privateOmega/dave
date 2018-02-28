#include <iostream>
#include <cpr/cpr.h>
using namespace std;
using namespace cpr;
int main(int argc, char **argv)
{
    auto r = Get(Url{"https://api.github.com/repos/whoshuu/cpr/contributors"},
                 Authentication{"user", "password"},
                 Parameters{{"anon", "true"}});
    r.status_code;            // 200
    r.header["content-type"]; // application/json; charset=utf-8
    r.text;                   // JSON text string
    cout << r.text;
}
