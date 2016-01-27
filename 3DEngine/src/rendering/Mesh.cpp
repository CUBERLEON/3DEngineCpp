#include "Mesh.h"

#include <regex>
#include <locale>
// #include <fbxsdk.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/cimport.h>
#include "Vertex.h"
#include "../core/Debug.h"
#include "resources/MeshData.h"

Mesh::Mesh(std::string filePath)
{
	m_filePath = filePath;

	if (m_loadedMeshes.count(filePath) && (m_data = m_loadedMeshes[filePath]) != nullptr) 
	{
		m_data->addReference();
	}
	else 
	{
		loadMesh(filePath);
		Debug::info("Mesh('%s') was loaded", m_filePath.c_str());
	}
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<int> &indices, bool needCalcNormals)
{
	setVertices(vertices, indices, needCalcNormals);
}

Mesh::~Mesh()
{
	Debug::info("Mesh destructor");
	delete m_data;
}

void Mesh::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_data->getVertexBufferID());
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 4 * 8, (void*)(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * 8, (void*)(4 * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, 4 * 8, (void*)(4 * (3 + 2)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->getIndicesBufferID());
	glDrawElements(GL_TRIANGLES, m_data->getIndicesCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

std::map<std::string, MeshData*> Mesh::m_loadedMeshes = std::map<std::string, MeshData*>();

void Mesh::setVertices(std::vector<Vertex>& vertices, std::vector<int>& indices, bool needCalcNormals)
{
	if (needCalcNormals)
		calcNormals(vertices, indices);

// 	std::vector<float> v;
// 	for (int i = 0; i < vertices.size(); ++i) {
// 		v.push_back(vertices[i].getPosition().x);
// 		v.push_back(vertices[i].getPosition().y);
// 		v.push_back(vertices[i].getPosition().z);
// 		v.push_back(vertices[i].getTexCoord().x);
// 		v.push_back(vertices[i].getTexCoord().y);
// 		v.push_back(vertices[i].getNormal().x);
// 		v.push_back(vertices[i].getNormal().y);
// 		v.push_back(vertices[i].getNormal().z);
// 	}

	m_data = new MeshData(indices.size());
	m_loadedMeshes[m_filePath] = m_data;

	glBindBuffer(GL_ARRAY_BUFFER, m_data->getVertexBufferID());
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->getIndicesBufferID());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &(indices[0]), GL_STATIC_DRAW);
}

void Mesh::calcNormals(std::vector<Vertex> &vertices, std::vector<int> &indices)
{
	for (Vertex vertex : vertices)
		vertex.setNormal(glm::vec3(0, 0, 0));

	for (int i = 0; i < indices.size(); i += 3) 
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		glm::vec3 v1 = vertices[i1].getPosition() - vertices[i0].getPosition();
		glm::vec3 v2 = vertices[i2].getPosition() - vertices[i0].getPosition();

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		vertices[i0].getNormal() += normal;
		vertices[i1].getNormal() += normal;
		vertices[i2].getNormal() += normal;
	}

	for (Vertex vertex : vertices)
		glm::normalize(vertex.getNormal());
}

// /* Tab character ("\t") counter */
// int numTabs = 0;
// 
// /**
// * Print the required number of tabs.
// */
// void PrintTabs() {
// 	for (int i = 0; i < numTabs; i++)
// 		printf("\t");
// }
// 
// /**
// * Return a string-based representation based on the attribute type.
// */
// FbxString GetAttributeTypeName(FbxNodeAttribute::EType type) {
// 	switch (type) {
// 	case FbxNodeAttribute::eUnknown: return "unidentified";
// 	case FbxNodeAttribute::eNull: return "null";
// 	case FbxNodeAttribute::eMarker: return "marker";
// 	case FbxNodeAttribute::eSkeleton: return "skeleton";
// 	case FbxNodeAttribute::eMesh: return "mesh";
// 	case FbxNodeAttribute::eNurbs: return "nurbs";
// 	case FbxNodeAttribute::ePatch: return "patch";
// 	case FbxNodeAttribute::eCamera: return "camera";
// 	case FbxNodeAttribute::eCameraStereo: return "stereo";
// 	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
// 	case FbxNodeAttribute::eLight: return "light";
// 	case FbxNodeAttribute::eOpticalReference: return "optical reference";
// 	case FbxNodeAttribute::eOpticalMarker: return "marker";
// 	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
// 	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
// 	case FbxNodeAttribute::eBoundary: return "boundary";
// 	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
// 	case FbxNodeAttribute::eShape: return "shape";
// 	case FbxNodeAttribute::eLODGroup: return "lodgroup";
// 	case FbxNodeAttribute::eSubDiv: return "subdiv";
// 	default: return "unknown";
// 	}
// }
// 
// /**
// * Print an attribute.
// */
// void PrintAttribute(FbxNodeAttribute* pAttribute) {
// 	if (!pAttribute) return;
// 
// 	FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
// 	FbxString attrName = pAttribute->GetName();
// 	PrintTabs();
// 	// Note: to retrieve the character array of a FbxString, use its Buffer() method.
// 	printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
// }
// 
// /**
// * Print a node, its attributes, and all its children recursively.
// */
// void PrintNode(FbxNode* pNode) {
// 	PrintTabs();
// 	const char* nodeName = pNode->GetName();
// 	FbxDouble3 translation = pNode->LclTranslation.Get();
// 	FbxDouble3 rotation = pNode->LclRotation.Get();
// 	FbxDouble3 scaling = pNode->LclScaling.Get();
// 
// 	// Print the contents of the node.
// 	printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
// 		nodeName,
// 		translation[0], translation[1], translation[2],
// 		rotation[0], rotation[1], rotation[2],
// 		scaling[0], scaling[1], scaling[2]
// 		);
// 	numTabs++;
// 
// 	// Print the node's attributes.
// 	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
// 		PrintAttribute(pNode->GetNodeAttributeByIndex(i));
// 
// 	// Recursively print the children.
// 	for (int j = 0; j < pNode->GetChildCount(); j++)
// 		PrintNode(pNode->GetChild(j));
// 
// 	numTabs--;
// 	PrintTabs();
// 	printf("</node>\n");
// }

