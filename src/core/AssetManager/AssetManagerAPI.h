#include <filesystem>
#include <cstdint>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

//
//	Import 3d model(".fbx", ".obj")
//
__declspec(dllexport) extern std::vector<uint64_t> ImportModel(std::filesystem::path Path);

//
//	Import picture as texture(".png", ".jpg")
//
__declspec(dllexport) extern uint64_t ImportTexture(std::filesystem::path Path);

__declspec(dllexport) extern void SetTextureForMaterial(uint64_t Texture, uint64_t Material, TextureType Type);

__declspec(dllexport) extern CMesh* GetMesh(uint64_t ID);
__declspec(dllexport) extern CTexture* GetTexture(uint64_t ID);
__declspec(dllexport) extern CMaterial* GetMaterial(uint64_t ID);

__declspec(dllexport) extern uint64_t GetDefaultMaterialGUID();