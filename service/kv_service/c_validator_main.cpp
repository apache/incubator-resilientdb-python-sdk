#include "c_validator.h"

#include <iostream>

int main() {
  CValidator cval;
  std::string fulfillment = "pGSAIB4t58gi0CHneoXjs358ykJTwUWGZkWkBo7DLZV64c2KgUDoeWkz2-KrjDXh5ulHa2t-WiF5TT4RnBhqrcXJulJ135i_ipXmtJkLUrsGy884eRNb2_LE8RU2CMtRe4J-3IYM";
  std::string str = cval.CCFulfill(fulfillment);

  // std::cout<< "\nDER Decoding\n";
  // cval.DERDecode(str);
  std::string tx = "{\"inputs\":[{\"owners_before\":[\"C1CECot9umaqYvCjpt31GiKpYmsaGWQDdnHJjCv8yQiS\"],\"fulfills\":{\"transaction_id\":\"123415ca19849d95571e0d828102365f24bd322a54d6701e477d32a5bd009c6f\",\"output_index\":0},\"fulfillment\":\"pGSAIKN9QFdMwU21tgN2hzUd8pi75C8EsQ6LjnMjLssTKgivgUAmOHl2O1vsWN_bvPjoofVWyHf1p_thSJIUNCkfNStc748Rz37tMPT8NouEgjIvwgXpM1zOvA3TmzdoCjpaNm0N\"}]}";
  std::cout << cval.CreateMessage(tx) << std::endl;

  // std::string tx2 = "{\"inputs\":[{\"owners_before\":[\"C1CECot9umaqYvCjpt31GiKpYmsaGWQDdnHJjCv8yQiS\"],\"fulfills\":{\"transaction_id\":\"123415ca19849d95571e0d828102365f24bd322a54d6701e477d32a5bd009c6f\",\"output_index\":0},\"fulfillment\":\"pGSAIKN9QFdMwU21tgN2hzUd8pi75C8EsQ6LjnMjLssTKgivgUAmOHl2O1vsWN_bvPjoofVWyHf1p_thSJIUNCkfNStc748Rz37tMPT8NouEgjIvwgXpM1zOvA3TmzdoCjpaNm0N\"}]}";
  // std::cout << cval.SerializeJSON(tx2) << std::endl;
}