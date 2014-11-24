#include "../common/npVector.hpp"
#include "ObjReader.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <ctime>

#define MAXLINELENGTH 256

#define FLOATTUPLEREGEX "%f %f %f\n"
#define FLOATDOUBLEREGEX "%f %f\n"
#define FACETOUBLEREGEX "f %d/%d/%d %d/%d/%d %d/%d/%d\n"
#define FACETOUBLEREGEXBARE " %d/%d/%d %d/%d/%d %d/%d/%d\n"
#define FACEDOUBLEREGEX "f %d//%d %d//%d %d//%d\n"
#define FACEDOUBLEREGEXBARE " %d//%d %d//%d %d//%d\n"
#define FACESINGLEREGEX "f %d %d %d \n"
#define FACESINGLEREGEXBARE " %d %d %d \n"

//! 
//!... Gets values vertex, texturecoordinates and normals from a line 
//!
static inline int getValuesFromLine(const int fTypeIdx, const bool firstTime, FILE * file,
	unsigned int vertexIndex[], unsigned int uvIndex[], unsigned int normalIndex[]) {

	int matches;

	switch (fTypeIdx) {
	case 9:
		matches = fscanf(file, firstTime ? FACETOUBLEREGEX : FACETOUBLEREGEXBARE, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
		break;
	case 6:
		uvIndex[0] = -1;
		uvIndex[1] = -1;
		uvIndex[2] = -1;
		matches = fscanf(file, firstTime ? FACEDOUBLEREGEX : FACEDOUBLEREGEXBARE, &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
		break;
	case 3:
		uvIndex[0] = -1;
		uvIndex[1] = -1;
		uvIndex[2] = -1;
		normalIndex[0] = -1;
		normalIndex[1] = -1;
		normalIndex[2] = -1;
		matches = fscanf(file, firstTime ? FACESINGLEREGEX : FACESINGLEREGEXBARE, &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
		break;
	}

	return matches;
}

//! 
//!... Sets the flag for how many integers are in a FACE line
//!
static inline void setRegexForFaceTypes(FILE * file, int& fTypeIdx, unsigned int vertexIndex[], unsigned int uvIndex[], unsigned int normalIndex[]) {

	char line[MAXLINELENGTH];
	auto tmpFile = file;
	fgets(line, sizeof line, tmpFile);

	std::string 
	int idx = 0;
	while (line[idx] != '\n') {
		if (line[idx] == '/') {
			if (line[idx + 1] == '/') {
				fTypeIdx = 6;
				return;
			}
			else {
				fTypeIdx = 9;
				return;
			}
		}
		idx++;
	}
 	
	//delete tmpFile;

	fTypeIdx = 3;
}


//! 
//!... Reads an .obj file as returns verticies, texture coordinates and normals from that file
//!
bool ObjReader::readObjFile(const char *filename,
							npObject& object)
{

	printf("Loading OBJ file:\n %s\n", filename);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<npVector3f> temp_vertices;
	std::vector<npPoint2f> temp_uvs;
	std::vector<npVector3f> temp_normals;

	FILE * file = fopen(filename, "r");
	if (file == NULL) {
		printf("Impossible to open the file! Are you in the right path ? \n");
		getchar();
		return false;
	}

	char lineHeader[MAXLINELENGTH]; // line buffer

	int faceTypeIdx = -1;

	clock_t begin = clock();
	while (1){

		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0){
			npVector3f vertex;
			fscanf(file, FLOATTUPLEREGEX, &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			//we ignore texture points;
			//npPoint2f uv;
			//fscanf(file, FLOATDOUBLEREGEX, &uv.x, &uv.y);
			//uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			//temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			npVector3f normal;
			fscanf(file, FLOATTUPLEREGEX, &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){

			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches;

			if (faceTypeIdx <= 0) {
				setRegexForFaceTypes(file, faceTypeIdx);
				matches = getValuesFromLine(faceTypeIdx, true, file, vertexIndex, uvIndex, normalIndex);
			}
			else {
				matches = getValuesFromLine(faceTypeIdx, false, file, vertexIndex, uvIndex, normalIndex);
			}

			if (matches != faceTypeIdx){
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			//uvIndices.push_back(uvIndex[0]);
			//uvIndices.push_back(uvIndex[1]);
			//uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else{
			// Probably a comment, eat up the rest of the line
			char commentBuffer[1000];
			fgets(commentBuffer, 1000, file);
		}

	}

	//For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		//unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		npVector3f vertex = temp_vertices[vertexIndex - 1];
		//npPoint2f uv = temp_uvs[uvIndex - 1];
		npVector3f normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		object.vertices.push_back(vertex);
		//object.uvs.push_back(uv);
		object.normals.push_back(normal);

	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	printf("Time:\n %d\n", elapsed_secs);

	return true;
}