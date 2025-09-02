#include <iostream>
#include <string>
#include "Storage.h"

int main() {
  Storage<std::string> store;
  store.set("name", "Jack");

  if (auto val = store.get("name")) {
    std::println("Name: {}", *val);
  }
  return 0;
}