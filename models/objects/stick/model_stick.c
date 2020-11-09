#include <ultra64.h>

Lights1 stick_Wood_f3d_lights = gdSPDefLights1(
	0x47, 0x28, 0x12,
	0x8F, 0x50, 0x24, 0x28, 0x28, 0x28);

Vtx stick_Stick1_mesh_vtx_0[19] = {
	{{{-281, -23, 29},0, {368, 1008},{0x9B, 0xB7, 0x1A, 0xFF}}},
	{{{-281, 23, 29},0, {624, 1008},{0xB4, 0x57, 0x34, 0xFF}}},
	{{{-241, -23, -29},0, {368, 752},{0xE1, 0xF3, 0x85, 0xFF}}},
	{{{144, -23, 29},0, {368, 240},{0x13, 0x99, 0x47, 0xFF}}},
	{{{-281, 23, 29},0, {624, -16},{0xB4, 0x57, 0x34, 0xFF}}},
	{{{-281, -23, 29},0, {368, -16},{0x9B, 0xB7, 0x1A, 0xFF}}},
	{{{144, 23, 29},0, {624, 240},{0x16, 0x5C, 0x55, 0xFF}}},
	{{{254, -23, -26},0, {368, 240},{0x3C, 0x93, 0x18, 0xFF}}},
	{{{283, 23, -83},0, {368, 496},{0x56, 0x16, 0xA6, 0xFF}}},
	{{{144, 23, -29},0, {368, 496},{0xE5, 0x23, 0x89, 0xFF}}},
	{{{-241, -23, -29},0, {112, 496},{0xE1, 0xF3, 0x85, 0xFF}}},
	{{{-281, -23, 29},0, {112, 240},{0x9B, 0xB7, 0x1A, 0xFF}}},
	{{{254, 23, -26},0, {624, 240},{0x44, 0x51, 0x45, 0xFF}}},
	{{{283, 23, -83},0, {624, 496},{0x56, 0x16, 0xA6, 0xFF}}},
	{{{144, 23, -29},0, {624, 496},{0xE5, 0x23, 0x89, 0xFF}}},
	{{{-281, 23, 29},0, {880, 240},{0xB4, 0x57, 0x34, 0xFF}}},
	{{{144, 23, -29},0, {624, 496},{0xE5, 0x23, 0x89, 0xFF}}},
	{{{-241, -23, -29},0, {880, 496},{0xE1, 0xF3, 0x85, 0xFF}}},
	{{{-281, 23, 29},0, {880, 240},{0xB4, 0x57, 0x34, 0xFF}}},
};

Gfx stick_Stick1_mesh_tri_0[] = {
	gsSPVertex(stick_Stick1_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(3, 6, 4, 0),
	gsSP1Triangle(6, 3, 7, 0),
	gsSP1Triangle(3, 8, 7, 0),
	gsSP1Triangle(3, 9, 8, 0),
	gsSP1Triangle(10, 9, 3, 0),
	gsSP1Triangle(10, 3, 11, 0),
	gsSP1Triangle(6, 7, 12, 0),
	gsSP1Triangle(13, 12, 7, 0),
	gsSP1Triangle(14, 12, 13, 0),
	gsSP1Triangle(14, 6, 12, 0),
	gsSP1Triangle(14, 15, 6, 0),
	gsSPVertex(stick_Stick1_mesh_vtx_0 + 16, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};


Gfx mat_stick_Wood_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(stick_Wood_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx stick_Stick1_mesh[] = {
	gsSPDisplayList(mat_stick_Wood_f3d),
	gsSPDisplayList(stick_Stick1_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



