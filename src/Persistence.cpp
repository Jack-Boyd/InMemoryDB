#include "Persistence.hpp"
#include "json.hpp"
#include <fstream>

void Persistence::save(const Database &db, const std::string &filename) {
  nlohmann::json j;
  for (const auto &[key, value] : db.dump()) {
    j[key] = value;
  }

  std::ofstream file(filename);
  if (file.is_open()) {
    file << j.dump(4);
  }
}

void Persistence::load(Database &db, const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    return;

  nlohmann::json j;
  file >> j;

  for (auto &[key, value] : j.items()) {
    db.set(key, value.get<std::string>());
  }
}