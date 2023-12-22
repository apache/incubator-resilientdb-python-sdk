/*
 * WORK IN PROGRESS
 * 
 * To be used with libcryptoconditions for SDK transaction validation
 */

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