void Mesh::loadMesh(std::string filePath)
{
// 	std::smatch m;
// 	if (!std::regex_match(filePath, m, std::regex(".*\\.([a-zA-Z0-9]+)")))
// 		Debug::fatalError("incorrect file path of mesh '" + filePath + "'!");

// 	std::string ext = std::tolower(m[1], std::locale());
// 	if (ext != "obj")
// 		Debug::fatalError("'" + ext + "' mesh format isn't supported!");

	// Change the following filename to a suitable filename value.
// 	const char* lFilename = "./res/models/barrels/metal_barrel.obj";
// 	const char* lFilename = "./res/models/NYPD_ford_mondeo/car.obj";
// 
// 	// Initialize the SDK manager. This object handles all our memory management.
// 	FbxManager* lSdkManager = FbxManager::Create();
// 
// 	// Create the IO settings object.
// 	FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
// 	lSdkManager->SetIOSettings(ios);
// 
// 	// Create an importer using the SDK manager.
// 	FbxImporter* lImporter = FbxImporter::Create(lSdkManager, "");
// 
// 	// Use the first argument as the filename for the importer.
// 	if (!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings())) {
// 		printf("Call to FbxImporter::Initialize() failed.\n");
// 		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
// 		exit(-1);
// 	}
// 
// 	// Create a new scene so that it can be populated by the imported file.
// 	FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
// 
// 	// Import the contents of the file into the scene.
// 	lImporter->Import(lScene);
// 
// 	// The file is imported; so get rid of the importer.
// 	lImporter->Destroy();
// 
// 	// Print the nodes of the scene and their attributes recursively.
// 	// Note that we are not printing the root node because it should
// 	// not contain any attributes.
// 	FbxNode* lRootNode = lScene->GetRootNode();
// 	if (lRootNode) {
// 		for (int i = 0; i < lRootNode->GetChildCount(); i++)
// 			PrintNode(lRootNode->GetChild(i));
// 	}
// 	// Destroy the SDK manager and all the other objects it was handling.
// 	lSdkManager->Destroy();

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(("./res/" + filePath).c_str(), 
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs);

	if (!scene)
	{
		Debug::fatalError("'" + filePath + "' : mesh loading failed!");
	}

	const aiMesh* model = scene->mMeshes[0];

	std::vector<Vertex> vertices;
// 	std::vector<glm::vec3> positions;
// 	std::vector<glm::vec2> texCoords;
// 	std::vector<glm::vec3> normals;
// 	std::vector<glm::vec3> tangents;
	std::vector<int> indices;

	const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < model->mNumVertices; i++)
	{
		const aiVector3D pos = model->mVertices[i];
		const aiVector3D normal = model->HasNormals() ? model->mNormals[i] : aiZeroVector;
		const aiVector3D texCoord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiZeroVector;
// 		const aiVector3D tangent = model->mTangents[i];

// 		positions.push_back(glm::vec3(pos.x, pos.y, pos.z));
// 		texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
// 		normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
// 		tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
		vertices.push_back(Vertex(glm::vec3(pos.x, pos.y, pos.z), glm::vec2(texCoord.x, texCoord.y), glm::vec3(normal.x, normal.y, normal.z)));
	}

	for (unsigned int i = 0; i < model->mNumFaces; i++)
	{
		const aiFace& face = model->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	setVertices(vertices, indices, !model->HasNormals());
}