#include <ultra64.h>

Lights1 bush_leaves_f3d_lights = gdSPDefLights1(
	0x1B, 0x51, 0x21,
	0x37, 0xA3, 0x43, 0x28, 0x28, 0x28);

Lights1 bush_concrete_f3d_lights = gdSPDefLights1(
	0x26, 0x26, 0x28,
	0x4C, 0x4C, 0x50, 0x28, 0x28, 0x28);

Vtx bush_Bush_mesh_vtx_0[31] = {
	{{{208, 139, 461},0, {582, 240},{0x56, 0x20, 0x57, 0xFF}}},
	{{{194, 177, 443},0, {594, 231},{0x45, 0x52, 0x43, 0xFF}}},
	{{{-194, 177, 443},0, {594, -7},{0xBB, 0x52, 0x43, 0xFF}}},
	{{{-208, 139, 461},0, {582, -16},{0xAA, 0x20, 0x57, 0xFF}}},
	{{{-213, -213, 470},0, {368, -16},{0xCC, 0x6C, 0x2A, 0xFF}}},
	{{{213, -213, 470},0, {368, 240},{0x34, 0x6C, 0x2A, 0xFF}}},
	{{{-208, 139, 461},0, {582, 1008},{0xAA, 0x20, 0x57, 0xFF}}},
	{{{-194, 177, 443},0, {594, 1003},{0xBB, 0x52, 0x43, 0xFF}}},
	{{{-194, 177, -443},0, {594, 757},{0xBB, 0x52, 0xBD, 0xFF}}},
	{{{-208, 139, -461},0, {582, 752},{0xAA, 0x20, 0xA9, 0xFF}}},
	{{{-213, -213, -470},0, {368, 752},{0xCC, 0x6C, 0xD6, 0xFF}}},
	{{{213, -213, -470},0, {368, 496},{0x34, 0x6C, 0xD6, 0xFF}}},
	{{{208, 139, -461},0, {582, 496},{0x56, 0x20, 0xA9, 0xFF}}},
	{{{194, 177, -443},0, {594, 505},{0x45, 0x52, 0xBD, 0xFF}}},
	{{{-194, 177, -443},0, {594, 743},{0xBB, 0x52, 0xBD, 0xFF}}},
	{{{208, 139, 461},0, {582, 240},{0x56, 0x20, 0x57, 0xFF}}},
	{{{208, 139, -461},0, {582, 496},{0x56, 0x20, 0xA9, 0xFF}}},
	{{{194, 177, 443},0, {611, 245},{0x45, 0x52, 0x43, 0xFF}}},
	{{{208, 139, 461},0, {582, 240},{0x56, 0x20, 0x57, 0xFF}}},
	{{{194, 177, -443},0, {611, 491},{0x45, 0x52, 0xBD, 0xFF}}},
	{{{159, 212, 399},0, {654, 257},{0x27, 0x75, 0x20, 0xFF}}},
	{{{159, 212, -399},0, {654, 479},{0x27, 0x75, 0xE0, 0xFF}}},
	{{{-159, 212, -399},0, {850, 479},{0xD9, 0x75, 0xE0, 0xFF}}},
	{{{-194, 177, -443},0, {871, 491},{0xBB, 0x52, 0xBD, 0xFF}}},
	{{{194, 177, -443},0, {633, 491},{0x45, 0x52, 0xBD, 0xFF}}},
	{{{-194, 177, 443},0, {871, 245},{0xBB, 0x52, 0x43, 0xFF}}},
	{{{-159, 212, 399},0, {850, 257},{0xD9, 0x75, 0x20, 0xFF}}},
	{{{194, 177, 443},0, {633, 245},{0x45, 0x52, 0x43, 0xFF}}},
	{{{-208, 139, 461},0, {582, 1008},{0xAA, 0x20, 0x57, 0xFF}}},
	{{{-213, -213, -470},0, {368, 752},{0xCC, 0x6C, 0xD6, 0xFF}}},
	{{{-213, -213, 470},0, {368, 1008},{0xCC, 0x6C, 0x2A, 0xFF}}},
};

