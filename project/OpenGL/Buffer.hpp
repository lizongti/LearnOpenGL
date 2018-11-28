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

class FrameArrayBuffer : public ArrayBuffer
{
public:
    FrameArrayBuffer() : ArrayBuffer()
    {};
    virtual ~FrameArrayBuffer()
    {};

    virtual void Import(void* data, size_t size)
    {
        ArrayBuffer::Import(data, size);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);   
    };
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

class TextureNormalVertexBuffer : public ArrayBuffer
{
public:
    TextureNormalVertexBuffer() : ArrayBuffer()
    {};
    virtual ~TextureNormalVertexBuffer()
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
    };
};

class TextureModelInstanceVertexBuffer : public ArrayBuffer
{
public:
    TextureModelInstanceVertexBuffer()
    {};
    virtual ~TextureModelInstanceVertexBuffer()
    {};

    virtual void Import(void* data, size_t size)
    {
        ArrayBuffer::Import(data, size);

        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
        glEnableVertexAttribArray(3); 
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(4); 
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(5); 
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
    };
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