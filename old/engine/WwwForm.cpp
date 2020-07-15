//#include "WwwForm.hpp"
//
//#include "Random.hpp"
//#include "WwwTranscoder.hpp"
//
//mobagen::WwwForm::WwwForm() {
//  for (int index = 0; index < 40; ++index) {
//    int num = Random::Range(48, 110);
//    if (num > 57)
//      num += 7;
//    if (num > 90)
//      num += 6;
//    boundary.push_back(num);
//  }
//  headers["Content-Type"] = "application/x-www-form-urlencoded";
//  containsFiles = false;
//}
//
//void
//mobagen::WwwForm::AddField(
//    std::string &fieldName,
//    std::string &value){
//  fieldNames.push_back(fieldName);
//  fileNames.emplace_back("");
//  std::vector<uint8_t> data(value.begin(), value.end());
//  formData.push_back(data);
//  types.emplace_back("text/plain; charset=\"utf-8\"");
//}
//
//void
//mobagen::WwwForm::AddBinaryData(
//    std::string &fieldName,
//    std::vector<uint8_t> &contents) {
//  std::string nothing; // todo: improve this
//  AddBinaryData(fieldName, contents, nothing, nothing);
//}
//
//void
//mobagen::WwwForm::AddBinaryData(
//    std::string &fieldName,
//    std::vector<uint8_t> &contents,
//    std::string &fileName) {
//  std::string nothing; // todo: improve this
//  AddBinaryData(fieldName, contents, fileName, nothing);
//}
//
//void
//mobagen::WwwForm::AddBinaryData(
//    std::string &fieldName,
//    std::vector<uint8_t> &contents,
//    std::string &fileName,
//    std::string &mimeType) {
//  containsFiles = true;
//  headers["Content-Type"] = "multipart/form-data; boundary=\"" + boundary + "\"";
//  bool flag = contents.size() > 8 && contents[0] == 137 && (contents[1] == 80 && contents[2] == 78) && (contents[3] == 71 && contents[4] == 13 && (contents[5] == 10 && contents[6] == 26)) && contents[7] == 10;
//  if (fileName.empty())
//    fileName = fieldName + (flag ? ".png" : ".dat");
//  if (mimeType.empty())
//    mimeType = !flag ? "application/octet-stream" : "image/png";
//  fieldNames.push_back(fieldName);
//  fileNames.push_back(fileName);
//  formData.push_back(contents);
//  types.push_back(mimeType);
//}
//
//std::map<std::string, std::string> &
//    mobagen::WwwForm::GetHeaders() {
//  headers["Content-Type"] =
//      !containsFiles ?
//      "application/x-www-form-urlencoded" :
//      "multipart/form-data; boundary=\"" + boundary + "\"";
//  return headers;
//}
//
//void
//mobagen::WwwForm::SetHeader(const std::string& key, const std::string& value) {
//  headers[key] = value;
//}
//
//void
//mobagen::WwwForm::RemoveHeader(const std::string& key) {
//  headers.erase(key);
//}
//
//std::vector<uint8_t> mobagen::WwwForm::GetData() {
//  if (containsFiles)
//  {
//    auto bytes1 = str2vec("--");
//    auto bytes2 = str2vec("\r\n");
//    auto bytes3 = str2vec("Content-Type: ");
//    auto bytes4 = str2vec("Content-disposition: form-data; name=\"");
//    auto bytes5 = str2vec("\"");
//    auto bytes6 = str2vec("; filename=\"");
//
//    std::vector<uint8_t> memoryStream;
//
//    for (int index = 0; index < formData.size(); ++index) {
//      Append(memoryStream, bytes2);
//      Append(memoryStream, bytes1);
//      Append(memoryStream, str2vec(boundary));
//      Append(memoryStream, bytes2);
//      Append(memoryStream, bytes3);
//      std::vector<uint8_t> bytes7 = str2vec(types[index]);
//      Append(memoryStream, bytes7);
//      Append(memoryStream, bytes2);
//      Append(memoryStream, bytes4);
//      std::string headerName = "utf-8";
//      std::string str1 = fieldNames[index];
//      if (!SevenBitClean(str1) || str1.find("=?") > -1)
//          str1 = "=?" + headerName + "?Q?" + QPEncode(str1) + "?=";
//        std::vector<uint8_t> bytes8 = str2vec(str1);
//        Append(memoryStream, bytes8);
//      Append(memoryStream, bytes5);
//      if (!fileNames[index].empty())
//      {
//        std::string str2 = fileNames[index];
//        if (!SevenBitClean(str2) || str2.find("=?") > -1)
//          str2 = "=?" + headerName + "?Q?" + QPEncode(str2) + "?=";
//        std::vector<uint8_t> bytes9 = str2vec(str2);
//        Append(memoryStream, bytes6);
//        Append(memoryStream, bytes9);
//        Append(memoryStream, bytes5);
//      }
//      Append(memoryStream, bytes2);
//      Append(memoryStream, bytes2);
//      std::vector<uint8_t> buffer = formData[index];
//      Append(memoryStream, buffer);
//    }
//    Append(memoryStream, bytes2);
//    Append(memoryStream, bytes1);
//    Append(memoryStream, str2vec(boundary));
//    Append(memoryStream, bytes1);
//    Append(memoryStream, bytes2);
//    return memoryStream;
//  }
//  else
//  {
//    uint8_t bytes1 = '&';
//    uint8_t bytes2 = '=';
//
//    std::vector<uint8_t> memoryStream;
//    for (int index = 0; index < formData.size(); ++index) {
//      std::string space = "%20";
//      auto fieldName = str2vec(fieldNames[index]);
//      std::vector<uint8_t> buffer1 = str2vec(Encode(fieldName, 37, space, urlForbidden, false));
//      std::vector<uint8_t> buffer2 = str2vec(Encode(formData[index], 37, space, urlForbidden, false));
//      if (index > 0)
//        memoryStream.push_back(bytes1);
//      Append(memoryStream, buffer1);
//      memoryStream.push_back(bytes2);
//      Append(memoryStream, buffer2);      }
//      return memoryStream;
//  }
//}
