#include <napi.h>
#include <vector>
#include <iostream>
#include "worker_buffer.h"
#include "../include/json/single_include/nlohmann/json.hpp"


using json = nlohmann::json;
using namespace std;

void WorkerBuffer::Execute()
{
  cout << "Running worker\n";

  std::string ret(buffer);
  auto j = json::parse(ret);

  for (unsigned int i = 0; i < j.size(); i++)
  {
    auto obj = j.at(i);
    total = total + obj["total"].get<int>();
  }
}

void WorkerBuffer::OnOK()
{
  Napi::HandleScope scope(Env());

  Callback().Call({Env().Undefined(), Napi::Number::New(Env(), total), Napi::Number::New(Env(), workerId)});
}
