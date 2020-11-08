#include "../Core.h"
#include "Shader.h"

// constructor generates the shader on the fly
// ------------------------------------------------------------------------
Shader::Shader(const string& vertexPath, const string& fragmentPath, const string& geometryPath, string include)
{
    string vertexCode = Load(vertexPath, include);
    string fragmentCode = Load(fragmentPath, include);
    string geometryCode; if (geometryPath != "") geometryCode = Load(geometryPath, include);
    
    id_ = GenShader(vertexCode, fragmentCode, geometryCode);
}
    
unsigned int Shader::GenShader(const string& vertexCode, const string& fragmentCode, const string& geometryCode)
{
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry;
    if(geometryCode != "")
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        CheckCompileErrors(geometry, "GEOMETRY");
    }
    // shader Program
    unsigned int id;
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    if(geometryCode != "")
        glAttachShader(id, geometry);
    glLinkProgram(id);
    CheckCompileErrors(id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryCode != "")
        glDeleteShader(geometry);

    return id;
}

// activate the shader
// ------------------------------------------------------------------------
void Shader::Use() const
{ 
    glUseProgram(id_);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::SetBool(const string& name, bool value) const
{         
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value); 
}
// ------------------------------------------------------------------------
void Shader::SetInt(const string& name, int value) const
{ 
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::SetFloat(const string& name, float value) const
{ 
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value); 
}
// ------------------------------------------------------------------------
void Shader::SetVec2(const string& name, const vec2& value) const
{ 
    glUniform2fv(glGetUniformLocation(id_, name.c_str()), 1,& value[0]); 
}
void Shader::SetVec2(const string& name, float x, float y) const
{ 
    glUniform2f(glGetUniformLocation(id_, name.c_str()), x, y); 
}
// ------------------------------------------------------------------------
void Shader::SetVec3(const string& name, const vec3& value) const
{ 
    glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
}
void Shader::SetVec3(const string& name, float x, float y, float z) const
{ 
    glUniform3f(glGetUniformLocation(id_, name.c_str()), x, y, z); 
}
// ------------------------------------------------------------------------
void Shader::SetVec4(const string& name, const vec4& value) const
{ 
    glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]); 
}
void Shader::SetVec4(const string& name, float x, float y, float z, float w) 
{ 
    glUniform4f(glGetUniformLocation(id_, name.c_str()), x, y, z, w); 
}
// ------------------------------------------------------------------------
void Shader::SetMat2(const string& name, const mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat3(const string& name, const mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::SetMat4(const string& name, const mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// utility function for loading shader file and processing shader #include directves
// ---------------------------------------------------------------------------------

string Shader::Load(string path, string include)
{
    static bool isRecursiveCall = false;

    string sourceCode = "";
    ifstream file(path);

    if (!file.is_open())
    {
        cerr << "ERROR: could not open the shader at: " << path << "\n" << endl;
        return sourceCode;
    }

    string lineBuffer;
    while (getline(file, lineBuffer))
    {
        // Look for the new shader include identifier
        if (lineBuffer.find(include) != lineBuffer.npos)
        {
            // Remove the include identifier, this will cause the path to remain
            lineBuffer.erase(0, include.size());

            // The include path is relative to the current shader file path
            lineBuffer.insert(0, path.substr(0, path.find_last_of("/\\") + 1));

            // By using recursion, the new include file can be extracted
            // and inserted at this location in the shader source code
            isRecursiveCall = true;
            sourceCode += Load(lineBuffer);
        } else
        {
            sourceCode += lineBuffer + '\n';
        }
    }

    // Only add the null terminator at the end of the complete file,
    // essentially skipping recursive function calls this way
    if (!isRecursiveCall) sourceCode += '\0';

    file.close();

    return sourceCode;
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::CheckCompileErrors(GLuint shader, string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
        }
    }
}
