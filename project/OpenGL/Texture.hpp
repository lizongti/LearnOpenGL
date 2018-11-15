#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Base/Base.hpp"
#include "OpenGL/OpenGL.hpp"

class Texture
{
public:
	typedef std::function<void(void)> HandleFunc;

	Texture()
	{
		glGenTextures(1, &texture_);
	};

	~Texture()
	{
		glDeleteTextures(1, &texture_);
	};

	virtual void Use(uint32_t unit)
	{
		glActiveTexture((uint32_t)GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture_);
	};

	virtual void Import(const std::string& resource)
	{
		glBindTexture(GL_TEXTURE_2D, texture_);
		Mode();
		Load(resource);
		glBindTexture(GL_TEXTURE_2D, 0);
	};
	
	virtual void Mode() = 0;

	virtual bool Load(const std::string& resource, bool srgb = false) = 0;

protected:
	void Mode(uint32_t min_filter, uint32_t mag_filter, uint32_t s_wrap, uint32_t t_wrap,  float* s_border_color = nullptr, float* t_border_color = nullptr)
	{ 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap);
		if (s_wrap == GL_CLAMP_TO_BORDER)
		{
			if (s_border_color == nullptr)
			{
				float board_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, board_color);
			}
			else
			{
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, s_border_color);
			}
		}
		
		if (t_wrap == GL_CLAMP_TO_BORDER)
		{
			if (t_border_color == nullptr)
			{
				float board_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, board_color);
			}
			else
			{
				glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, t_border_color);
			}
		}
	};

public:
	bool loaded() { return loaded_; };
	bool index() { return texture_; };

protected:
	unsigned int texture_;
	bool loaded_ = false;
};

class SimpleTexture : public Texture
{
public:
	SimpleTexture() : Texture()
	{};

	virtual ~SimpleTexture()
	{};

	bool Load(const std::string& resource, bool srgb = false)
	{
		glBindTexture(GL_TEXTURE_2D, texture_);
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(resource.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			if (srgb)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}

			stbi_image_free(data);
			
			loaded_ = true;
			return true;
		}
		else
		{
			std::cerr << "[Texture] Failed to load texture! texture is " << resource << std::endl;
			return false;
		}
	};

	void Mode()
	{
		Texture::Mode(GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT);
	};
};

class TransparentTexture : public Texture
{
public:
	TransparentTexture() : Texture()
	{};

	virtual ~TransparentTexture()
	{};

	bool Load(const std::string& resource, bool srgb = false)
	{
		glBindTexture(GL_TEXTURE_2D, texture_);
		int width, height, channels;
		unsigned char* data = stbi_load(resource.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			if (srgb)
			{									// 纹理格式 					//像素格式
				glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
			
			loaded_ = true;
			return true;
		}
		else
		{
			std::cerr << "[Texture] Failed to load texture! texture is " << resource << std::endl;
			return false;
		}
	};

	void Mode()
	{
		Texture::Mode(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	};	
};

class MipMapTexture : public Texture
{
public:
	MipMapTexture() : Texture()
	{};

	bool Load(const std::string& resource, bool srgb = false)
	{
		glBindTexture(GL_TEXTURE_2D, texture_);
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(resource.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			if (boost::ends_with(resource, ".jpg"))
			{
				if (srgb)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				}
				else
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				}
			}
			else if (boost::ends_with(resource, ".png"))
			{
				if (srgb)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				}
				else
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				}
			}
			else
			{
				std::cerr << "[Texture] resource suffix is not valid! resource is " << resource << std::endl;
			}
			
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);

			loaded_ = true;
			return true;
		}
		else
		{
			std::cerr << "[Texture] Failed to load texture! texture is " << resource << std::endl;
			return false;
		}
	};

	void Mode()
	{
		Texture::Mode(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT);
	};
};

class CubeTexture : public Texture
{
public:
	CubeTexture() : Texture()
	{};

	virtual ~CubeTexture()
	{};

	virtual bool Load(const std::string& resource, bool srgb = false)
	{
		std::vector<std::string> resource_vector;
		resource_vector.push_back((boost::format(resource) % "right").str());
		resource_vector.push_back((boost::format(resource) % "left").str());
		resource_vector.push_back((boost::format(resource) % "top").str());
		resource_vector.push_back((boost::format(resource) % "bottom").str());
		resource_vector.push_back((boost::format(resource) % "front").str());
		resource_vector.push_back((boost::format(resource) % "back").str());

		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
		for(uint32_t index = 0; index < resource_vector.size(); ++index)
		{			
			auto& resource = resource_vector[index];
			int width, height, channels;
			unsigned char* data = stbi_load(resource.c_str(), &width, &height, &channels, 0);
			if (data)
			{
				if (boost::ends_with(resource, ".jpg"))
				{
					if (srgb)
					{
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					}
					else
					{
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					}
				}
				else if (boost::ends_with(resource, ".png"))
				{
					if (srgb)
					{
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_SRGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					}
					else
					{
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					}
				}
				else
				{
					std::cerr << "[Texture] resource suffix is not valid! resource is " << resource << std::endl;
				}
				
				stbi_image_free(data);
			}
			else
			{
				std::cerr << "[Texture] Failed to load texture! texture is " << resource << std::endl;
				return false;
			}
		}
		return true;
	};

	virtual void Mode()
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	};

	virtual void Use(uint32_t unit)
	{
		glActiveTexture((uint32_t)GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
	};

	virtual void Import(const std::string& resource)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
		Mode();
		Load(resource);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	};
};

#endif