#include "TestScene.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "components/DirectionalLight.h"
#include "components/PointLight.h"
#include "components/SpotLight.h"
#include "components/MeshRenderer.h"
#include "components/PerspectiveCamera.h"
#include "rendering/Vertex.h"
#include "rendering/Mesh.h"
#include "rendering/Material.h"
#include "rendering/Texture.h"
#include "core/Node.h"
#include "core/Transform.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::init() 
{
	//meshes
	float fieldDepth = 8.0f;
	float fieldWidth = 8.0f;

	std::vector<Vertex> vertices({ Vertex(glm::vec3(-fieldWidth, 0.0f, -fieldDepth), glm::vec2(0.0f, 0.0f)),
								   Vertex(glm::vec3(-fieldWidth, 0.0f, fieldDepth), glm::vec2(0.0f, 1.0f)),
								   Vertex(glm::vec3(fieldWidth, 0.0f, -fieldDepth), glm::vec2(1.0f, 0.0f)),
								   Vertex(glm::vec3(fieldWidth, 0.0f, fieldDepth), glm::vec2(1.0f, 1.0f)) });
	std::vector<int> indices({ 0, 1, 2,
							   2, 1, 3 });
	Mesh* planeMesh = new Mesh(vertices, indices, true);

	Material* material1 = new Material;
	material1->addTexture("diffuse", new Texture("models/barrels/diffuse_rust.jpg"));
	material1->addFloat("specularIntensity", 4.f);
	material1->addFloat("specularPower", 4);

	Material* material2 = new Material();
	material2->addTexture("diffuse", new Texture("models/test/test.png"));
	material2->addFloat("specularIntensity", 1.f);
	material2->addFloat("specularPower", 4);

	Node* planeNode = new Node();
	planeNode->addComponent(new MeshRenderer(planeMesh, material2));
	getRoot()->addChild(planeNode);

	Node* object1 = new Node();
	object1->addComponent(new MeshRenderer(new Mesh("models/barrels/metal_barrel.obj"), material1));
// 	object1->addComponent(new MeshRenderer(new Mesh("models/test/angel.obj"), material1));
// 	object1->addComponent(new MeshRenderer(new Mesh("models/test/mustang_gt500.obj"), material1));
	object1->getTransform()->setScale(0.03f, 0.03f, 0.03f);
	object1->getTransform()->setPosition(0, 0, 2);
	getRoot()->addChild(object1);

// 	S::NewSceneComponent("jhj")->
// 		S::Get<SceneComponent>("sdfsd")->GetTransform()->SetPOos()->SetScale
	Node* test1 = (new Node)->addComponent(new MeshRenderer(planeMesh, material2));
	Node* test2 = (new Node)->addComponent(new MeshRenderer(planeMesh, material2));
	Node* test3 = (new Node)->addComponent(new MeshRenderer(planeMesh, material2));

	test1->getTransform()->setScale(0.1f, 0.1f, 0.1f)->setPosition(0, 3, 0)->setRotation(glm::quat(glm::vec3(0, glm::radians(45.), 0)));
	test2->getTransform()->setPosition(50, 0, 0)->setRotation(glm::quat(glm::vec3(glm::radians(20.), 0, 0)));
	test3->getTransform()->setPosition(0, 0, 10)->setRotation(glm::quat(glm::vec3(glm::radians(25.), 0, 0)));

	test1->addChild(test2->addChild(test3));
	getRoot()->addChild(test1);

	//lights
	DirectionalLight* m_directionalLight = new DirectionalLight(glm::vec3(1, 1, 1), 0.4f);
	std::vector<PointLight*> m_pointLights({ new PointLight(glm::vec3(1, 1, 0), 3.0f, new Attenuation(0, 0, 1)),
											 new PointLight(glm::vec3(0, 1, 1), 3.0f, new Attenuation(0, 0, 1)) });
	std::vector<SpotLight*> m_spotLights({ new SpotLight(glm::vec3(1, 1, 1), 2.0f, new Attenuation(0.5f, 0.15f, 0), cos(glm::radians(15.))),
										   new SpotLight(glm::vec3(1, 1, 1), 2.0f, new Attenuation(0.5f, 0.15f, 0), cos(glm::radians(15.))) });

	std::vector<Node*> pointLightObjects;
	std::vector<Node*> spotLightObjects;
	Node* directionalLightObject = new Node();

	Material* whiteMaterial = new Material();
	whiteMaterial->addTexture("diffuse", new Texture("models/test/white.png"));

	directionalLightObject->addComponent(m_directionalLight);
	pointLightObjects.push_back((new Node())->addComponent(m_pointLights[0])/*->addComponent(new MeshRenderer(new Mesh("models/test/cube.obj"), whiteMaterial))*/);
	pointLightObjects.push_back((new Node())->addComponent(m_pointLights[1])/*->addComponent(new MeshRenderer(new Mesh("models/test/cube.obj"), whiteMaterial))*/);
	spotLightObjects.push_back((new Node())->addComponent(m_spotLights[0])/*->addComponent(new MeshRenderer(new Mesh("models/test/cube.obj"), whiteMaterial))*/);
	spotLightObjects.push_back((new Node())->addComponent(m_spotLights[1])/*->addComponent(new MeshRenderer(new Mesh("models/test/cube.obj"), whiteMaterial))*/);

	pointLightObjects[0]->getTransform()->setPosition(glm::vec3(0.0f, 2.0f, -3.0f))->setScale(0.1, 0.1, 0.1);
	pointLightObjects[1]->getTransform()->setPosition(glm::vec3(3.0f, 2.0f, 0.0f))->setScale(0.1, 0.1, 0.1);
	spotLightObjects[0]->getTransform()->setPosition(glm::vec3(0, 3, -2))->setRotation(glm::angleAxis(glm::radians(-150.f), glm::vec3(1, 0, 0)))->setScale(0.1, 0.1, 0.1);
	spotLightObjects[1]->getTransform()->setPosition(glm::vec3(4, 3, -4))->setRotation(glm::angleAxis(glm::radians(-120.f), glm::vec3(1, 0, 0)))->setScale(0.1, 0.1, 0.1);
	directionalLightObject->getTransform()->setRotation(glm::quat(glm::vec3(glm::radians(-45.), 0, 0)))->setScale(0.1, 0.1, 0.1);

	getRoot()->addChildren(pointLightObjects);
	getRoot()->addChildren(spotLightObjects);
// 	getRoot()->addChild(directionalLightObject);

	//camera
	Node* cameraObject = new Node();
// 	getRoot()->addChild(cameraObject);
// 	test3.addChild(cameraObject);
// 	cameraObject.addChild(test1);

	cameraObject->getTransform()->setPosition(glm::vec3(5, 5, 5))
							    ->setRotation(glm::quat(glm::vec3(glm::radians(-45.), 0, 0)));
	cameraObject->addComponent(new PerspectiveCamera(glm::radians(60.), 800. / 600., 0.1f, 100.0f));
	getRoot()->addChild(cameraObject);
// 	test3->addChild(cameraObject);
	// 	cameraObject.addComponent(new PerspectiveCamera((float)Math.toRadians(60), Window.getWidth() / (float)Window.getHeight(), 0.1f, 100.0f));
// //        cameraObject.addComponent(new OrthographicCamera(-10, 10, -10, 10, -100, 100));
// //        cameraObject
// // .removeComponent(OrthographicCamera.class);
}

