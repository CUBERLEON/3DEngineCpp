#pragma once

#include <string>
#include <map>

class TextureData;

class Texture
{
public:
	Texture(std::string filePath);
	~Texture();

	void bind(int samplerLocation);
protected:
// 	@Override
// 		protected void finalize() throws Throwable{
// 		try {
// 			if (m_data != null && m_data.deleteReference()) {
// 				if (m_filePath != null) {
// 					m_loadedTextures.remove(m_filePath, m_data);
// 					Debug.info("Mesh(" + m_filePath + ") was deleted (finalize)");
// 				}
// 			}
// 		}
// 		catch (Throwable t) {
// 			throw t;
// 		}
// 		finally {
// 			super.finalize();
// 		}
// 	}
private:
	static std::map<std::string, TextureData*> m_loadedTextures;
	TextureData* m_data;

	std::string m_filePath;

	void loadTexture(std::string filePath);
};

