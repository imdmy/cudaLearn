#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
std::vector<std::function<void()>> event_queue;

// 生产者：添加游戏事件
void add_event(const std::string &event_name) {
  std::lock_guard<std::mutex> lock(mtx);
  event_queue.push_back([event_name]() {
    std::cout << "Processing event: " << event_name << std::endl;
  });
}

// 消费者：处理游戏事件
void process_events() {
  while (true) {
    mtx.lock();
    auto tasks = std::move(event_queue);
    event_queue.clear();
    mtx.unlock();

    for (auto &task : tasks) {
      task();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}

int main() {
  std::thread consumer(process_events);

  add_event("Player moved");
  add_event("Enemy attacked");
  add_event("Item picked up");

  consumer.join(); // 阻塞调用，它会使主线程等待子线程 consumer
                   // 执行完成后再继续运行后续代码。//
                   // 阻塞调用，它会使主线程等待子线程 consumer
                   // 执行完成后再继续运行后续代码。

  printf("Main thread exit.\n");
  return 0;
}
