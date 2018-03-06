#ifndef __CONFIG__H__
#define __CONFIG__H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>

#include <cpr/cpr.h>
#include "../include/nlohmann/json.hpp"

using namespace std;
using namespace cpr;
using json = nlohmann::json;

void get_access_token();
void create_workspace();
json read_config_file(std::string);

#endif