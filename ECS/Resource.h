#pragma once

#ifndef __ECS_RESOURCE_H__
#define __ECS_RESOURCE_H__

#include "IResource.h"

namespace gecs {

    template<typename T>
    class Resource : public IResource {

    public:
        virtual ~Resource() {}
        virtual void Initialize() override {}
        virtual void Cleanup() override {}
        virtual void Clear() override {};
    protected:

        Resource() {}
    };
};

#endif