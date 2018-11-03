#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class Buffer
{
public:
    Buffer(GLenum buffer_type)
    {
        buffer_type_ = buffer_type;
        glGenBuffers(1, &buffer_object_);
    };

    virtual ~Buffer()
    {
        glDeleteBuffers(1, &buffer_object_);
    };

protected:
    virtual void Import(void* data, size_t size) = 0;

protected:
    GLenum buffer_type_;
    GLuint buffer_object_;
};

class ArrayBuffer : public Buffer
{
public:
    ArrayBuffer() : Buffer((GLenum)GL_ARRAY_BUFFER)
    {};

    virtual ~ArrayBuffer()
    {};

    virtual void Import(void* data, size_t size)
    {
        glBindBuffer(buffer_type_, buffer_object_);
        glBufferData(buffer_type_, size, data, GL_STATIC_DRAW);
    };
};

class ElementArrayBuffer : public Buffer
{
public:
    ElementArrayBuffer() : Buffer((GLenum)GL_ELEMENT_ARRAY_BUFFER)
    {};

    virtual ~ElementArrayBuffer()
    {};

    virtual void Import(void* data, size_t size)
    {
        glBindBuffer(buffer_type_, buffer_object_);
        glBufferData(buffer_type_, size, data, GL_STATIC_DRAW);
    };
};


class VertexBuffer : public ArrayBuffer
{
public:
    VertexBuffer() : ArrayBuffer()
    {};
    virtual ~VertexBuffer()
    {};  

    virtual void Import(void* data, size_t size)
    {
        ArrayBuffer::Import(data, size);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
};

class ColorVertexBuffer : public ArrayBuffer
{
public:
    ColorVertexBuffer() : ArrayBuffer()
    {};
    virtual ~ColorVertexBuffer()
    {};  

    virtual void Import(void* data, size_t size)
    {
        ArrayBuffer::Import(data, size);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
};

class TextureVertexBuffer : public ArrayBuffer
{
public:
    TextureVertexBuffer() : ArrayBuffer()
    {};
    virtual ~TextureVertexBuffer()
    {};  

    virtual void Import(void* data, size_t size)
    {
        ArrayBuffer::Import(data, size);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
};

class TextureColorVertexBuffer : public ArrayBuffer
{
public:
    TextureColorVertexBuffer() : ArrayBuffer()
    {};
    virtual ~TextureColorVertexBuffer()
    {};  

    virtual void Import(void* data, size_t size)
    {
        ArrayBuffer::Import(data, size);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
};

class IndiceBuffer : public ElementArrayBuffer
{
public:
    IndiceBuffer() : ElementArrayBuffer()
    {};
    virtual ~IndiceBuffer()
    {};
};

#endif