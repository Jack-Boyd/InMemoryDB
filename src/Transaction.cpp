#include "Transaction.h"

Transaction::Transaction(Database &db) : m_db(db) {}

void Transaction::begin() {
  m_inTransaction = true;
  m_pendingWrites.clear();
  m_pendingDeletes.clear();
}

void Transaction::commit() {
  if (!m_inTransaction)
    return;

  for (auto &[key, value] : m_pendingWrites) {
    m_db.set(key, value);
  }

  for (auto &key : m_pendingDeletes) {
    m_db.remove(key);
  }

  m_inTransaction = false;
  m_pendingWrites.clear();
  m_pendingDeletes.clear();
}

void Transaction::rollback() {
  if (!m_inTransaction)
    return;

  m_inTransaction = false;
  m_pendingWrites.clear();
  m_pendingDeletes.clear();
}

bool Transaction::set(const std::string &key, const std::string &value) {
  if (m_inTransaction) {
    m_pendingWrites[key] = value;
    m_pendingDeletes.erase(key);
    return true;
  }
  return m_db.set(key, value);
}

std::optional<std::string> Transaction::get(const std::string &key) const {
  if (m_inTransaction) {
    if (auto it = m_pendingWrites.find(key); it != m_pendingWrites.end()) {
      return it->second;
    }
    if (m_pendingDeletes.count(key)) {
      return std::nullopt;
    }
  }
  return m_db.get(key);
}

bool Transaction::remove(const std::string &key) {
  if (m_inTransaction) {
    m_pendingWrites.erase(key);
    m_pendingDeletes.insert(key);
    return true;
  }
  return m_db.remove(key);
}