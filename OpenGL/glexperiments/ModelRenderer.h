#pragma once
#include "DefaultRenderer.h"

class InvalidModelFileException : public std::exception {
public:
    InvalidModelFileException(const std::string& message)
        :std::exception(message.c_str())
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

    void setPerspective(int w, int h, float aspectRatio) override;

    void renderScene(void) override;

};