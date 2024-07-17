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
        //std::vector<uint64_t> MetalShelf = ImportModel("C:\\Users\\Osphi\\source\\repos\\Engine\\src\\Test_models\\little-girl-playing\\source\\sandgirl\\sandgirl.fbx");
        std::vector<uint64_t> MetalShelf = ImportModel("C://Users//Osphi//source//repos//Engine//src//Test_models//metal-shelf-14mb//source//metal shelf.fbx");
        // CMesh* Shelf = GetMesh(MetalShelf[0]);
        engine.Mainloop();
        engine.ShutDown();
    }
    getchar();
}