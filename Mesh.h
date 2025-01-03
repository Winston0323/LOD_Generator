#pragma once
#include <vector>
#include "Edge.h"
#include "Face.h"
#include "Halfedge.h"
#include "Vertex.h"
#include "Point.h"


class Mesh
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////								Methods										//////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	//(1) Constructor and Destructor
	Mesh();
	~Mesh();

	//(2) I/O
	int numVertices()	{return m_verts.size();}							//number of vertices
	int numEdges()		{return m_edges.size();}							//number of edges
	int numFaces()		{return m_faces.size();}							//number of faces
	void copyTo( Mesh & targetMesh );										//copy current mesh to the target mesh 
	bool readMFile( const char inFile[]);									//read an "M"-format mesh from inFile
	bool readOBJFile(const char inFile[]);									//read an "OBJ"-format mesh from inFile
	bool writeMFile( const char outFile[]);									//write a mesh to outFile in "M"-format
	bool writeOBJFile(const char outFile[]);								//write a mesh to outFile in "OBJ"-format
	void clear();

	//(3) BASIC OPERATIONS
	//Check whether an element is on the boundary:
	bool isBoundary( Vertex *  v ) const {return v->boundary();}
	bool isBoundary( Edge *    e ) const {return e->boundary();}
	bool isBoundary( Halfedge *  he ) const {return !(he->twin());}
	
	//indexing elements
	Vertex *			indVertex(unsigned int ind) { return (ind >= m_verts.size() ? 0 : m_verts[ind]); }
	Face *				indFace(unsigned int ind) { return (ind >= m_faces.size() ? 0 : m_faces[ind]); }
	Edge *				indEdge(unsigned int ind) { return (ind >= m_edges.size() ? 0 : m_edges[ind]); }

	Edge *				vertexEdge( Vertex * v0, Vertex * v1 );			//To find an edge sharing v0 and v1
	Halfedge *			vertexHalfedge(Vertex * srcV, Vertex * trgV);	//To find a half-edge from v0 to v1
	Edge *				idEdge( int vid0, int vid1 );					
	Halfedge *			idHalfedge( int srcVid, int trgVid );
	
	
protected:
	//(4) Mesh Modification Operators
	Vertex *	createVertex();
	Face *		createFace();
	Edge *		createEdge();

	Edge *		createEdge(Halfedge * he0, Halfedge * he1);	
	Face *		createFace(Vertex * verts[]);
	Face *		createFace(int vIds[]);

	void		LabelBoundaryVertices();
	
	////(6) Some Basic Mesh Processing Operations
	////	Flip the input edge, and return it.
	////	if the flip works, return the resultant edge, otherwise return NULL
	//Edge *				EdgeFlip(Edge * e);

	//// Split the given edge(input) into two. 
	////	  return :  newly created vertex or NULL(when the split fails);
	//Vertex *			EdgeSplit(Edge * e);
	//Vertex *			FaceSplit(Face * f, double bary[3]);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////								Variables										//////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

protected:	
	std::vector<Edge *>					m_edges;		// edge container
	std::vector<Vertex *>				m_verts;		// vertex container
	std::vector<Face *>					m_faces;		// face container

	//a temporary container to store halfedges surrounding some vertices
	std::vector<std::vector<Halfedge *>> v_adjInHEList;	

protected:
	friend class MeshVertexIterator;
	friend class MeshEdgeIterator;
	friend class MeshFaceIterator;
	friend class MeshHalfedgeIterator;
	friend class MeshUtility;
	friend class MeshIO;
};

