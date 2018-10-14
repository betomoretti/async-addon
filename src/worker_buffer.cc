#include <napi.h>
#include <vector>
#include <iostream>
#include <chrono>
#include "worker_buffer.h"
#include "../include/json/single_include/nlohmann/json.hpp"
#include "../include/rapidjson/include/rapidjson/document.h"


using json = nlohmann::json;
using namespace std;
using namespace rapidjson;

void WorkerBuffer::Execute()
{
  cout << "Running worker\n";
  int internalTotal = 0;

  // Parsing buffer to json
  std::chrono::steady_clock::time_point begin_buffer_rapidjson = std::chrono::steady_clock::now();
  Document document;
  document.Parse(buffer);
  std::chrono::steady_clock::time_point end_buffer_rapidjson= std::chrono::steady_clock::now();

  std::cout << "to rapid json buffer = " << std::chrono::duration_cast<std::chrono::microseconds>(end_buffer_rapidjson - begin_buffer_rapidjson).count() <<std::endl;

  // looping over the list
  std::chrono::steady_clock::time_point begin_buffer_iteration = std::chrono::steady_clock::now();
  for (auto& v: document.GetArray())
  {
    auto obj = v.GetObject();
    total = total + obj["total"].GetInt();
  }
  std::chrono::steady_clock::time_point end_buffer_iteration = std::chrono::steady_clock::now();
  std::cout << "json iteration = " << std::chrono::duration_cast<std::chrono::microseconds>(end_buffer_iteration - begin_buffer_iteration).count() <<std::endl;
}

void WorkerBuffer::OnOK()
{
  Napi::HandleScope scope(Env());

  Callback().Call({Env().Undefined(), Napi::Number::New(Env(), total), Napi::Number::New(Env(), workerId)});
}

// for (auto& v: document.GetArray())
// {
//   internalTotal = internalTotal + obj["total"].GetInt();
// }