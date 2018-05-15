#include "Mesh.h"
#include <gl_core_4_4.h>



Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
{
	// define 4 vertices for 2 triangles
	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { 0.5f, 0, -0.5f, 1 };
	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

	initialise(4, vertices, 6, indices);
}

void Mesh::initialise(unsigned int vertexCount, const Vertex * vertices, unsigned int indexCount, unsigned int * indices)
{
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);


	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	// bind indices if there are any
	if (indexCount != 0) 
	{
		glGenBuffers(1, &ibo);
		// bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		// fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		triCount = indexCount / 3;
	}
	else 
	{
		triCount = vertexCount / 3;
	}
	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//// define 6 vertices for 2 triangles
	//Mesh::Vertex verts[6];
	//verts[0].position = { -0.5f, 0, 0.5f, 1 };
	//verts[1].position = { 0.5f, 0, 0.5f, 1 };
	//verts[2].position = { -0.5f, 0, -0.5f, 1 };
	//verts[3].position = { -0.5f, 0, -0.5f, 1 };
	//verts[4].position = { 0.5f, 0, 0.5f, 1 };
	//verts[5].position = { 0.5f, 0, -0.5f, 1 };
	//m_quadMesh.initialise(6, vertices);
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	//using indices or just vertices?
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}
