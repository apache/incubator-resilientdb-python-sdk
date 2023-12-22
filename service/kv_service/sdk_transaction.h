/*
 * WORK IN PROGRESS
 * 
 * To be used with libcryptoconditions for SDK transaction validation
 */

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class SDKTransaction {
 public:
  SDKTransaction(rapidjson::Document& tx_body, bool skip_schema_validation);
  void Validate(std::unordered_map<std::string, SDKTransaction&>& current_transactions);
  bool InputsValid(rapidjson::Value::Array* outputs);
  bool InputsValid2(std::vector<std::string> output_condition_uris);
  void ValidateTransferInputs(std::unordered_map<std::string, SDKTransaction&>& current_transactions);
//  private:
  std::string SerializeMessage(std::string& tx);
  std::string HashData(std::string& data);
  void ValidateId(rapidjson::Document& tx_body);
  void ValidateOperation(rapidjson::Document& tx_body);
  bool IsCommitted(std::string& tx_id);
  rapidjson::Document doc_;
};