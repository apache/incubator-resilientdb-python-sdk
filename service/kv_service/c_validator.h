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
  std::string CCFulfill(std::string& fulfillment);
  std::unique_ptr<std::vector<std::string>> DERDecode(std::string& uri_bytes_str);
  void ConstructURI();
  void VerifyMessage();
  std::string CreateMessage(std::string& tx);
  void printHex(std::string& str);
 private:
  std::string base64_add_padding(std::string data);
  std::string SerializeMessage(std::string& tx);
  void RemoveSignature(rapidjson::Document& doc);
  const int PUBLIC_KEY_LENGTH = 32;
  const int SIGNATURE_LENGTH = 64;
};