#include <string>

class Shader {
	private:
		unsigned int m_RendererID;
		unsigned int vertShaderID;
		unsigned int fragShaderID;

		std::string ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, 
				const std::string& fragmentShader);
	public:
		Shader(const std::string& vertSLPath, const std::string& fragSLPath);
		~Shader();

		void Bind() const;
		void Unbind() const;
};
