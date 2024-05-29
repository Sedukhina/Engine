//temp
#include<cstdio>
#include "Engine.h"
#include "core/AssetManager/AssetManagerAPI.h"
#include "core/Level.h"

void ZoomModel(uint64_t Model, float Zoom)
{
    glm::vec3 Scale = GetModel(Model)->GetScale();
    Scale = Scale * Zoom;
    GetModel(Model)->SetScale(Scale);
}

void MoveModelRight(uint64_t Model, float Value)
{
    glm::vec3 Location = GetModel(Model)->GetLocation();
    Location = Location + glm::vec3(0.f, 0.f , Value);
    GetModel(Model)->SetLocation(Location);
}

void MoveModelUp(uint64_t Model, float Value)
{
    glm::vec3 Location = GetModel(Model)->GetLocation();
    Location = Location + glm::vec3(0.f, Value, 0.f);
    GetModel(Model)->SetLocation(Location);
}

void AddRotationToModel(uint64_t Model, glm::vec3 Rotation)
{
    glm::vec3 ModelRotation = GetModel(Model)->GetRotation();
    ModelRotation += Rotation;
    GetModel(Model)->SetRotation(ModelRotation);
}

int main()
{
    Engine engine;
    if (engine.StartUp())
    {
        // Loading all scene resources
        uint64_t Texture = ImportTexture("/Test_models/metal-shelf-14mb/textures/alpha_metal_shelf_BaseColor.png");
        uint64_t MetalMaterial = CreateMaterial("M_MetalShelf");
        SetTextureForMaterial(Texture, MetalMaterial, TextureType::Base);
        std::vector<std::vector<uint64_t>> MetalShelf = ImportModel("/Test_models/metal-shelf-14mb/source/metal shelf.fbx");
        uint64_t MetalShelfModel = MetalShelf[0][0];
        GetModel(MetalShelfModel)->SetMaterial(MetalMaterial);
        GetLevel()->AddModelOnScene(MetalShelf[0][0], glm::vec3(0));

        // Binding input
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&ZoomModel, MetalShelfModel, 2.f), InputKey::O, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&ZoomModel, MetalShelfModel, 0.5f), InputKey::P, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&MoveModelRight, MetalShelfModel, 1), InputKey::A, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&MoveModelRight, MetalShelfModel, -1), InputKey::D, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&MoveModelUp, MetalShelfModel, -1), InputKey::W, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&MoveModelUp, MetalShelfModel, 1), InputKey::S, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&AddRotationToModel, MetalShelfModel, glm::vec3(1, 0, 0)), InputKey::Z, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&AddRotationToModel, MetalShelfModel, glm::vec3(0, 1, 0)), InputKey::X, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&AddRotationToModel, MetalShelfModel, glm::vec3(0, 0, 1)), InputKey::C, InputAction::PRESSED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&AddRotationToModel, MetalShelfModel, glm::vec3(1, 0, 0)), InputKey::Z, InputAction::REPEATED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&AddRotationToModel, MetalShelfModel, glm::vec3(0, 1, 0)), InputKey::X, InputAction::REPEATED);
        GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&AddRotationToModel, MetalShelfModel, glm::vec3(0, 0, 1)), InputKey::C, InputAction::REPEATED);

        engine.Mainloop();
        engine.ShutDown();
    }
    getchar();
}