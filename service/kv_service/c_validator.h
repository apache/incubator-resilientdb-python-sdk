#include "service/tools/base64.h"

#pragma once

#include <memory>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class CValidator {
 public:
  std::string CCFulfill(std::string &fulfillment);
  std::unique_ptr<std::vector<std::string>> DERDecode(std::string &uri_bytes_str);
  std::string ConstructURI(std::string &public_key, std::string &signature);
  bool VerifyMessage(std::string &public_key, std::string &signature,
                    std::string &message);
  std::string CreateMessage(std::string &tx);
  void printHex(std::string &str);
 private:
  std::string base64_add_padding(std::string data);
  std::string base64_remove_padding(std::string data);
  std::string SerializeMessage(std::string &tx);
  void RemoveSignature(rapidjson::Document &doc);
  const int PUBLIC_KEY_LENGTH = 32;
  const int SIGNATURE_LENGTH = 64;
  const int ED25519_CRYPTOGRAPHY_COST = 131072; // 2^17
};