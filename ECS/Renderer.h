#ifndef GECS_RENDERER_H
#define GECS_RENDERER_H

#pragma once

#include "IRenderer.h"
// TODO: DONT NEED THIS REMOVE

namespace gecs {

    template<typename T>
    class Renderer : public IRenderer {

    [[deprecated("This class is obsolete. Should remove")]]
    public:
        Renderer() = default;
        virtual ~Renderer() = default;
        virtual void Initialize() override {}
        virtual void Update() override {}
        virtual void Render() override {}
        virtual void Cleanup() override {}
        virtual void Clear() override {}
    };
}

#endif // GECS_RENDERER_H