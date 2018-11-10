#include "MyView.hpp"
#include <tygra/FileHelper.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>




MyView::MyView()
{
}

MyView::~MyView() {
}

/*
  * Tutorial: This function is where we prepare for using OpenGL and prepare
  *           for drawing.  Usually we will create OpenGL resources here.
  */
void MyView::windowViewWillStart(tygra::Window * window)
{
    /*
     * Not usually required, but done here to give us a time for the shaders
     */
    start_time_ = std::chrono::system_clock::now();

    /*
     * Tutorial: Shaders are loaded from a text file into a string which is
     *           passed to OpenGL for compiling.  Compile errors can be
     *           queried via the info log.
     */

    GLint compile_status = GL_FALSE;
    
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertex_shader_string
        = tygra::createStringFromFile("resource:///first_vs.glsl");
    const char * vertex_shader_code = vertex_shader_string.c_str();
    glShaderSource(vertex_shader, 1,
                   (const GLchar **) &vertex_shader_code, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        const int string_length = 1024;
        GLchar log[string_length]= "";
        glGetShaderInfoLog(vertex_shader, string_length, NULL, log);
        std::cerr << log << std::endl;
    }
 
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragment_shader_string
        = tygra::createStringFromFile("resource:///first_fs.glsl");
    const char * fragment_shader_code = fragment_shader_string.c_str();
    glShaderSource(fragment_shader, 1,
                   (const GLchar **) &fragment_shader_code, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status != GL_TRUE) {
        const int string_length = 1024;
        GLchar log[string_length]= "";
        glGetShaderInfoLog(fragment_shader, string_length, NULL, log);
        std::cerr << log << std::endl;
    }

    /*
     * Tutorial: A program object is made to host the shaders and their
     *           settings. This program object attempts to bind the shaders
     *           together when it is linked. If the shaders aren't compatible
     *           the link process will fail.
     */
    first_program_ = glCreateProgram();
    glAttachShader(first_program_, vertex_shader);
    glBindAttribLocation(first_program_, kVertexPosition, "vertex_position");
    glDeleteShader(vertex_shader);
	glBindAttribLocation(first_program_, kVertexColour, "vertex_colour");
	glDeleteShader(vertex_shader);
    glAttachShader(first_program_, fragment_shader);
    glBindFragDataLocation(first_program_, kFragmentColour, "fragment_colour");
    glDeleteShader(fragment_shader);
    glLinkProgram(first_program_);


    /*
     * Tutorial: Test if the shader program linked successfully. If not then
     *           get the error log and display in the console window.
     */
    GLint link_status = GL_FALSE;
    glGetProgramiv(first_program_, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        const int string_length = 1024;
        GLchar log[string_length]= "";
        glGetProgramInfoLog(first_program_, string_length, NULL, log);
        std::cerr << log << std::endl;
    }

    /*
     * Tutorial: Generate the geometry data (vertex and element data). Often
     *           this data will come from a data file. Don't just copy this!
     */

    std::vector<Vertex> vertices ;
	std::vector<Vertex> quad_vertices;

    std::vector<unsigned int> elements;
	std::vector<unsigned int> quad_elements;

    unsigned int triangle_count = 7;
    unsigned int vertex_count = 10;
	int r = 0, g = 0, b = 0;
	
	vertices.resize(vertex_count);
    for (unsigned int i=0; i< vertex_count; ++i) {

		if (i % 5 == 0)
		{
			r = 1;
			g = 1;
			b = 0;
		}
		else if (i % 5 == 1)
		{
			g = 1;
			b = 1;
			r = 0;
		}
		else if (i % 5 == 2)
		{
			b = 1;
			r = 1;
			g = 0;
		}
		else if (i % 5 == 3)
		{
			b = 1;
			r = 0;
			g = 1;
		}
		else if (i % 5 == 4)
		{
			b = 0;
			r = 1;
			g = 1;
		}


		if (i < 6)
		{
			const float radius = 0.5f;
			const float angle_radians = 6.283f * (float)i / 5.0f;
			vertices[i].position = glm::vec2(radius * cos(angle_radians), radius * sin(angle_radians));
		}
	

		vertices[i].colour = glm::vec3(r%2,g%3,b%4);
    }
	
	vertices[5].colour = glm::vec3(1.f, 0.f,0.0f);
	vertices[5].position = glm::vec2(0,0);

	const unsigned int element_count = triangle_count * 3;
	elements.resize(element_count);

	for (unsigned int i = 0; i < triangle_count; ++i) {

		
		elements[3 * i + 0] = 5;
		elements[3 * i + 1] = i;
		elements[3 * i + 2] = (i + 1) % 5;
		
		
		
	}


	triangle_count = 4;
	vertex_count = triangle_count + 1;
	quad_vertices.resize(vertex_count);
	
	quad_vertices[0].position = glm::vec2(0.4, 0.2);
	quad_vertices[0].colour = glm::vec3(1, 0, 0);
	quad_vertices[1].position = glm::vec2(0.7, 0.2);
	quad_vertices[1].colour = glm::vec3(0, 1, 0);
	quad_vertices[2].position = glm::vec2(0.4, 0.5);
	quad_vertices[2].colour = glm::vec3(0, 0, 1);
	quad_vertices[3].position = glm::vec2(0.7, 0.5);
	quad_vertices[3].colour = glm::vec3(1, 1, 1);

	const unsigned int quad_element_count = triangle_count * 3;
	quad_elements.resize(quad_element_count);
	quad_elements[0] = 0;
	quad_elements[1] = 1;
	quad_elements[2] = 2;
	quad_elements[3] = 2;
	quad_elements[4] = 3;
	quad_elements[5] = 1;
	

	//VBOs
	GenerateBuffer(1, mesh_.vertex_vbo, GL_ARRAY_BUFFER, vertices.data(), (GLsizeiptr)(vertices.size() * sizeof(Vertex)), GL_STATIC_DRAW);

	//IBO
	GenerateBuffer(1, mesh_.element_vbo, GL_ELEMENT_ARRAY_BUFFER, elements.data(), (GLbyte)(elements.size() * sizeof(unsigned int)), GL_STATIC_DRAW);
    mesh_.element_count = (int)elements.size();

	GenerateBuffer(1, mesh_.qaud_vbo, GL_ARRAY_BUFFER, quad_vertices.data(), (GLbyte)(quad_vertices.size() * sizeof(Vertex)), GL_STATIC_DRAW);

	//IBO
	GenerateBuffer(1, mesh_.quad_element_ibo, GL_ELEMENT_ARRAY_BUFFER, quad_elements.data(), (GLbyte)(quad_elements.size() * sizeof(unsigned int)), GL_STATIC_DRAW);
	mesh_.quad_element_count = (int)quad_elements.size();

	int stride = sizeof(glm::vec2) + sizeof(glm::vec3);

	int offsetPos = 0;
	int offsetColour = sizeof(glm::vec2);
	

    glGenVertexArrays(1, &mesh_.vao);
    glBindVertexArray(mesh_.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_.element_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, mesh_.vertex_vbo);
	glEnableVertexAttribArray(kVertexPosition);
	glVertexAttribPointer(kVertexPosition, 2, GL_FLOAT, GL_FALSE, stride , TGL_BUFFER_OFFSET(offsetPos));

	glBindBuffer(GL_ARRAY_BUFFER, mesh_.vertex_vbo);
	glEnableVertexAttribArray(kVertexColour);
	glVertexAttribPointer(kVertexColour, 3, GL_FLOAT, GL_FALSE, stride, TGL_BUFFER_OFFSET(offsetColour));

	glBindBuffer(GL_ARRAY_BUFFER, kNullId);
	glBindVertexArray(kNullId);

	glGenVertexArrays(1, &mesh_.quad_vao);
	glBindVertexArray(mesh_.quad_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_.quad_element_ibo);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_.qaud_vbo);
	glEnableVertexAttribArray(kVertexPosition);
	glVertexAttribPointer(kVertexPosition, 2, GL_FLOAT, GL_FALSE, stride, (const void *)offsetPos);

	glBindBuffer(GL_ARRAY_BUFFER, mesh_.qaud_vbo);
	glEnableVertexAttribArray(kVertexColour);
	glVertexAttribPointer(kVertexColour, 3, GL_FLOAT, GL_FALSE, stride, (const void *)offsetColour);

	
	glBindBuffer(GL_ARRAY_BUFFER, kNullId);
	glBindVertexArray(kNullId);

    /*
     * Tutorial: By default OpenGL assumes your pixel data is 4-byte aligned.
     *           Our data is not necessarily 4-byte aligned so we change it.
     */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /*
     * Tutorial: Create a texture object from pixel data read from an PNG.
     *           There is no image loading in OpenGL, so we use a helper.
     */
    tygra::Image texture_image = tygra::createImageFromPngFile("resource:///hex.png");

    if (texture_image.doesContainData()) {
        glGenTextures(1, &test_texture_);
        glBindTexture(GL_TEXTURE_2D, test_texture_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        GLenum pixel_formats[] = { 0, GL_RED, GL_RG, GL_RGB, GL_RGBA };
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     texture_image.width(),
                     texture_image.height(),
                     0,
                     pixel_formats[texture_image.componentsPerPixel()],
                     texture_image.bytesPerComponent() == 1
                        ? GL_UNSIGNED_BYTE : GL_UNSIGNED_SHORT,
                     texture_image.pixelData());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, kNullId);
    }
}

