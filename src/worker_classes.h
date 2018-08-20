#include <napi.h>

#ifndef WORKER_CLASSES_H
#define WORKER_CLASSES_H

class WorkerClasses : public Napi::AsyncWorker {
  public:
    WorkerClasses(Napi::Function& callback,
              std::vector<Order> &orders,
              int total,
              int workerId,
              bool breakIt)
      : Napi::AsyncWorker(callback), orders(orders), total(total), workerId(workerId), breakIt(breakIt) {}

    void Execute ();
  protected:
    void OnOK();
  private:
    std::vector<Order> orders;
    int total;
    int workerId;
    bool breakIt;
};

#endif