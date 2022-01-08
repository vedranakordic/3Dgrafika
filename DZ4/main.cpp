#include "shader.h"
#include "model.h"


int main()
{
    // zapocni GL kontekst
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    // definiraj prozor
    GLFWwindow* window = glfwCreateWindow(1024, 768, "I59 3D RacGraf", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }

    // definiraj prostor ekrana
    int nx, ny;
    glfwGetFramebufferSize(window, &nx, &ny);
    glViewport(0, 0, nx, ny);

    // postavi trenutni kontekst
    glfwMakeContextCurrent(window);

    // inicijalizacija GLEW
    glewInit();

    // radi dagiranja
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version  = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // definiraj z-spremnik
    glEnable(GL_DEPTH_TEST); // test dubine
    glDepthFunc(GL_LESS); // manja vrijednost z-spremnika ja "bliza"

    // ulaz
    // ulat
    std::vector<Vertex> vertices = {
            // pozicije              // normale           // teksturne koordinate
             {{ 0.5f,  0.5f, 1.0f},   {1.0f, 1.0f, 0.0f},   {1.0f, 1.0f}},
             {{0.5f, -0.5f, -1.0f},    {1.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
             {{-0.5f, -0.5f, 0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 0.0f}},
             {{-0.5f,  0.5f, 1.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}
        };

    std::vector<unsigned int> indices = {
            0, 1, 3, // prvi trokut
            1, 2, 3  // drugi trokut
        };

    std::vector<Texture> textures = {{0,"texture_diffuse","container.jpg"}};

    // definiraj sjencare
    Shader shader("shader.vert","shader.frag");
    // koristi shader
    shader.use();

    // definiraj model
    Mesh mesh(vertices,indices,textures);


    bool flushed = false;
    // iscrtaj u petlji
    while(!glfwWindowShouldClose(window))
    {
        // ocisti ekran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // prostor kamere
        glm::vec3 viewPos = glm::vec3(0.0f, 2.0f, -3.0f);
        glm::vec3 viewDir = glm::vec3(0.0f, 0.0f, 1.0f); // smjer
        glm::vec3 upDir   = glm::vec3(0.0f, 1.0f, 0.0f); // smjer
        glm::mat4 view = glm::lookAt(viewPos, viewDir, upDir);

        // transformacija pogleda
        glm::mat4 model = glm::mat4(4.0);

        /*
        modelMatrix = glm::translate(modelMatrix,glm::vec3(0.0,1.0,0.0));
        float rot = (-90.0/180.0) * M_PI;
        modelMatrix = glm::rotate(modelMatrix,rot,glm::vec3(1,0,0));
        */

        glm::mat4 projection = glm::ortho(-5.0,5.0,-5.0,5.0,-10.0,10.0);
        shader.setMat4("model",model);
        shader.setMat4("projection",projection);
        shader.setMat4("view",view);

        // postaviti materijal
        shader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
        shader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
        shader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        shader.setFloat("material.shininess", 32.0f);


        // svjetlo
        shader.setVec3("light.position",glm::vec3(1.2f,1.0f,2.0f));

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);
        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
        shader.setVec3("light.ambient", ambientColor);
        shader.setVec3("light.diffuse", diffuseColor);
        shader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        // iscrtaj model koristeci shader 'shader'
        mesh.Draw(shader);

        if(!flushed) {glfwSwapBuffers(window); flushed=true; }

        // definiraj dogadjaje
        glfwPollEvents();
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);

        if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS) flushed = false;

    }
    // zatvori GL kontekst
    glfwTerminate();
    return 0;
}
