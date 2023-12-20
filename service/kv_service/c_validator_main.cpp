/*
 * FOR TESTING PURPOSES
 * 
 * Delete when c validation is completed and integrated with kv server
 */

#include "c_validator.h"
#include "sdk_transaction_manager.h"

#include <iostream>

#include <openssl/bytestring.h>

int main(int argc, char** argv) {
  CValidator cval;
  std::string fulfillment = argc < 2 ? "pGSAIB4t58gi0CHneoXjs358ykJTwUWGZkWkBo7DLZV64c2KgUDoeWkz2-KrjDXh5ulHa2t-WiF5TT4RnBhqrcXJulJ135i_ipXmtJkLUrsGy884eRNb2_LE8RU2CMtRe4J-3IYM"
                                    : std::string(argv[1]);
  std::string decoded_fulfillment = cval.CCFulfill(fulfillment);

  // DER decode
  uint8_t bytes[decoded_fulfillment.length()];
  std::memcpy(bytes, decoded_fulfillment.data(), decoded_fulfillment.length());

  std::cout<< "\nDER Decoding\n";
  cval.DERDecode(decoded_fulfillment);
/*  // std::string tx = "{\"inputs\":[{\"owners_before\":[\"C1CECot9umaqYvCjpt31GiKpYmsaGWQDdnHJjCv8yQiS\"],\"fulfills\":{\"transaction_id\":\"123415ca19849d95571e0d828102365f24bd322a54d6701e477d32a5bd009c6f\",\"output_index\":0},\"fulfillment\":\"pGSAIKN9QFdMwU21tgN2hzUd8pi75C8EsQ6LjnMjLssTKgivgUAmOHl2O1vsWN_bvPjoofVWyHf1p_thSJIUNCkfNStc748Rz37tMPT8NouEgjIvwgXpM1zOvA3TmzdoCjpaNm0N\"}]}";
  
  std::string tx = "{ \"inputs\":[ { \"owners_before\":[ \"C1CECot9umaqYvCjpt31GiKpYmsaGWQDdnHJjCv8yQiS\" ], \"fulfills\":{ \"transaction_id\":\"123415ca19849d95571e0d828102365f24bd322a54d6701e477d32a5bd009c6f\", \"output_index\":0 }, \"fulfillment\":\"pGSAIKN9QFdMwU21tgN2hzUd8pi75C8EsQ6LjnMjLssTKgivgUAmOHl2O1vsWN_bvPjoofVWyHf1p_thSJIUNCkfNStc748Rz37tMPT8NouEgjIvwgXpM1zOvA3TmzdoCjpaNm0N\" } ], \"outputs\":[ { \"public_keys\":[ \"DeVmcDk2G9TDYUtuLsozEWs9eCNRfbgfxaCntdKYKxXE\" ], \"condition\":{ \"details\":{ \"type\":\"ed25519-sha-256\", \"public_key\":\"DeVmcDk2G9TDYUtuLsozEWs9eCNRfbgfxaCntdKYKxXE\" }, \"uri\":\"ni:///sha-256;koZKY5-hToyQh-71lMhRS4WdYKFyNagSXEeBKxbuZpM?fpt=ed25519-sha-256&cost=131072\" }, \"amount\":\"1\" } ], \"operation\":\"TRANSFER\", \"metadata\":null, \"asset\":{ \"id\":\"123415ca19849d95571e0d828102365f24bd322a54d6701e477d32a5bd009c6f\" }, \"version\":\"2.0\", \"id\":\"780b0c416519aac2137c143ed1929b8783c99df001d3660a4b29508fad58443b\" }";
  std::string tx2 = "{ \"inputs\":[ { \"owners_before\":[ \"DnnUfvQZgPkL1njR34LDZvJMwJgj7YQ5mrYP8XVzZg9y\" ], \"fulfills\":\"None\", \"fulfillment\":\"pGSAIL4GzPYkwd8ZlktV3gKtos1PjD2ryjlbconNp4wHcxKUgUBCH1jY4t3QsxZgRh9PvDY9bA5x1BQrQ_SATDqvlU-u0kPa06cyoEkHRdJcrxkOFg_RZRoqiqjpPXyLIhpJV6oN\" } ], \"outputs\":[ { \"public_keys\":[ \"HEoggCcFUqn61v9xNwjVeCdDXNNWcX4AXfermVbFKgw7\" ], \"condition\":{ \"details\":{ \"type\":\"ed25519-sha-256\", \"public_key\":\"HEoggCcFUqn61v9xNwjVeCdDXNNWcX4AXfermVbFKgw7\" }, \"uri\":\"ni:///sha-256;1EsVBQSH5bINVz55A7-Q7yg8RqQeRwex-RwLwuQwVaM?fpt=ed25519-sha-256&cost=131072\" }, \"amount\":\"1\" } ], \"operation\":\"CREATE\", \"metadata\":{ \"price\":\"100\" }, \"asset\":{ \"data\":{ \"token_for\":{ \"game_boy\":{ \"serial_number\":\"LR35902\" } }, \"description\":\"Time share token. Each token equals one hour of usage.\" } }, \"version\":\"2.0\", \"id\":\"61f7385eda0633220d3d6ad170b740511f97dc2d0875f9f0a46dd1705e484936\" }";
  std::cout << cval.CreateMessage(tx) << std::endl;

  // std::string tx2 = "{\"inputs\":[{\"owners_before\":[\"C1CECot9umaqYvCjpt31GiKpYmsaGWQDdnHJjCv8yQiS\"],\"fulfills\":{\"transaction_id\":\"123415ca19849d95571e0d828102365f24bd322a54d6701e477d32a5bd009c6f\",\"output_index\":0},\"fulfillment\":\"pGSAIKN9QFdMwU21tgN2hzUd8pi75C8EsQ6LjnMjLssTKgivgUAmOHl2O1vsWN_bvPjoofVWyHf1p_thSJIUNCkfNStc748Rz37tMPT8NouEgjIvwgXpM1zOvA3TmzdoCjpaNm0N\"}]}";
  // std::cout << cval.SerializeJSON(tx2) << std::endl;
  rapidjson::Document doc;
  doc.Parse(tx2);
  SDKTransaction sdktx(doc, true);
  */
}