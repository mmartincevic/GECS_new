#pragma once

#ifndef __ECS_IRESOURCE_H__
#define __ECS_IRESOURCE_H__

class IResource {
public:
    virtual ~IResource() {}
    virtual void Initialize() = 0;
    virtual void Cleanup() = 0;
    virtual void Clear() = 0;

protected:
    IResource() {}
};

#endif