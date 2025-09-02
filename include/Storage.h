#pragma once 

#include <string>
#include <unordered_map>
#include <optional>
#include <shared_mutex>

template <typename T>
class Storage {
public:
  bool set(const std::string& key, const T& value) {
    std::unique_lock lock(m_mutex);
    m_data[key] = value;
    return true;
  };

  std::optional<T> get(const std::string& key) const {
    std::shared_lock lock(m_mutex);
    auto value = m_data.find(key);
    if (value != m_data.end()) {
      return value->second;
    }
    return std::nullopt;
  };

  bool remove(const std::string& key) {
    std::unique_lock lock(m_mutex);
    return m_data.erase(key) > 0;
  };

  size_t size() const {
    return m_data.size();
  };
private:
  std::unordered_map<std::string, T> m_data;
  mutable std::shared_mutex m_mutex;
};