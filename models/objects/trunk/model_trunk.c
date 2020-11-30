#include <ultra64.h>

Lights1 trunk_trunk_f3d_lights = gdSPDefLights1(
	0x37, 0x1D, 0xF,
	0x6F, 0x3B, 0x1E, 0x28, 0x28, 0x28);

Vtx trunk_Trunk_mesh_vtx_0[13] = {
	{{{-3, 132, -24},0, {996, -16},{0xEC, 0x4E, 0x9E, 0xFF}}},
	{{{18, 132, -17},0, {875, -16},{0x4D, 0x4E, 0xBF, 0xFF}}},
	{{{5, -109, -24},0, {973, 496},{0x16, 0xB1, 0x9F, 0xFF}}},
	{{{24, -109, -6},0, {789, 496},{0x63, 0xB3, 0xEC, 0xFF}}},
	{{{22, 132, 11},0, {667, -16},{0x57, 0x4C, 0x36, 0xFF}}},
	{{{-3, 132, -24},0, {21, -16},{0xEC, 0x4E, 0x9E, 0xFF}}},
	{{{-9, 132, 21},0, {426, -16},{0xD7, 0x4C, 0x5E, 0xFF}}},
	{{{-23, 132, -6},0, {203, -16},{0x9C, 0x4C, 0xED, 0xFF}}},
	{{{-14, -109, -18},0, {101, 496},{0xBF, 0xB0, 0xB5, 0xFF}}},
	{{{5, -109, -24},0, {3, 496},{0x16, 0xB1, 0x9F, 0xFF}}},
	{{{-13, -109, 17},0, {389, 496},{0xC5, 0xB1, 0x51, 0xFF}}},
	{{{11, -109, 21},0, {564, 496},{0x2F, 0xB4, 0x5A, 0xFF}}},
	{{{-22, -109, 0},0, {245, 496},{0x9C, 0xB1, 0x4, 0xFF}}},
};

Gfx trunk_Trunk_mesh_tri_0[] = {
	gsSPVertex(trunk_Trunk_mesh_vtx_0 + 0, 13, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(4, 1, 5, 0),
	gsSP1Triangle(5, 6, 4, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSP1Triangle(7, 5, 8, 0),
	gsSP1Triangle(5, 9, 8, 0),
	gsSP1Triangle(8, 9, 3, 0),
	gsSP1Triangle(3, 10, 8, 0),
	gsSP1Triangle(3, 11, 10, 0),
	gsSP1Triangle(4, 11, 3, 0),
	gsSP1Triangle(4, 6, 11, 0),
	gsSP1Triangle(6, 10, 11, 0),
	gsSP1Triangle(12, 10, 6, 0),
	gsSP1Triangle(12, 6, 7, 0),
	gsSP1Triangle(7, 8, 12, 0),
	gsSP1Triangle(10, 12, 8, 0),
	gsSPEndDisplayList(),
};


Gfx mat_trunk_trunk_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(trunk_trunk_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx trunk_Trunk_mesh[] = {
	gsSPDisplayList(mat_trunk_trunk_f3d),
	gsSPDisplayList(trunk_Trunk_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



