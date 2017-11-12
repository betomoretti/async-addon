#include <nan.h>
#include <node.h>
#include <v8.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace v8;

class Order {
public:
  Order (int t) {
    total = t;
  }

  int total;
};

class DoItWorker : public Nan::AsyncWorker {
  public:
    DoItWorker(Nan::Callback *callback,
               std::vector<Order> &orders,
              int total,
              std::string workerId)
      : Nan::AsyncWorker(callback), orders(orders), total(total), workerId(workerId) {}

    void Execute () {
      cout << "Running worker\n";
      int internalTotal = 0;
      for (unsigned int i = 0; i < orders.size(); i++) {
        for (unsigned int j = 0; j < orders.size(); ++j)
        {
          Order order = orders.at(i);
          internalTotal = internalTotal + order.total;
        }
        Order order = orders.at(i);
        total = total + order.total;
      }
    }

  protected:
    void HandleOKCallback() {
      Nan::HandleScope scope;
      v8::Local<v8::Value> argv[] = {
        Nan::Null(), // no error occured
        Nan::New(total),
        Nan::New(workerId).ToLocalChecked()
      };
      callback->Call(3, argv);
    }

    void HandleErrorCallback() {
      cout << "Runs BAD\n";
    }

  private:
    std::vector<Order> orders;
    int total;
    std::string workerId;
};

Order unpack_order(v8::Local<Object> order_obj) {

  v8::Local<v8::Value> key = Nan::New("total").ToLocalChecked();
  Handle<Value> total = Nan::Get(order_obj, key).ToLocalChecked();
  Order ord(total->NumberValue());

  return ord;
}


NAN_METHOD(DoIt) {
  v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(info[0]);
  std::string workerId = std::string(*Nan::Utf8String(info[1]->ToString()));
  Nan::Callback *callback = new Nan::Callback(info[2].As<v8::Function>());
  std::vector<Order> orders;

  for (unsigned int i = 0; i < jsArr->Length(); i++) {
    v8::Local<Object> order_obj = Nan::To<v8::Object>(jsArr->Get(i)).ToLocalChecked();
    orders.push_back(unpack_order(order_obj));
  }

  AsyncQueueWorker(new DoItWorker(callback, orders, 0, workerId));

  info.GetReturnValue().Set(Nan::New(true));
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, DoIt);
}

NODE_MODULE(async, Initialize)
