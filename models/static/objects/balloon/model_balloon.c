#include <ultra64.h>

Lights1 balloon_balloon_f3d_lights = gdSPDefLights1(
	0x7F, 0x2, 0x0,
	0xFE, 0x4, 0x0, 0x28, 0x28, 0x28);

Lights1 balloon_string_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx balloon_Balloon_mesh_vtx_0[27] = {
	{{{0, -213, 0},0, {624, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{0, -150, -150},0, {752, 752},{0x0, 0xB1, 0x9D, 0xFF}}},
	{{{150, -150, 0},0, {496, 752},{0x63, 0xB1, 0x0, 0xFF}}},
	{{{213, 0, 0},0, {496, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, 0, -213},0, {752, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-150, -150, 0},0, {1008, 752},{0x9D, 0xB1, 0x0, 0xFF}}},
	{{{0, -213, 0},0, {880, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-213, 0, 0},0, {1008, 496},{0x81, 0x0, 0x0, 0xFF}}},
	{{{0, 150, -150},0, {752, 240},{0x0, 0x4F, 0x9D, 0xFF}}},
	{{{-150, 150, 0},0, {1008, 240},{0x9D, 0x4F, 0x0, 0xFF}}},
	{{{0, 213, 0},0, {880, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{150, 150, 0},0, {496, 240},{0x63, 0x4F, 0x0, 0xFF}}},
	{{{0, 213, 0},0, {624, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, 150, 150},0, {240, 240},{0x0, 0x4F, 0x63, 0xFF}}},
	{{{0, 213, 0},0, {368, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, 0, 213},0, {240, 496},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, 0, 213},0, {240, 496},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{0, 150, 150},0, {240, 240},{0x0, 0x4F, 0x63, 0xFF}}},
	{{{-150, 150, 0},0, {-16, 240},{0x9D, 0x4F, 0x0, 0xFF}}},
	{{{0, 213, 0},0, {112, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-213, 0, 0},0, {-16, 496},{0x81, 0x0, 0x0, 0xFF}}},
	{{{0, -150, 150},0, {240, 752},{0x0, 0xB1, 0x63, 0xFF}}},
	{{{-150, -150, 0},0, {-16, 752},{0x9D, 0xB1, 0x0, 0xFF}}},
	{{{0, -213, 0},0, {112, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{150, -150, 0},0, {496, 752},{0x63, 0xB1, 0x0, 0xFF}}},
	{{{213, 0, 0},0, {496, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{0, -213, 0},0, {368, 1008},{0x0, 0x81, 0x0, 0xFF}}},
};

Gfx balloon_Balloon_mesh_tri_0[] = {
	gsSPVertex(balloon_Balloon_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(5, 4, 1, 0),
	gsSP1Triangle(6, 5, 1, 0),
	gsSP1Triangle(5, 7, 4, 0),
	gsSP1Triangle(7, 8, 4, 0),
	gsSP1Triangle(7, 9, 8, 0),
	gsSP1Triangle(9, 10, 8, 0),
	gsSP1Triangle(4, 8, 11, 0),
	gsSP1Triangle(8, 12, 11, 0),
	gsSP1Triangle(4, 11, 3, 0),
	gsSP1Triangle(3, 11, 13, 0),
	gsSP1Triangle(11, 14, 13, 0),
	gsSP1Triangle(3, 13, 15, 0),
	gsSPVertex(balloon_Balloon_mesh_vtx_0 + 16, 11, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(0, 2, 4, 0),
	gsSP1Triangle(5, 0, 4, 0),
	gsSP1Triangle(5, 4, 6, 0),
	gsSP1Triangle(7, 5, 6, 0),
	gsSP1Triangle(8, 0, 5, 0),
	gsSP1Triangle(8, 9, 0, 0),
	gsSP1Triangle(10, 8, 5, 0),
	gsSPEndDisplayList(),
};Vtx balloon_Balloon_mesh_vtx_1[20] = {
	{{{0, -563, 24},0, {837, 240},{0x0, 0xF9, 0x81, 0xFF}}},
	{{{0, -193, -7},0, {837, -16},{0x0, 0xF5, 0x81, 0xFF}}},
	{{{8, -192, 6},0, {667, -16},{0x6F, 0x5, 0x3D, 0xFF}}},
	{{{8, -562, 37},0, {667, 240},{0x6D, 0x4, 0x41, 0xFF}}},
	{{{0, -934, 35},0, {837, 496},{0x0, 0xFC, 0x81, 0xFF}}},
	{{{8, -934, 48},0, {667, 496},{0x6F, 0x2, 0x3E, 0xFF}}},
	{{{8, -562, 37},0, {496, 240},{0x6D, 0x4, 0x41, 0xFF}}},
	{{{8, -192, 6},0, {496, -16},{0x6F, 0x5, 0x3D, 0xFF}}},
	{{{-8, -192, 6},0, {325, -16},{0x91, 0x5, 0x3D, 0xFF}}},
	{{{-8, -562, 37},0, {325, 240},{0x93, 0x4, 0x41, 0xFF}}},
	{{{8, -934, 48},0, {496, 496},{0x6F, 0x2, 0x3E, 0xFF}}},
	{{{-8, -934, 48},0, {325, 496},{0x91, 0x2, 0x3E, 0xFF}}},
	{{{-8, -562, 37},0, {155, 240},{0x93, 0x4, 0x41, 0xFF}}},
	{{{-8, -192, 6},0, {155, -16},{0x91, 0x5, 0x3D, 0xFF}}},
	{{{0, -193, -7},0, {-16, -16},{0x0, 0xF5, 0x81, 0xFF}}},
	{{{0, -563, 24},0, {-16, 240},{0x0, 0xF9, 0x81, 0xFF}}},
	{{{-8, -934, 48},0, {155, 496},{0x91, 0x2, 0x3E, 0xFF}}},
	{{{-8, -562, 37},0, {155, 240},{0x93, 0x4, 0x41, 0xFF}}},
	{{{0, -563, 24},0, {-16, 240},{0x0, 0xF9, 0x81, 0xFF}}},
	{{{0, -934, 35},0, {-16, 496},{0x0, 0xFC, 0x81, 0xFF}}},
};

Gfx balloon_Balloon_mesh_tri_1[] = {
	gsSPVertex(balloon_Balloon_mesh_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(4, 3, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(10, 6, 9, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(balloon_Balloon_mesh_vtx_1 + 16, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};


Gfx mat_balloon_balloon_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetEnvColor(254, 250, 250, 255),
	gsSPSetLights1(balloon_balloon_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_balloon_string_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(balloon_string_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx balloon_Balloon_mesh[] = {
	gsSPSetGeometryMode(G_SHADING_SMOOTH),
	gsSPDisplayList(mat_balloon_balloon_f3d),
	gsSPDisplayList(balloon_Balloon_mesh_tri_0),
	gsSPDisplayList(mat_balloon_string_f3d),
	gsSPDisplayList(balloon_Balloon_mesh_tri_1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



