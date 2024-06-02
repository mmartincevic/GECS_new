#include "Player.h"

#include "../Game/Input/InputBuffer.h"
#include "../Utils/SDL_Wrapper.h"
#include "../States/Player/PlayerIdleState.h"
#include "../TextureManager.h"
#include "../Events/CollisionEvent.h"
#include "../World/World.h"

Player::Player(gecs::EntityId _id)
    : currentState(nullptr), 
    m_PlayerTransformComponent(nullptr),
    m_PlayerRigidBodyComponent(nullptr),
    m_PlayerTextureComponent(nullptr),
    gecs::Entity(_id)
{}


void Player::SetCollisionState(CollisionSide collisionSide) 
{ 
    m_Collisioning = collisionSide; 
}

CollisionSide Player::GetCollisionState() const
{ 
    return m_Collisioning; 
}

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
    //delete currentState;
    currentState = newState;
    currentState->Enter(this);
}

void Player::HandleInput(const InputBuffer inputBuffer) {
    if (currentState) {
        currentState->HandleInput(this, inputBuffer);
    }
}

void Player::ToggleState() {
    currentState->Toggle(this);
}

void Player::Update(float deltaTime) {
    if (currentState) {
        currentState->Update(this, deltaTime);
    }
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
        transformComponent->Position().x, transformComponent->Position().y,
        transformComponent->Width(), transformComponent->Height(), 0);

}

BoundingBox Player::GetCollisionBox(float dt) 
{
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

    Vector2D cameraPos = World::Instance().Camera()->Position();
    BoundingBox bbox = (draw_collision_box) ? GetCollisionBox(dt) : GetBoundingBox();
    //// Create a rectangle to represent the bounding box
    SDL_Rect boundingBox;
    boundingBox.x = bbox.x - cameraPos.x;
    boundingBox.y = bbox.y - cameraPos.y;
    boundingBox.w = bbox.width;
    boundingBox.h = bbox.height;

    // Draw the rectangle outline
    SDL_RenderDrawRect(SDL_Wrapper::getInstance().getRenderer(), &boundingBox);
}


Texture* Player::PlayerTexture()
{
    if (m_PlayerTextureComponent == nullptr)
    {
        m_PlayerTextureComponent = gecs::ECS_Engine.components().GetComponentForEntity<Texture>(GetID()).get();
    }
    return m_PlayerTextureComponent;
}

Transform* Player::PlayerTransform()
{
    if (m_PlayerTransformComponent == nullptr)
    {
        m_PlayerTransformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(GetID()).get();
    }
    return m_PlayerTransformComponent;
}

RigidBody* Player::PlayerRigidBody()
{
    if (m_PlayerRigidBodyComponent == nullptr)
    {
         m_PlayerRigidBodyComponent = gecs::ECS_Engine.components().GetComponentForEntity<RigidBody>(GetID()).get();
    }
    return m_PlayerRigidBodyComponent;
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