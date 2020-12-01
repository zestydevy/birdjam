#include <ultra64.h>

Lights1 balloon_deflated_balloon_f3d_lights = gdSPDefLights1(
	0x7F, 0x7, 0x0,
	0xFE, 0xE, 0x0, 0x28, 0x28, 0x28);

Lights1 balloon_deflated_string_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx balloon_deflated_Balloon_Deflated_mesh_vtx_0[20] = {
	{{{0, -25, 0},0, {368, 1008},{0x0, 0x88, 0xD7, 0xFF}}},
	{{{21, -7, 0},0, {496, 752},{0x74, 0xCC, 0x4, 0xFF}}},
	{{{0, -7, 21},0, {240, 752},{0x0, 0xF5, 0x7F, 0xFF}}},
	{{{0, 14, 5},0, {240, 496},{0x3, 0x41, 0x6D, 0xFF}}},
	{{{30, 14, -25},0, {496, 496},{0x6F, 0xEA, 0xC7, 0xFF}}},
	{{{-30, 14, -21},0, {1008, 496},{0x8B, 0xEB, 0xD4, 0xFF}}},
	{{{-21, -7, 0},0, {1008, 752},{0x8D, 0xCA, 0x3, 0xFF}}},
	{{{0, -25, 0},0, {880, 1008},{0x0, 0x88, 0xD7, 0xFF}}},
	{{{21, 35, -25},0, {496, 240},{0x5E, 0x49, 0xD2, 0xFF}}},
	{{{0, 35, -4},0, {240, 240},{0x3, 0x56, 0x5D, 0xFF}}},
	{{{0, 44, -42},0, {368, -16},{0x0, 0x31, 0x8B, 0xFF}}},
	{{{-30, 14, -21},0, {-16, 496},{0x8B, 0xEB, 0xD4, 0xFF}}},
	{{{-21, 35, -25},0, {-16, 240},{0xA3, 0x44, 0xCB, 0xFF}}},
	{{{0, 44, -42},0, {112, -16},{0x0, 0x31, 0x8B, 0xFF}}},
	{{{-21, -7, 0},0, {-16, 752},{0x8D, 0xCA, 0x3, 0xFF}}},
	{{{0, -25, 0},0, {112, 1008},{0x0, 0x88, 0xD7, 0xFF}}},
	{{{-30, 14, -21},0, {1008, 496},{0x8B, 0xEB, 0xD4, 0xFF}}},
	{{{-21, 35, -25},0, {1008, 240},{0xA3, 0x44, 0xCB, 0xFF}}},
	{{{21, 35, -25},0, {496, 240},{0x5E, 0x49, 0xD2, 0xFF}}},
	{{{0, 44, -42},0, {624, -16},{0x0, 0x31, 0x8B, 0xFF}}},
};

Gfx balloon_deflated_Balloon_Deflated_mesh_tri_0[] = {
	gsSPVertex(balloon_deflated_Balloon_Deflated_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(1, 4, 3, 0),
	gsSP1Triangle(4, 1, 5, 0),
	gsSP1Triangle(6, 5, 1, 0),
	gsSP1Triangle(7, 6, 1, 0),
	gsSP1Triangle(8, 4, 5, 0),
	gsSP1Triangle(4, 8, 9, 0),
	gsSP1Triangle(8, 10, 9, 0),
	gsSP1Triangle(4, 9, 3, 0),
	gsSP1Triangle(9, 11, 3, 0),
	gsSP1Triangle(9, 12, 11, 0),
	gsSP1Triangle(9, 13, 12, 0),
	gsSP1Triangle(3, 11, 14, 0),
	gsSP1Triangle(3, 14, 2, 0),
	gsSP1Triangle(15, 2, 14, 0),
	gsSPVertex(balloon_deflated_Balloon_Deflated_mesh_vtx_0 + 16, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSPEndDisplayList(),
};Vtx balloon_deflated_Balloon_Deflated_mesh_vtx_1[20] = {
	{{{-8, -562, 37},0, {155, 240},{0x85, 0x1, 0x1E, 0xFF}}},
	{{{0, -747, 35},0, {-16, 496},{0x1, 0xFB, 0x81, 0xFF}}},
	{{{-8, -746, 48},0, {155, 496},{0x92, 0x4, 0x3F, 0xFF}}},
	{{{0, -376, 24},0, {-16, 240},{0x2C, 0xF9, 0x89, 0xFF}}},
	{{{-8, -5, 6},0, {155, -16},{0x91, 0x5, 0x3D, 0xFF}}},
	{{{0, -5, -7},0, {-16, -16},{0x0, 0xF5, 0x81, 0xFF}}},
	{{{8, -746, 48},0, {496, 496},{0x6E, 0x5, 0x3F, 0xFF}}},
	{{{-8, -562, 37},0, {325, 240},{0x85, 0x1, 0x1E, 0xFF}}},
	{{{-8, -746, 48},0, {325, 496},{0x92, 0x4, 0x3F, 0xFF}}},
	{{{8, -375, 37},0, {496, 240},{0x56, 0x5, 0x5E, 0xFF}}},
	{{{-8, -5, 6},0, {325, -16},{0x91, 0x5, 0x3D, 0xFF}}},
	{{{8, -5, 6},0, {496, -16},{0x6F, 0x5, 0x3D, 0xFF}}},
	{{{0, -376, 24},0, {837, 240},{0x2C, 0xF9, 0x89, 0xFF}}},
	{{{8, -746, 48},0, {667, 496},{0x6E, 0x5, 0x3F, 0xFF}}},
	{{{0, -747, 35},0, {837, 496},{0x1, 0xFB, 0x81, 0xFF}}},
	{{{8, -375, 37},0, {667, 240},{0x56, 0x5, 0x5E, 0xFF}}},
	{{{0, -376, 24},0, {837, 240},{0x2C, 0xF9, 0x89, 0xFF}}},
	{{{8, -5, 6},0, {667, -16},{0x6F, 0x5, 0x3D, 0xFF}}},
	{{{8, -375, 37},0, {667, 240},{0x56, 0x5, 0x5E, 0xFF}}},
	{{{0, -5, -7},0, {837, -16},{0x0, 0xF5, 0x81, 0xFF}}},
};

Gfx balloon_deflated_Balloon_Deflated_mesh_tri_1[] = {
	gsSPVertex(balloon_deflated_Balloon_Deflated_mesh_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 9, 7, 0),
	gsSP1Triangle(9, 10, 7, 0),
	gsSP1Triangle(9, 11, 10, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 15, 13, 0),
	gsSPVertex(balloon_deflated_Balloon_Deflated_mesh_vtx_1 + 16, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPEndDisplayList(),
};


Gfx mat_balloon_deflated_balloon_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(balloon_deflated_balloon_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_balloon_deflated_string_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(balloon_deflated_string_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx balloon_deflated_Balloon_Deflated_mesh[] = {
	gsSPDisplayList(mat_balloon_deflated_balloon_f3d),
	gsSPDisplayList(balloon_deflated_Balloon_Deflated_mesh_tri_0),
	gsSPDisplayList(mat_balloon_deflated_string_f3d),
	gsSPDisplayList(balloon_deflated_Balloon_Deflated_mesh_tri_1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



