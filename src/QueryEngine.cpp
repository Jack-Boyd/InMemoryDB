#include "QueryEngine.h"
#include <sstream>
#include <vector>
#include <algorithm>

QueryEngine::QueryEngine(Database &db) : m_db(db), m_tx(db) {}

std::string QueryEngine::execute(const std::string &command) {
  std::istringstream iss(command);
  std::string action;
  iss >> action;

  std::transform(action.begin(), action.end(), action.begin(), ::toupper);

  if (action == "SET") {
    std::string key, value;
    iss >> key;
    std::getline(iss, value);
    if (!key.empty() && !value.empty()) {
      if (!value.empty() && value[0] == ' ')
        value.erase(0, 1);
      m_tx.set(key, value);
      return "OK";
    }
    return "ERROR: SET requires key and value";
  }
  else if (action == "GET") {
    std::string key;
    iss >> key;
    if (auto val = m_tx.get(key)) {
      return *val;
    }
    return "NULL";
  }
  else if (action == "DELETE") {
    std::string key;
    iss >> key;
    if (m_tx.remove(key)) {
      return "OK";
    }
    return "ERROR: Key not found";
  }
  else if (action == "BEGIN") {
    m_tx.begin();
    return "Transaction started";
  }
  else if (action == "COMMIT") {
    m_tx.commit();
    return "Transaction committed";
  }
  else if (action == "ROLLBACK") {
    m_tx.rollback();
    return "Transaction rolled back";
  }
  else {
    return "ERROR: Unknown command";
  }
}