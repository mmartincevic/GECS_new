#include "Player.h"

#include "../Game/Input/InputBuffer.h"
#include "../Utils/SDL_Wrapper.h"
#include "../States/Player/PlayerIdleState.h"
#include "../Events/CollisionEvent.h"
#include "../World/World.h"

#include "../Resources/SDLRender.h"
#include "../Resources/SDLTexture.h"
#include "../Resources/SDLCamera.h"
#include "../Resources/SDLImgui.h"
#include "../Components/ObjectColor.h"

#include "PlayerImgui.h"

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

// TODO : Fix frame drawing
void Player::Draw(float dt)
{
    auto transformComponent = gecs::ECS_Engine.components().GetComponentForEntity<Transform>(this->GetID());
    auto textureComponent = gecs::ECS_Engine.components().GetComponentForEntity<Texture>(this->GetID());
    int frame = ((int)dt / 10) % 7;

    std::shared_ptr<SDLTexture> texture = gecs::ECS_Engine.resources().Manager<SDLTexture>();

    texture->Draw(textureComponent->getTextureId(),
        transformComponent->Position().x, transformComponent->Position().y,
        transformComponent->Width(), transformComponent->Height());
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
    BoundingBox bbox = (draw_collision_box) ? GetCollisionBox(dt) : GetBoundingBox();

    Vector2D cameraPos = gecs::ECS_Engine.resources().Manager<SDLCamera>()->Position();
    //bbox.x += cameraPos.x;
    bbox.y += cameraPos.y;

    ObjectColor boxColor;
    boxColor.r = 255;
    boxColor.g = 0;
    boxColor.b = 0;
    boxColor.a = 255;
    gecs::ECS_Engine.resources().Manager<SDLRender>()->DrawRect(bbox, boxColor);
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


void Player::HandleCollision(const CollisionEvent& event) {}

void Player::RegisterEvents() {
    /*gecs::ECS_Engine.events().subscribe("COLLISION", [this](const EventData& data) {
        const auto& event = std::get<CollisionEvent>(data);
        if (event.entityA == *this || event.entityB == *this) {
            HandleCollision(event);
        }
        });*/
}


void Player::RegisterImguiWindow()
{
    gecs::ECS_Engine.resources().Manager<SDLImgui>()->AddImguiWindow(std::make_shared<PlayerImgui>(this));
}