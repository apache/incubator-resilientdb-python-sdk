#include "sdk_transaction.h"

#include <cryptopp/sha3.h>

#include <nlohmann/json.hpp>

#include <iostream>

SDKTransaction::SDKTransaction(rapidjson::Document& tx_body, bool skip_schema_validation) {
  if (!skip_schema_validation) {
    ValidateId(tx_body);
    ValidateOperation(tx_body);
  }
  id_ = tx_body["id"].GetString();
  operation_ = tx_body["operation"].GetString();
  rapidjson::GenericArray<false, rapidjson::Value> inputs = tx_body["inputs"].GetArray();
  inputs_ = &inputs;
  rapidjson::GenericArray<false, rapidjson::Value> outputs = tx_body["outputs"].GetArray();
  outputs_ = &outputs;
  // metadata_.CopyFrom(tx_body["metadata"], metadata_.GetAllocator());
  
  // TODO: check if null beforehand)
  rapidjson::Value::Object metadata = tx_body["metadata"].GetObject();
  metadata_ = &metadata;

  rapidjson::Value::Object asset = tx_body["asset"].GetObject();
  asset_ = &asset;

  // for (auto& elem : *inputs_) {
  //   std::cout << elem["fulfillment"].GetString() << std::endl;
  // }
  // for (auto& elem : *outputs_) {
  //   std::cout << elem["amount"].GetString() << std::endl;
  // }
  // std::cout << (*metadata_)["price"].GetString() << std::endl;
  // std::cout << (*metadata_).HasMember("price") << std::endl;
  // std::cout << (*asset_)["data"]["description"].GetString() << std::endl;
}

// TODO
// SDKTransaction& SDKTransaction::Validate(std::unordered_map<std::string, SDKTransaction&>& current_transactions) {
//   return current_transactions[id_];
// }

// TODO
bool SDKTransaction::InputsValid() {
  return true;
}

std::string SDKTransaction::SerializeMessage(std::string& tx) {
  nlohmann::json j;
  j = nlohmann::json::parse(tx); // sort keys
  std::string str = j.dump(-1, ' ', false); // don't indent, don't ensure ascii

  return str;
}

std::string SDKTransaction::HashData(std::string& data) {
  return "";
}

void SDKTransaction::ValidateId(rapidjson::Document& tx_body) {
  ;
}

void SDKTransaction::ValidateOperation(rapidjson::Document& tx_body) {
  ;
}

bool SDKTransaction::IsCommitted(std::string& tx_id) {
  return true;
}