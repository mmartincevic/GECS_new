#ifndef TILEGROUP_H
#define TILEGROUP_H

#pragma once

#include <string>

namespace tiller {

    struct TileGroup
    {
        int ID;
        float Opacity = 1.0f;
        std::string Name;
        bool Collider = false;
    };

};

#endif // TILEGROUP_H