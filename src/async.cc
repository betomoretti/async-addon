#include <napi.h>
#include <vector>
#include <iostream>
#include "order.h"
#include "order_helper.h"
#include "worker_buffer.h"
#include "worker_instances.h"
#include <chrono>

using namespace std;

// Function that proccess the data using buffers
Napi::Boolean UseBuffers(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::cout << "Mapping params.." << std::endl;
  // Getting arguments
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  Napi::Number workerId = info[1].As<Napi::Number>();
  Napi::Boolean breakIt = info[2].As<Napi::Boolean>();
  Napi::Function callback = info[3].As<Napi::Function>();

  std::cout << "Queueing worker.." << std::endl;
  // Queueing worker
  WorkerBuffer* worker = new WorkerBuffer(callback, buffer.Data(), 0, workerId, breakIt.Value());
  worker->Queue();

  // Returning value to JS
  return Napi::Boolean::New(env, true);
}

// Function that proccess the data using instances
Napi::Boolean UseInstances(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // Getting arguments
  Napi::Array jsArr = info[0].As<Napi::Array>();
  Napi::Number workerId = info[1].As<Napi::Number>();
  Napi::Boolean breakIt = info[2].As<Napi::Boolean>();
  Napi::Function callback = info[3].As<Napi::Function>();
  vector<Order> orders;

  // Mapping to C++ classes
  std::chrono::steady_clock::time_point begin_classes = std::chrono::steady_clock::now();
  for (unsigned int i = 0; i < jsArr.Length(); i++) {
    Napi::Object order_obj = Napi::Object(env, jsArr.Get(i));
    orders.push_back(unpack_order(env, order_obj));
  }
  std::chrono::steady_clock::time_point end_classes = std::chrono::steady_clock::now();
  std::cout << "to classes = " << std::chrono::duration_cast<std::chrono::microseconds>(end_classes - begin_classes).count() <<std::endl;

  // Queueing worker
  WorkerInstances* worker = new WorkerInstances(callback, orders, 0, workerId, breakIt.Value());
  worker->Queue();

  // Returning value to JS
  return Napi::Boolean::New(env, true);
}


Napi::Object init(Napi::Env env, Napi::Object exports) {
  // Exporting functions
  exports.Set(Napi::String::New(env, "UseBuffers"), Napi::Function::New(env, UseBuffers));
  exports.Set(Napi::String::New(env, "UseInstances"), Napi::Function::New(env, UseInstances));
  return exports;
};

NODE_API_MODULE(async, init);
