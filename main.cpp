#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>


#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.hpp"

int main(int args, const char* argv[])
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 800, 800, "Mandelbrot", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    glfwPollEvents();
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile GLSL program
    // Use you own path!!!
    GLuint programID = LoadShaders( "/Users/ycx/Desktop/programming/mandelbrot\:c++/mandelbrot/vertices.glsl", "/Users/ycx/Desktop/programming/mandelbrot\:c++/mandelbrot/fragment.glsl");
    
    std::vector<GLfloat> vertices = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f
    };
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    GLuint cID = glGetUniformLocation(programID, "c");
    GLuint centerID = glGetUniformLocation(programID, "center");
    GLuint scaleID = glGetUniformLocation(programID, "scale");
    
    GLfloat c[2] = {0.0f, 0.0f};
    GLfloat center[2] = {0.0f, 0.0f};
    GLfloat scale = 1.0;
    
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glUseProgram(programID);
    
    glUniform1f(scaleID, scale);
    glUniform2fv(centerID, 1, center);
    glUniform2fv(cID, 1, c);
        
    // Draw the square
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
    
    glfwSwapBuffers(window);
    
    do{
        glfwPollEvents();
        
        // handle events. a better way is to register a callback function.
        if (glfwGetKey(window, GLFW_KEY_EQUAL ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            scale /= 1.01f;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_MINUS ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            scale *= 1.01f;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            center[1] += 0.05f * scale;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            center[1] -= 0.05f * scale;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            center[0] += 0.05f * scale;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            center[0] -= 0.05f * scale;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_J ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            c[0] += 0.005f;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_K ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            c[0] -= 0.005f;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_N ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            c[1] += 0.005f;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
        else if (glfwGetKey(window, GLFW_KEY_M ) == GLFW_PRESS) {
            
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            c[1] -= 0.005f;
            glUniform1f(scaleID, scale);
            glUniform2fv(centerID, 1, center);
            glUniform2fv(cID, 1, c);
            
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );
            glfwSwapBuffers(window);
        }
    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}


