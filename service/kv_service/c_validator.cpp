#include "c_validator.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/queue.h>
#include <cryptopp/sha3.h>
#include <cryptopp/xed25519.h>

#include <nlohmann/json.hpp>

#include <string>
#include <iostream>

void printHex(std::string& str) {
  std::byte bytes[str.length()];
  std::memcpy(bytes, str.data(), str.length());
  // std::cout << "decoded str length: " << decoded_str.length() << " size: " << decoded_str.size() << std::endl;

  for (auto &b: bytes) {
    std::cout << std::to_integer<int>(b) << ' ';
  }
  std::cout << std::endl;
}

std::string CValidator::CCFulfill(std::string& fulfillment) {
  // std::cout << base64_add_padding(fulfillment);

  std::string decoded_str = base64_decode(base64_add_padding(fulfillment), false);
  std::cout << decoded_str << std::endl;
 
  printHex(decoded_str);

  return decoded_str;
}

/* 
 * TODO: Use actual BER/DER decoding functions from a cryptographic library
 *
 * Example string: pGSAIB4t58gi0CHneoXjs358ykJTwUWGZkWkBo7DLZV64c2KgUDoeWkz2-KrjDXh5ulHa2t-WiF5TT4RnBhqrcXJulJ135i_ipXmtJkLUrsGy884eRNb2_LE8RU2CMtRe4J-3IYM
 *
 * Fulfillment ::= CHOICE {
 *   ed25519Sha256    [0] Ed25519Sha512Fulfillment
 * }
 *
 * Ed25519Sha512Fulfillment ::= SEQUENCE {
 *   publicKey            OCTET STRING (SIZE(32)),
 *   signature            OCTET STRING (SIZE(64))
 * }
 */
void CValidator::DERDecode(std::string& uri_bytes_str) {
  std::byte bytes[uri_bytes_str.length()];
  std::memcpy(bytes, uri_bytes_str.data(), uri_bytes_str.length());

  assert(std::to_integer<int>(bytes[0]) == 164);
  assert(std::to_integer<int>(bytes[1]) == 100);
  assert(std::to_integer<int>(bytes[2]) == 128);

  // public key length is 32
  assert(std::to_integer<int>(bytes[3]) == 32);
  std::string public_key = uri_bytes_str.substr(4, 32);
  // std::cout << public_key << std::endl;
  printHex(public_key);

  assert(std::to_integer<int>(bytes[36]) == 129);

  // signature length is 64
  assert(std::to_integer<int>(bytes[37]) == 64);
  std::string signature = uri_bytes_str.substr(38, 64);
  // std::cout << signature << std::endl;

  printHex(signature);
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
  doc.AddMember("id", rapidjson::Value(), doc.GetAllocator());

  rapidjson::StringBuffer buffer;
  buffer.Clear();
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
  doc.Accept(writer);
  std::string json_str = buffer.GetString();

  std::string serialized_str = SerializeMessage(json_str);
  // std::cout << serialized_str << std::endl;

  // sha3 256 encode the serialized json
  CryptoPP::SHA3_256 hash;
  hash.Update((const CryptoPP::byte*) serialized_str.data(), serialized_str.size());
  
  // add encoded tx id it fulfills and its index to the sha 256 hash
  std::string tail_str = "";
  std::string tx_id = doc["inputs"][0]["fulfills"]["transaction_id"].GetString();
  int output_index = doc["inputs"][0]["fulfills"]["output_index"].GetInt();
  tail_str += tx_id;
  tail_str += std::to_string(output_index);
  hash.Update((const CryptoPP::byte*) tail_str.data(), tail_str.size());

  std::string digest;
  digest.resize(hash.DigestSize());
  hash.Final((CryptoPP::byte*)&digest[0]);

  std::cout << "Digest: ";
  CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
  CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));
  std::cout << std::endl;

  return digest;
}

std::string CValidator::SerializeMessage(std::string& tx) {
  nlohmann::json j;
  j = nlohmann::json::parse(tx); // sort keys
  std::string str = j.dump(-1, ' ', false); // don't indent, don't ensure ascii

  return str;
}

void CValidator::RemoveSignature(rapidjson::Document& doc) {
  // assert(doc.HasMember("inputs"));
  // assert(doc["inputs"].IsArray());

  for (auto& inp : doc["inputs"].GetArray()) {
    inp.AddMember("fulfillment", rapidjson::Value(), doc.GetAllocator());
  }
}