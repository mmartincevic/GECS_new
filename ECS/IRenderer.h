#ifndef GECS_IRENDERER_H
#define GECS_IRENDERER_H

#pragma once
// TODO: DONT NEED THIS REMOVE
namespace gecs {
    class IRenderer {
    public:
        [[deprecated("This class is obsolete. Should remove")]]
        IRenderer() = default;
        virtual ~IRenderer() = default;
        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Cleanup() = 0;
        virtual void Clear() = 0;
    };
}

#endif // GECS_IRENDERER_H