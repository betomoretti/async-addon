#include <napi.h>
#include <vector>
#include <iostream>
#include "worker.h"
#include <typeinfo>
#include "../include/json/single_include/nlohmann/json.hpp"


using json = nlohmann::json;
using namespace std;

void Worker::Execute()
{
  cout << "Running worker\n";
  // if (breakIt) {
  //   SetError("Something happened");
  // }

  std::string ret(buffer);
  auto j = json::parse(ret);

  std::cout << j.size() << std::endl;
  for (unsigned int i = 0; i < j.size(); i++)
  {
    auto obj = j.at(i);
    total = total + obj["total"].get<int>();
  }
}

void Worker::OnOK()
{
  Napi::HandleScope scope(Env());

  Callback().Call({Env().Undefined(), Napi::Number::New(Env(), total), Napi::Number::New(Env(), workerId)});
}

