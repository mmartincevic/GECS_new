#ifndef DYNAMICBODY_COMPONENT_H__
#define DYNAMICBODY_COMPONENT_H__
#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"

#include "../Utils/GameHelper.h"
#include "../World.h"


struct DynamicBody : public gecs::Component<DynamicBody>
{
    public:
        DynamicBody(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
            : gecs::Component<DynamicBody>(typeId, ownerId) {}
};



//struct DynamicBody : public gecs::Component<DynamicBody>
//{
//public:
//    DynamicBody(gecs::ComponentTypeId typeId, gecs::EntityId ownerId,
//        float sizeX, float sizeY, float posX, float posY, float angle)
//        : gecs::Component<DynamicBody>(typeId, ownerId) {
//
//        m_SizeX = sizeX;
//        m_SizeY = sizeY;
//
//        b2Vec2 Size = b2Vec2(sizeX, sizeY);
//        b2Vec2 SizeHalf = b2Vec2(Size.x * 0.5f, Size.y * 0.5f);
//        b2Vec2 Position = b2Vec2(posX, posY);
//
//        b2BodyDef BodyDefinition;
//        BodyDefinition.type = b2BodyType::b2_dynamicBody;
//        BodyDefinition.angle = angle;
//        BodyDefinition.position = GameHelper::Get().PixelToMeter(Position);
//        b2PolygonShape Shape;
//
//
//        Shape.SetAsBox(
//            GameHelper::Get().PixelToMeter(SizeHalf.x),
//            GameHelper::Get().PixelToMeter(SizeHalf.y),
//            GameHelper::Get().PixelToMeter(b2Vec2(0.0f, 0.0f)), 0.0f);
//
//        b2FixtureDef FixtureDefinition;
//        FixtureDefinition.shape = &Shape;
//        FixtureDefinition.friction = 0.2f;
//        FixtureDefinition.restitution = 0.6f;
//        FixtureDefinition.density = 1.0f;
//        body_ = World::Get().GetPhysicsWorld()->CreateBody(&BodyDefinition);
//        body_->CreateFixture(&FixtureDefinition);
//    }
//
//
//    void UpdatePositionX(float dt)
//    {
//        /*b2Vec2 newPosition = b2Vec2(
//            GameHelper::Get().MeterToPixel(body_->GetPosition().x) + dt,
//            GameHelper::Get().MeterToPixel(body_->GetPosition().y));
//        body_->SetTransform(GameHelper::Get().PixelToMeter(newPosition), body_->GetAngle());*/
//        b2Vec2 vel = body_->GetLinearVelocity();
//        b2Vec2 pos = body_->GetPosition();
//        //body_->ApplyLinearImpulse(b2Vec2(GameHelper::Get().PixelToMeter(dt), body_->GetPosition().y), body_->GetWorldCenter(), true);
//        body_->ApplyLinearImpulse(b2Vec2(2, 0), body_->GetWorldCenter(), true);
//    }
//
//    void UpdatePositionY(float dt)
//    {
//        /*b2Vec2 newPosition = b2Vec2(
//            GameHelper::Get().MeterToPixel(body_->GetPosition().x),
//            GameHelper::Get().MeterToPixel(body_->GetPosition().y) + dt);
//        body_->SetTransform(GameHelper::Get().PixelToMeter(newPosition), body_->GetAngle());*/
//        body_->ApplyLinearImpulse(b2Vec2(0, -20), body_->GetWorldCenter(), true);
//    }
//
//
//    [[nodiscard]] inline float GetPositionX()
//    {
//        const b2Vec2& position = body_->GetPosition();
//        return GameHelper::Get().MeterToPixel(body_->GetPosition().x) - m_SizeX / 2;
//    }
//
//    [[nodiscard]] inline float GetPositionY()
//    {
//        const b2Vec2& position = body_->GetPosition();
//        return GameHelper::Get().MeterToPixel(body_->GetPosition().y) - m_SizeY / 2;
//    }
//
//    [[nodiscard]] inline float GetWidth() const
//    {
//        return m_SizeX;
//    }
//
//    [[nodiscard]] inline float GetHeight() const
//    {
//        return m_SizeY;
//    }
//
//    [[nodiscard]] inline double GetAngleDegrees() const
//    {
//        float radianAngle = body_->GetAngle();
//        double pi = 3.14159;
//        return(radianAngle * (180 / pi));
//    }
//
//    [[nodiscard]] inline b2Body* GetBody() const
//    {
//        return body_;
//    }
//
//protected:
//    b2Body* body_;
//    float m_SizeX;
//    float m_SizeY;
//};
#endif // DYNAMICBODY_COMPONENT_H__