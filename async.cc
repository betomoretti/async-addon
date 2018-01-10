#include <vector>
#include <napi.h>
#include <iostream>

#include "order.h"
#include "order_helper.h"
#include "worker.h"

using namespace std;

Napi::Boolean DoIt(const Napi::CallbackInfo& info) {
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

  Worker* worker = new Worker(callback, orders, 0, workerId, breakIt.Value());
  worker->Queue();

  return Napi::Boolean::New(env, true);
}


Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "DoIt"), Napi::Function::New(env, DoIt));
    return exports;
};

NODE_API_MODULE(bcrypt_napi, init);
