﻿#include "PROJECTScene.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

using namespace::std;

PROJECTScene::PROJECTScene()
{
}

PROJECTScene::~PROJECTScene()
{
}

bool hideKnife = false;

void PROJECTScene::InitJunk()
{
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader" );
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");

	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	glUseProgram(m_programID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f, 1);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//Skybox//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f, 1);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Skybox//back.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f, 1);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Skybox//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f, 1);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Skybox//right.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f, 1);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Skybox//bottom.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f, 1);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//Skybox//top.tga");
}

void PROJECTScene::RicssonInit()
{
	Mesh* tempMesh;
	Mesh* cube;
	Vector3 hitBox;
	float size = 0;

	hitBox = player.collision.hitbox; player.collision.boundingBox =  MeshBuilder::GenerateCube("PlayerHitbox", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	
	tempMesh = MeshBuilder::GenerateOBJ("Shelf", "OBJ//shelf-2.obj"); tempMesh->textureID = LoadTGA("Image//shelf-blue.tga");
	hitBox = Vector3(8,6,3); cube = MeshBuilder::GenerateCube("ShelfHitbox", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	for (int x = -11; x <= 11; x+=11)
	{	
		for (int z = -30; z >= -54; z-=12)
		{
			object.push_back( new Object(Vector3(x,0,z), Vector3(0,hitBox.y/2,0), hitBox, tempMesh, cube));
		}
	}

	tempMesh = MeshBuilder::GenerateOBJ("Chocolate", "OBJ//Food//chocolate.obj"); tempMesh->textureID = LoadTGA("Image//Food//chocolate.tga");
	hitBox = Vector3(1.5f, 0.25f, 1.5f); cube = MeshBuilder::GenerateCube("Chocolate", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	for (int y = 0; y <= 10; y++)
	{
		object.push_back( new Item(Vector3(0,y,-20), Vector3(0,hitBox.y/2,0), hitBox, tempMesh, cube, 1, 0, true) );
	}

	tempMesh = MeshBuilder::GenerateOBJ("Cigarettes", "OBJ//Food//marlbororeds.obj"); tempMesh->textureID = LoadTGA("Image//Food//marlbororeds.tga");
	hitBox = Vector3(0.2f, 0.325f, 0.075f); cube = MeshBuilder::GenerateCube("Cigarettes", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	for (int y = 0; y <= 10; y++)
	{
		object.push_back( new Item(Vector3(3,y,-20), Vector3(0,hitBox.y/2,0), hitBox, tempMesh, cube, 1, 0, true) );
	}

	tempMesh = MeshBuilder::GenerateOBJ("Cereal Box", "OBJ//Food//cerealbox.obj"); tempMesh->textureID = LoadTGA("Image//Food//cerealbox.tga");
	hitBox = Vector3(0.6f, 0.8f, 0.6f); cube = MeshBuilder::GenerateCube("CerealBoxHitbox", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	for (int y = 0; y <= 10; y++)
	{
		object.push_back( new Item(Vector3(-3,y,-20), Vector3(0,hitBox.y/2,0), hitBox, tempMesh, cube, 1, 0, true) );
	}

	tempMesh = MeshBuilder::GenerateQuad("", Color(1, 1, 1), 200.f, 84.875f, 30); tempMesh->textureID = LoadTGA("Image//floor.tga");
	hitBox = Vector3(200, 0.1f, 85); cube = MeshBuilder::GenerateCube("FloorHitbox", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	object.push_back( new Object(Vector3(0,0,-22.4375), Vector3(0,0,0), hitBox, tempMesh, cube) );
}

void PROJECTScene::JeremiahInit()
{
	Mesh* tempMesh;
	Mesh* cube;
	Vector3 hitBox;
	float size = 0;
}

void PROJECTScene::JessicaInit()
{
	Mesh* tempMesh;
	Mesh* cube;
	Vector3 hitBox;
	float size = 0;
}

void PROJECTScene::DarrenInit()
{
	Mesh* tempMesh;
	Mesh* cube;
	Vector3 hitBox;
	float size = 0;

	tempMesh = MeshBuilder::GenerateOBJ("Elevator Border", "OBJ//elevatorborder.obj"); tempMesh->textureID = LoadTGA("Image//silver.tga");
	hitBox = Vector3(1.75f, 40.25f, 3.5f); cube = MeshBuilder::GenerateCube("ElevatorBorderHitbox", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	object.push_back( new Object(Vector3(6,0,20), Vector3(0,20.125f,0), hitBox, tempMesh, cube) );
	object.push_back( new Object(Vector3(-6,0,20), Vector3(0,20.125f,0), hitBox, tempMesh, cube) );

	tempMesh = MeshBuilder::GenerateOBJ("Button", "OBJ//button.obj"); tempMesh->textureID = LoadTGA("Image//buttonOff.tga");
	hitBox = Vector3(1, 2.1f, 1.4f); cube = MeshBuilder::GenerateCube("ButtonHitbox", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	Object ButtonIn(Vector3(-10,4,-1), Vector3(0,1.05f,0), hitBox, tempMesh, cube, 1, 0, true);
	Object ButtonOut(Vector3(5.5,4,3), Vector3(0,1.05f,0), hitBox, tempMesh, cube, 1, 90, true);

	tempMesh = MeshBuilder::GenerateOBJ("Elevator Door", "OBJ//elevatordoor.obj"); tempMesh->textureID = LoadTGA("Image//elevatordoor.tga");
	hitBox = Vector3(6.7,18,1.2f); cube = MeshBuilder::GenerateCube("ElevatorHitbox", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	Object Door(Vector3(0,0,0), Vector3(0,9,0), hitBox, tempMesh, cube);
	doorway.Init(Vector3(0,0,20), Door, ButtonIn, ButtonOut);
	object.push_back( &doorway.Door[0] );
	object.push_back( &doorway.Door[1] );
	object.push_back( &doorway.Button[0] );
	object.push_back( &doorway.Button[1] );

	tempMesh = MeshBuilder::GenerateOBJ("elevator", "OBJ//elevatorright.obj"); tempMesh->textureID = LoadTGA("Image//white.tga");
	hitBox = Vector3(1, 9, 11); cube = MeshBuilder::GenerateCube("Elevator", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	object.push_back( new Object(Vector3(-13,0,25), Vector3(6.5,4.5f,-0.55f), hitBox, tempMesh, cube) );

	tempMesh = MeshBuilder::GenerateOBJ("elevator", "OBJ//elevatorleft.obj"); tempMesh->textureID = LoadTGA("Image//white.tga");
	hitBox = Vector3(1, 9, 11); cube = MeshBuilder::GenerateCube("Elevator", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	object.push_back( new Object(Vector3(13,0,25), Vector3(-6.5,4.5f,-0.55f), hitBox, tempMesh, cube) );

	tempMesh = MeshBuilder::GenerateOBJ("elevator", "OBJ//elevatorbottom.obj"); tempMesh->textureID = LoadTGA("Image//white.tga");
	hitBox = Vector3(11, 1, 9); cube = MeshBuilder::GenerateCube("Elevator", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	object.push_back( new Object(Vector3(0,0,25), Vector3(0,0,0), hitBox, tempMesh, cube) );

	tempMesh = MeshBuilder::GenerateOBJ("elevator", "OBJ//elevatortop.obj"); tempMesh->textureID = LoadTGA("Image//white.tga");
	hitBox = Vector3(11, 1, 9); cube = MeshBuilder::GenerateCube("Elevator", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	object.push_back( new Object(Vector3(0,0,26), Vector3(0,9,0), hitBox, tempMesh, cube) );

	tempMesh = MeshBuilder::GenerateOBJ("elevator", "OBJ//elevatorback.obj"); tempMesh->textureID = LoadTGA("Image//white.tga");
	hitBox = Vector3(11, 9, 1); cube = MeshBuilder::GenerateCube("Elevator", Color(1,1,1), hitBox.x, hitBox.y, hitBox.z, 0);
	object.push_back( new Object(Vector3(0,0,34), Vector3(0,4,-5), hitBox, tempMesh, cube) );


}

void PROJECTScene::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	InitJunk();

	camera.Init(Vector3(85,12,-10), Vector3(80, 12, -10), Vector3(0, 1, 0));

	RicssonInit();
	JeremiahInit();
	JessicaInit();
	DarrenInit();

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("Cube", Color(1,1,1), 0.1f, 0.1f, 0.1f, 1);
	meshList[GEO_BIGCUBE] = MeshBuilder::GenerateCube("Cube", Color(1,1,1), 36.f, 36.f, 36.f, 1);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//font.tga");
	
	meshList[GEO_KNIFE] = MeshBuilder::GenerateOBJ("knife", "OBJ//arm2.obj");
	meshList[GEO_KNIFE]->textureID = LoadTGA("Image//arm.tga");

	meshList[GEO_LINE] = MeshBuilder::GenerateLine("crosshair", Color(0,1,0), 0.15f);

	Mtx44 projection;
	projection.SetToPerspective(60.f, 4.f / 3.f, 0.1f, 100000.f);
	projectionStack.LoadMatrix(projection);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0,50,0);
	light[0].power = 0.5f;

	light[1].type = Light::LIGHT_POINT;
	light[2].type = Light::LIGHT_POINT;
	light[2].kC = 0.05f;

	glUniform1i(m_parameters[U_NUMLIGHTS], 3);

	for (int i = 0; i < 3; i++)
	{
		glUniform3fv(m_parameters[U_LIGHT0_COLOR + 11*i], 1, &light[i].color.r);
		glUniform1f(m_parameters[U_LIGHT0_POWER + 11*i], light[i].power);
		glUniform1f(m_parameters[U_LIGHT0_KC + 11*i], light[i].kC);
		glUniform1f(m_parameters[U_LIGHT0_KL + 11*i], light[i].kL);
		glUniform1f(m_parameters[U_LIGHT0_KQ + 11*i], light[i].kQ);
		glUniform1i(m_parameters[U_LIGHT0_TYPE + 11*i], light[i].type);
		glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF + 11*i], light[i].cosCutoff);
		glUniform1f(m_parameters[U_LIGHT0_COSINNER + 11*i], light[i].cosInner);
		glUniform1f(m_parameters[U_LIGHT0_EXPONENT + 11*i], light[i].exponent);
	}

}

//static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

long double x;
std::string fps;

void PROJECTScene::Update(double dt)
{
	if(Application::IsKeyPressed('1'))
		hideKnife = false;
	if(Application::IsKeyPressed('2'))
		hideKnife = true;

	if(Application::IsKeyPressed('R'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	camera.lookAt = camera.lookingAt(object);
	
	if ((Application::IsKeyPressed('E')))
	{
		if (object[camera.lookAt]->type == "Item")
		{
			Vector3 tPos = object[camera.lookAt]->position; 
			tPos += object[camera.lookAt]->collision.centre;
			player.loot.push_back( new Loot(object[camera.lookAt]->mesh->name,tPos) );

			if (player.inventory.emptySlot() >= 0)
				player.inventory.Insert(object[camera.lookAt]);
			object.erase(object.begin()+camera.lookAt);
		}
		else if (object[camera.lookAt]->mesh->name == "Button")
		{
			doorway.open = true; doorway.close = false;
			doorway.Button[0].mesh = doorway.buttonStatus[1]; doorway.Button[1].mesh = doorway.buttonStatus[1];
			doorway.elapsedTime = 0;
		}

	}
	
	if ((player.checkCollision(&doorway.Door[0]) || player.checkCollision(&doorway.Door[1])) && doorway.close == false)
	{
		doorway.open = true; doorway.close = false;
		doorway.Button[0].mesh = doorway.buttonStatus[1]; doorway.Button[1].mesh = doorway.buttonStatus[1];
		doorway.elapsedTime = 0;
	}

	player.Update(dt, object);
	camera.Update(dt, &player, object);
	doorway.Update(dt);

	Vector3 view = (camera.target - camera.position).Normalized(); view/=10;
	Vector3 intersectionPoint;

	for (unsigned int i = 0; i < object.size(); i++)
	{
		int reach = 0;

		if (object[i]->mesh->name == "Garfield")
		{
			for (Vector3 p = camera.position; reach <= 180; p += view)
			{
				Object o(p, Vector3(0,0,0), Vector3(0.1f,0.1f,0.1f));
				if ( PROJECTScene::checkCollision(object[i], &o) )
				{
					intersectionPoint = o.position;
					break;
				}
				reach++;
			}
		}
	}
	if (player.value[player.knifeStrike] == 1 && intersectionPoint != Vector3(0,0,0))
	{
		int r = rand() % 30 + 10;
		for (int i = 0; i < r; i++)
		{
			blood.push_back(new Particles(intersectionPoint));
		}
	}

	for (unsigned int i = 0; i < blood.size(); i++)
	{
		blood[i]->Update(dt);
		if (blood[i]->elapsedTime > 0.5f)
		{
			delete blood[i];
			blood.erase(blood.begin() + i);
		}
	}

	fps = '\0';
	x = 1/dt;
	fps += "FPS: ";
	fps += to_string(x);
}

void PROJECTScene::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	modelStack.LoadIdentity();
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y,
	camera.position.z, camera.target.x, camera.target.y,
	camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	Mtx44 projection;
	projection.SetToPerspective(60.f, 4.f / 3.f, 0.1f, 100000.f);
	projectionStack.LoadMatrix(projection);
	
	for (int i = 0; i < 3; i++)
	{
		if(light[i].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(light[i].position.x, light[i].position.y, light[i].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + i*11], 1, &lightDirection_cameraspace.x);
		}
		else if(light[i].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[i].position;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + i*11], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * light[i].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION + i*11], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * light[i].position;
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + i*11], 1, &lightPosition_cameraspace.x);
		}
	}

	if(Application::IsKeyPressed('T'))
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.target);
		RenderMesh(meshList[GEO_AXES], false);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(camera.position);
	modelStack.Scale(500);
	RenderSkybox();
	modelStack.PopMatrix();

	for (unsigned int i = 0; i < object.size(); i++)
	{
		if (object[i]->mesh != NULL)
		{
			modelStack.PushMatrix();
			modelStack.Translate(object[i]->position);

			modelStack.Translate(object[i]->collision.centre);
			modelStack.Rotate(object[i]->orientation, 0, 1, 0); 
			modelStack.Translate(-object[i]->collision.centre);

			RenderMesh(object[i]->mesh, true);
			modelStack.PopMatrix();
		}
	}

	for (unsigned int i = 0; i < blood.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(blood[i]->position);
		modelStack.Rotate(camera.orientation, 0, 1, 0); 
		modelStack.Rotate(-camera.look, 1, 0, 0); 
		modelStack.Rotate(90, 1, 0, 0); 
		RenderMesh(blood[i]->mesh, false);
		modelStack.PopMatrix();
	}
	
	if(Application::IsKeyPressed('Q'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

		for (unsigned int i = 0; i < object.size(); i++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(object[i]->position);
			modelStack.Translate(object[i]->collision.centre);
			RenderMesh(object[i]->collision.boundingBox, false);
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix();
		modelStack.Translate(player.position);
		modelStack.Translate(player.collision.centre);
		RenderMesh(player.collision.boundingBox, false);
		modelStack.PopMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y,
	light[0].position.z);
	//RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	for (unsigned int i = 0; i < player.loot.size(); i++)
	{
		std::string text = "+1 "; text += player.loot[i]->name;

		modelStack.PushMatrix();
		modelStack.Translate(player.loot[i]->textPos);
		modelStack.Rotate(camera.orientation, 0,1,0);
		modelStack.Rotate(-camera.look,1,0,0);
		modelStack.Rotate(180, 0,1,0);
		float textLength = float(text.size());
		modelStack.Translate(-textLength/2, 0, 0);
		RenderText(meshList[GEO_TEXT], text, Color(1, 1, 1));
		modelStack.PopMatrix();
	}
	//2D

	glDisable(GL_DEPTH_TEST);

	modelStack.PushMatrix();
	viewStack.PushMatrix();
	projectionStack.PushMatrix();

	modelStack.LoadIdentity();
	viewStack.LoadIdentity();
	projectionStack.Ortho(-10, 10, -10, 10, 0, 10);
	
	modelStack.PushMatrix();
	modelStack.Translate(1 + player.value[player.bobbing],-1,-10);
	modelStack.Scale(1,1,1);
	RenderMesh(meshList[GEO_KNIFE], true);
	modelStack.PopMatrix();

	RenderCrosshair();

	projection.SetToOrtho(-16, 16, -12, 12, -10, 10);
	projectionStack.LoadMatrix(projection);

	for (int i = 0; i < 9; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(player.inventory.slots[i].position);
		RenderMesh(player.inventory.slots[i].mesh, false);
		modelStack.PopMatrix();
		if (!player.inventory.slots[i].item.empty())
		{
			string stack = to_string(long double(player.inventory.slots[i].item.size()));
			modelStack.PushMatrix();
			modelStack.Translate(player.inventory.slots[i].position - Vector3(0,0.5f,0));
			modelStack.Rotate(0, 0,1,0);
			modelStack.Rotate(-5, 1,0,0);
			//modelStack.Scale(0.5f,0.5f,0.5f);
			RenderMesh(player.inventory.slots[i].item[0]->mesh, false);
			RenderText(meshList[GEO_TEXT], stack, Color(1, 1, 1));
			modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix();
	modelStack.Translate(player.inventory.selector->position);
	RenderMesh(player.inventory.selector->mesh, false);
	modelStack.PopMatrix();

	string x = to_string(long double(camera.position.x));
	string y = to_string(long double(camera.position.y));
	string z = to_string(long double(camera.position.z));

	modelStack.PushMatrix();
	modelStack.Translate(-15,11,0);
	RenderText(meshList[GEO_TEXT], x, Color(1, 1, 1));
	modelStack.Translate(0,-1,0);
	RenderText(meshList[GEO_TEXT], y, Color(1, 1, 1));
	modelStack.Translate(0,-1,0);
	RenderText(meshList[GEO_TEXT], z, Color(1, 1, 1));
	modelStack.Translate(-1,-1,0);
	RenderText(meshList[GEO_TEXT], fps, Color(1, 1, 1));
	modelStack.PopMatrix();
	
	if (object[camera.lookAt]->ignoreCollision)
	{
		string tooltip;
		if (object[camera.lookAt]->mesh->name == "Button")
			tooltip += "'E' to push ";
		else
			tooltip += "'E' to loot ";
		tooltip += object[camera.lookAt]->mesh->name;

		modelStack.PushMatrix();
		modelStack.Translate(-7,-5,0);
		modelStack.Scale(0.75f,1,0.75f);
		RenderText(meshList[GEO_TEXT],tooltip , Color(1, 1, 1));
		modelStack.PopMatrix();
	}

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void PROJECTScene::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() *
		modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
		&MVP.a[0]);
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1,GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1,&mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once 
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


}
void PROJECTScene::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
}
void PROJECTScene::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void PROJECTScene::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0,0,-0.499f);
	modelStack.Rotate(180,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,0, 0.499f);
	modelStack.Rotate(-90,1,0,0);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.499f,0,0);
	modelStack.Rotate(180,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Rotate(90,0,0,1);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.499f,0,0);
	modelStack.Rotate(180,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Rotate(-90,0,0,1);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,0.499f,0);
	modelStack.Rotate(180,1,0,0);
	modelStack.Rotate(-90,0,1,0);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,-0.499f,0);
	modelStack.Rotate(90,0,1,0);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}
void PROJECTScene::RenderCrosshair()
{
	modelStack.PushMatrix();
	modelStack.Translate(0,0.13f,0);
	modelStack.Rotate(90,1,0,0);
	RenderMesh(meshList[GEO_LINE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0,-0.13f,0);
	modelStack.Rotate(90,1,0,0);
	RenderMesh(meshList[GEO_LINE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.13f,0,0);
	modelStack.Rotate(90,0,0,1);
	modelStack.Rotate(90,1,0,0);
	RenderMesh(meshList[GEO_LINE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.13f,0,0);
	modelStack.Rotate(90,0,0,1);
	modelStack.Rotate(90,1,0,0);
	RenderMesh(meshList[GEO_LINE], false);
	modelStack.PopMatrix();
}

void Object::Update(double dt)
{
}
void Doorway::Update(double dt)
{
	if (open == true)
	{
		elapsedTime += float(dt);

		if (elapsedTime > 3.f)
		{
			open = false;
			Button[0].mesh = buttonStatus[0]; Button[1].mesh = buttonStatus[0];
			elapsedTime = 0;
		}
		
		Door[0].position.x -= float(10.f * dt);
		Door[1].position.x += float(10.f * dt);

		if(Door[0].position.x <= doorPosition[0].x - Door[0].collision.hitbox.x)
			Door[0].position.x = doorPosition[0].x - Door[0].collision.hitbox.x;
		if(Door[1].position.x >= doorPosition[1].x + Door[1].collision.hitbox.x)
			Door[1].position.x = doorPosition[1].x + Door[1].collision.hitbox.x;
	}

	else
	{
		Door[0].position.x += float(10.f * dt);
		Door[1].position.x -= float(10.f * dt);

		if (Door[0].position.x >= doorPosition[0].x)
		{
			Door[0].position.x = doorPosition[0].x; close = true;
		}
		if (Door[1].position.x <= doorPosition[1].x)
		{
			Door[1].position.x = doorPosition[1].x; close = true;
		}
	}
}
void Particles::Update(double dt)
{
	position += direction * float(dt);
	elapsedTime += float(dt);
}

bool PROJECTScene::checkCollision(Object* a, Object* b)
{
	Vector3 CubeA = a->collision.hitbox/2; CubeA += a->collision.centre; 
	Vector3 CubeB = b->collision.hitbox/2; CubeB += b->collision.centre;

	Vector3 maxCubeA = CubeA ; maxCubeA += a->position;
	Vector3 minCubeA = CubeA - a->collision.hitbox; minCubeA += a->position;

	Vector3 maxCubeB = CubeB; maxCubeB += b->position;
	Vector3 minCubeB = CubeB - b->collision.hitbox; minCubeB += b->position;

	return(maxCubeA.x > minCubeB.x && 
    minCubeA.x < maxCubeB.x &&
    maxCubeA.y > minCubeB.y &&
    minCubeA.y < maxCubeB.y &&
    maxCubeA.z > minCubeB.z &&
    minCubeA.z < maxCubeB.z);
} 