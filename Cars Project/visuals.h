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
	int vertices;
	int faces;
	point obj_points[17006];
	face obj_faces[35673];

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

