#include <napi.h>
#include <vector>
#include <iostream>
#include "order.h"
#include "order_helper.h"
#include "worker_buffer.h"
#include "worker_classes.h"

using namespace std;

Napi::Boolean UseBuffers(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::cout << "Mapping params.." << std::endl;
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  Napi::Number workerId = info[1].As<Napi::Number>();
  Napi::Boolean breakIt = info[2].As<Napi::Boolean>();
  Napi::Function callback = info[3].As<Napi::Function>();
  std::cout << "Queueing worker.." << std::endl;
  WorkerBuffer* worker = new WorkerBuffer(callback, buffer.Data(), 0, workerId, breakIt.Value());
  worker->Queue();

  return Napi::Boolean::New(env, true);
}

Napi::Boolean UseClasses(const Napi::CallbackInfo& info) {
  Napi::Array jsArr = info[0].As<Napi::Array>();
  Napi::Env env = info.Env();
  Napi::Number workerId = info[1].As<Napi::Number>();
  Napi::Boolean breakIt = info[2].As<Napi::Boolean>();
  Napi::Function callback = info[3].As<Napi::Function>();
  vector<Order> orders;

  for (unsigned int i = 0; i < jsArr.Length(); i++) {
    Napi::Object order_obj = Napi::Object(env, jsArr.Get(i));
    orders.push_back(unpack_order(env, order_obj));
  }

  WorkerClasses* worker = new WorkerClasses(callback, orders, 0, workerId, breakIt.Value());
  worker->Queue();

  return Napi::Boolean::New(env, true);
}


Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "UseBuffers"), Napi::Function::New(env, UseBuffers));
    exports.Set(Napi::String::New(env, "UseClasses"), Napi::Function::New(env, UseClasses));
    return exports;
};

NODE_API_MODULE(async, init);
