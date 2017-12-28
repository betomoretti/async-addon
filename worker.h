#ifndef WORKER_H
#define WORKER_H

class Worker : public Nan::AsyncWorker {
  public:
    Worker(Nan::Callback *callback,
               std::vector<Order> &orders,
              int total,
              std::string workerId)
      : Nan::AsyncWorker(callback), orders(orders), total(total), workerId(workerId) {}

    void Execute ();
  protected:
    void HandleOKCallback();
    void HandleErrorCallback();
  private:
    std::vector<Order> orders;
    int total;
    std::string workerId;
};

#endif