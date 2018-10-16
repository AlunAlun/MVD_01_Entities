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

	//four vertices in a square
	const GLfloat position_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	//texture coordinates (uvs)
	const GLfloat texture_buffer_data[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	//normals point 'out of screen'
	const GLfloat normal_buffer_data[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};
	//index buffer
	const GLuint index_buffer_data[] = { 0, 1, 2, 0, 2, 3 };

	//set number of triangles (of passed variable)
	num_tris = 2;

	//create Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Now create Vertex Buffer Objects for each buffer: positions, uvs, normals, and indices
	GLuint vbo;
	//positions
	glGenBuffers(1, &vbo); //create buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo); //set OpenGL state to say we want to work with this buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(position_buffer_data), position_buffer_data, GL_STATIC_DRAW); //copy data
	glEnableVertexAttribArray(0); //enable attribute labelled as '0' in vertex shader: "layout(location = 0) in vec3 a_vertex;"
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //each attribute '0' is composed of 3 floats (in this case, xyz)

	//texture coords
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_buffer_data), texture_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1); // (1 = a_uv)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); //only two coordinates for textures: uv
	//normals								   
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normal_buffer_data), normal_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2); // (2 = a_normal)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//indices
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}
