#include "ModuleRenderer3D.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleEditor.h"
#include "Globals.h"
#include "Log.h"
#include "ModuleLoadGeometry.h"

#include "External/Optick/include/optick.h"

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	context = nullptr;

	VBO = 0;
	EBO = 0;
	VAO = 0;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

static const GLfloat TriangleVertices_BufferData[] = {

	0, 0, 0,
	1, 1, 0,
	1, 0, 0,

	0, 0, 0,
	0, 1, 0,
	1, 1, 0,

	0, 0, 1,
	1, 0, 1,
	1, 1, 1,

	0, 0, 1,
	1, 1, 1,
	0, 1, 1,

	0, 0, 0, 
	1, 0, 0, 
	0, 0, 1,

	1, 0, 1,
	0, 0, 1, 
	1, 0, 0,

	0, 1, 0, 
	0, 1, 1,
	1, 1, 0,

	1, 1, 1,
	1, 1, 0, 
	0, 1, 1,

	0, 0, 0, 
	0, 1, 1, 
	0, 1, 0,

	0, 0, 0,
	0, 0, 1,
	0, 1, 1,

	1, 0, 0,
	1, 1, 0,
	1, 1, 1,

	1, 0, 0, 
	1, 1, 1,
	1, 0, 1

};

static const GLfloat CubeVertices_BufferData[] = {

	 1,1,1, // 0
	 0,1,1, // 1
	 0,0,1, // 2
	 1,0,1, // 3

	 1,0,0, // 4
	 1,1,0, // 5
	 0,1,0, // 6
	 0,0,0  // 7

};

static const GLuint TriangleIndices_BufferData[] = {

	0, 1, 2,   // Front face
	2, 3, 0,

	6, 4, 7,   // Back face
	4, 6, 5,

	0, 3, 4,   // Right face
	4, 5, 0,

	1, 6, 2,   // Left face
	6, 7, 2,

	0, 5, 6,   // Top face
	0, 6, 1,

	7, 4, 3,   // Bottom face
	7, 3, 2

};

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;

	// OpenGL initial attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	// Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// Initializing Glew 2.1.0
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		LOG("Error in loading Glew: %s\n", glewGetErrorString(err));
	}
	else {
		LOG("Successfully using Glew %s", glewGetString(GLEW_VERSION));
	}
	
	if(ret == true)
	{
		// Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		// Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Check for errors
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		// Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Check for errors
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		// Enable OpenGL initial configurations

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);

		// Additional OpenGL configurations (starting disabled)

		glDisable(GL_TEXTURE_3D);
		glDisable(GL_BLEND);
		glDisable(GL_MULTISAMPLE);
		glDisable(GL_STENCIL_TEST);
		glDisable(GL_SCISSOR_TEST);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_POINT_SPRITE);
		glDisable(GL_FOG);
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glDisable(GL_NORMALIZE);
		glDisable(GL_POLYGON_OFFSET_FILL);

		// Wireframe-Only Mode starting disabled

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);

	Grid.axis = true;

	// OpenGL buffers (This code must only be executed one time in Init)

		// Vertex Buffer Object: holds actual vertex attribute data.

	/*glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriangleVertices_BufferData), TriangleVertices_BufferData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	glGenBuffers(1, &VBO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices_BufferData), CubeVertices_BufferData, GL_STATIC_DRAW); 
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

		// Element Buffer Object: holds indices used for indexed rendering.

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TriangleIndices_BufferData), TriangleIndices_BufferData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Vertex Object Attributes: are used to manage the setup of vertex 
		// attributes, making it easier to switch between different sets of 
	    // attributes when rendering different objects.

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	OPTICK_EVENT();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	App->editor->AddFPS(App->GetFPS());
	App->editor->AddDT(App->GetDT());
	App->editor->AddMS(App->GetMS());

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	OPTICK_EVENT();

	// Render Grid
	
	if (showGrid) {

		Grid.Render();

	}
	
	// -------------- Drawing a cube using OpenGL Direct Mode rendering --------------

	/*glLineWidth(2.0f);
	glBegin(GL_TRIANGLES);

	glVertex3d(0, 0, 0); glVertex3d(1, 1, 0); glVertex3d(1, 0, 0);
	glVertex3d(0, 0, 0); glVertex3d(0, 1, 0); glVertex3d(1, 1, 0);

	glVertex3d(0, 0, 1); glVertex3d(1, 0, 1); glVertex3d(1, 1, 1);
	glVertex3d(0, 0, 1); glVertex3d(1, 1, 1); glVertex3d(0, 1, 1);

	glVertex3d(0, 0, 0); glVertex3d(1, 0, 0); glVertex3d(0, 0, 1);
	glVertex3d(1, 0, 1); glVertex3d(0, 0, 1); glVertex3d(1, 0, 0);

	glVertex3d(0, 1, 0); glVertex3d(0, 1, 1); glVertex3d(1, 1, 0);
	glVertex3d(1, 1, 1); glVertex3d(1, 1, 0); glVertex3d(0, 1, 1);

	glVertex3d(0, 0, 0); glVertex3d(0, 1, 1); glVertex3d(0, 1, 0);
	glVertex3d(0, 0, 0); glVertex3d(0, 0, 1); glVertex3d(0, 1, 1);

	glVertex3d(1, 0, 0); glVertex3d(1, 1, 0); glVertex3d(1, 1, 1);
	glVertex3d(1, 0, 0); glVertex3d(1, 1, 1); glVertex3d(1, 0, 1);

	glEnd();
	glLineWidth(1.0f);*/

	// -------------- Drawing a cube using OpenGL Vertex Arrays Mode rendering --------------

	/*glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, (sizeof(TriangleVertices_BufferData) / sizeof(float) / 3));

	glDisableClientState(GL_VERTEX_ARRAY);*/

	// -------------- Drawing a cube using OpenGL Vertex Indices Mode rendering --------------

	/*glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);*/

	// -------------- Drawing vector of primitives -----------------

	DrawPrimitives();

	// --------------------------- Drawing editor and Swaping Window -------------------------

	App->editor->DrawEditor();

	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	// CleanUp OpenGL Buffers

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO); 
		VBO = 0;
	}

	if (EBO != 0) {
		glDeleteBuffers(1, &EBO);
		EBO = 0;
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	// detach log stream
	aiDetachAllLogStreams();
	
	// Delete OpenGL context

	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//todo: USE MATHGEOLIB here BEFORE 1st delivery! (TIP: Use MathGeoLib/Geometry/Frustum.h, view and projection matrices are managed internally.)
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(ProjectionMatrix.M);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::DrawPrimitives()
{
	for (auto it = primitives.begin(); it != primitives.end(); ++it) {

		(*it)->Render();

	}
}

void ModuleRenderer3D::ClearPrimitives()
{
	for (auto it = primitives.begin(); it != primitives.end(); ++it) {

		delete (*it);
		(*it) = nullptr;
	}

	primitives.clear();
}
