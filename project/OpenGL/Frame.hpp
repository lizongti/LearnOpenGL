#ifndef FRAME_HPP
#define FRAME_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class Frame
{
public:
    typedef std::function<void(void)> HandleFunc;

    Frame()
    {
        glGenBuffers(1, &frame_buffer_object_);
    };

    virtual ~Frame()
    {
        glDeleteBuffers(1, &frame_buffer_object_);
    };

    bool Completed()
    {
        bool completed = false;
        glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);
        completed = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return completed;
    };

    uint32_t texture()
    {
        return texture_; 
    };

    uint32_t render_buffer_object()
    {
        return render_buffer_object_;
    };

    virtual void Use(uint32_t unit)
	{
		glActiveTexture((uint32_t)GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture_);
	};

    void Work(HandleFunc handle_func)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 我们现在不使用模板缓冲
        glEnable(GL_DEPTH_TEST);

        handle_func();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };

    static void DefaultWork(HandleFunc handle_func)
    {   
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);

        handle_func();
    };

    void AttachTexture()// 纹理附件
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);

        glGenTextures(1, &texture_);
        glBindTexture(GL_TEXTURE_2D, texture_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_WIDTH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0);

    };

    void AttachRenderBuffer() // 渲染缓冲对象附件
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_object_);

        glGenRenderbuffers(1, &render_buffer_object_);
        glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object_);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_WIDTH); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer_object_); // now actually attach it

        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };

protected:
    GLuint frame_buffer_object_;

    GLuint texture_;
    GLuint render_buffer_object_;
};

#endif