// private int k = 0;
// 
// @Override
// public void input(float time) {
// 	m_root.input(time);
// 
// 	if (Input.getKeyDown(Input.KEY_C))
// 		k = (k + 1) % m_pointLights.length;
// 
// 	if (Input.getKey(Input.KEY_UP))
// 		m_pointLights[k].getTransform().getPosition().add(new Vector3f(0, 0, -time * 3.0f));
// 	if (Input.getKey(Input.KEY_DOWN))
// 		m_pointLights[k].getTransform().getPosition().add(new Vector3f(0, 0, time * 3.0f));
// 	if (Input.getKey(Input.KEY_LEFT))
// 		m_pointLights[k].getTransform().getPosition().add(new Vector3f(-time * 3.0f, 0, 0));
// 	if (Input.getKey(Input.KEY_RIGHT))
// 		m_pointLights[k].getTransform().getPosition().add(new Vector3f(time * 3.0f, 0, 0));
// 	if (Input.getKey(Input.KEY_SPACE))
// 		m_pointLights[k].getTransform().getPosition().add(new Vector3f(0, time * 3.0f, 0));
// 	if (Input.getKey(Input.KEY_LSHIFT))
// 		m_pointLights[k].getTransform().getPosition().add(new Vector3f(0, -time * 3.0f, 0));
// 	if (Input.getKey(Input.KEY_ADD))
// 		m_pointLights[k].setIntensity(m_pointLights[k].getIntensity() + time * 3.0f);
// 	if (Input.getKey(Input.KEY_SUBTRACT))
// 		m_pointLights[k].setIntensity(m_pointLights[k].getIntensity() - time * 3.0f);
// }
