#pragma once
#include "vertex.h"
#include <vector>

DrawDetails uploadMesh(const std::vector<Vertex>& verts, const std::vector<uint32_t> elem);
void unloadMesh(std::vector<DrawDetails>& details);
