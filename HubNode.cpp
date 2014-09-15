/*
Project:        GroupProject
File Name:      HubNode.cpp
Description:    This class has the destructor of HubNode.
Copyright:      2014 Acuna Matata.
Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
*/
#include "HubNode.h"

// HubNode Destructor
HubNode::~HubNode() {
    if (next != NULL) {
        delete next;
    }
}