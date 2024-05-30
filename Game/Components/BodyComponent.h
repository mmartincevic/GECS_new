//#ifndef BODY_COMPONENT_H__
//#define BODY_COMPONENT_H__
//#pragma once
//
//#include "../ECS/API.h"
//#include "../ECS/ECS.h"
//#include "../ECS/Component.h"
//
//
////#include "../Game/Systems/PhysicsSystem.h"
//#include "../Utils/GameHelper.h"
////#include "../World.h"
//
//
//struct BodyComponent : public gecs::Component<BodyComponent>
//{
//   /* BodyComponent(std::shared_ptr<b2Body> body)
//        : body(body) {}*/
//
//    public:
//        BodyComponent(gecs::ComponentTypeId typeId, gecs::EntityId ownerId)
//            : gecs::Component<BodyComponent>(typeId, ownerId) {
//            
//           // body = world.CreateBody(&bodyDef)
//
//            // GET WORLD AND SET CREATE BODY 
//           // b2World* world = gecs::ECS_Engine.systems().getSystem<PhysicsSystem>()->GetWorld();
//            //body_ = world.CreateBody(&bodyDef);
//            
//
//            /*b2World* world = World::Get().GetPhysicsWorld();
//
//            b2Vec2 Size = b2Vec2(400.0f, 20.0f);
//            b2Vec2 SizeHalf = b2Vec2(Size.x * 0.5f, Size.y * 0.5f);
//            b2Vec2 Position = b2Vec2(100.0f, 100.0f);
//
//            b2BodyDef BodyDefinition;
//            BodyDefinition.type = b2BodyType::b2_dynamicBody;
//            BodyDefinition.angle = 0.0f;
//            BodyDefinition.position = GameHelper::Get().PixelToMeter(Position);
//            b2PolygonShape Shape;
//
//
//            Shape.SetAsBox(
//                GameHelper::Get().PixelToMeter(Position.x),
//                GameHelper::Get().PixelToMeter(Position.y),
//                GameHelper::Get().PixelToMeter(b2Vec2(0.0f, 0.0f)), 0.0f);
//
//            b2FixtureDef FixtureDefinition;
//
//            FixtureDefinition.shape = &Shape;
//            FixtureDefinition.friction = 0.3f;
//            FixtureDefinition.restitution = 0.6f;
//            FixtureDefinition.density = 1.0f;
//
//            body_ = world->CreateBody(&BodyDefinition);
//            body_->CreateFixture(&FixtureDefinition);
//        }
//
//
//        [[nodiscard]] inline b2Body* GetBody() const
//        {
//            return body_;
//        }
//
//    protected:
//        b2Body* body_;*/
//};
//#endif
//
