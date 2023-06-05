#pragma once

#include <string>
#include <unordered_map>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class SDKTransaction {
 public:
  SDKTransaction(rapidjson::Document& tx_body, bool skip_schema_validation);
  // SDKTransaction& Validate(std::unordered_map<std::string, SDKTransaction&>& current_transactions);
  bool InputsValid();
 private:
  std::string SerializeMessage(std::string& tx);
  std::string HashData(std::string& data);
  void ValidateId(rapidjson::Document& tx_body);
  void ValidateOperation(rapidjson::Document& tx_body);
  bool IsCommitted(std::string& tx_id);
  std::string id_;
  std::string operation_;
  rapidjson::GenericArray<false, rapidjson::Value>* inputs_;
  rapidjson::GenericArray<false, rapidjson::Value>* outputs_;
  rapidjson::Value::Object* metadata_;
  rapidjson::Value::Object* asset_;
};