#include "Camera.h"

glm::mat4 SCamera::GetCameraPerspectiveMatrix(float ScreenRatio)
{
    glm::vec3 FrontVector = Location + Rotation;
    glm::mat4 ViewMatrix = glm::lookAt(Location, FrontVector, GetUpVector());
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(100.0f), ScreenRatio, 0.1f, 100.f);
    return ProjectionMatrix * ViewMatrix;
}
