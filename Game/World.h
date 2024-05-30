#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "Utils/CBox2DDebugRender.h"
#include "Utils/SDL_Wrapper.h"


class World {
    protected:
        World() {};
        ~World() {};

    public:
        static World& Get() {
            static World instance;
            return instance;
        }

        void InitializePhysics()
        {
            /*world_ = new b2World(b2Vec2(0.0f, 9.8f));
            CBox2DDebugRenderer* pB2DebugRenderer = new CBox2DDebugRenderer(SDL_Wrapper::getInstance().getRenderer(), 32.0f, b2Draw::e_shapeBit);
            world_->SetDebugDraw(pB2DebugRenderer);*/
        }

        //inline b2World* GetPhysicsWorld() { return world_; }
        
        World(const World&) = delete;
        void operator=(const World&) = delete;
};

#endif // GAMEWORLD_H__