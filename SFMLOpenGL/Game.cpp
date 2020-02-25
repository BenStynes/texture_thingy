#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vertex;

Vertex vertex[24];
Vertex initialvertex[24];
GLubyte triangles[36];
Matrix3 matrix;
/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo[1],		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID

//const string filename = "texture.tga";
//const string filename = "cube.tga";

const std::string filename = "cube.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glEnable(GL_CULL_FACE);

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	/* Vertices counter-clockwise winding */

	vertex[0].coordinate[0] = -1.0f;  //FRONT FACE
	vertex[0].coordinate[1] = -1.0f;
	vertex[0].coordinate[2] = 1.0f;

	vertex[1].coordinate[0] = 1.0f;
	vertex[1].coordinate[1] = -1.0f;
	vertex[1].coordinate[2] = 1.0f;

	vertex[2].coordinate[0] = 1.0f;
	vertex[2].coordinate[1] = 1.0f;
	vertex[2].coordinate[2] = 1.0f;

	vertex[3].coordinate[0] = -1.0f;
	vertex[3].coordinate[1] = 1.0f;
	vertex[3].coordinate[2] = 1.0f;

	/// <summary>
	/// 
	/// </summary>
	vertex[4].coordinate[0] = 1.0f; //BACK 
	vertex[4].coordinate[1] = 1.0f;
	vertex[4].coordinate[2] = -1.0f;

	vertex[7].coordinate[0] = -1.0f;
	vertex[7].coordinate[1] = 1.0f;
	vertex[7].coordinate[2] = -1.0f;

	vertex[6].coordinate[0] = -1.0f;
	vertex[6].coordinate[1] = -1.0f;
	vertex[6].coordinate[2] = -1.0f;

	vertex[5].coordinate[0] =  1.0f;//
	vertex[5].coordinate[1] = -1.0f;
	vertex[5].coordinate[2] = -1.0f;
	/// <summary>
	/// 
	// </summary>
	vertex[8].coordinate[0] = -1.0f;// LEFT
	vertex[8].coordinate[1] = -1.0f;
	vertex[8].coordinate[2] = -1.0f;

	vertex[9].coordinate[0] = -1.0f;//12
	vertex[9].coordinate[1] = -1.0f;
	vertex[9].coordinate[2] = 1.0f;

	vertex[10].coordinate[0] = -1.0f;//22
	vertex[10].coordinate[1] = 1.0f;
	vertex[10].coordinate[2] = 1.0f;

	vertex[11].coordinate[0] = -1.0f;//23
	vertex[11].coordinate[1] =  1.0f;
	vertex[11].coordinate[2] = -1.0f;
	/* <summary>*/
	/// 
	/// </summary>
	vertex[12].coordinate[0] = 1.0f;// Right
	vertex[12].coordinate[1] = 1.0f;
	vertex[12].coordinate[2] = 1.0f;

	vertex[15].coordinate[0] = 1.0f;//25
	vertex[15].coordinate[1] = 1.0f;
	vertex[15].coordinate[2] =-1.0f;

	vertex[14].coordinate[0] =  1.0f;//26
	vertex[14].coordinate[1] = -1.0f;
	vertex[14].coordinate[2] =  -1.0f;

	vertex[13].coordinate[0] =  1.0f;//27
	vertex[13].coordinate[1] = -1.0f;
	vertex[13].coordinate[2] =  1.0f;
	/// <summary>
	/// 
	/// </summary>
	vertex[16].coordinate[0] =-1.0f;// top
	vertex[16].coordinate[1] = 1.0f;
	vertex[16].coordinate[2] = 1.0f;

	vertex[17].coordinate[0] = 1.0f;//33
	vertex[17].coordinate[1] = 1.0f;
	vertex[17].coordinate[2] = 1.0f;

	vertex[18].coordinate[0] = 1.0f;//32
	vertex[18].coordinate[1] = 1.0f;
	vertex[18].coordinate[2] = -1.0f;

	vertex[19].coordinate[0] = -1.0f;//31
	vertex[19].coordinate[1] = 1.0f;
	vertex[19].coordinate[2] = -1.0f;
	
	/// <summary>
	/// 
	/// </summary>
	vertex[20].coordinate[0] = -1.0f;//bottom
	vertex[20].coordinate[1] = -1.0f;
	vertex[20].coordinate[2] = -1.0f;

	vertex[23].coordinate[0] = -1.0f;//35
	vertex[23].coordinate[1] = -1.0f;
	vertex[23].coordinate[2] =  1.0f;

	vertex[22].coordinate[0] = 1.0f;//36
	vertex[22].coordinate[1] = -1.0f;
	vertex[22].coordinate[2] = 1.0f;

	vertex[21].coordinate[0] = 1.0f;//37
	vertex[21].coordinate[1] = -1.0f;
	vertex[21].coordinate[2] = -1.0f;

	

	vertex[0].color[0] = 1.0f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.5f;
	vertex[0].color[3] = 1.0f;

	vertex[1].color[0] = 1.0f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 1.0f;
	vertex[1].color[3] = 1.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 1.0f;
	vertex[2].color[3] = 1.0f;


	vertex[3].color[0] = 0.0f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;
	vertex[3].color[3] = 1.0f;


	vertex[4].color[0] = 0.0f;
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 0.0f;
	vertex[4].color[3] = 1.0f;


	vertex[5].color[0] = 1.0f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.25f;
	vertex[5].color[3] = 1.0f;


	vertex[6].color[0] = 1.0f;
	vertex[6].color[1] = 0.25f;
	vertex[6].color[2] = 1.0f;
	vertex[6].color[3] = 1.0f;


	vertex[7].color[0] = 1.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 1.0f;
	vertex[7].color[3] = 1.0f;

	

	vertex[0].texel[0] = 0.25f;
	vertex[0].texel[1] = 0.00f;

	vertex[1].texel[0] = 0.50f;
	vertex[1].texel[1] = 0.0f;

	vertex[2].texel[0] = 0.50f;
	vertex[2].texel[1] = 0.25f;

	vertex[3].texel[0] = 0.25f;
	vertex[3].texel[1] = 0.25f;//BACK FACE


	vertex[4].texel[0] = 0.25f;
	vertex[4].texel[1] = 0.25f;

	vertex[5].texel[0] = 0.25f;
	vertex[5].texel[1] = 0.50f;

	vertex[7].texel[0] = 0.50f;
	vertex[7].texel[1] = 0.25f;

	vertex[6].texel[0] = 0.50f;
	vertex[6].texel[1] = 0.50f;
	//2 FACE
	vertex[8].texel[0] = 0.0f;
	vertex[8].texel[1] = 0.25f;

	vertex[9].texel[0] = 0.0f;
	vertex[9].texel[1] = 0.50f;

	vertex[11].texel[0] = 0.25f;
	vertex[11].texel[1] = 0.25f;

	vertex[10].texel[0] = 0.25f;
	vertex[10].texel[1] = 0.50f;
	//3 FACE
	vertex[12].texel[0] = 0.25f;
	vertex[12].texel[1] = 0.50f;

	vertex[13].texel[0] = 0.5f;
	vertex[13].texel[1] = 0.5f;

	vertex[14].texel[0] = 0.50f;
	vertex[14].texel[1] = 0.75f;

	vertex[15].texel[0] = 0.25f;
	vertex[15].texel[1] = 0.75f;
	//4 FACE
	vertex[16].texel[0] = 0.50f;
	vertex[16].texel[1] = 0.25f;

	vertex[17].texel[0] = 0.75f;
	vertex[17].texel[1] = 0.25f;

	vertex[18].texel[0] = 0.75f;
	vertex[18].texel[1] = 0.50f;

	vertex[19].texel[0] = 0.50f;
	vertex[19].texel[1] = 0.50f;
	//5 FACE
	vertex[20].texel[0] = 0.75f;
	vertex[20].texel[1] = 0.25f;

	vertex[21].texel[0] = 1.0f;
	vertex[21].texel[1] = 0.25f;

	vertex[22].texel[0] = 1.0f;
	vertex[22].texel[1] = 0.50f;

	vertex[23].texel[0] = 0.75f;
	vertex[23].texel[1] = 0.50f;

	/*Index of Poly / Triangle to Draw */
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 2;   triangles[4] = 3;   triangles[5] = 0;
	triangles[6] = 4;   triangles[7] = 5;   triangles[8] = 6;
	triangles[9] = 6;   triangles[10] = 7;   triangles[11] = 4;

	triangles[12] = 8;   triangles[13] = 9;   triangles[14] = 10;
	triangles[15] = 10;   triangles[16] = 11;   triangles[17] = 8;
	triangles[18] = 12;   triangles[19] = 13;   triangles[20] = 14;
	triangles[21] = 14;   triangles[22] = 15;   triangles[23] = 12;

	triangles[24] = 16;   triangles[25] = 17;   triangles[26] = 18;
	triangles[27] = 18;   triangles[28] = 19;   triangles[29] = 16;
	triangles[30] = 20;   triangles[31] = 21;   triangles[32] = 22;
	triangles[33] = 22;   triangles[34] = 23;   triangles[35] = 20;

	for (int i = 0; i < 24; i++)
	{
		initialvertex[i] = vertex[i];
	}
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_texel;"
		"out vec4 color;"
		"out vec2 texel;"
		"void main() {"
		"	color = sv_color;"
		"	texel = sv_texel;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"uniform sampler2D f_texture;"
		"in vec4 color;"
		"in vec2 texel;"
		"out vec4 fColor;"
		"void main() {"
		//"	fColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);"
		"	fColor =color + texture(f_texture, texel.st);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f / 60.0F)
	{
		clock.restart();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			rotation.setX(rotation.getX() + rotationAngle);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			rotation.setY(rotation.getY() + rotationAngle);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			rotation.setZ(rotation.getZ() + rotationAngle);
	}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			translation.setY(translation.getY() - 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			translation.setY(translation.getY() + 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			translation.setX(translation.getX() - 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			translation.setX(translation.getX() + 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			scale += 10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			scale -= 10;
		}

		Matrix3 identity{ 1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f };

		identity = identity * matrix.Scale3D(scale);

		identity = identity * matrix.RotationX(rotation.getX());
		identity = identity * matrix.RotationY(rotation.getY());
		identity = identity * matrix.RotationZ(rotation.getZ());

		for (int i = 0; i < 24; i++)
		{


			vector3 localvect{ initialvertex[i].coordinate[0],initialvertex[i].coordinate[1] ,initialvertex[i].coordinate[2] };
			vector3 answerVector = identity * localvect;
			vertex[i].coordinate[2] = answerVector.getZ();

			answerVector.setZ(1);
			vector3 secondAnswer = identity.Translate(translation.getX(), translation.getY()) * answerVector;
			vertex[i].coordinate[0] = secondAnswer.getX();
			vertex[i].coordinate[1] = secondAnswer.getY();

		}
}


	//Change vertex data


#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.25f, 0.5f, 0.25f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

