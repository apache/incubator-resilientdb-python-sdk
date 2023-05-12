#include "c_validator.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/xed25519.h>

#include <string>
#include <iostream>

std::string CValidator::CCFulfill(std::string fulfillment) {
  // std::cout << base64_add_padding(fulfillment);

  std::string decoded_str = base64_decode(base64_add_padding(fulfillment), false);
  std::cout << decoded_str << std::endl;
 
  std::byte bytes[decoded_str.length()];
  std::memcpy(bytes, decoded_str.data(), decoded_str.length());
  std::cout << "decoded str length: " << decoded_str.length() << " size: " << decoded_str.size() << std::endl;

  for (auto &b: bytes) {
    std::cout << std::to_integer<int>(b) << ' ';
  }
  std::cout << std::endl;

  return decoded_str;
}

void CValidator::DERDecode() {
  ;
}

void CValidator::ConstructURI() {
  ;
}

void CValidator::VerifyMessage() {
  ;
}

std::string CValidator::base64_add_padding(std::string data) {
  // convert data to bytes
  std::string encoded_data = data;
  // char8_t* encoded_data = "";

  int missing_padding = (4 - data.size() % 4) % 4;
  std::cout << "missing padding: " << missing_padding << std::endl;
  for (int i = 0; i < missing_padding; i++) {
    // todo: make sure '=' char is utf8 byte
    encoded_data += u8"=";
  }

  return encoded_data;
}