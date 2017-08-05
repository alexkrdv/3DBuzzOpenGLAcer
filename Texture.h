#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef __WIN32__
 #include <Windows.h>
#endif
#include <GL/GL.h>
#include <GL/GLU.h>

#include <string>

using std::string;
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
	unsigned int texId;
};
#endif