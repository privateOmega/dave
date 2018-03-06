#ifndef __DAVE__H__
#define __DAVE__H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <portaudio/portaudio.h>
#include "config.h"

using namespace std;
using json = nlohmann::json;

class Dave
{
  public:
    void load_config();
    void get_input();
    void print_response();

  private:
    void clear();
    bool run;
    json environmentVariables;
};

#endif