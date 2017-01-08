#pragma once
#include <memory>
#include <string>
#include <sstream>
#include <Combiner.h>
#include <Graphics/OpenGLContext/opengl_GLInfo.h>
#include <Graphics/CombinerProgram.h>

namespace glsl {

	class ShaderPart
	{
	public:
		void write(std::stringstream & shader)
		{
			shader << m_part;
		}

	protected:
		std::string m_part;
	};

	class CombinerProgramBuilder
	{
	public:
		CombinerProgramBuilder(const opengl::GLInfo & _version);
		~CombinerProgramBuilder();
		graphics::CombinerProgram * buildCombinerProgram(Combiner & _color, Combiner & _alpha, const CombinerKey & _key);

	private:
		int compileCombiner(const CombinerKey & _key, Combiner & _color, Combiner & _alpha, std::string & _strShader);

		typedef std::unique_ptr<ShaderPart> ShaderPartPtr;
		ShaderPartPtr m_blender1;
		ShaderPartPtr m_blender2;
		ShaderPartPtr m_legacyBlender;
		ShaderPartPtr m_clamp;
		ShaderPartPtr m_signExtendColorC;
		ShaderPartPtr m_signExtendAlphaC;
		ShaderPartPtr m_signExtendColorABD;
		ShaderPartPtr m_signExtendAlphaABD;
		ShaderPartPtr m_alphaTest;
		ShaderPartPtr m_callDither;

		ShaderPartPtr m_vertexHeader;
		ShaderPartPtr m_vertexRect;
		ShaderPartPtr m_vertexTexturedRect;
		ShaderPartPtr m_vertexTriangle;
		ShaderPartPtr m_vertexTexturedTriangle;

		ShaderPartPtr m_fragmentHeader;
		ShaderPartPtr m_fragmentGlobalVariablesTex;
		ShaderPartPtr m_fragmentGlobalVariablesNotex;
		ShaderPartPtr m_fragmentHeaderNoise;
		ShaderPartPtr m_fragmentHeaderWriteDepth;
		ShaderPartPtr m_fragmentHeaderCalcLight;
		ShaderPartPtr m_fragmentHeaderMipMap;
		ShaderPartPtr m_fragmentHeaderReadMSTex;
		ShaderPartPtr m_fragmentHeaderDither;
		ShaderPartPtr m_fragmentHeaderDepthCompare;
		ShaderPartPtr m_fragmentHeaderReadTex;
		ShaderPartPtr m_fragmentMain;
		ShaderPartPtr m_fragmentMain2Cycle;
		ShaderPartPtr m_fragmentBlendMux;
		ShaderPartPtr m_fragmentReadTex0;
		ShaderPartPtr m_fragmentReadTex1;
		ShaderPartPtr m_fragmentReadTexMipmap;
		ShaderPartPtr m_fragmentCallN64Depth;
		ShaderPartPtr m_fragmentRenderTarget;

		ShaderPartPtr m_shaderNoise;
		ShaderPartPtr m_shaderDither;
		ShaderPartPtr m_shaderWriteDepth;
		ShaderPartPtr m_shaderMipmap;
		ShaderPartPtr m_shaderCalcLight;
		ShaderPartPtr m_shaderReadtex;
		ShaderPartPtr m_shaderN64DepthCompare;
		ShaderPartPtr m_shaderN64DepthRender;

		GLuint  m_vertexShaderRect;
		GLuint  m_vertexShaderTriangle;
		GLuint  m_vertexShaderTexturedRect;
		GLuint  m_vertexShaderTexturedTriangle;
	};

}
