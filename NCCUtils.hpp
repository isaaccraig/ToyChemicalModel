
#pragma once
#include "Parameters.hpp"
#include <string>
#include <map>
#include <vector>

template <typename T>
  std::map<std::string, T> NCC_READIN (const std::string *filename, std::vector<const std::string> varnames);
