#pragma once

#include "Edge.h"

class Vertex;
class Face;

class Halfedge
{
public:
	Halfedge() : m_edge(0), m_vertex(0), m_face(0), m_prev(0), m_next(0), m_propertyIndex(-1) {	; }
	~Halfedge()	{;}

	//Pointers for Halfedge Data Structure
	Face     * & face()    { return m_face;}
	Edge     * & edge()    { return m_edge;}
	Vertex   * & target()  { return m_vertex;}	
	Halfedge * & prev() { return m_prev;}
	Halfedge * & next() { return m_next;}

	//Computed by Halfedge Data Structure
	Halfedge * & twin()  { return m_edge->twin(this); }
	Vertex   * & source()  { return m_prev->target();}

	//Rotation operations
	Halfedge * clw_rotate_about_target() {return next()->twin();}
	Halfedge * ccw_rotate_about_source() {return prev()->twin();}
	Halfedge * clw_rotate_about_source() {
		Halfedge * he = twin();
		return (he)?(he->next()):(NULL);
	}
	Halfedge * ccw_rotate_about_target() {
		Halfedge * he_dual = twin();
		return (he_dual)?(he_dual->prev()):(NULL);
	}

	//optional: for indexing computed attributes
	int & index() {return m_propertyIndex; }

protected:
	//for Halfedge Data Structure
	Edge     *     m_edge;
    Face     *     m_face;
	Vertex   *     m_vertex;		//target vertex
	Halfedge *	   m_prev;
	Halfedge *     m_next;
	//optional
	int			   m_propertyIndex; // index to Property array
};
