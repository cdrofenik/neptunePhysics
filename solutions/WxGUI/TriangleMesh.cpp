#include "TriangleMesh.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <ctime>
#include <sstream>

void TriangleMesh::createWavefrontMesh(const char* filepath) {
	std::ifstream ifs(filepath, std::ifstream::in);
	std::string line, key;
	while (ifs.good() && !ifs.eof() && std::getline(ifs, line)) {
		key = "";
		std::stringstream stringstream(line);
		stringstream >> key >> std::ws;

		if (key == "v") { // vertex
			npVector3f v; float x;
			int idx = 0;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				switch (idx)
				{
				case 0: v.x = x; break;
				case 1: v.y = x; break;
				case 2: v.z = x; break;
				}
				idx++;
			}
			vertices.push_back(v);
		}
		else if (key == "vt") { // texture coordinate
			npPoint2f v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.pnts.push_back(x);
			}
			texcoords.push_back(v);
		}
		else if (key == "vn") { // normal
			npPoint3f v; float x;
			while (!stringstream.eof()) {
				stringstream >> x >> std::ws;
				v.pnts.push_back(x);
			}
			v.normalize();
			normals.push_back(v);
		}
		else if (key == "f") { // face
			face f; int v, t, n;
			while (!stringstream.eof()) {
				stringstream >> v >> std::ws;
				f.vertex.push_back(v - 1);
				if (stringstream.peek() == '/') {
					stringstream.get();
					if (stringstream.peek() == '/') {
						stringstream.get();
						stringstream >> n >> std::ws;
						f.normal.push_back(n - 1);
					}
					else {
						stringstream >> t >> std::ws;
						f.texture.push_back(t - 1);
						if (stringstream.peek() == '/') {
							stringstream.get();
							stringstream >> n >> std::ws;
							f.normal.push_back(n - 1);
						}
					}
				}
			}
			faces.push_back(f);
		}
		else {

		}
	}
	ifs.close();
	std::cout << "               Name: " << filepath << std::endl;
	std::cout << "           Vertices: " << std::to_string(vertices.size()) << std::endl;
	std::cout << "Texture Coordinates: " << std::to_string(texcoords.size()) << std::endl;
	std::cout << "            Normals: " << std::to_string(normals.size()) << std::endl;
	std::cout << "              Faces: " << std::to_string(faces.size()) << std::endl << std::endl;
	list = glGenLists(1);
	vertices.clear();
	texcoords.clear();
	normals.clear();
	faces.clear();
}

void TriangleMesh::render() {
	glNewList(list, GL_COMPILE);
	for (int i = 0; i < faces.size(); i++) {
		if (faces[i].vertex.size() == 3) { // triangle
			if (faces[i].normal.size() == 3) { // with normals
				glBegin(GL_TRIANGLES);
				glNormal3f(normals[faces[i].normal[0]].pnts[0], normals[faces[i].normal[0]].pnts[1], normals[faces[i].normal[0]].pnts[2]);
				glVertex3f(vertices[faces[i].vertex[0]].x, vertices[faces[i].vertex[0]].y, vertices[faces[i].vertex[0]].z);
				glNormal3f(normals[faces[i].normal[1]].pnts[0], normals[faces[i].normal[1]].pnts[1], normals[faces[i].normal[1]].pnts[2]);
				glVertex3f(vertices[faces[i].vertex[1]].x, vertices[faces[i].vertex[1]].y, vertices[faces[i].vertex[1]].z);
				glNormal3f(normals[faces[i].normal[2]].pnts[0], normals[faces[i].normal[2]].pnts[1], normals[faces[i].normal[2]].pnts[2]);
				glVertex3f(vertices[faces[i].vertex[2]].x, vertices[faces[i].vertex[2]].y, vertices[faces[i].vertex[2]].z);
				glEnd();
			}
			else { // without normals -- evaluate normal on triangle
				npVector3f v = (vertices[faces[i].vertex[1]] - vertices[faces[i].vertex[0]]).vectorProduct(vertices[faces[i].vertex[2]] - vertices[faces[i].vertex[0]]);
				v.normalize();
				glBegin(GL_TRIANGLES);
				glNormal3f(v.x, v.y, v.z);
				glVertex3f(vertices[faces[i].vertex[0]].x, vertices[faces[i].vertex[0]].y, vertices[faces[i].vertex[0]].z);
				glVertex3f(vertices[faces[i].vertex[1]].x, vertices[faces[i].vertex[1]].y, vertices[faces[i].vertex[1]].z);
				glVertex3f(vertices[faces[i].vertex[2]].x, vertices[faces[i].vertex[2]].y, vertices[faces[i].vertex[2]].z);
				glEnd();
			}
		}
		else if (faces[i].vertex.size() == 4) { // quad
			if (faces[i].normal.size() == 4) { // with normals
				glBegin(GL_QUADS);
				glNormal3f(normals[faces[i].normal[0]].pnts[0], normals[faces[i].normal[0]].pnts[1], normals[faces[i].normal[0]].pnts[2]);
				glVertex3f(vertices[faces[i].vertex[0]].x, vertices[faces[i].vertex[0]].y, vertices[faces[i].vertex[0]].z);
				glNormal3f(normals[faces[i].normal[1]].pnts[0], normals[faces[i].normal[1]].pnts[1], normals[faces[i].normal[1]].pnts[2]);
				glVertex3f(vertices[faces[i].vertex[1]].x, vertices[faces[i].vertex[1]].y, vertices[faces[i].vertex[1]].z);
				glNormal3f(normals[faces[i].normal[2]].pnts[0], normals[faces[i].normal[2]].pnts[1], normals[faces[i].normal[2]].pnts[2]);
				glVertex3f(vertices[faces[i].vertex[2]].x, vertices[faces[i].vertex[2]].y, vertices[faces[i].vertex[2]].z);
				glNormal3f(normals[faces[i].normal[3]].pnts[0], normals[faces[i].normal[3]].pnts[1], normals[faces[i].normal[3]].pnts[2]);
				glVertex3f(vertices[faces[i].vertex[3]].x, vertices[faces[i].vertex[3]].y, vertices[faces[i].vertex[3]].z);
				glEnd();
			}
			else { // without normals -- evaluate normal on quad
				npVector3f v = (vertices[faces[i].vertex[1]] - vertices[faces[i].vertex[0]]).vectorProduct(vertices[faces[i].vertex[2]] - vertices[faces[i].vertex[0]]);
				v.normalize();
				glBegin(GL_QUADS);
				glNormal3f(v.x, v.y, v.z);
				glVertex3f(vertices[faces[i].vertex[0]].x, vertices[faces[i].vertex[0]].y, vertices[faces[i].vertex[0]].z);
				glVertex3f(vertices[faces[i].vertex[1]].x, vertices[faces[i].vertex[1]].y, vertices[faces[i].vertex[1]].z);
				glVertex3f(vertices[faces[i].vertex[2]].x, vertices[faces[i].vertex[2]].y, vertices[faces[i].vertex[2]].z);
				glVertex3f(vertices[faces[i].vertex[3]].x, vertices[faces[i].vertex[3]].y, vertices[faces[i].vertex[3]].z);
				glEnd();
			}
		}
	}
	glEndList();
}