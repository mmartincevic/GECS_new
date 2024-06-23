#include "Wall.h"
#include "../Components/Transform.h"
#include "../Components/Texture.h"
#include "../World/World.h"

#include "../Resources/SDLRender.h"
#include "../Resources/SDLTexture.h"
#include "../Components/ObjectColor.h"

void Wall::Draw(float dt)
{
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());
    auto textureComponent = gecs::ECS_Engine.components().GetComponentForEntity<Texture>(this->GetID());

    TextureResource resource = Component<Texture>()->GetActiveResource();

    gecs::ECS_Engine.resources().Manager<SDLTexture>()->Draw(resource.m_ResourceId,
        transformComponent->Position().x, transformComponent->Position().y,
        transformComponent->Width(), transformComponent->Height(),
        textureComponent->ScaleX(), textureComponent->ScaleY());
}

void Wall::DrawBoundingBox()
{
    BoundingBox bbox = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID())->GetBoundingBox();
    auto textureComponent = gecs::ECS_Engine.components().GetComponentForEntity<Texture>(this->GetID());
    Vector2D cameraPos = gecs::ECS_Engine.resources().Manager<SDLCamera>()->Position();
   // bbox.x -= cameraPos.x;
    bbox.y += cameraPos.y;
    bbox.width *= textureComponent->ScaleX();
    bbox.height *= textureComponent->ScaleY();

    ObjectColor boxColor;
    boxColor.r = 255;
    boxColor.g = 0;
    boxColor.b = 0;
    boxColor.a = 255;
    gecs::ECS_Engine.resources().Manager<SDLRender>()->DrawRect(bbox, boxColor);
}