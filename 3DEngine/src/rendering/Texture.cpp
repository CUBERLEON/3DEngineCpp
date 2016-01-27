#include "Texture.h"

#include <GL/glew.h>
#include "../core/Debug.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"
#include "resources/TextureData.h"

Texture::Texture(std::string filePath)
{
	m_filePath = filePath;

	if (m_loadedTextures.count(filePath) && (m_data = m_loadedTextures[filePath]) != nullptr) 
	{
		m_data->addReference();
	}
	else
	{
		loadTexture(filePath);
		Debug::info("Texture('%s') was loaded", m_filePath.c_str());
	}
}

Texture::~Texture()
{
	Debug::info("Texture destructor");
// 		if (m_data != null)
// 			m_data.dispose();
}

void Texture::bind(int samplerLocation)
{
	if (samplerLocation < 0 || samplerLocation > 31)
		Debug::fatalError("sampler location(" + std::to_string(samplerLocation) + ") is out of valid range [0, 31]");

	glActiveTexture(GL_TEXTURE0 + samplerLocation);
	glBindTexture(GL_TEXTURE_2D, m_data->getBufferID());
}

std::map<std::string, TextureData*> Texture::m_loadedTextures = std::map<std::string, TextureData*>();

void Texture::loadTexture(std::string filePath)
{
	int width, height, bytesPerPixel;
	unsigned char* image = stbi_load(("./res/" + filePath).c_str(), &width, &height, &bytesPerPixel, 4);

	if (image == NULL)
		Debug::fatalError("Texture '" + filePath + "' loading failed!");

	m_data = new TextureData();
	glBindTexture(GL_TEXTURE_2D, m_data->getBufferID());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);

	m_loadedTextures[filePath] = m_data;

// 	std::string[] splitArray = filePath.split("\\.");
// 	//        String ext = splitArray[splitArray.length - 1].toUpperCase();
// 
// 	try {
// 		if (!new File("./res/" + filePath).exists())
// 			throw new Exception("'" + filePath + "' texture doesn't exist");
// 
// 		BufferedImage image = ImageIO.read(new File("./res/" + filePath));
// 		int[] pixels = image.getRGB(0, 0, image.getWidth(), image.getHeight(), null, 0, image.getWidth());
// 
// 		ByteBuffer buffer = BufferUtils.createByteBuffer(image.getHeight() * image.getWidth() * 4);
// 		boolean hasAlpha = image.getColorModel().hasAlpha();
// 
// 		for (int y = 0; y < image.getHeight(); y++) {
// 			for (int x = 0; x < image.getWidth(); x++) {
// 				int pixel = pixels[y * image.getWidth() + x];
// 
// 				buffer.put((byte)((pixel >> 16) & 0xFF));
// 				buffer.put((byte)((pixel >> 8) & 0xFF));
// 				buffer.put((byte)((pixel)& 0xFF));
// 				if (hasAlpha)
// 					buffer.put((byte)((pixel >> 24) & 0xFF));
// 				else
// 					buffer.put((byte)(0xFF));
// 			}
// 		}
// 
// 		buffer.flip();
// 
// 		m_data = new TextureData();
// 
// 		glBindTexture(GL_TEXTURE_2D, m_data.getBufferID());
// 
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 
// 		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
// 	}
// 	catch (Exception e) {
// 		Debug.fatalError(e.getMessage());
// 	}
// 
// 	m_loadedTextures.put(filePath, new WeakReference<>(m_data));
}
