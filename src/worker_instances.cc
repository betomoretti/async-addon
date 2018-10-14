
#include <napi.h>
#include <vector>
#include <iostream>
#include "order.h"
#include "worker_instances.h"
#include <chrono>

using namespace std;

void WorkerInstances::Execute() {
  cout << "Running worker\n";
  int internalTotal = 0;
  // if (breakIt) {
  //   SetError("Something happened");
  // }

  // looping over the list
  std::chrono::steady_clock::time_point begin_instances_iteration = std::chrono::steady_clock::now();
  for (unsigned int i = 0; i < orders.size(); i++)
  {
    Order order = orders.at(i);
    total = total + order.total;
  }
  std::chrono::steady_clock::time_point end_instances_iteration = std::chrono::steady_clock::now();
  std::cout << "instances iteration = " << std::chrono::duration_cast<std::chrono::microseconds>(end_instances_iteration - begin_instances_iteration).count() <<std::endl;
}

void WorkerInstances::OnOK() {
  Napi::HandleScope scope(Env());

  Callback().Call({Env().Undefined(), Napi::Number::New(Env(), total), Napi::Number::New(Env(), workerId)});
}

// for (unsigned int j = 0; j < orders.size(); j++)
// {
//   Order order = orders.at(j);
//   internalTotal = internalTotal + order.total;
// }