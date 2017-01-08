#include <Log.h>
#include <Graphics/OpenGLContext/opengl_Attributes.h>
#include "glsl_Utils.h"

using namespace glsl;

void Utils::locateAttributes(GLuint _program, bool _rect, bool _textures)
{
	if (_rect) {
		glBindAttribLocation(_program, opengl::rectAttrib::position, "aRectPosition");
		glBindAttribLocation(_program, opengl::rectAttrib::color, "aRectColor");
		if (_textures) {
			glBindAttribLocation(_program, opengl::rectAttrib::texcoord0, "aTexCoord0");
			glBindAttribLocation(_program, opengl::rectAttrib::texcoord1, "aTexCoord1");
		}
		return;
	}

	glBindAttribLocation(_program, opengl::triangleAttrib::position, "aPosition");
	glBindAttribLocation(_program, opengl::triangleAttrib::color, "aColor");
	glBindAttribLocation(_program, opengl::triangleAttrib::numlights, "aNumLights");
	glBindAttribLocation(_program, opengl::triangleAttrib::modify, "aModify");
	if (_textures)
		glBindAttribLocation(_program, opengl::triangleAttrib::texcoord, "aTexCoord");
}


static const GLsizei nShaderLogSize = 1024;

bool Utils::checkShaderCompileStatus(GLuint obj)
{
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLchar shader_log[nShaderLogSize];
		GLsizei nLogSize = nShaderLogSize;
		glGetShaderInfoLog(obj, nShaderLogSize, &nLogSize, shader_log);
		shader_log[nLogSize] = 0;
		LOG(LOG_ERROR, "shader_compile error: %s\n", shader_log);
		return false;
	}
	return true;
}

bool Utils::checkProgramLinkStatus(GLuint obj)
{
	GLint status;
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLsizei nLogSize = nShaderLogSize;
		GLchar shader_log[nShaderLogSize];
		glGetProgramInfoLog(obj, nShaderLogSize, &nLogSize, shader_log);
		LOG(LOG_ERROR, "shader_link error: %s\n", shader_log);
		return false;
	}
	return true;
}

void Utils::logErrorShader(GLenum _shaderType, const std::string & _strShader)
{
	LOG(LOG_ERROR, "Error in %s shader", _shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment");

	const int max = 800;
	int pos = 0;

	while (pos < _strShader.length()) {

		if (_strShader.length() - pos < max) {
			LOG(LOG_ERROR, "%s", _strShader.substr(pos).data());
		}
		else {
			LOG(LOG_ERROR, "%s", _strShader.substr(pos, max).data());
		}
		pos += max;
	}
}