void MyView::windowViewDidReset(tygra::Window * window,
                                int width,
                                int height)
{
    /*
     * Tutorial: This is where we respond to the window resizing. At a minimum
     *           we tell OpenGL to use the entire area of the resized window.
     */
    glViewport(0, 0, width, height);
}

void MyView::windowViewDidStop(tygra::Window * window)
{
    /*
     * Tutorial: This is where we must free any OpenGL resources we've created.
     */

    glDeleteProgram(first_program_);
    glDeleteBuffers(1, &mesh_.vertex_vbo);
	glDeleteBuffers(1, &mesh_.vertex_colour);
    glDeleteBuffers(1, &mesh_.element_vbo);
    glDeleteVertexArrays(1, &mesh_.vao);
}

void MyView::windowViewRender(tygra::Window * window)
{
    /*
     * Tutorial: Configure OpenGL pipeline settings before drawing.
     */

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    /*
     * Tutorial: Erase the image of the previous frame ready to render this one.
     */

    glClearColor(0.f, 0.f, 0.25f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * Tutorial: Compute values needed by shader uniform variables.
     */

    const auto clock_time = std::chrono::system_clock::now() - start_time_;
    const auto clock_millisecs
        = std::chrono::duration_cast<std::chrono::milliseconds>(clock_time);
    const float time_seconds = 0.001f * clock_millisecs.count();

    const float angle_radians = time_seconds;
    const float radius = 0.25f;
    glm::mat4 mystery_xform
        = glm::translate(glm::mat4(1.f),
                         glm::vec3(radius * std::cos(angle_radians),
                                   radius * std::sin(angle_radians),
                                   0.0f));
	glm::vec3 uniform_colour(1.0f,0.0f,1.0f);
    /*
     * Tutorial: Use our shader program and populate its uniform variables.
     */

    glUseProgram(first_program_);

	GLuint colour_id = glGetUniformLocation(first_program_, "uniform_colour");
	glUniform3fv(colour_id, 1, glm::value_ptr(uniform_colour));

    GLuint time_seconds_id = glGetUniformLocation(first_program_,
                                                  "time_seconds");
    glUniform1f(time_seconds_id, time_seconds);

    GLuint mystery_xform_id = glGetUniformLocation(first_program_,
                                                   "mystery_xform");
    glUniformMatrix4fv(mystery_xform_id, 1, GL_FALSE, glm::value_ptr(mystery_xform));

	glActiveTexture(GL_TEXTURE0 );
	glBindTexture(GL_TEXTURE0);

    /*
     * Tutorial: Bind (attach) texture objects to texture sampling units.
     *           Pass the texture sampling unit index into the shader via
     *           a uniform variable.
     */

    glActiveTexture(GL_TEXTURE0 + kTextureTest);
    glBindTexture(GL_TEXTURE_2D, test_texture_);
    GLuint mystery_sampler_id = glGetUniformLocation(first_program_,
                                                     "mystery_sampler");
    glUniform1i(mystery_sampler_id, kTextureTest);

    /*
     * Tutorial: Bind (attach to the pipeline) our geometry and draw it.
     */

    glBindVertexArray(mesh_.vao);
    glDrawElements(GL_TRIANGLES, mesh_.element_count, GL_UNSIGNED_INT, 0);

	glBindVertexArray(mesh_.quad_vao);
	glDrawElements(GL_TRIANGLES, mesh_.quad_element_count, GL_UNSIGNED_INT, 0);
	
}

void MyView::GenerateBuffer(int num, GLuint & name, GLenum target, const GLvoid * data, GLsizeiptr  size, GLenum use)
{
	glGenBuffers(num, &name);
	glBindBuffer(target, name);
	glBufferData(target, size, data, use);
	glBindBuffer(target, kNullId);
}
