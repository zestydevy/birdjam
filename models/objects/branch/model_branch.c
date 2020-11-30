#include <ultra64.h>

Lights1 branch_trunk_f3d_lights = gdSPDefLights1(
	0x37, 0x1D, 0xF,
	0x6F, 0x3B, 0x1E, 0x28, 0x28, 0x28);

Vtx branch_Branch_mesh_vtx_0[12] = {
	{{{0, 346, -2},0, {875, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{23, -224, -5},0, {789, 496},{0x66, 0xB7, 0xEC, 0xFF}}},
	{{{4, -224, -22},0, {973, 496},{0x16, 0xB4, 0x9D, 0xFF}}},
	{{{0, 346, -2},0, {667, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{10, -224, 22},0, {564, 496},{0x30, 0xB7, 0x5C, 0xFF}}},
	{{{-14, -224, 18},0, {389, 496},{0xC5, 0xB3, 0x53, 0xFF}}},
	{{{0, 346, -2},0, {426, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-23, -224, 1},0, {245, 496},{0x9B, 0xB4, 0x3, 0xFF}}},
	{{{-15, -224, -17},0, {101, 496},{0xBD, 0xB3, 0xB5, 0xFF}}},
	{{{0, 346, -2},0, {203, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{4, -224, -22},0, {3, 496},{0x16, 0xB4, 0x9D, 0xFF}}},
	{{{0, 346, -2},0, {21, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx branch_Branch_mesh_tri_0[] = {
	gsSPVertex(branch_Branch_mesh_vtx_0 + 0, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 1, 0),
	gsSP1Triangle(1, 4, 5, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(7, 5, 6, 0),
	gsSP1Triangle(5, 7, 8, 0),
	gsSP1Triangle(9, 8, 7, 0),
	gsSP1Triangle(8, 10, 5, 0),
	gsSP1Triangle(11, 10, 8, 0),
	gsSP1Triangle(10, 1, 5, 0),
	gsSPEndDisplayList(),
};


Gfx mat_branch_trunk_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(branch_trunk_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx branch_Branch_mesh[] = {
	gsSPDisplayList(mat_branch_trunk_f3d),
	gsSPDisplayList(branch_Branch_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



