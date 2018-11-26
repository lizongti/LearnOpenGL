#ifndef OPENGL_HPP
#define OPENGL_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/string_cast.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <External/stb_image.h>


#define USE_GAMMA_CORRECTION 1
//#define USE_CULL_FACE 1
#define USE_MSAA 16
#define USE_VSYNC 1
#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 600.0f

#include <OpenGL/Buffer.hpp>
#include <OpenGL/Profile.hpp>
#include <OpenGL/Shader.hpp>
#include <OpenGL/Uniform.hpp>
#include <OpenGL/Window.hpp>
#include <OpenGL/Texture.hpp>
#include <OpenGL/MVP.hpp>
#include <OpenGL/IO.hpp>
#include <OpenGL/Light.hpp>
//#include <OpenGL/Frame.hpp>

#endif