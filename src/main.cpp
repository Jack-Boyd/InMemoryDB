#include <iostream>
#include <string>
#include "Database.h"

int main() {
  Database db;
  db.set("name", "Jack");

  if (auto val = db.get("name")) {
    std::println("Name: {}", *val);
  }
  return 0;
}