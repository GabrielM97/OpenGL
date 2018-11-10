#pragma once
#include <tygra/WindowViewDelegate.hpp>
#include <tgl/tgl.h>
#include <glm/glm.hpp>
#include <chrono>
#include <bitset>





typedef unsigned char BYTE;
/*
 * Tutorial: This class exists to integrate with the tygra framework. It
 *           implements the tygra::WindowViewDelegate interface which the
 *           tygra::Window object (which initialises OpenGL) uses to perform
 *           all drawing within the operating system window.
 */

struct Vertex
{
	glm::vec2 position;
	glm::vec3 colour;
};

class MyView : public tygra::WindowViewDelegate
{
public:
	
    MyView();
	
    ~MyView();

private:

    /*
     * Tutorial: These methods are needed to implement the framework's
     *           tygra::WindowViewDelegate interface.
     */

    void windowViewWillStart(tygra::Window * window) override;
	
    void windowViewDidReset(tygra::Window * window,
                            int width,
                            int height) override;

    void windowViewDidStop(tygra::Window * window) override;
    
    void windowViewRender(tygra::Window * window) override;


	void GenerateBuffer(int num, GLuint & name, GLenum target, const GLvoid * data, GLsizeiptr  size, GLenum use);

private:

    /**
     * Tutorial: Not an essential variable for GL rendering, used here to
     *         measure an application running time to use as a shader variable.
     */
    std::chrono::system_clock::time_point start_time_;

    /*
     * Tutorial: OpenGL objects (e.g. shaders or data buffers) are referenced
     *           via integer ids. We store the ids so we can use the objects
     *           each frame when drawing.
     */
    GLuint test_texture_{ 0 };

    /*
     * Tutorial: Handle (id) of our shader program.
     */
    GLuint first_program_{ 0 };

    /*
     * Tutorial: Encapsulate the vertex array and buffer objects into a data
     *           structure to make it easy to have many of them in the future.
     */
    struct MeshGL
    {
        // VertexBufferObject for the vertex positions
        GLuint vertex_vbo{ 0 };

		GLuint qaud_vbo{0};

		GLuint vertex_colour{0};

        // VertexBufferObject for the elements (indices)
        GLuint element_vbo{ 0 };
		GLuint quad_element_ibo{0};

        // VertexArrayObject for the shape's vertex array settings
        GLuint vao{ 0 };
		GLuint quad_vao{0};

        // Needed for when we draw using the vertex arrays
        int element_count{ 0 };
		int quad_element_count{ 0 };
    };
    MeshGL mesh_;

    /*
     * Tutorial: Define integer constants to improve readability. Any integers 
     *           found in the code should be counting numbers, not ids.
     */
    const static GLuint kNullId = 0;
    enum VertexAttribIndexes {
        kVertexPosition = 0,
        kVertexColour = 1
    };
    enum FragmentDataIndexes {
        kFragmentColour = 0
    };
    enum TextureIndexes {
        kTextureTest = 0
    };

	

};


