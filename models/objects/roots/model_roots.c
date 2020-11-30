#include <ultra64.h>

Lights1 roots_trunk_f3d_lights = gdSPDefLights1(
	0x37, 0x1D, 0xF,
	0x6F, 0x3B, 0x1E, 0x28, 0x28, 0x28);

Vtx roots_Roots_mesh_vtx_0[22] = {
	{{{-21, -6, -30},0, {310, 712},{0xBC, 0xF0, 0x96, 0xFF}}},
	{{{-32, -4, 18},0, {93, 712},{0x9F, 0x8, 0x51, 0xFF}}},
	{{{-6, 22, -6},0, {170, 605},{0xE5, 0x7B, 0xEF, 0xFF}}},
	{{{8, -6, 36},0, {845, 727},{0x10, 0xEF, 0x7D, 0xFF}}},
	{{{38, -10, 4},0, {658, 727},{0x7A, 0xDF, 0xA, 0xFF}}},
	{{{13, 18, 8},0, {729, 605},{0x2E, 0x72, 0x21, 0xFF}}},
	{{{6, -18, 2},0, {845, 727},{0xA, 0x82, 0x6, 0xFF}}},
	{{{-32, -4, 18},0, {993, 712},{0x9F, 0x8, 0x51, 0xFF}}},
	{{{-6, 22, -6},0, {939, 566},{0xE5, 0x7B, 0xEF, 0xFF}}},
	{{{13, 18, 8},0, {868, 605},{0x2E, 0x72, 0x21, 0xFF}}},
	{{{17, -6, -35},0, {472, 727},{0x38, 0xF0, 0x8F, 0xFF}}},
	{{{-6, 22, -6},0, {344, 586},{0xE5, 0x7B, 0xEF, 0xFF}}},
	{{{9, -13, -13},0, {484, 720},{0xD, 0x87, 0xDB, 0xFF}}},
	{{{13, 18, 8},0, {589, 605},{0x2E, 0x72, 0x21, 0xFF}}},
	{{{-6, 22, -6},0, {519, 565},{0xE5, 0x7B, 0xEF, 0xFF}}},
	{{{6, -18, 2},0, {310, 712},{0xA, 0x82, 0x6, 0xFF}}},
	{{{-38, -19, -1},0, {-16, 1008},{0x96, 0xB9, 0xFE, 0xFF}}},
	{{{-32, -4, 18},0, {-16, 1008},{0x9F, 0x8, 0x51, 0xFF}}},
	{{{-21, -6, -30},0, {310, 712},{0xBC, 0xF0, 0x96, 0xFF}}},
	{{{6, -18, 2},0, {-16, 1008},{0xA, 0x82, 0x6, 0xFF}}},
	{{{-21, -6, -30},0, {-16, 1008},{0xBC, 0xF0, 0x96, 0xFF}}},
	{{{8, -6, 36},0, {-16, 1008},{0x10, 0xEF, 0x7D, 0xFF}}},
};

Gfx roots_Roots_mesh_tri_0[] = {
	gsSPVertex(roots_Roots_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(4, 3, 6, 0),
	gsSP1Triangle(7, 3, 8, 0),
	gsSP1Triangle(8, 3, 9, 0),
	gsSP1Triangle(10, 0, 11, 0),
	gsSP1Triangle(10, 12, 0, 0),
	gsSP1Triangle(10, 4, 12, 0),
	gsSP1Triangle(4, 10, 13, 0),
	gsSP1Triangle(13, 10, 14, 0),
	gsSP1Triangle(12, 4, 15, 0),
	gsSP1Triangle(12, 15, 0, 0),
	gsSPVertex(roots_Roots_mesh_vtx_0 + 16, 6, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 1, 0, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(3, 5, 1, 0),
	gsSPEndDisplayList(),
};


Gfx mat_roots_trunk_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(roots_trunk_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx roots_Roots_mesh[] = {
	gsSPDisplayList(mat_roots_trunk_f3d),
	gsSPDisplayList(roots_Roots_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



