#include "Game.h"
#include "extern.h"
#include "Shader.h"
#include "Texture.h"

void Game::init() {

	//******** INITIALISATION CODE **********//
    
	//add shader
	temp_program = graphics_system_.loadShader("phong", "data/shaders/phong.vert", "data/shaders/phong.frag");
    
	//create a temporary texture as we don't have a material system yet
	temp_texture = graphics_system_.loadTexture("data/assets/test.tga");

	//create plane geometry for use with Mesh Component
	graphics_system_.createPlaneGeometry(temp_vao, temp_tris);

	//set 'background' colour of framebuffer
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	//temporary code to create a camera
	temp_camera = new Camera();
	temp_camera->lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	temp_camera->setPerspective(60.0f*DEG2RAD, 1, 0.01f, 100.0f);


	//******* CREATE ENTITIES AND ADD COMPONENTS *******//

	//TODO:
	// - init Graphics System (with camera and GL setup code
	// - create entity for plane
	// - fill in MeshComponent properties in Components.h
	// - create mesh component for plane - use function in ECS
	// - assign mesh component vao and num tris
	
}

//Entry point for game update code
void Game::update(float dt) {

	//TODO
	// - update graphics system
	// - move drawing code to graphics system


	//tell OpenGL which shader to use
	glUseProgram(temp_program);

	//model matrix
	lm::mat4 model_matrix;

	//normal matrix
	lm::mat4 normal_matrix = model_matrix;
	normal_matrix.inverse();
	normal_matrix.transpose();

	//Model view projection matrix
	lm::mat4 mvp_matrix = temp_camera->ViewProjection() * model_matrix;

	//ask shader for a reference to the uniforms 
	GLint u_mvp = glGetUniformLocation(temp_program, "u_mvp");
	GLint u_model = glGetUniformLocation(temp_program, "u_model");
	GLint u_normal_matrix = glGetUniformLocation(temp_program, "u_normal_matrix");
	GLint u_light_pos = glGetUniformLocation(temp_program, "u_light_pos");
	GLint u_cam_pos = glGetUniformLocation(temp_program, "u_cam_pos");
	GLint u_texture_diffuse = glGetUniformLocation(temp_program, "u_texture_diffuse");
	GLint u_glossiness = glGetUniformLocation(temp_program, "u_glossiness");

	//if the uniforms exist, send the data to the shader
	if (u_mvp != -1) glUniformMatrix4fv(u_mvp, 1, GL_FALSE, mvp_matrix.m);
	if (u_model != -1) glUniformMatrix4fv(u_model, 1, GL_FALSE, model_matrix.m);
	if (u_normal_matrix != -1) glUniformMatrix4fv(u_normal_matrix, 1, GL_FALSE, normal_matrix.m);
	if (u_light_pos != -1) glUniform3f(u_light_pos, 1000.0f, 0.0f, 1000.0f); //... 3f - is 3 floats
	if (u_cam_pos != -1) glUniform3fv(u_cam_pos, 1, temp_camera->eye().value_); // ...3fv - is array of 3 floats
	if (u_texture_diffuse != -1) glUniform1i(u_texture_diffuse, 0); // ...1i - is integer
	if (u_glossiness != -1) glUniform1f(u_glossiness, 80.0f); //...1f - for float

	//activate texture unit 0, and bind our texture there
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, temp_texture);

	//tell OpenGL we want to the the vao_ container with our buffers
	glBindVertexArray(temp_vao);

	//draw our geometry
	glDrawElements(GL_TRIANGLES, temp_tris * 3, GL_UNSIGNED_INT, 0);

	//tell OpenGL we don't want to use our container anymore
	glBindVertexArray(0);

	glUseProgram(0);

}

