struct point
{
	float x;
	float y;
	float z;
};

struct face
{
	int vtx[3];
};

typedef struct model
{
	point obj_points[10];
	face obj_faces[4];
	int vertices;
	int faces;
} model;


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

