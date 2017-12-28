#include "order.h"
#include <v8.h>
#include <nan.h>

using namespace v8;

Order unpack_order(Local<Object> order_obj) {
  Local<Value> key = Nan::New("total").ToLocalChecked();
  Handle<Value> total = Nan::Get(order_obj, key).ToLocalChecked();
  Order ord(total->NumberValue());

  return ord;
}