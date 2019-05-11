//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "EditorGUI.hpp"
#include <Logger.hpp>
#include "components/MeshRenderer.hpp"
#include <Plane.hpp>
#include <string>
#include "Material.hpp"
#include "Logger.hpp"
#ifndef EMSCRIPTEN
//#include <curl/curl.h>
#endif
#include <iostream>

static float histogramDataOriginal[256];
static float transferOriginal[256];
static float histogramDataOffset[256];
static float transferOffset[256];
static float histogramDataOffsetEqualized[256];
static float histogramDataEqualized[256];
static float maxValueOriginal=0;
static float maxValueOffset=0;
static float maxValueOffsetEqualized=0;
static float maxValueEqualized=0;
static int imageOffset=0;

ImVec2 windowFactor;

static bool applied = false;

//std::vector<int> histogram(std::shared_ptr<Texture> originalImage)
//{
//  std::vector<int> histogram;
//  histogram.resize(256,0);
//  for (int i = 0; i < originalImage->height() * originalImage->width(); i++) {
//    auto color = originalImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
//    histogram[color] += 1;
//  }
//  return histogram;
//}


//std::shared_ptr<Texture> equalizeHistogram(std::shared_ptr<Texture> originalImage)
//{
//  // histogram
//  static float histogram[256];
//  memset(histogram, 0, sizeof(float)*256);
//  for (int i = 0; i < originalImage->height() * originalImage->width(); i++) {
//    auto color = originalImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
//    histogram[color] += 1;
//  }
//
//  // transfer function
//  float transfer[256];
//  memset(transfer, 0, sizeof(float)*256);
//  transfer[0] = 255.0f * transfer[0] / (float) (originalImage->height() * originalImage->width());
//  for (int i = 1; i < 256; i++)
//    transferOriginal[i] = transferOriginal[i - 1] + 255.0f * histogramDataOriginal[i] / (float) (originalImage->height() * originalImage->width());
//
//  // apply transfer
//  auto equalizedData = originalImage->getTextureData()->data;
//  for (int i = 0; i < equalizedData.size(); i += 4) {
//    int newValue = (int) floor(transferOriginal[equalizedData[i]]);
//    newValue = MIN(255, MAX(0, newValue));
//    equalizedData[i] = newValue;   // r
//    equalizedData[i + 1] = newValue; // g
//    equalizedData[i + 2] = newValue; // b
//  }
//  unsigned char *newEqualizedData = &equalizedData[0];
//
//  auto newTextureData = std::make_shared<TextureData>(originalImage->width(),originalImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
//  return std::make_shared<Texture>(newTextureData);
//}

void EditorGUI::onGUI(ImGuiContext* context)
{
  mainMenu();

  if(!applied) {
    // options
    ImGui::Begin("Options", nullptr, ImVec2(128*windowFactor.x, 128*windowFactor.y), 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(370*windowFactor.x, 20*windowFactor.y), 0);
    if (option == 0)
      options();

    if (option == 1 && !applied)
      equalize();

    if (option == 2 && !applied)
      highPass();
    ImGui::End();
  }

  if (option == 1)
  {
    ImGui::Begin("Histogram", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(50 * windowFactor.x, 20 * windowFactor.y), 0);
    ImGui::PlotHistogram("", histogramDataOriginal, IM_ARRAYSIZE(histogramDataOriginal), 0, "Original", 0.f, maxValueOriginal, ImVec2(300 * windowFactor.x, 80 * windowFactor.y));
    ImGui::End();

    ImGui::Begin("Histogram2", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(653 * windowFactor.x, 20 * windowFactor.y), 0);
    ImGui::PlotHistogram("", histogramDataOffset, IM_ARRAYSIZE(histogramDataOffset), 0, "Offset", 0.f, maxValueOffset, ImVec2(300 * windowFactor.x, 80 * windowFactor.y));
    ImGui::End();

    ImGui::Begin("Histogram3", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(50 * windowFactor.x, 500 * windowFactor.y), 0);
    ImGui::PlotHistogram("", histogramDataEqualized, IM_ARRAYSIZE(histogramDataEqualized), 0, "Equalized", 0.f, maxValueEqualized, ImVec2(300 * windowFactor.x, 80 * windowFactor.y));
    ImGui::End();

    ImGui::Begin("Histogram4", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(653 * windowFactor.x, 500 * windowFactor.y), 0);
    ImGui::PlotHistogram("", histogramDataOffsetEqualized, IM_ARRAYSIZE(histogramDataOffsetEqualized), 0, "Offset Equalized", 0.f, maxValueOffsetEqualized, ImVec2(300 * windowFactor.x, 80 * windowFactor.y));
    ImGui::End();
  }

  if (option == 2)
  {
    ImGui::Begin("Original", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(50 * windowFactor.x, 50 * windowFactor.y), 0);
    ImGui::Text("Original");
    ImGui::End();

    ImGui::Begin("Laplacian", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(653 * windowFactor.x, 50 * windowFactor.y), 0);
    ImGui::Text("Laplacian");
    ImGui::End();

    ImGui::Begin("Sobel", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(50 * windowFactor.x, 550 * windowFactor.y), 0);
    ImGui::Text("Sobel");
    ImGui::End();

    ImGui::Begin("Kirsch", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(653 * windowFactor.x, 550 * windowFactor.y), 0);
    ImGui::Text("Kirsch");
    ImGui::End();
  }
}

