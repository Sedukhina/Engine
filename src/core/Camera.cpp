#include "Camera.h"
#include "Camera.h"
#include "..\render\Renderer.h"

SCamera::SCamera(glm::vec3 location, glm::vec3 rotation) : CSceneObject(location, rotation)
{
    UpdatePerspectiveMatrix();
}

void SCamera::UpdatePerspectiveMatrix()
{
    glm::vec3 FrontVector = Location + Rotation;
    glm::mat4 ViewMatrix = glm::lookAt(Location, FrontVector, GetUpVector());
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FOV), CachedScreenRatio, MinDistance, MaxDistance);
    CameraPerspectiveMatrix = ProjectionMatrix * ViewMatrix;
}

glm::mat4 SCamera::GetCameraPerspectiveMatrix(float ScreenRatio)
{
    if (CachedScreenRatio != ScreenRatio)
    {
        CachedScreenRatio = ScreenRatio;
        UpdatePerspectiveMatrix();
    }
    return CameraPerspectiveMatrix;
}
