#include <napi.h>
#include <vector>
#include <iostream>
#include "order.h"
#include "worker.h"

using namespace std;

void Worker::Execute() {
  cout << "Running worker\n";
  int internalTotal = 0;
  if (breakIt) {
    SetError("Something happened");
  }
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

void Worker::OnOK() {
  Napi::HandleScope scope(Env());

  Callback().Call({Env().Undefined(), Napi::Number::New(Env(), total), Napi::Number::New(Env(), workerId)});
}

