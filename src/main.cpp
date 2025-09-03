#include <print>
#include <thread>
#include <vector>
#include <boost/asio.hpp>

#include "Database.hpp"
#include "QueryEngine.hpp"
#include "Network.hpp"

int main() {
  try {
    Database db;
    QueryEngine engine(db);
    boost::asio::io_context io_context;

    engine.setShutdownCallback([&io_context]() {
      io_context.stop();
    });


    Server server(io_context, 5454, engine);
    std::print("Server running on 5454\n");

    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;

    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < numThreads; ++i) {
      threads.emplace_back([&io_context]() { io_context.run(); });
    }

    for (auto& t : threads) {
      t.join();
    }
  }
  catch (std::exception& e) {
    std::print("Exception: {}\n", e.what());
  }


  return 0;
}