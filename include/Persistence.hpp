#include "Database.hpp"

class Persistence {
public:
  static void save(const Database& db, const std::string& filename);
  static void load(Database& db, const std::string& filename);
};