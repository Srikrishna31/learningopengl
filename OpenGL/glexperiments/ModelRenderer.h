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

public:
    ModelRenderer(const std::string& modelFilePath);
};