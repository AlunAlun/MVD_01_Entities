#include "GraphicsSystem.h"
#include "Game.h"
#include "extern.h"

//destructor
GraphicsSystem::~GraphicsSystem() {
	//delete shader pointers
	for (auto shader_pair : shaders_) {
		if (shader_pair.second)
			delete shader_pair.second;
	}
}


void GraphicsSystem::init() {
	//TODO: 
	// - initialise state of openGL
	// - create camera variable in .h and initialise camera here

}

void GraphicsSystem::update(float dt) {
	
	//TODO:
	// - clear buffers
	// - set shader program
	// render all mesh components in ECS
	// suggest you abstract drawing code to renderMeshComponent function




}

//renders a given mesh component
void GraphicsSystem::renderMeshComponent_(Mesh& comp) {
	//TODO:
	// - drawing code for a single mesh component


}



//********************************************
// OpenGL helper functions
//********************************************

//loads a shader and returns its program id
int GraphicsSystem::loadShader(std::string name, std::string vs_path, std::string fs_path) {
	shaders_[name] = new Shader(vs_path, fs_path);
	return shaders_[name]->program;
}

//returns a shader program id
int GraphicsSystem::getShaderProgram(std::string name) {
	return shaders_[name]->program;
}

//creates a standard plane geometry
void GraphicsSystem::createPlaneGeometry(GLuint& vao, GLuint& num_tris) {

	const GLfloat position_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	const GLfloat texture_buffer_data[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	const GLfloat normal_buffer_data[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	const GLuint index_buffer_data[] = { 0, 1, 2,0, 2, 3 };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	//positions
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position_buffer_data), position_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//texture coords
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_buffer_data), texture_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//normals								   
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normal_buffer_data), normal_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//indices
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	num_tris = 2;
}
