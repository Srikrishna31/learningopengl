#pragma once
#include "DefaultRenderer.h"

class InvalidModelFileException : public std::invalid_argument {
public:
    InvalidModelFileException(const std::string& message)
        :std::invalid_argument(message.c_str())
    {}
};

class ModelRenderer : public DefaultRenderer
{
private:
    std::unique_ptr<struct Internal> m_data;

private:
    void updateModelViewProjectionMatrix();

public:
    ModelRenderer(const std::string& modelFilePath);
    ~ModelRenderer() override;

    void setPerspective(int w, int h, float aspectRatio) override;

    void renderScene(void) override;

};