#include <nan.h>
#include <node.h>
#include <v8.h>
#include <vector>
#include <iostream>

#include "order.h"
#include "order_helper.h"
#include "worker.h"

using namespace std;
using namespace v8;

NAN_METHOD(DoIt) {
  Local<Array> jsArr = Local<Array>::Cast(info[0]);
  string workerId = string(*Nan::Utf8String(info[1]->ToString()));
  Nan::Callback *callback = new Nan::Callback(info[2].As<Function>());
  vector<Order> orders;

  for (unsigned int i = 0; i < jsArr->Length(); i++) {
    Local<Object> order_obj = Nan::To<Object>(jsArr->Get(i)).ToLocalChecked();
    orders.push_back(unpack_order(order_obj));
  }

  AsyncQueueWorker(new Worker(callback, orders, 0, workerId));

  info.GetReturnValue().Set(Nan::New(true));
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, DoIt);
}

NODE_MODULE(async, Initialize)
