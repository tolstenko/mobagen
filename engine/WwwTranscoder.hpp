//#pragma once
//
//#include <vector>
//#include <cstdint>
//#include <string>
//
//// todo: put this on a isolated file
//std::vector<uint8_t> str2vec(std::basic_string<char> str){
//  std::vector<uint8_t> vec;
//  vec.assign(str.begin(), str.end());
//  return vec;
//}
//
//std::vector<uint8_t> str2vec(std::basic_string<int8_t> str){
//  std::vector<uint8_t> vec;
//  vec.assign(str.begin(), str.end());
//  return vec;
//}
//
//std::vector<uint8_t> str2vec(std::basic_string<uint8_t> str){
//  std::vector<uint8_t> vec;
//  vec.assign(str.begin(), str.end());
//  return vec;
//}
//
//// todo: put this on a isolated file
//template <typename T>
//void Append(std::vector<T>& a, const std::vector<T>& b)
//{
//  a.reserve(a.size() + b.size());
//  a.insert(a.end(), b.begin(), b.end());
//}
//
//bool ByteArrayContains(std::string array, uint8_t b)
//{
//  int length = array.size();
//  for (int index = 0; index < length; ++index)
//  {
//    if ((int) array[index] == (int) b)
//      return true;
//  }
//  return false;
//}
//
//std::string ucHexChars = "0123456789ABCDEF";
//std::string lcHexChars = "0123456789abcdef";
//std::string qpForbidden = "&;=?\"'%+_";
//std::string urlForbidden = "@&;:<>=?\"'/\\!#%+$,{}|^[]`";
//char urlEscapeChar = 37;
//std::string dataSpace = "%20";
//
//std::string Byte2Hex(uint8_t b, std::string hexChars) {
//  std::string str;
//  str += hexChars[b >> (uint8_t) 4];
//  str += hexChars[b & (uint8_t) 15];
//  return str;
//}
//
//std::string Encode(
//    std::vector<uint8_t> &input,
//    char escapeChar,
//    std::string &space,
//    std::string &forbidden,
//    bool uppercase) {
//  std::string memoryStream;
//  memoryStream.reserve(input.size()*2);
//  for (int index = 0; index < input.size(); ++index) {
//    if (input[index] == 32)
//      memoryStream += space;
//    else if (input[index] < 32 || input[index] > 126 || ByteArrayContains(forbidden, input[index])) {
//      memoryStream.push_back(escapeChar);
//      memoryStream += Byte2Hex(input[index], uppercase ? ucHexChars : lcHexChars);
//    } else
//      memoryStream.push_back(input[index]);
//  }
//  return memoryStream;
//}
//
//bool SevenBitClean(std::string &input)
//{
//  for (int index = 0; index < input.size(); ++index)
//  {
//    if (input[index] < 32 || input[index] > 126)
//      return false;
//  }
//  return true;
//}
//
//std::string QPEncode(std::string &toEncode)
//{
//  std::string space = "_";
//  auto input = str2vec(toEncode);
//  Encode(input, 61, space, qpForbidden, true);
//}
