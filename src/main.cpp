#include <print>
#include <string>
#include <iostream>

#include "Database.h"
#include "QueryEngine.h"

int main() {
  Database db;
  QueryEngine engine(db);

  std::print("Welcome to InMemoryDB (type EXIT to quit)\n");

  std::string line;
  while (true) {
    std::print("> ");
    if (!std::getline(std::cin, line)) {
      break;
    }

    if (line.empty())
      continue;

    if (line == "EXIT" || line == "QUIT") {
      std::print("Goodbye!\n");
      break;
    }

    std::string result = engine.execute(line);
    std::print("{}\n", result);
  }

  return 0;
}