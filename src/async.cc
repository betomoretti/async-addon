#include <napi.h>
#include <iostream>

#include "order.h"
#include "order_helper.h"
#include "worker.h"

using namespace std;

Napi::Boolean DoIt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::cout << "Mapping params.." << std::endl;
  Napi::Buffer<char> buffer = info[0].As<Napi::Buffer<char>>();
  Napi::Number workerId = info[1].As<Napi::Number>();
  Napi::Boolean breakIt = info[2].As<Napi::Boolean>(); 
  Napi::Function callback = info[3].As<Napi::Function>();
  std::cout << "Queueing worker.." << std::endl;
  Worker* worker = new Worker(callback, buffer.Data(), 0, workerId, breakIt.Value());
  worker->Queue();

  return Napi::Boolean::New(env, true);
}


Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "DoIt"), Napi::Function::New(env, DoIt));
    return exports;
};

NODE_API_MODULE(async, init);
