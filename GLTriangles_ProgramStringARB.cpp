#include <windows.h>
#include "glew-2.1.0/include/GL/glew.h">
#include <string>
#include "SOIL/SOIL.h"
//#include "glew-2.1.0/include/GL/wglew.h"

// Define vertex data for a rectangle and corresponding texture coordinates
GLfloat vertices[] = {
    -1.0f, 1.0f, 0.8f,   // Top-left vertex (x, y, z)
    -1.0f, 0.0f, 0.8f,  // Bottom-left vertex (x, y, z)
    0.0f, 0.0f, 0.8f,   // Bottom-right vertex (x, y, z)
    0.0f, 1.0f, 0.8f     // Top-right vertex (x, y, z)
};

// Define vertex data for a rectangle and corresponding texture coordinates
GLfloat vertices2[] = {
    0.0f, 0.0f, 0.8f,   // Top-left vertex (x, y, z)
    0.0f, -1.0f, 0.8f,  // Bottom-left vertex (x, y, z)
    1.0f, -1.0f, 0.8f,   // Bottom-right vertex (x, y, z)
    1.0f, 0.0f, 0.8f     // Top-right vertex (x, y, z)
};
// Define vertex data for a rectangle and corresponding texture coordinates
GLfloat vertices3[] = {
    0.0f, 1.0f, 0.8f,   // Top-left vertex (x, y, z)
    0.0f, 0.0f, 0.8f,  // Bottom-left vertex (x, y, z)
    1.0f, 0.0f, 0.8f,   // Bottom-right vertex (x, y, z)
    1.0f, 1.0f, 0.8f     // Top-right vertex (x, y, z)
};

// Define vertex data for a rectangle and corresponding texture coordinates
GLfloat vertices4[] = {
    -1.0f, 0.0f, 0.8f,   // Top-left vertex (x, y, z)
    -1.0f, -1.0f, 0.8f,  // Bottom-left vertex (x, y, z)
    0.0f, -1.0f, 0.8f,   // Bottom-right vertex (x, y, z)
    0.0f, 0.0f, 0.8f     // Top-right vertex (x, y, z)
};

GLfloat texcoords[] = {
    0.0f, 1.0f,   // Top-left vertex texture coordinate (s, t)
    0.0f, 0.0f,   // Bottom-left vertex texture coordinate (s, t)
    1.0f, 0.0f,   // Bottom-right vertex texture coordinate (s, t)
    1.0f, 1.0f    // Top-right vertex texture coordinate (s, t)
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch( message ) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void renderScene(GLuint textureID, GLuint shadowMapID, GLuint shadowMapsrc) {
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_VERTEX_PROGRAM_ARB);
    // Enable the fragment program
    glEnable(GL_FRAGMENT_PROGRAM_ARB);

    //// Set vertex data and texture coordinates using glVertexPointer and glTexCoordPointer
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

    //// Enable vertex arrays and texture coordinate arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Enable textures and bind the textures
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMapID);

   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_NEVER);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_DEPTH, GL_NONE);


    // Define the indices to draw the rectangle as two triangles
    GLubyte indices[] = {
        0, 1, 2,   // Triangle 1: Top-left, bottom-left, bottom-right
        0, 2, 3    // Triangle 2: Top-left, bottom-right, top-right
    };

    // Draw the rectangle using indexed vertex arrays
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

    //// Unbind first Textures
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMapsrc);
    
    //// Set vertex data and texture coordinates using glVertexPointer and glTexCoordPointer
    glVertexPointer(3, GL_FLOAT, 0, vertices2);

    // Draw the 2nd rectangle using indexed vertex arrays
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

    //// Unbind first Textures
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMapID);

    //// Set vertex data and texture coordinates using glVertexPointer and glTexCoordPointer
    glVertexPointer(3, GL_FLOAT, 0, vertices3);

    // Draw the 2nd rectangle using indexed vertex arrays
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

    ////// Unbind first Textures
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMapsrc);

    //// Set vertex data and texture coordinates using glVertexPointer and glTexCoordPointer
    glVertexPointer(3, GL_FLOAT, 0, vertices4);

    // Draw the 2nd rectangle using indexed vertex arrays
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);



    //// Disable vertex arrays and texture coordinate arrays
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    // Draw the rectangle plane
   /* glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);
    glEnd();*/

    // Disable textures
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);

    // Unbind the shaders
    glDisable(GL_VERTEX_PROGRAM_ARB);
    glDisable(GL_FRAGMENT_PROGRAM_ARB);

    glFlush();
}

