//temp
#include<cstdio>
#include "Engine.h"
#include "core/AssetManager/AssetManagerAPI.h"
#include "core/Level.h"


int main()
{
    Engine engine;
    if (engine.StartUp())
    {
        // Metal Shelf
        // Loading all scene resources
        uint64_t Texture = ImportTexture("/Test_models/metal-shelf-14mb/textures/alpha_metal_shelf_BaseColor.png");
        uint64_t MetalMaterial = CreateMaterial("M_MetalShelf");
        SetTextureForMaterial(Texture, MetalMaterial, TextureType::Base);
        std::vector<std::vector<uint64_t>> MetalShelf = ImportModel("/Test_models/metal-shelf-14mb/source/metal shelf.fbx");
        if (MetalShelf.size() > 0)
        {
            uint64_t MetalShelfModel = MetalShelf[0][0];
            GetModel(MetalShelfModel)->SetMaterial(MetalMaterial);
            //GetLevel()->AddModelOnScene(MetalShelf[0][0], glm::vec3(0, 0, 0));
            GetLevel()->AddModelOnScene(MetalShelf[0][0], glm::vec3(0, 100, 100));
        
            engine.Mainloop();
        }
       
        engine.ShutDown();
    }
    getchar();
}