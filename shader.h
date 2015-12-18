#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

using namespace std;

class Shader {

public:

	GLuint Program;

	Shader(const char* vertexPath, const char* fragmentPath) {

		const char* vertexCode;
		const char* fragmentCode;
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];

		if (!this->fileExists(vertexPath)) {
			printf("file %s does not exist\n", vertexPath);
		}
	
		if (!this->fileExists(vertexPath)) {
			printf("file %s does not exist\n", vertexPath);
		}
	
		vertexCode = this->getCodeFromFile(vertexPath);
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		
		fragmentCode = this->getCodeFromFile(fragmentPath);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		this->Program = glCreateProgram();	
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		printf("compiling shaders...\n");	
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			printf("No SUCCES on shader compile\n");
			printf("%s\n", infoLog);
		}	
		
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}


private:

	// functie die string uit file trekt 
	const char* getCodeFromFile(const char* filePath) {
		stringstream stream;
		string fileString;
		ifstream file;
		const char * code;

		file.open(filePath);
		stream << file.rdbuf();
		file.close();
		fileString = stream.str();
		code = fileString.c_str();
		return code;
	}

	bool fileExists(const char* filePath) {
		ifstream file(filePath);
		return file.good();
	}

	void checkCompileErrors(GLuint shader, string type) {
		GLchar infoLog[1024];
		GLint success;

		if (type != "PRGORAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				cout << "Error on " << type << endl << infoLog << endl;
			}
		}
	}
};
