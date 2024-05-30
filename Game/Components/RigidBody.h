#ifndef RIGIDBODY_COMPONENT_H__
#define RIGIDBODY_COMPONENT_H__
#pragma once

#include "../ECS/API.h"
#include "../ECS/ECS.h"
#include "../ECS/Component.h"


#include "../Utils/GameHelper.h"
#include "../World.h"


struct RigidBody : public gecs::Component<RigidBody>
{
    public:
        RigidBody(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
            : gecs::Component<RigidBody>(typeId, ownerId) {}
};


//struct RigidBody : public gecs::Component<RigidBody>
//{
//    public:
//        RigidBody(gecs::ComponentTypeId typeId, gecs::EntityId ownerId, 
//            float sizeX, float sizeY, float posX, float posY, float angle)
//            : gecs::Component<RigidBody>(typeId, ownerId) {
//
//            m_SizeX = sizeX;
//            m_SizeY = sizeY;
//
//            b2Vec2 Size = b2Vec2(sizeX, sizeY);
//            b2Vec2 SizeHalf = b2Vec2(Size.x * 0.5f, Size.y * 0.5f);
//            b2Vec2 Position = b2Vec2(posX, posY);
//
//            b2BodyDef BodyDefinition;
//            BodyDefinition.type = b2BodyType::b2_staticBody;
//            BodyDefinition.angle = angle;
//            BodyDefinition.position = GameHelper::Get().PixelToMeter(Position);
//            b2PolygonShape Shape;
//
// 
//            Shape.SetAsBox(
//                GameHelper::Get().PixelToMeter(SizeHalf.x),
//                GameHelper::Get().PixelToMeter(SizeHalf.y),
//                GameHelper::Get().PixelToMeter(b2Vec2(0.0f, 0.0f)), 0.0f);
//
//            b2FixtureDef FixtureDefinition;
//            FixtureDefinition.shape = &Shape;
//            FixtureDefinition.friction = 0.2f;
//            FixtureDefinition.restitution = 0.6f;
//            FixtureDefinition.density = 1.0f;
//            body_ = World::Get().GetPhysicsWorld()->CreateBody(&BodyDefinition);
//            body_->CreateFixture(&FixtureDefinition);
//        }
//
//        [[nodiscard]] inline float GetPositionX()
//        {
//            const b2Vec2& position = body_->GetPosition();
//            return GameHelper::Get().MeterToPixel(body_->GetPosition().x) - m_SizeX / 2;
//        }
//
//        [[nodiscard]] inline float GetPositionY()
//        {
//            const b2Vec2& position = body_->GetPosition();
//            return GameHelper::Get().MeterToPixel(body_->GetPosition().y) - m_SizeY / 2;
//        }
//
//        [[nodiscard]] inline float GetWidth() const
//        {
//            return m_SizeX;
//        }
//
//        [[nodiscard]] inline float GetHeight() const
//        {
//            return m_SizeY;
//        }
//
//        [[nodiscard]] inline double GetAngleDegrees() const
//        {
//            float radianAngle = body_->GetAngle();
//            double pi = 3.14159;
//            return(radianAngle * (180 / pi));
//        }
//
//        [[nodiscard]] inline b2Body* GetBody() const
//        {
//            return body_;
//        }
//
//    protected:
//        b2Body* body_;
//        float m_SizeX;
//        float m_SizeY;
//};
#endif

