#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include "Light.h"
#include "Material.h"
#include "Mesh.h"
#include "Scene.h"
#include "Camera.h"
#include "Camera3.h"
#include "Utility.h"
#include "MatrixStack.h"
#include "LoadTGA.h"
#include "collision.h"
#include "player.h"

#include <vector>
#include <string>

class PROJECTScene : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_LIGHTBALL,
		GEO_QUAD,
		GEO_TEXT,
		GEO_KNIFE,
		GEO_LINE,
		GEO_CUBE,
		GEO_BIGCUBE,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_LIGHT0_POSITION, U_LIGHT0_COLOR, U_LIGHT0_POWER, U_LIGHT0_KC, U_LIGHT0_KL, U_LIGHT0_KQ,
		U_LIGHT0_TYPE, U_LIGHT0_SPOTDIRECTION, U_LIGHT0_COSCUTOFF, U_LIGHT0_COSINNER, U_LIGHT0_EXPONENT,
		U_LIGHT1_POSITION, U_LIGHT1_COLOR, U_LIGHT1_POWER, U_LIGHT1_KC, U_LIGHT1_KL, U_LIGHT1_KQ,
		U_LIGHT1_TYPE, U_LIGHT1_SPOTDIRECTION, U_LIGHT1_COSCUTOFF, U_LIGHT1_COSINNER, U_LIGHT1_EXPONENT,
		U_LIGHT2_POSITION, U_LIGHT2_COLOR, U_LIGHT2_POWER, U_LIGHT2_KC, U_LIGHT2_KL, U_LIGHT2_KQ,
		U_LIGHT2_TYPE, U_LIGHT2_SPOTDIRECTION, U_LIGHT2_COSCUTOFF, U_LIGHT2_COSINNER, U_LIGHT2_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	void RenderSkybox();
	void RenderCrosshair();
	void RenderFishtank();
	void RenderGarfield(Garfield garfield, float legR, float legT);

public:
	PROJECTScene();
	~PROJECTScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	static bool checkCollision(Camera3 a, Object* b);
	static bool checkCollision(Object* a, Object* b);

private:
	unsigned m_vertexArrayID;
	Mesh * meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	std::vector<Object*> object;
	std::vector<Particles*> blood;
	FishTank fishtank;
	Doorway doorway;
	Garfield garfield;
	Garfield realGarfield;
	Light light[3];
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	Camera3 camera;
	Player player;

	MS modelStack, viewStack, projectionStack;
};

#endif