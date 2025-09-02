#pragma once

#include "Storage.h"
#include <string>
#include <optional>

class Database {
public:
  Database() = default;

  bool set(const std::string &key, const std::string &value);
  std::optional<std::string> get(const std::string &key) const;
  bool remove(const std::string &key);
  size_t size() const;

private:
  Storage<std::string> m_storage;
};