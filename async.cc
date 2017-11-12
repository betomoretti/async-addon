#include <nan.h>

using v8::Function;
using v8::Local;
using v8::Number;
using v8::Value;
// using Nan::AsyncQueueWorker;
// using Nan::AsyncWorker;
using Nan::Callback;
// using Nan::HandleScope;
using Nan::New;
using Nan::Null;
// using Nan::To;

// const int baseCase = 1;

// int async(int value) {

// }

NAN_METHOD(DoIt) {

  Local<Value> argv[] = {
      Null()
    , New<Number>(0)
  };

  Callback *callback = new Callback(info[0].As<Function>());
  callback->Call(2, argv);
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, DoIt);
}

NODE_MODULE(async, Initialize)
