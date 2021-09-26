#pragma once

#ifndef OPENGL_INCLUDED
#include "VNOpenGLInclude.hpp"
#endif // !OPENGL_INCLUDED

#include "VNNode.hpp"

#define ADD     0
#define DELETE  1
#define REPLACE 2

class VNTimeLine
{
public:
	VNTimeLine();
	~VNTimeLine();
	void VNAddNode();
	void VNAddAction(unsigned int node_index, int action, VNImage* target, VNImage* object);

private:
	std::vector<VNNode*> mNodes;
};

VNTimeLine::VNTimeLine()
{
}

VNTimeLine::~VNTimeLine()
{
}

void VNTimeLine::VNAddNode()
{
	VNNode* node = new VNNode();
	mNodes.push_back(node);
	return;
}

void VNTimeLine::VNAddAction(unsigned int node_index, int action, VNImage* target, VNImage* object)
{
	if (node_index >= mNodes.size())
		std::cout << "ERROR::NODES::INDEX_OUT_OF_RANGE" << std::endl;
	else
		mNodes[node_index]->VNAddAction(action, target, object);
	return;
}

void VNTimeLine::VNAddAction(unsigned int node_index, int action, VNShader* target, VNShader* object)
{
	if (node_index >= mNodes.size())
		std::cout << "ERROR::NODES::INDEX_OUT_OF_RANGE" << std::endl;
	else
		mNodes[node_index]->VNAddAction(action, target, object);
	return;
}
