#include "task_scheduler.h"
#include <iostream>

TaskScheduler::TaskScheduler() {
  exit_signal_fut = exit_promise.get_future();
}

void TaskScheduler::Start() {
  // launch main thread
  main_thread_fut = std::async(std::launch::async, &TaskScheduler::MainThread, this);
}


void TaskScheduler::CreateClassTask(TaskWorker** worker) {
  (*worker)->exit_singal = this->exit_signal_fut;
  auto fut =
      std::async(std::launch::async, &TaskWorker::WorkerMain, (*worker));

  //
  workers_futures.push_back(std::make_pair(std::move(fut), (*worker)));
  (*worker) = nullptr;

  std::cout << "CreateTask exit\n";
  //
}

void TaskScheduler::MainThread() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    std::cout << "checking if any task has finished to remove its future from our list\n";
    this->workers_futures.remove_if(
        [](std::pair<std::future<void>, TaskWorker*>& worker) -> bool {
          if (worker.first.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            if (nullptr != worker.second) {
              delete worker.second;
            }
            return true;
          }
          return false;
        });

    std::cout << this->workers_futures.size() << "\n";  // num of running workers

    if (exit_signal_fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {  //
      std::cout << "scheduler has been signaled to terminate\n";
      // check if tasks has finished
      if (this->workers_futures.size() == 0) {
        return;
      }
      // force terminating workers
      std::cout << "scheduler has been signaled to terminate "
                << "some tasks have NOT finished working yet .. wait for them\n";
    }
  }
}

void TaskScheduler::TerminateTasks() {
  std::cout << "Terminate tasks .. by signaling\n";
  this->exit_promise.set_value(true);
}

void TaskScheduler::WaitForSchedulerTermination() {
  try {
    main_thread_fut.get();
  } catch (const std::exception& e) {
    std::cout << "Task Scheduler main thread has already finished - excep: " << e.what() << "\n";
  }
}