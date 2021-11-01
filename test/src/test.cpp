//TEST(TestCaseName, TestName) {
//  EXPECT_EQ(1, 1);
//  EXPECT_TRUE(true);
//}


#include <iostream>
#include <task_scheduler.h>

inline bool ShouldExit(std::shared_future<bool> exit_signal) {
  if (exit_signal.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    return true;
  return false;
}

void testAsyncFunc(std::shared_future<bool> exit_signal, std::string sx) {
  if (ShouldExit(exit_signal)) {
    std::cout << "exit is signaled before check\n";
    std::cout << "input: " << sx << std::endl;
    return;
  }
  std::cout << "testAsyncFunc before check\n";

  if (ShouldExit(exit_signal)) {
    std::cout << "exit is signaled\n";
    std::cout << "input: " << sx << std::endl;
    return;
  }
  // sleep here so that other threads work
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "testAsyncFunc after check\n";

  if (ShouldExit(exit_signal)) {
    if (true == exit_signal.get()) {
      std::cout << "exit is signaled after check\n";
      std::cout << "input: " << sx << std::endl;
      return;
    }
  }
  std::cout << "testAsyncFunc finished\n";
}

void testAsyncFunc1(std::shared_future<bool> exit_signal, int sx) {
  if (ShouldExit(exit_signal)) {
    std::cout << "11 exit is signaled before check\n";
    std::cout << "input: " << sx << std::endl;
    return;
  }
  std::cout << "testAsyncFunc111 before check\n";
  if (ShouldExit(exit_signal)) {
    std::cout << "11 exit is signaled\n";
    std::cout << "input: " << sx << std::endl;
    return;
  }
  std::cout << "testAsyncFunc111 after check\n";

  if (ShouldExit(exit_signal)) {
    std::cout << "11 exit is signaled after check\n";
    std::cout << "input: " << sx << std::endl;
    return;
  }
  std::cout << "testAsyncFunc111 finished\n";
}

class MonitorWorker : public TaskWorker {
  // all related work
  // keep checking exist_singal_to exit thrad when needed
 public:
  void WorkerMain() override {
    internals = "hello Worker Thread Child\n";
    std::cout << internals << "\n";
    // ShouldExit();
  }

  //private:
  std::string internals;
};


int main() {
  TaskScheduler scheduler;
  scheduler.Start();

  // how to use task scheduler by lambda expression
  scheduler.CreateFuncTask([](std::shared_future<bool> exit_signal, int sx) { std::cout << "hello from lambda expr\n"; }, 1);

  // how to use task scheduler by traditional function ptr/callback
  std::cout << "call another\n";
  scheduler.CreateFuncTask(testAsyncFunc1, 1);
  scheduler.CreateFuncTask(testAsyncFunc, "string param");

  MonitorWorker* worker = new MonitorWorker();
  scheduler.CreateClassTask((TaskWorker**)&worker);
  
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // exit
  scheduler.TerminateTasks();
  scheduler.WaitForSchedulerTermination();

  std::cout << "main exit\n";

  return 0;
}