#pragma once

#include <map>
#include <string>
#include <vector>

class Vertex;
class MeshData;

class Mesh
{
public:
	Mesh(std::string filePath);
	Mesh(std::vector<Vertex> &vertices, std::vector<int> &indices, bool needCalcNormals);
	~Mesh();

	void draw();
protected:
// 	@Override
// 		protected void finalize() throws Throwable{
// 		try {
// 			if (m_data.deleteReference()) {
// 				if (m_filePath != null) {
// 					m_loadedMeshes.remove(m_filePath, m_data);
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
	static std::map<std::string, MeshData*> m_loadedMeshes;
	MeshData* m_data;

	std::string m_filePath;

	void setVertices(std::vector<Vertex> &vertices, std::vector<int> &indices, bool needCalcNormals);
	void calcNormals(std::vector<Vertex> &vertices, std::vector<int> &indices);
	void loadMesh(std::string filePath);
};

