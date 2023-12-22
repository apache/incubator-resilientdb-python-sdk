#include "c_validator.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/queue.h>
#include <cryptopp/sha3.h>
#include <cryptopp/xed25519.h>

#include <nlohmann/json.hpp>

#include <iostream>

void CValidator::printHex(std::string& str) {
  std::byte bytes[str.length()];
  std::memcpy(bytes, str.data(), str.length());

  for (auto &b: bytes) {
    std::cout << std::to_integer<int>(b) << ' ';
  }
  std::cout << std::endl;
}

std::string CValidator::CCFulfill(std::string& fulfillment) {
  std::string decoded_str = base64_decode(base64_add_padding(fulfillment), false);
  std::cout << decoded_str << std::endl;
 
  printHex(decoded_str);

  return decoded_str;
}

/* 
 * TODO: Use actual BER/DER decoding functions from a cryptographic library and
 * replace hardcoded numbers with names of ASN1 bits
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
std::unique_ptr<std::vector<std::string>> CValidator::DERDecode(std::string& uri_bytes_str) {
  // 4 + 32 + 2 + 64
  if (uri_bytes_str.length() != 102) return nullptr;

  std::byte bytes[uri_bytes_str.length()];
  std::memcpy(bytes, uri_bytes_str.data(), uri_bytes_str.length());

  if (std::to_integer<int>(bytes[0]) != 164 ||
      std::to_integer<int>(bytes[1]) != 100 ||
      std::to_integer<int>(bytes[2]) != 128) {
    return nullptr;
  }

  if (std::to_integer<int>(bytes[3]) != PUBLIC_KEY_LENGTH) return nullptr;
  std::string public_key = uri_bytes_str.substr(4, 32);
  printHex(public_key);

  if (std::to_integer<int>(bytes[36]) != 129) return nullptr;

  if (std::to_integer<int>(bytes[37]) != SIGNATURE_LENGTH) return nullptr;
  std::string signature = uri_bytes_str.substr(38, 64);

  printHex(signature);

  std::unique_ptr<std::vector<std::string>> ptr(new std::vector<std::string>);
  ptr->push_back(public_key);
  ptr->push_back(signature);
  return ptr;
}

/*
 * TODO: Follow the steps according to
 * https://perfect-sunstone-a3b.notion.site/NexRes-C-validation-369f5ad4ef074a1684dc227702a5c866
 */
std::string CValidator::ConstructURI(std::string &public_key, std::string &signature) {
  // TODO: DER encode the fingerprint content object 

  // TODO: SHA256 hash the fingerprint content

  // TODO: Generate the fingerprint from the hash
  std::string fingerprint = "";

  return "ni:///sha-256;" + fingerprint + "?fpt=" + "ed25519-sha-256" + 
  "&cost=" + std::to_string(ED25519_CRYPTOGRAPHY_COST);
}

/*
 * TODO: Follow the steps according to
 * https://perfect-sunstone-a3b.notion.site/NexRes-C-validation-369f5ad4ef074a1684dc227702a5c866
 */
bool CValidator::VerifyMessage(std::string &public_key, std::string &signature,
                              std::string &message) {
  return true;
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

std::string CValidator::base64_remove_padding(std::string data) {
  int i = data.length() - 1;
  while (i >= 0 && data[i] == '=') {
    i--;
  }
  return data.substr(0, i+1);
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