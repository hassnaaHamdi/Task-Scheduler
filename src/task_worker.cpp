#include "task_worker.h"

bool TaskWorker::ShouldExit() {
  if (this->exit_singal.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    return true;
  return false;
}