int main() {
    //OpenGL context
    //Callbacks
    //Draw Everything
    //Delete of all the resources

    //Window and Device Context (GPU)
    // glut or glfw for easy windows creation 
    // Driver calls Function Pointer - library to do that, glew or glad for loading function 


    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"OpenGLExample";
    RegisterClass(&wc);

    //WIndow creation done
    HWND hWnd = CreateWindow(
        L"OpenGLExample", L"OpenGL Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );
    if( !hWnd ) {
        MessageBox(NULL, L"Failed to create window.", L"Error", MB_ICONERROR);
        return 1;
    }

    HDC hDC = GetDC(hWnd);

    // Enable GLEW experimental features
    glewExperimental = GL_TRUE;

    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, pixelFormat, &pfd);
    //creating context done
    HGLRC hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);



    // Initialize GLEW
    if( glewInit() ) {
        MessageBox(NULL, L"Failed to initialize GLEW.", L"Error", MB_ICONERROR);
        return 1;
    }

    // Check for OpenGL version support
    if( !GLEW_VERSION_3_3 ) {
        fprintf(stderr, "OpenGL 3.3 not supported.\n");
        return 1;
    }

    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error!");
        //return 0;
    }


    // Example: Print the OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);
    printf("OpenGL Version: %s\n", version);

    // Create and bind a simple vertex shader
    const char* vertexShaderSource = "!!ARBvp1.0\n"
        "MOV result.position, vertex.position;\n"
        "MOV result.texcoord[0], vertex.texcoord;\n"
        "END\n";

    GLuint vertexShaderID;
    glGenProgramsARB(1, &vertexShaderID);
    glBindProgramARB(GL_VERTEX_PROGRAM_ARB, vertexShaderID);
    glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, strlen(vertexShaderSource), vertexShaderSource);

    GLint linkStatus;
    glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_BINDING_ARB, &linkStatus);
    if( linkStatus != 1 ) {
        //Gets the position in the program string where program fails
        GLint errorPos;
        glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &errorPos);

        //Gets the first bad string that causes failure
        const GLubyte* errorString;
        errorString = glGetString(GL_PROGRAM_ERROR_STRING_ARB);

        GLint infoLogLength;
        glGetProgramivARB(GL_VERTEX_PROGRAM_ARB, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[ infoLogLength ];
        glGetProgramInfoLog(GL_VERTEX_PROGRAM_ARB, infoLogLength, NULL, infoLog);
        //MessageBox(NULL, reinterpret_cast<const char*>( infoLog ), "Error", MB_ICONERROR);
        delete[] infoLog;
    }

    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error1!");
        //return 0;
    }

    const char* fragmentShaderSource =
        "!!ARBfp1.0\n"
        "OPTION ARB_fragment_program_shadow;\n"
        "TEMP depth;\n"   // Declare a parameter (depth)
        "TEX depth, fragment.texcoord, texture[1], SHADOW2D;\n"
        "MOV result.color, depth;\n"
        "END\n";

    GLuint fragmentShaderID;
    glGenProgramsARB(1, &fragmentShaderID);
    glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, fragmentShaderID);
    glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB, strlen(fragmentShaderSource), fragmentShaderSource);

    glGetProgramivARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_BINDING_ARB, &linkStatus);
    if( linkStatus == GL_FALSE ) {
        GLint infoLogLength;
        glGetProgramiv(GL_VERTEX_PROGRAM_ARB, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[ infoLogLength ];
        glGetProgramInfoLog(GL_VERTEX_PROGRAM_ARB, infoLogLength, NULL, infoLog);
        //MessageBox(NULL, L"Vertex program failed to bind: " + std::string(infoLog), L"Error", MB_ICONERROR);
        delete[] infoLog;
    }
    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error2!");
        //return 0;
    }


     GLuint textureID = SOIL_load_OGL_texture("Social.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y); //Nvidia
    //GLuint textureID = SOIL_load_OGL_texture("C:\\GithubRepos\\GLTriangles_ProgramStringARB\\x64\\Debug\\Social.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if( textureID == 0 ) {
        MessageBox(NULL, L"Failed to load texture.", L"Error", MB_ICONERROR);
        return 1;
    }
    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error3!");
        //return 0;
    }


    // Load the shadow map texture (depth texture) for shadow2D sampling
    GLuint shadowMapID = SOIL_load_OGL_texture("stage_curtains.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y); //Nvdia
    //GLuint shadowMapID = SOIL_load_OGL_texture("C:\\GithubRepos\\GLTriangles_ProgramStringARB\\x64\\Debug\\stage_curtains.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if( shadowMapID == 0 ) {
        MessageBox(NULL, L"Failed to load shadow map texture.", L"Error", MB_ICONERROR);
        return 1;
    }
    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error4!");
        //return 0;
    }


    // Bind the texture and set texture parameters
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error5!");
        //return 0;
    }

    glBindTexture(GL_TEXTURE_2D, shadowMapID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LESS);
    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error6!");
        //return 0;
    }

    // For demonstration purposes, you can create a simple white texture representing a depth map
    const int shadowMapWidth = 800;
    const int shadowMapHeight = 600;

    GLfloat* shadowData = new GLfloat[ shadowMapWidth * shadowMapHeight ];
    for( int i = 0; i < shadowMapWidth * shadowMapHeight; ++i ) {
        shadowData[ i ] = 0.7f; // White represents maximum depth (far plane)
    }

    GLuint shadowMapsrc;

    glGenTextures(1, &shadowMapsrc);
    glBindTexture(GL_TEXTURE_2D, shadowMapsrc);
    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error7!");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, shadowData);
    if( glGetError() != GL_NO_ERROR )
    {
        printf("Error8!");
    }
        
    delete[] shadowData;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



    //// Set the texture compare mode for the shadow map texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_NEVER);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    // Show and update the window
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // Main message loop
    MSG msg;
    while( true ) {
        if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            if( msg.message == WM_QUIT )
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            renderScene(textureID, shadowMapID, shadowMapsrc);
            SwapBuffers(hDC);
        }
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    DestroyWindow(hWnd);
    UnregisterClass(L"OpenGLExample", GetModuleHandle(NULL));

    return 0;
}
