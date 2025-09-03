#pragma once

#include "Database.hpp"
#include "Transaction.hpp"
#include <functional>
#include <string>

class QueryEngine {
public:
  explicit QueryEngine(Database& db);
  std::string execute(const std::string& cmd);
  void setShutdownCallback(std::function<void()> cb);
private:
  Database& m_db;
  Transaction m_tx;
  std::function<void()> m_shutdownCallback;
};