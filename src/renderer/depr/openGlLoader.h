#pragma once
#include "drawdetails.h"
#include "../vertex.h"
#include <vector>
#include <string>

DrawDetails uploadMesh(const std::vector<Vertex>& verts, const std::vector<unsigned int> elem);
void unloadMesh(std::vector<DrawDetails>& details);
void updateBuffer(const Vertex& verticis, int verOffset, const DrawDetails& drawDetails);
