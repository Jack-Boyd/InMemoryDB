#include <string>
#include "Database.h"

class QueryEngine {
public:
  explicit QueryEngine(Database& db);
  std::string execute(const std::string& cmd);
private:
  Database& m_db;
};