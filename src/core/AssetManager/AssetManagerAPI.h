#include <filesystem>
#include <cstdint>

#include "Mesh.h"
#include "Texture.h"
#include "Model.h"
#include "Material.h"

__declspec(dllexport) extern std::vector<std::vector<uint64_t>> ImportModel(std::filesystem::path Path);
__declspec(dllexport) extern uint64_t ImportTexture(std::filesystem::path Path);

__declspec(dllexport) extern uint64_t CreateMaterial(std::string Name);

__declspec(dllexport) extern void SetTextureForMaterial(uint64_t Texture, uint64_t Material, TextureType Type);

__declspec(dllexport) extern CMesh* GetMesh(uint64_t ID);
__declspec(dllexport) extern CTexture* GetTexture(uint64_t ID);
__declspec(dllexport) extern CMaterial* GetMaterial(uint64_t ID);
__declspec(dllexport) extern CModel* GetModel(uint64_t ID);