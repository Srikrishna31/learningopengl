#pragma once
#include "DefaultRenderer.h"

class RectangularMeshRenderer final : public DefaultRenderer
{
    std::unique_ptr<struct Impl> m_data;

    void updateModelViewProjecttionMatrix();
public:

};