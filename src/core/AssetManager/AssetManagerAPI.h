#include <filesystem>
#include <cstdint>

#include "Mesh.h"
#include "Texture.h"
#include "Model.h"
#include "Material.h"

extern std::vector<std::vector<uint64_t>> ImportModel(std::filesystem::path Path);
extern uint64_t ImportTexture(std::filesystem::path Path);

extern uint64_t CreateMaterial(std::string Name);

extern void SetTextureForMaterial(uint64_t Texture, uint64_t Material, TextureType Type);

extern CMesh* GetMesh(uint64_t ID);
extern CTexture* GetTexture(uint64_t ID);
extern CMaterial* GetMaterial(uint64_t ID);
extern CModel* GetModel(uint64_t ID);