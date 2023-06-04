#include "c_validator.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/queue.h>
#include <cryptopp/xed25519.h>

// #include "json.hpp"
#include <nlohmann/json.hpp>

#include <string>
#include <iostream>

std::string CValidator::CCFulfill(std::string& fulfillment) {
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

void CValidator::DERDecode(std::string& uri_bytes) {
  // CryptoPP::byte* byteStr = new CryptoPP::byte[uri_bytes.length()];
  // std::memcpy(byteStr, uri_bytes.data(), uri_bytes.length());
  
  // CryptoPP::ByteQueue queue;
  // queue.Put(byteStr, uri_bytes.length());
  // size_t len = uri_bytes.length();
  // CryptoPP::ASNTag tag = CryptoPP::OCTET_STRING;

  // std::string str;
  // CryptoPP::ByteQueue decodedQueue;
  // // CryptoPP::SecByteBlock sbb;
  
  // CryptoPP::BERDecodeOctetString(queue, decodedQueue);

  // for (int i = 0; i < queue.CurrentSize(); i++)
  //   std::cout << queue[i];
  // std::cout << std::endl;

  // https://www.cryptopp.com/docs/ref/class_o_i_d.html
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
    encoded_data += u8"=";
  }

  return encoded_data;
}

std::string CValidator::CreateMessage(std::string& tx) {
  rapidjson::Document doc;
  doc.Parse(tx);

  RemoveSignature(doc);
  doc.RemoveMember("id");

  rapidjson::StringBuffer buffer;
  buffer.Clear();
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);
  std::string json_str = buffer.GetString();

  std::string serialized_str = SerializeJSON(json_str);
  return serialized_str;
}

std::string CValidator::SerializeJSON(std::string& tx) {
  nlohmann::json j;
  j = nlohmann::json::parse(tx); // sort keys
  std::string str = j.dump(-1, ' ', false); // don't indent, don't ensure ascii

  return str;
}

void CValidator::RemoveSignature(rapidjson::Document& doc) {
  assert(doc.HasMember("inputs"));
  assert(doc["inputs"].IsArray());

  for (auto& inp : doc["inputs"].GetArray()) {
    inp.RemoveMember("fulfillment");
  }
}