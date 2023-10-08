#pragma once

#include <unordered_map>

#include "sdk_transaction.h"

class SDKTransactionManager {
 public:
  SDKTransactionManager();
  ~SDKTransactionManager();
 private:
  std::unordered_map<std::string, SDKTransaction&> current_transactions;
};