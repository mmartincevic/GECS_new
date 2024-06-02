#include "Wall.h"
#include "../Utils/SDL_Wrapper.h"
#include "../Components/Transform.h"
#include "../Components/Texture.h"
#include "../TextureManager.h"
#include "../World/World.h"

void Wall::Draw(float dt)
{
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());
    auto textureComponent = gecs::ECS_Engine.components().GetComponentForEntity<Texture>(this->GetID());

    TextureManager::Instance().Draw(
        SDL_Wrapper::getInstance().getRenderer(), textureComponent->getTextureId(),
        transformComponent->Position().x, transformComponent->Position().y, 
        transformComponent->Width(), transformComponent->Height(), 0);
}

void Wall::DrawBoundingBox()
{
    // Set the draw color (RGBA)
    SDL_SetRenderDrawColor(SDL_Wrapper::getInstance().getRenderer(), 255, 0, 0, 255);  // Red color
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());
    Vector2D cameraPos = World::Instance().Camera()->Position();

    // Create a rectangle to represent the bounding box
    SDL_Rect boundingBox;
    boundingBox.x = transformComponent->Position().x - cameraPos.x;
    boundingBox.y = transformComponent->Position().y - cameraPos.y;
    boundingBox.w = transformComponent->Width();
    boundingBox.h = transformComponent->Height();

    // Draw the rectangle outline
    SDL_RenderDrawRect(SDL_Wrapper::getInstance().getRenderer(), &boundingBox);
}