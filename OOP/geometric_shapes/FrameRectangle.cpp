#include "FrameRectangle.h"

double FrameRectangle::getWidth() const {
    return width_;
}

double FrameRectangle::getHeight() const {
    return height_;
}

Point FrameRectangle::getPos() const {
    return center_;
}