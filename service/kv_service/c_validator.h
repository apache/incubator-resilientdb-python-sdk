#include "service/tools/base64.h"

#pragma once

#include <string>

class CValidator {
 public:
  std::string CCFulfill(std::string fulfillment);
  void DERDecode();
  void ConstructURI();
  void VerifyMessage();
 private:
  std::string base64_add_padding(std::string data);
};