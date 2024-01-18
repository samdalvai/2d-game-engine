#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include <string>

struct FPSComponent {
    std::string assetId;

    FPSComponent(std::string assetId = "") {
        this->assetId = assetId;
    };
};

#endif
