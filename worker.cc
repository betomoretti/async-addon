#include <nan.h>
#include <node.h>
#include <vector>
#include <iostream>
#include "order.h"
#include "worker.h"

using namespace std;

void Worker::Execute() {
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

void Worker::HandleOKCallback() {
  Nan::HandleScope scope;
  v8::Local<v8::Value> argv[] = {
    Nan::Null(), // no error occured
    Nan::New(total),
    Nan::New(workerId).ToLocalChecked()
  };
  callback->Call(3, argv);
}

void Worker::HandleErrorCallback() {}