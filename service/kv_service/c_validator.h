#include "service/tools/base64.h"

#pragma once

#include <string>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class CValidator {
 public:
  std::string CCFulfill(std::string& fulfillment);
  void DERDecode(std::string& uri_bytes);
  void ConstructURI();
  void VerifyMessage();
  void CreateMessage(std::string& tx);
 private:
  std::string base64_add_padding(std::string data);
  std::string SerializeJSON(std::string& tx);
  void RemoveSignature(rapidjson::Document& doc);
};