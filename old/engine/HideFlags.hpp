#pragma once
namespace mobagen {
/// Bit mask that controls object destruction, saving and visibility in inspectors.
  enum class HideFlags {
    None = 0,
    HideInHierarchy = 1,
    HideInInspector = 2,
    DontSaveInEditor = 4,
    NotEditable = 8,
    DontSaveInBuild = 16, // 0x00000010
    DontUnloadUnusedAsset = 32, // 0x00000020
    DontSave = DontUnloadUnusedAsset | DontSaveInBuild | DontSaveInEditor, // 0x00000034
    HideAndDontSave = DontSave | NotEditable | HideInHierarchy, // 0x0000003D
  };
}