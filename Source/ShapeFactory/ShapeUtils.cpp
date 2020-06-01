#include <vector>
#include <sstream>
#include <glm/gtc/random.hpp>

#include "ShapeUtils.h"

ShapeUtils::ShapeUtils()
{
}

void ShapeUtils::ProdPoint(vec3& point, float min, float max)
{
    vec3 delta(linearRand(min, max), linearRand(min, max), linearRand(min, max));
    point += delta;
}

void ShapeUtils::MovePoints(std::vector<vec3> &points, const vec3& offset)
{
    for (int i = 0; i < points.size(); ++i) {
        points[i] += offset;
    }
}

vec3 ShapeUtils::Hex2rgb(std::string hex) {
    using namespace std;
    ivec3 rgb;
    stringstream ss;
	string str;

	// Drop a hash if the value has one
	if (hex[0] == '#') {
		hex.erase(0,1);
	}

	int size = hex.size();

	for (int i = 0; i < 3; i++) {
		// Determine 3 or 6 character format.
		if (size == 3) { str = string(2, hex[i]); }
		else if (size == 6) { str = hex.substr(i * 2, 2); }
		else { break; }

		ss << std::hex << str;
		ss >> rgb[i];
		ss.clear();
	}

	return vec3(rgb) / 255.0f;
}
