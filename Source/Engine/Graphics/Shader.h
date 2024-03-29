#pragma once

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace glm;

namespace Kyst {

class Shader {
 public:
  Shader(const string &vertexCode, const string &fragmentCode, const string &geometryCode = "", string include = "#include ");

  unsigned int GetId();

  void Use() const;
  void SetBool(const string &name, bool value) const;
  void SetInt(const string &name, int value) const;
  void SetFloat(const string &name, float value) const;
  void SetVec2(const string &name, const vec2 &value) const;
  void SetVec2(const string &name, float x, float y) const;
  void SetVec3(const string &name, const vec3 &value) const;
  void SetVec3(const string &name, float x, float y, float z) const;
  void SetVec4(const string &name, const vec4 &value) const;
  void SetVec4(const string &name, float x, float y, float z, float w);
  void SetMat2(const string &name, const mat2 &mat) const;
  void SetMat3(const string &name, const mat3 &mat) const;
  void SetMat4(const string &name, const mat4 &mat) const;

  static string Load(string path, string include = "#include");
  static unsigned int GenShader(const string &vertexCode, const string &fragmentCode, const string &geometryCode = "");

 private:
  static void CheckCompileErrors(unsigned int shader, string type);

  unsigned int id_;
};

}  // namespace Kyst
