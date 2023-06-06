#include "sdk_transaction.h"

#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha3.h>

#include <nlohmann/json.hpp>

#include <iostream>
#include <stdexcept>

SDKTransaction::SDKTransaction(rapidjson::Document& tx_body, bool skip_schema_validation) {
  if (!skip_schema_validation) {
    ValidateId(tx_body);
    ValidateOperation(tx_body);
  }
  id_ = tx_body["id"].GetString();
  operation_ = tx_body["operation"].GetString();
  rapidjson::Value::Array inputs = tx_body["inputs"].GetArray();
  inputs_ = &inputs;
  rapidjson::Value::Array outputs = tx_body["outputs"].GetArray();
  outputs_ = &outputs;
  
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

// TODO: find better exceptions
void SDKTransaction::Validate(std::unordered_map<std::string, SDKTransaction&>& current_transactions) {
  if (operation_ == "CREATE") {
    // check for txn with same id in current_transactions
    if (current_transactions.find(id_) != current_transactions.end()) {
      throw std::invalid_argument("Transaction with same id already found in current_transactions");
    }
    if (IsCommitted(id_)) {
      throw std::invalid_argument("Transaction with same id already committed to NexRes");
    }
    if (!InputsValid(nullptr)) { // pass empty array
      throw std::invalid_argument("Invalid inputs");
    }
  }
  else if (operation_ == "TRANSFER") {
    ValidateTransferInputs(current_transactions);
  }
}

// TODO: find better exceptions
// Validates the Inputs in the Transaction against given Outputs
bool SDKTransaction::InputsValid(rapidjson::Value::Array* outputs) {
  if (operation_ == "CREATE") {
    std::vector<std::string> dummy_outputs;
    for (unsigned int i = 0; i < inputs_->Size(); i++) {
      dummy_outputs.push_back("dummy_value");
    }
    std::cout << "inputs size: " << inputs_->Size() << std::endl;
    return InputsValid2(dummy_outputs);
  }
  else if (operation_ == "TRANSFER") {
    std::vector<std::string> output_condition_uris;
    if (outputs) {
      for (auto& output : *outputs) {
        output_condition_uris.push_back(output["condition"]["uri"].GetString());
      }
    }
    return InputsValid2(output_condition_uris);
  }
  else {
    throw std::invalid_argument("Invalid operation type");
    return false;
  }
}

// TODO
// Validates the Inputs in the Transaction against given Outputs
// Note: The number of `output_condition_uris` must be equal to the number of Inputs a Transaction has.
bool SDKTransaction::InputsValid2(std::vector<std::string> output_condition_uris) {
  return true;
}

std::string SDKTransaction::SerializeMessage(std::string& tx) {
  nlohmann::json j;
  j = nlohmann::json::parse(tx); // sort keys
  std::string str = j.dump(-1, ' ', false); // don't indent, don't ensure ascii

  return str;
}

std::string SDKTransaction::HashData(std::string& data) {
  CryptoPP::SHA3_256 hash;
  hash.Update((const CryptoPP::byte*) data.data(), data.size());

  std::string digest;
  digest.resize(hash.DigestSize());
  hash.Final((CryptoPP::byte*)&digest[0]);

  std::string encoded;
  CryptoPP::StringSource ss((const CryptoPP::byte*) digest.data(), digest.size(), true,
    new CryptoPP::HexEncoder(
      new CryptoPP::StringSink(encoded)
    )
  );
  return encoded;
}

// TODO: find better exceptions
void SDKTransaction::ValidateId(rapidjson::Document& tx_body) {
  rapidjson::Document tx_body_copy;
  tx_body_copy.CopyFrom(tx_body, tx_body_copy.GetAllocator());

  if (!tx_body_copy.HasMember("id")) {
    throw std::invalid_argument("tx_body has no member \"id\"");
  }
  std::string proposed_tx_id = tx_body_copy["id"].GetString();

  // set id to null
  tx_body_copy.AddMember("id", rapidjson::Value(), tx_body_copy.GetAllocator());

  // create string of serialized transaction
  rapidjson::StringBuffer buffer;
  buffer.Clear();
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  tx_body_copy.Accept(writer);
  std::string tx_body_str = buffer.GetString();
  std::string tx_body_serialized_str = SerializeMessage(tx_body_str);

  std::string valid_tx_id = HashData(tx_body_serialized_str);
  if (proposed_tx_id != valid_tx_id) {
    throw std::invalid_argument("proposed tx id differs from valid tx id");
  }
}

// TODO
bool SDKTransaction::IsCommitted(std::string& tx_id) {
  // use storage pointer?
  return true;
}

void SDKTransaction::ValidateOperation(rapidjson::Document& tx_body) {
  std::string operation = tx_body["operation"].GetString();

  if (operation != "CREATE" && operation != "TRANSFER") {
    throw std::invalid_argument("Invalid operation type");
  }
}

// TODO
void SDKTransaction::ValidateTransferInputs(std::unordered_map<std::string, SDKTransaction&>& current_transactions) {
  ;
}