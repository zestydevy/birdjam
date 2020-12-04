#include <ultra64.h>

Lights1 plank_sm64_material_lights = gdSPDefLights1(
	0x51, 0x31, 0x1A,
	0xA2, 0x63, 0x34, 0x28, 0x28, 0x28);

Vtx plank_Plank_mesh_vtx_0[14] = {
	{{{213, 37, -1586},0, {624, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{-213, 37, -1586},0, {880, 496},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-213, 37, 1586},0, {880, 240},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{213, 37, 1586},0, {624, 240},{0x49, 0x49, 0x49, 0xFF}}},
	{{{213, -37, -1586},0, {368, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{213, -37, 1586},0, {368, 240},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-213, 37, 1586},0, {624, -16},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{-213, -37, 1586},0, {368, -16},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-213, -37, -1586},0, {112, 496},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-213, -37, 1586},0, {112, 240},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-213, -37, 1586},0, {368, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-213, 37, 1586},0, {624, 1008},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{-213, 37, -1586},0, {624, 752},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-213, -37, -1586},0, {368, 752},{0xB7, 0xB7, 0xB7, 0xFF}}},
};

Gfx plank_Plank_mesh_tri_0[] = {
	gsSPVertex(plank_Plank_mesh_vtx_0 + 0, 14, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(4, 3, 5, 0),
	gsSP1Triangle(5, 3, 6, 0),
	gsSP1Triangle(5, 6, 7, 0),
	gsSP1Triangle(8, 4, 5, 0),
	gsSP1Triangle(8, 5, 9, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 12, 13, 0),
	gsSP1Triangle(13, 12, 0, 0),
	gsSP1Triangle(13, 0, 4, 0),
	gsSPEndDisplayList(),
};


Gfx mat_plank_sm64_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(plank_sm64_material_lights),
	gsSPEndDisplayList(),
};


Gfx plank_Plank_mesh[] = {
	gsSPDisplayList(mat_plank_sm64_material),
	gsSPDisplayList(plank_Plank_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



