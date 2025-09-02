#pragma once

#include "Database.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <optional>

class Transaction {
public:
  explicit Transaction(Database& db);

  void begin();
  void commit();
  void rollback();

  bool set(const std::string& key, const std::string& value);
  std::optional<std::string> get(const std::string& key) const;
  bool remove(const std::string& key);

  bool active() const { return m_inTransaction; }
private:
  Database& m_db;
  bool m_inTransaction{false};

  std::unordered_map<std::string, std::string> m_pendingWrites;
  std::unordered_set<std::string> m_pendingDeletes;
};