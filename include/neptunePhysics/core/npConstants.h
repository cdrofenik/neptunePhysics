#ifndef NEPTUNE_NPDISCRETEWORLD_H
#define NEPTUNE_NPDISCRETEWORLD_H

#include "math/npPrecision.hpp"

#include <math.h>
#include <vector>

namespace NeptunePhysics {

	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const npReal AABB_BUFFER_DATA[] = {
		-1.0f, -1.0f, -1.0f, // triangle 1 : begin
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f, -1.0f, // triangle 2 : begin
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f, // triangle 2 : end
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	npReal* GenerateSphere(npReal r, const int& lats, const int& longs) {
		int i, j;
		std::vector<npReal> sphere_data = std::vector<npReal>();
		for (i = 0; i <= lats; i++) {
			npReal lat0 = NP_PI * (-0.5 + (npReal)(i - 1) / lats);
			npReal z0 = sin(lat0);
			npReal zr0 = cos(lat0);

			npReal lat1 = NP_PI * (-0.5 + (npReal)i / lats);
			npReal z1 = sin(lat1);
			npReal zr1 = cos(lat1);

			for (j = 0; j <= longs; j++) {
				npReal lng = 2 * NP_PI * (npReal)(j - 1) / longs;
				npReal x = cos(lng);
				npReal y = sin(lng);

				sphere_data.push_back(x * zr0, y * zr0, z0);
				sphere_data.push_back(x * zr1, y * zr1, z1);
			}
		}
	}

	
}

#endif