// show image
// show histogram
// add remove constant value to pixels
// average
// median
// equalization
// high-pass
// http://www.cis.umac.mo/cybernetics/WCSR-L2L1/DenoisedResults.htm


const char* EditorGUI::getType()
{
  return "EDITORGUI";
}

void EditorGUI::update(Input *input, std::chrono::microseconds delta) {}

#ifndef EMSCRIPTEN
size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s)
{
  s->append((char*)ptr,size*nmemb);

  return size*nmemb;
}
#endif


EditorGUI::EditorGUI()
{
#ifndef EMSCRIPTEN
//  CURL *curl;
//  CURLcode res;
//
//  curl = curl_easy_init();
//
//  if(curl) {
//    std::string s;
//    curl_easy_setopt(curl, CURLOPT_URL, "http://ip.jsontest.com/");
//    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
//    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
//
//    /* Perform the request, res will get the return code */
//    res = curl_easy_perform(curl);
//    /* Check for errors */
//    if(res != CURLE_OK)
//      log_err("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//
//    log_info("%s",s.data());
//
//    /* always cleanup */
//    curl_easy_cleanup(curl);
//  }
#endif

  auto object = new Object();
  Object::Destroy(object);
  log_info("%x",object->GetInstanceID());

  windowFactor.y = getEngine()->getWindow()->getHeight()/1024.0f;
  windowFactor.x = getEngine()->getWindow()->getWidth()/1024.0f;

  memset(histogramDataOriginal,0, sizeof(histogramDataOriginal));
  memset(histogramDataOffset,0, sizeof(histogramDataOffset));
  memset(histogramDataOffsetEqualized,0, sizeof(histogramDataOffsetEqualized));
  memset(histogramDataEqualized,0, sizeof(histogramDataEqualized));

//  auto dicomAsset = Asset("brain.dcm");
//  gdcm::ImageReader imageReader;
//
//  auto fileSize = dicomAsset.getIOStream()->fileSize();
//
//  auto dicomFileData = new char[fileSize];
//  dicomAsset.getIOStream()->read(dicomFileData,1,fileSize);
//
//  std::stringstream str;
//
//  str.write(dicomFileData,fileSize);
//  imageReader.SetStream(str);
//  imageReader.Read();
//
//  auto image = imageReader.GetImage();
//
//  auto photometric = image.GetPhotometricInterpretation();
//
//  auto pixelformat = image.GetPixelFormat();
//
//  char * imageBuffer = new char[pixelformat.GetPixelSize()*image.GetColumns()*image.GetRows()];
//  image.GetBuffer(imageBuffer);
//
//  log_info("format %d", pixelformat.GetBitsAllocated());
//
//  delete []dicomFileData;
//  delete []imageBuffer;

  //auto normal = std::make_shared<Texture>(Asset("default_normal.jpg"));
  //auto specular = std::make_shared<Texture>(Asset("default_specular.jpg"));

  //originalImage = std::make_shared<Texture>(Asset("boat.png"));
  //originalImage->bind(0);
  //std::make_shared<Material>(originalImage, normal, specular);

}

