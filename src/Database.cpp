#include "Database.hpp"

bool Database::set(const std::string& key, const std::string& value) {
  return m_storage.set(key, value);
}

std::optional<std::string> Database::get(const std::string& key) const {
  return m_storage.get(key);
}

bool Database::remove(const std::string& key) {
  return m_storage.remove(key);
}

size_t Database::size() const {
  return m_storage.size();
}

std::unordered_map<std::string, std::string> Database::dump() const {
  std::unordered_map<std::string, std::string> snapshot;
  for (const auto& [key, value] : m_storage.data()) {
    snapshot[key] = value;
  }
  return snapshot;
}