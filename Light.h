#ifndef LIGHT_H
#define LIGHT_H

#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <vector>


enum LIGHT_TYPE{

	LIGHT_SPOT,
	LIGHT_POINT,
	LIGHT_DIRECTIONAL
};

using std::vector;
class Light{

public:

	static void Initialize(void);

	Light(LIGHT_TYPE lightType);
	~Light();

	void Visible(bool value = true);

	void setDiffuse(float r, float g, float b, float a);
	void setAmbient(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);

	void setLightType(LIGHT_TYPE lightType);
	void setPosition(float x,float y,float z);

	//set spotlight-specific member functions
	void setSpotDirection(float x,float y,float z);
	void setCutoff(float value);
	void setExponent(float value);

	void setAttenuation(float constant,float linear,float quadratic);

	int getLightNum(void);
	void updateLight(void);

	static int numLights;
	static vector<int> avialableLights;
	static vector<Light*> lights;

private:
	GLfloat	position[4];
	GLfloat	diffuse[4];
	GLfloat	ambient[4];
	GLfloat	specular[4];
	GLfloat	spotDirection[4];
	
	float cutoff;
	float exponent;

	bool visible;
	int lightType;

	int lightNum;
};

#endif