#pragma once
#include "Engine.hpp"
#include "Texture.hpp"

using namespace mobagen;
class EditorGUI : public Component
{
public:
  EditorGUI();
  ~EditorGUI() = default;
  const char* getType() override;
  void update(Input *input, std::chrono::microseconds delta) override;
  void render(Shader* shader) override {};
  void registerWithEngine(Engine* engine) override {};
  void deregisterFromEngine(Engine* engine) override {};
  void onGUI(ImGuiContext* context) override;

  std::shared_ptr<Texture> firstImage;
  std::shared_ptr<Entity> firstEntity;

  std::shared_ptr<Texture> secondImage;
  std::shared_ptr<Entity> secondEntity;

  std::shared_ptr<Texture> thirdImage;
  std::shared_ptr<Entity> thirdEntity;

  std::shared_ptr<Texture> forthImage;
  std::shared_ptr<Entity> forthEntity;

  std::shared_ptr<Texture> normalTexture;
  std::shared_ptr<Texture> specularTexture;

  std::shared_ptr<Entity> rootScene;
private:
  void mainMenu();
  void options();
  void equalize();
  void highPass();

  float ApplyMask(unsigned char * input, int width, int height, int line, int column, float *mask, int maskWidth, int maskHeight, int bytesPerChannels = 1, int numberOfChannels = 4);
  void Laplace(unsigned char * input, unsigned char * output, int width, int height, int bytesPerChannels = 1, int numberOfChannels = 4);
  void Sobel(unsigned char * input, unsigned char * output, int width, int height, int bytesPerChannels = 1, int numberOfChannels = 4);
  void Kirsch(unsigned char * input, unsigned char * output, int width, int height, int bytesPerChannels = 1, int numberOfChannels = 4);


  // 0 -> not chosen
  // 1 -> equalization
  // 2 -> high-pass
  int option = 0;
};