Gfx bush_Bush_mesh_tri_0[] = {
	gsSPVertex(bush_Bush_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(0, 3, 4, 0),
	gsSP1Triangle(0, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(6, 9, 10, 0),
	gsSP1Triangle(9, 11, 10, 0),
	gsSP1Triangle(9, 12, 11, 0),
	gsSP1Triangle(9, 13, 12, 0),
	gsSP1Triangle(9, 14, 13, 0),
	gsSP1Triangle(12, 5, 11, 0),
	gsSP1Triangle(12, 15, 5, 0),
	gsSPVertex(bush_Bush_mesh_vtx_0 + 16, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 1, 3, 0),
	gsSP1Triangle(4, 3, 5, 0),
	gsSP1Triangle(6, 4, 5, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSP1Triangle(5, 8, 7, 0),
	gsSP1Triangle(6, 7, 9, 0),
	gsSP1Triangle(6, 9, 10, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(10, 11, 4, 0),
	gsSP1Triangle(6, 10, 4, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSPEndDisplayList(),
};Vtx bush_Bush_mesh_vtx_1[20] = {
	{{{-213, -213, -470},0, {368, 752},{0xCC, 0x6C, 0xD6, 0xFF}}},
	{{{-233, -218, 515},0, {368, 1008},{0xB5, 0x46, 0x4C, 0xFF}}},
	{{{-213, -213, 470},0, {368, 1008},{0xCC, 0x6C, 0x2A, 0xFF}}},
	{{{-233, -218, -515},0, {368, 752},{0xB5, 0x46, 0xB4, 0xFF}}},
	{{{213, -213, -470},0, {368, 496},{0x34, 0x6C, 0xD6, 0xFF}}},
	{{{233, -218, -515},0, {368, 496},{0x4B, 0x46, 0xB4, 0xFF}}},
	{{{213, -213, 470},0, {368, 240},{0x34, 0x6C, 0x2A, 0xFF}}},
	{{{233, -218, 515},0, {368, 240},{0x4B, 0x46, 0x4C, 0xFF}}},
	{{{-213, -213, 470},0, {368, -16},{0xCC, 0x6C, 0x2A, 0xFF}}},
	{{{-233, -218, 515},0, {368, -16},{0xB5, 0x46, 0x4C, 0xFF}}},
	{{{233, -265, 515},0, {368, 240},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-233, -265, 515},0, {368, -16},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{233, -265, -515},0, {368, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-233, -265, 515},0, {112, 240},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-233, -265, -515},0, {112, 496},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-233, -265, -515},0, {368, 752},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-233, -218, -515},0, {368, 752},{0xB5, 0x46, 0xB4, 0xFF}}},
	{{{-233, -265, -515},0, {368, 752},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-233, -265, 515},0, {368, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-233, -218, 515},0, {368, 1008},{0xB5, 0x46, 0x4C, 0xFF}}},
};

Gfx bush_Bush_mesh_tri_1[] = {
	gsSPVertex(bush_Bush_mesh_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(6, 7, 5, 0),
	gsSP1Triangle(8, 7, 6, 0),
	gsSP1Triangle(8, 9, 7, 0),
	gsSP1Triangle(9, 10, 7, 0),
	gsSP1Triangle(9, 11, 10, 0),
	gsSP1Triangle(7, 10, 12, 0),
	gsSP1Triangle(12, 10, 13, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(7, 12, 5, 0),
	gsSP1Triangle(5, 12, 15, 0),
	gsSP1Triangle(5, 15, 3, 0),
	gsSPVertex(bush_Bush_mesh_vtx_1 + 16, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_bush_leaves_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(bush_leaves_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_bush_concrete_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(bush_concrete_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx bush_Bush_mesh[] = {
	gsSPDisplayList(mat_bush_leaves_f3d),
	gsSPDisplayList(bush_Bush_mesh_tri_0),
	gsSPDisplayList(mat_bush_concrete_f3d),
	gsSPDisplayList(bush_Bush_mesh_tri_1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



