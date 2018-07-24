#include <napi.h>
#include "order.h"

Order unpack_order(Napi::Env env, Napi::Object order_obj) {
  Napi::String key = Napi::String::New(env, "total");
  Napi::Value total = order_obj.Get(key);
  Order ord(total.ToNumber());

  return ord;
}