#include <fstream>
#include <sstream>
#include <string>
namespace ryangl {
	static unsigned int CompileShader(unsigned int type, const std::string& source) {
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS,&result);
		if(result == GL_FALSE) {
			int length;
			glGetShaderiv(id,GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length*sizeof(char));
			glGetShaderInfoLog(id, length,&length,message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
			std::cout << message << std::endl;
			glDeleteProgram(id);
			return 0;
		}
		return id;
	}
	unsigned int CreateShader(const std::string file, const unsigned int &program) {
		std::ifstream stream(file);
		std::string fl;
		std::getline(stream,fl);
		unsigned int type;
		if(fl.compare("fragment")==0) {
			type = GL_FRAGMENT_SHADER;
		}
		if(fl.compare("vertex")==0) {
			type = GL_VERTEX_SHADER;
		}
		std::stringstream buff;
		buff << stream.rdbuf();
		unsigned int vs = CompileShader(type, buff.str());
		glAttachShader(program,vs);
		glLinkProgram(program);
		glValidateProgram(program);
		glDeleteProgram(vs);
		return program;
	}
	void clearErrors() {
		while(!glGetError());
	}
	void getErrors() {
		bool b = true;
		int i;
		while(b) {
			i=glGetError();
			if(i==0) {
				b = false;
			} else {
				std::cout << i << std::endl;
			}
		}
	}
	float randfloat() {
		return ((float)rand())/((float)RAND_MAX);
	}
	class object {
		private:
			unsigned int *vao;
			unsigned int vbo;
			unsigned int ibo;
			unsigned int shader;
			std::vector<float> positions;
			std::vector<unsigned int> indicies;
			std::vector<int> uniforms;
		public:
			object(std::vector<float> posin, std::vector<unsigned int> indin,int stride, std::vector<std::string> shad) {
        			shader = glCreateProgram();
				for(int i = 0; i<=shad.size()-1;i++) {
					shader = CreateShader(shad[i],shader);
				}
				for(int i = 0; i<=posin.size()-1;i++) {
					positions.push_back(posin[i]);
				}
				for(int i = 0; i<=indin.size()-1;i++) {
					indicies.push_back(indin[i]);
				}
				//std::cout << positions.size() << std::endl;
				//std::cout << indicies.size() << std::endl;
				vao = new unsigned int;
				glGenVertexArrays(1,vao);
        			glBindVertexArray(*vao);
				
				glGenBuffers(1,&vbo);
        			glBindBuffer(GL_ARRAY_BUFFER,vbo);
        			glBufferData(GL_ARRAY_BUFFER,positions.size()*sizeof(float),positions.data(),GL_DYNAMIC_DRAW);
        			glEnableVertexAttribArray(0);
        			glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,stride*sizeof(float),0);
				
				glGenBuffers(1,&ibo);
        			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        			glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicies.size()*sizeof(unsigned int),indicies.data(),GL_DYNAMIC_DRAW);
			}
			object(object copy, std::vector<unsigned int> indin, std::vector<std::string> shad) {
        			shader = glCreateProgram();
				for(int i = 0; i<=shad.size()-1;i++) {
					shader = CreateShader(shad[i],shader);
				}
				/*for(int i = 0; i<=posin.size()-1;i++) {
					positions.push_back(posin[i]);
				}*/
				for(int i = 0; i<=indin.size()-1;i++) {
					indicies.push_back(indin[i]);
				}
				//std::cout << positions.size() << std::endl;
				//std::cout << indicies.size() << std::endl;
				/*vao = new unsigned int;
				glGenVertexArrays(1,vao);
        			glBindVertexArray(*vao);
				
				glGenBuffers(1,&vbo);
        			glBindBuffer(GL_ARRAY_BUFFER,vbo);
        			glBufferData(GL_ARRAY_BUFFER,positions.size()*sizeof(float),positions.data(),GL_DYNAMIC_DRAW);
        			glEnableVertexAttribArray(0);
        			glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),0);
				*/
				vao = copy.getVao();
				glGenBuffers(1,&ibo);
        			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        			glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicies.size()*sizeof(unsigned int),indicies.data(),GL_DYNAMIC_DRAW);
			}
			int newUniform(std::string in) {
				uniforms.push_back(glGetUniformLocation(shader,in.c_str()));
				//std::cout << uniforms[uniforms.size()-1] << std::endl;
				return uniforms.size()-1;
			}
			void setUniform(int id, int a, int b, int c, int d) {
				glUniform4f(uniforms[id],a,b,c,d);
			}
			unsigned int *getVao() {
				return vao;
			}
			unsigned int getShader() {
				return shader;
			}
			void draw() {
				glUseProgram(shader);
				glBindVertexArray(*vao);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				glDrawElements(GL_TRIANGLES,indicies.size(),GL_UNSIGNED_INT,nullptr);
			}
	};
}
