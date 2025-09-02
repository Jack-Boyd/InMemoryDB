#pragma once

#include "Database.h"
#include "Transaction.h"
#include <string>

class QueryEngine {
public:
  explicit QueryEngine(Database& db);
  std::string execute(const std::string& cmd);
private:
  Database& m_db;
  Transaction m_tx;
};