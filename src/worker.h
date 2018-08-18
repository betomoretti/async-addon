#include <napi.h>

#ifndef WORKER_H
#define WORKER_H

class Worker : public Napi::AsyncWorker {
  public:
    Worker(Napi::Function& callback,
              char* buffer,
              int total,
              int workerId,
              bool breakIt)
      : Napi::AsyncWorker(callback), buffer(buffer), total(total), workerId(workerId), breakIt(breakIt) {}

    void Execute ();
  protected:
    void OnOK();
  private:
    char* buffer;
    int total;
    int workerId;
    bool breakIt;
};

#endif