void EditorGUI::mainMenu() {
    ImGui::BeginMainMenuBar();

    bool browseButtonPressed = false;
    if (ImGui::BeginMenu("File"))   {
        browseButtonPressed = ImGui::MenuItem("Open...", "CTRL+O");
        ImGui::EndMenu();
    }
//    static ImGuiFs::Dialog dlg;
//    const char* chosenPath = dlg.chooseFileDialog(browseButtonPressed);
//
//  if (ImGui::BeginMenu("File"))
//  {
//    ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(0,0,0,0));
//    const bool browseButtonPressed = ImGui::Button("New Scene");
//    static ImGuiFs::Dialog dlg;                                                     // one per dialog (and must be static)
//    const char* chosenPath = dlg.chooseFileDialog(browseButtonPressed, nullptr, nullptr);
//    ImGui::PopStyleColor(1);
//
//    if (ImGui::MenuItem("Open Scene")) {}
//    ImGui::Separator();
//    if (ImGui::MenuItem("Save Scene")) {}
//    if (ImGui::MenuItem("Save Scene as...")) {}
//    ImGui::Separator();
//    if (ImGui::MenuItem("New Project")) {}
//    if (ImGui::MenuItem("Open Project")) {}
//    if (ImGui::MenuItem("Save Project")) {}
//    ImGui::Separator();
//    if (ImGui::MenuItem("Build Settings")) {}
//    if (ImGui::MenuItem("Build and Run")) {}
//    ImGui::Separator();
//    if (ImGui::MenuItem("Close")) {
//#ifndef EMSCRIPTEN
//      exit(0);
//#endif
//    }
//
//    ImGui::EndMenu();
//  }
// }

  if (ImGui::BeginMenu("Edit"))
  {
    if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
    if (ImGui::MenuItem("Redo", "CTRL+SHIFT+Z", false, false)) {}  // Disabled item
    ImGui::Separator();
    if (ImGui::MenuItem("Cut", "CTRL+X")) {}
    if (ImGui::MenuItem("Copy", "CTRL+C")) {}
    if (ImGui::MenuItem("Paste", "CTRL+V")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Duplicate", "CTRL+D")) {}
    if (ImGui::MenuItem("Delete", "Del")) {}
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();
}

void EditorGUI::options() {
  ImGui::BeginGroup();
  ImGui::Text("Choose your Algorithm:");
  if(ImGui::Button("Equalization")){option = 1;}
  if(ImGui::Button("High-Pass")){option=2;}
  ImGui::EndGroup();
}

void EditorGUI::equalize() {
  ImGui::BeginGroup();
  ImGui::Text("Type the offset to be added to image:");
  ImGui::InputInt("Offset", &imageOffset,1,2,0);

  if (applied == false && ImGui::Button("Apply offset and calculate"))
  {
    // apply offset
    applied = true;
    {
      auto modifiedData = firstImage->getTextureData()->data;
      for (int i = 0; i < modifiedData.size(); i += 4) {
        int newValue = modifiedData[i] + imageOffset;
        newValue = MIN(255, MAX(0, newValue));
        modifiedData[i] = newValue;   // r
        modifiedData[i + 1] = newValue; // g
        modifiedData[i + 2] = newValue; // b
      }
      unsigned char *newData = &modifiedData[0];

      auto newTextureData = std::make_shared<TextureData>(firstImage->width(), firstImage->height(), newData, GL_TEXTURE_2D, GL_LINEAR);
      secondImage = std::make_shared<Texture>(newTextureData);

      secondEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(secondImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      secondEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      secondEntity->getTransform().setPosition(glm::vec3(-300, 0, 200));
      secondEntity->getTransform().setScale(glm::vec3(400, 1, 400));
      rootScene->addChild(secondEntity);
    }

    // set histogram original
    {
      memset(histogramDataOriginal, 0, sizeof(histogramDataOriginal));
      for (int i = 0; i < firstImage->height() * firstImage->width(); i++) {
        auto color = firstImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataOriginal[color] += 1;
      }
      maxValueOriginal = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataOriginal[i] > maxValueOriginal)
          maxValueOriginal = histogramDataOriginal[i];
    }

    // set histogram offset
    {
      memset(histogramDataOffset, 0, sizeof(histogramDataOffset));
      for (int i = 0; i < secondImage->height() * secondImage->width(); i++) {
        auto color = secondImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataOffset[color] += 1;
      }
      maxValueOffset = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataOffset[i] > maxValueOffset)
          maxValueOffset = histogramDataOffset[i];
    }

    // new equalized image from original
    {
      memset(transferOriginal, 0, sizeof(transferOriginal));
      transferOriginal[0] =
          255.0f * histogramDataOriginal[0] / (float) (firstImage->height() * firstImage->width());
      for (int i = 1; i < 256; i++)
        transferOriginal[i] = transferOriginal[i - 1] + 255.0f * histogramDataOriginal[i] /
                                                        (float) (firstImage->height() * firstImage->width());
      auto equalizedData = firstImage->getTextureData()->data;
      for (int i = 0; i < equalizedData.size(); i += 4) {
        int newValue = (int) floor(transferOriginal[equalizedData[i]]);
        newValue = MIN(255, MAX(0, newValue));
        equalizedData[i] = newValue;   // r
        equalizedData[i + 1] = newValue; // g
        equalizedData[i + 2] = newValue; // b
      }
      unsigned char *newEqualizedData = &equalizedData[0];

      auto newTextureData = std::make_shared<TextureData>(firstImage->width(),firstImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
      thirdImage = std::make_shared<Texture>(newTextureData);

      thirdEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(thirdImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      thirdEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      thirdEntity->getTransform().setPosition(glm::vec3(300, 0, -300));
      thirdEntity->getTransform().setScale(glm::vec3(400, 1, 400));
      rootScene->addChild(thirdEntity);
    }

    // new equalized image from offset
    {
      memset(transferOffset, 0, sizeof(transferOffset));
      transferOffset[0] = 255.0f * histogramDataOffset[0] / (float) (firstImage->height() * firstImage->width());
      for (int i = 1; i < 256; i++)
        transferOffset[i] = transferOffset[i - 1] + 255.0f * histogramDataOffset[i] / (float) (firstImage->height() * firstImage->width());
      auto equalizedData = secondImage->getTextureData()->data;
      for (int i = 0; i < equalizedData.size(); i += 4) {
        int newValue = (int) floor(transferOffset[equalizedData[i]]);
        newValue = MIN(255, MAX(0, newValue));
        equalizedData[i] = newValue;     // r
        equalizedData[i + 1] = newValue; // g
        equalizedData[i + 2] = newValue; // b
      }
      unsigned char *newEqualizedData = &equalizedData[0];

      auto newTextureData = std::make_shared<TextureData>(firstImage->width(),firstImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
      forthImage = std::make_shared<Texture>(newTextureData);

      forthEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(forthImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      forthEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      forthEntity->getTransform().setPosition(glm::vec3(-300, 0, -300));
      forthEntity->getTransform().setScale(glm::vec3(400, 1, 400));
      rootScene->addChild(forthEntity);
    }

    // set histogram equalized
    {
      memset(histogramDataEqualized, 0, sizeof(histogramDataEqualized));
      for (int i = 0; i < secondImage->height() * secondImage->width(); i++) {
        auto color = thirdImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataEqualized[color] += 1;
      }
      maxValueEqualized = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataEqualized[i] > maxValueEqualized)
          maxValueEqualized = histogramDataEqualized[i];
    }

    // set histogram offset equalized
    {
      memset(histogramDataOffsetEqualized, 0, sizeof(histogramDataOffsetEqualized));
      for (int i = 0; i < forthImage->height() * forthImage->width(); i++) {
        auto color = forthImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataOffsetEqualized[color] += 1;
      }
      maxValueOffsetEqualized = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataOffsetEqualized[i] > maxValueOffsetEqualized)
          maxValueOffsetEqualized = histogramDataOffsetEqualized[i];
    }
  }
  ImGui::EndGroup();

}

void EditorGUI::highPass() {
  applied = true;
  {
    auto outputdata = new unsigned char[firstImage->getTextureData()->data.size()];
    Laplace(&(firstImage->getTextureData()->data[0]), outputdata, firstImage->width(), firstImage->height());

    auto newTextureData = std::make_shared<TextureData>(firstImage->width(), firstImage->height(), outputdata,
                                                        GL_TEXTURE_2D, GL_LINEAR);
    secondImage = std::make_shared<Texture>(newTextureData);

    secondEntity = std::make_shared<Entity>();
    auto modifiedMat = std::make_shared<Material>(secondImage, normalTexture, specularTexture);
    auto modifiedMesh = Plane::getMesh();
    secondEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
    secondEntity->getTransform().setPosition(glm::vec3(-300, 0, 200));
    secondEntity->getTransform().setScale(glm::vec3(400, 1, 400));
    rootScene->addChild(secondEntity);
    delete[] outputdata;
  }

  {
    auto outputdata = new unsigned char[firstImage->getTextureData()->data.size()];
    Sobel(&(firstImage->getTextureData()->data[0]), outputdata, firstImage->width(), firstImage->height());

    auto newTextureData = std::make_shared<TextureData>(firstImage->width(), firstImage->height(), outputdata,
                                                        GL_TEXTURE_2D, GL_LINEAR);
    thirdImage = std::make_shared<Texture>(newTextureData);

    thirdEntity = std::make_shared<Entity>();
    auto modifiedMat = std::make_shared<Material>(thirdImage, normalTexture, specularTexture);
    auto modifiedMesh = Plane::getMesh();
    thirdEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
    thirdEntity->getTransform().setPosition(glm::vec3(300, 0, -300));
    thirdEntity->getTransform().setScale(glm::vec3(400, 1, 400));
    rootScene->addChild(thirdEntity);

    delete[] outputdata;
  }

  {
    auto outputdata = new unsigned char[firstImage->getTextureData()->data.size()];
    Kirsch(&(firstImage->getTextureData()->data[0]), outputdata, firstImage->width(), firstImage->height());

    auto newTextureData = std::make_shared<TextureData>(firstImage->width(), firstImage->height(), outputdata,
                                                        GL_TEXTURE_2D, GL_LINEAR);
    forthImage = std::make_shared<Texture>(newTextureData);

    forthEntity = std::make_shared<Entity>();
    auto modifiedMat = std::make_shared<Material>(forthImage, normalTexture, specularTexture);
    auto modifiedMesh = Plane::getMesh();
    forthEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
    forthEntity->getTransform().setPosition(glm::vec3(-300, 0, -300));
    forthEntity->getTransform().setScale(glm::vec3(400, 1, 400));
    rootScene->addChild(forthEntity);

    delete[] outputdata;
  }
}

void EditorGUI::Laplace(unsigned char * input, unsigned char * output, int width, int height, int bytesPerChannels, int numberOfChannels)
{
  if(numberOfChannels!=4 || bytesPerChannels!=1)
    throw NotImplementedException();

  float laplace[] = {-1,-1,-1,
                     -1, 8,-1,
                     -1,-1,-1};

  for(int line =0;line<height;line++){
    for(int column =0;column<width;column++){
      int pos = (line * width + column) * numberOfChannels * bytesPerChannels;

      auto value = ApplyMask(input,width,height,line,column,laplace,3,3);
      auto color = (unsigned char) MIN(MAX(value,0),255);

      output[pos]  =color;
      output[pos+1]=color;
      output[pos+2]=color;
      output[pos+3]=255;
    }
  }
}


void EditorGUI::Sobel(unsigned char *input, unsigned char *output, int width, int height, int bytesPerChannels, int numberOfChannels)
{
  if(numberOfChannels!=4 || bytesPerChannels!=1)
    throw NotImplementedException();

  float vert[] = {-1,0,+1,
                  -2,0,2,
                  -1,0,1};
  float hor[] = { 1, 2, 1,
                  0, 0, 0,
                 -1,-2,-1};

  for(int line =0;line<height;line++){
    for(int column =0;column<width;column++){
      int pos = (line * width + column) * numberOfChannels * bytesPerChannels;

      auto vertvalue = ApplyMask(input,width,height,line,column,vert,3,3);
      auto horivalue = ApplyMask(input,width,height,line,column,hor,3,3);

      auto color = (unsigned char) MIN(MAX(sqrt(vertvalue*vertvalue + horivalue*horivalue),0),255);

      output[pos]  =color;
      output[pos+1]=color;
      output[pos+2]=color;
      output[pos+3]=255;
    }
  }
}

void EditorGUI::Kirsch(unsigned char *input, unsigned char *output, int width, int height, int bytesPerChannels, int numberOfChannels)
{
  if(numberOfChannels!=4 || bytesPerChannels!=1)
    throw NotImplementedException();

  float v1[] = { 5,  5,  5,
                -3,  0, -3,
                -3, -3, -3};
  float v2[] = { 5,  5, -3,
                 5,  0, -3,
                -3, -3, -3};
  float v3[] = { 5, -3, -3,
                 5,  0, -3,
                 5, -3, -3};
  float v4[] = {-3, -3, -3,
                 5,  0, -3,
                 5,  5, -3};
  float v5[] = {-3, -3, -3,
                -3,  0, -3,
                 5,  5,  5};
  float v6[] = {-3, -3, -3,
                -3,  0,  5,
                -3,  5,  5};
  float v7[] = {-3, -3,  5,
                -3,  0,  5,
                -3, -3,  5};
  float v8[] = {-3,  5,  5,
                -3,  0,  5,
                -3, -3, -3};

  for(int line =0;line<height;line++){
    for(int column =0;column<width;column++){
      int pos = (line * width + column) * numberOfChannels * bytesPerChannels;

      auto r1 = ApplyMask(input,width,height,line,column,v1,3,3);
      auto r2 = ApplyMask(input,width,height,line,column,v2,3,3);
      auto r3 = ApplyMask(input,width,height,line,column,v3,3,3);
      auto r4 = ApplyMask(input,width,height,line,column,v4,3,3);
      auto r5 = ApplyMask(input,width,height,line,column,v5,3,3);
      auto r6 = ApplyMask(input,width,height,line,column,v6,3,3);
      auto r7 = ApplyMask(input,width,height,line,column,v7,3,3);
      auto r8 = ApplyMask(input,width,height,line,column,v8,3,3);

      // 765 == 3*255 -> this is used to clamp the maximum pixel value properly
      auto max = MIN(MAX(MAX(MAX(MAX(r1,r2),MAX(r3,r4)), MAX(MAX(r5,r6),MAX(r7,r8))),0),765)/3;
      auto color = (unsigned char) max;

      output[pos]  =color;
      output[pos+1]=color;
      output[pos+2]=color;
      output[pos+3]=255;
    }
  }
}

float EditorGUI::ApplyMask(unsigned char *input, int width, int height, int line, int column, float *mask, int maskWidth, int maskHeight, int bytesPerChannels, int numberOfChannels) {
  // TODO: handle borders
  if (column >= width - maskWidth/2 + 1 || column <= maskWidth/2 - 1 || line >= height - maskHeight/2 + 1 || line <= maskHeight/2 - 1)
    return 0;

  float ret = 0;
  for (int y = -maskHeight/2; y <= maskHeight/2; y++) {
    for (int x = -maskWidth/2; x <= maskWidth/2; x++) {
      int pos = ((line+y) * width + column+x) * numberOfChannels * bytesPerChannels;
      float color = 0;
      for (auto i = 0; i < numberOfChannels - 1; i++)
        color += input[pos + i];
      color /= numberOfChannels - 1;
      color *= mask[x + maskWidth/2 + (y + maskHeight/2) * maskWidth];
      ret += color;
    }
  }

  return ret;
}


