#pragma once
#include <future>

class TaskWorker {
 public:
  bool ShouldExit();

  virtual void WorkerMain() = 0;

 private:
  std::shared_future<bool> exit_singal;
  friend class TaskScheduler;
};