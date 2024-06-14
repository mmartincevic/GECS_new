#include "CollisionSystem.h"

#include "../Components/Transform.h"
#include "../Components/Drawable.h"
#include "../Components/Texture.h"
#include "../Components/BodyComponent.h"
#include "../Components/RigidBody.h"
#include "../Components/DynamicBody.h"
#include "../Objects/Player.h"
#include "../Objects/Wall.h"
#include "../Events/CollisionEvent.h"

#include "../Game/States/Player/PlayerFallingState.h"
#include "../Game/States/Player/PlayerStates.h"

#include "../Map/Tile.h"
#include "../Map/Tiller.h"

bool IsColliding(const BoundingBox& a, const BoundingBox& b) {
    return (a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y);
}

BoundingBox TileBoundingBox(const tiller::Tile& tile) {
    BoundingBox bbox;
    bbox.x = tile.displayCol * tile.width;
    bbox.y = tile.displayRow * tile.height;
    bbox.width = tile.width;
    bbox.height = tile.height;
    return bbox;
}

CollisionSide CollisionSystem::CheckCollision(const BoundingBox& a, const BoundingBox& b) 
{
    if (!IsColliding(a, b)) {
        return CollisionSide::NONE;
    }

    float a_center_x = a.x + a.width / 2.0f;
    float a_center_y = a.y + a.height / 2.0f;
    float b_center_x = b.x + b.width / 2.0f;
    float b_center_y = b.y + b.height / 2.0f;

    float dx = b_center_x - a_center_x;
    float dy = b_center_y - a_center_y;

    float combined_half_width = (a.width + b.width) / 2.0f;
    float combined_half_height = (a.height + b.height) / 2.0f;

    float overlapX = combined_half_width - std::abs(dx);
    float overlapY = combined_half_height - std::abs(dy);

    if (overlapX < overlapY) {
        if (dx > 0) {
            return CollisionSide::LEFT;
        }
        else {
            return CollisionSide::RIGHT;
        }
    }
    else {
        if (dy > 0) {
            return CollisionSide::TOP;
        }
        else {
            return CollisionSide::BOTTOM;
        }
    }
}

void CollisionSystem::Update(float dt) 
{
    // TODO: Fix collisions with Tiled elements

    FOUND_COLLISION = false;
    auto wall_entities = gecs::ECS_Engine.entities().GetEntity<Wall>();
    auto player_entities = gecs::ECS_Engine.entities().GetEntity<Player>();
    std::vector<tiller::Tile> tilecoliders = tiller::Tiller::Instance().Colliders();

    for (auto player : player_entities)
    {   
        auto player_entity = player_entities.front();
        auto playerTransformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(player->GetID());

        BoundingBox playerBBox = player_entity->GetCollisionBox(10.0f);

        for (auto wall : wall_entities)
        {
            auto entityTransformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(wall->GetID());

            BoundingBox wallBBox = entityTransformComponent->GetBoundingBox();
            CollisionSide collisionSide = CheckCollision(wallBBox, playerBBox);

            if (collisionSide != CollisionSide::NONE) {
                FOUND_COLLISION = true;
                player_entity->SetCollisionState(collisionSide); // set new collision side
            }
        }

        for (auto tile : tilecoliders)
        {
            BoundingBox tileBBox = TileBoundingBox(tile);
            CollisionSide collisionSide = CheckCollision(tileBBox, playerBBox);

            if (collisionSide != CollisionSide::NONE) {
                FOUND_COLLISION = true;
                player_entity->SetCollisionState(collisionSide); // set new collision side
            }
        }


        if (!FOUND_COLLISION)
        {
            player->SetCollisionState(CollisionSide::NONE); // reset collision on each update if NONE found
        }
    }
};