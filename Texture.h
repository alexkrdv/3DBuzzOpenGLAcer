#ifndef TEXTURE_H
#define TEXTURE_H


#include <windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

struct TGA_Header{

	GLubyte ID_Length;
	GLubyte ColorMapType;
	GLubyte ImageType;
	GLubyte ColorMapSpecification[5];
	GLshort xOrigin;
	GLshort yOrigin;
	GLshort ImageWidth;
	GLshort ImageHeight;
	GLubyte PixelDepth;

};

class Texture{

public:
	Texture(string filename, string name="");
	~Texture();

public:
	//raw image ptr
	unsigned char *imageData;
	//bits per pixel
	unsigned int bpp;
	unsigned int width;
	unsigned int height;
	unsigned int texID;

	string name;

	static vector<Texture*> textures;
private:
	bool loadTGA(string filename);
	bool createTexture(unsigned char *imageData, int width, int height, int type);
};
#endif