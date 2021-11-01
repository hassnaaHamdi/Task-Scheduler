#pragma once
#include "task_worker.h"
#include <list>


class TaskScheduler {
 public:
  TaskScheduler();

  void Start();

  template <typename F, typename... Ts>
  void CreateFuncTask(F&& f, Ts&&... params) {
    auto fut =
        std::async(std::launch::async, std::forward<F>(f), this->exit_signal_fut, std::forward<Ts>(params)...);

    workers_futures.push_back(std::make_pair(std::move(fut), nullptr));

    printf("CreateTask exit\n");
    //
  }

  void CreateClassTask(TaskWorker** worker);

  void MainThread();

  void TerminateTasks();

  void WaitForSchedulerTermination();

 private:
  std::promise<bool> exit_promise;
  std::shared_future<bool> exit_signal_fut;
  std::list<std::pair<std::future<void>, TaskWorker*>> workers_futures;
  std::future<void> main_thread_fut;
};
