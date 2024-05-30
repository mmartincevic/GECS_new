#include "Player.h"

#include "../Game/Input/InputBuffer.h"

#include "../Utils/SDL_Wrapper.h"
#include "../States/Player/PlayerIdleState.h"
#include "../Components/Transform.h"
#include "../Components/Texture.h"
#include "../TextureManager.h"


PlayerStates Player::GetState()
{
    if (currentState != nullptr)
    {
        return currentState->getState();
    }

    return PlayerStates::NONE;
}

void Player::ChangeState(std::shared_ptr<PlayerState> newState) {
    if (currentState != nullptr && currentState == newState) { return; }
    currentState = newState;
    currentState->Enter(this);
}

void Player::HandleInput(const InputBuffer inputBuffer) {
    if (currentState) {
        currentState->HandleInput(this, inputBuffer);
    }
}

void Player::Update(float deltaTime) {
    if (currentState) {
        currentState->Update(this, deltaTime);
    }
    // Check if we need to transition back to IdleState
    if (!movementKeyPressed) {
        //ChangeState(new PlayerIdleState());
    }

    // Reset movement key pressed flag
    movementKeyPressed = false;
}

void Player::Render() {
    if (currentState) {
        currentState->Render(this);
    }
}

bool Player::IsKeyPressed(SDL_Keycode key) {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
    return state[scancode];
}

void Player::Draw(float dt)
{
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());
    auto textureComponent = gecs::ECS_Engine.components().GetComponentForEntity<Texture>(this->GetID());
    int frame = ((int)dt / 10) % 7;

    /*TextureManager::Instance().DrawFrame(
        SDL_Wrapper::getInstance().getRenderer(), textureComponent->getTextureId(),
        transformComponent->GetPosition()->x, transformComponent->GetPosition()->y,
        transformComponent->GetWidth(), transformComponent->GetHeight(), 0, frame);*/
    TextureManager::Instance().Draw(
        SDL_Wrapper::getInstance().getRenderer(), textureComponent->getTextureId(),
        transformComponent->GetPosition()->x, transformComponent->GetPosition()->y,
        transformComponent->GetWidth(), transformComponent->GetHeight(), 0);

}

BoundingBox Player::GetCollisionBox(float dt) 
{
    /*auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());
    BoundingBox bbox = transformComponent->GetBoundingBox();
    return bbox;*/
    //return currentState->GetBoundingBox(this, dt);
    BoundingBox bbox = this->GetBoundingBox();
    bbox.width += dt;
    bbox.height += dt;
    return bbox;
}

BoundingBox Player::GetBoundingBox()
{
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());
    return transformComponent->GetBoundingBox();
}

void Player::DrawBoundingBox(bool draw_collision_box, float dt) 
{
    // Set the draw color (RGBA)
    SDL_SetRenderDrawColor(SDL_Wrapper::getInstance().getRenderer(), 255, 0, 0, 255);  // Red color
    //auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());

    BoundingBox bbox = (draw_collision_box) ? GetCollisionBox(dt) : GetBoundingBox();
    //// Create a rectangle to represent the bounding box
    SDL_Rect boundingBox;
    boundingBox.x = bbox.x;
    boundingBox.y = bbox.y;
    boundingBox.w = bbox.width;
    boundingBox.h = bbox.height;

    // Draw the rectangle outline
    SDL_RenderDrawRect(SDL_Wrapper::getInstance().getRenderer(), &boundingBox);
}



void Player::HandleCollision(const CollisionEvent& event) {
    // Example collision handling logic
    //auto& transform = GetComponent<TransformComponent>();
    //auto& velocity = GetComponent<VelocityComponent>();
    //auto& state = GetComponent<StateComponent>();

    //if (event.otherEntity.HasComponent<GroundComponent>()) {
    //    if (state.state == PlayerState::Falling || state.state == PlayerState::Jumping) {
    //        // Collision with the ground, stop vertical movement
    //        velocity.vy = 0;
    //        state.state = PlayerState::Idle;
    //        transform.y = event.otherEntity.GetComponent<TransformComponent>().y - transform.height;
    //    }
    //}
}

void Player::RegisterEvents() {
    /*gecs::ECS_Engine.events().subscribe("COLLISION", [this](const EventData& data) {
        const auto& event = std::get<CollisionEvent>(data);
        if (event.entityA == *this || event.entityB == *this) {
            HandleCollision(event);
        }
        });*/
}