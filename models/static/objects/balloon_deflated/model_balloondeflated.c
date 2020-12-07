#include <ultra64.h>

Lights1 balloon_deflated_balloon_f3d_lights = gdSPDefLights1(
	0x7F, 0x7, 0x0,
	0xFE, 0xE, 0x0, 0x28, 0x28, 0x28);

Lights1 balloon_deflated_string_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Vtx balloon_deflated_Balloon_Deflated_mesh_vtx_0[20] = {
	{{{0, -317, 12},0, {368, 1008},{0x0, 0x78, 0x29, 0xFF}}},
	{{{21, -335, 12},0, {496, 752},{0x74, 0x34, 0xFC, 0xFF}}},
	{{{0, -335, -10},0, {240, 752},{0x0, 0xB, 0x81, 0xFF}}},
	{{{0, -356, 7},0, {240, 496},{0x3, 0xBF, 0x93, 0xFF}}},
	{{{30, -356, 37},0, {496, 496},{0x6F, 0x16, 0x39, 0xFF}}},
	{{{-30, -356, 33},0, {1008, 496},{0x8B, 0x15, 0x2C, 0xFF}}},
	{{{-21, -335, 12},0, {1008, 752},{0x8D, 0x36, 0xFD, 0xFF}}},
	{{{0, -317, 12},0, {880, 1008},{0x0, 0x78, 0x29, 0xFF}}},
	{{{21, -377, 37},0, {496, 240},{0x5E, 0xB7, 0x2E, 0xFF}}},
	{{{0, -377, 16},0, {240, 240},{0x3, 0xAA, 0xA3, 0xFF}}},
	{{{0, -386, 54},0, {368, -16},{0x0, 0xCF, 0x75, 0xFF}}},
	{{{-30, -356, 33},0, {-16, 496},{0x8B, 0x15, 0x2C, 0xFF}}},
	{{{-21, -377, 37},0, {-16, 240},{0xA3, 0xBC, 0x35, 0xFF}}},
	{{{0, -386, 54},0, {112, -16},{0x0, 0xCF, 0x75, 0xFF}}},
	{{{-21, -335, 12},0, {-16, 752},{0x8D, 0x36, 0xFD, 0xFF}}},
	{{{0, -317, 12},0, {112, 1008},{0x0, 0x78, 0x29, 0xFF}}},
	{{{-30, -356, 33},0, {1008, 496},{0x8B, 0x15, 0x2C, 0xFF}}},
	{{{-21, -377, 37},0, {1008, 240},{0xA3, 0xBC, 0x35, 0xFF}}},
	{{{21, -377, 37},0, {496, 240},{0x5E, 0xB7, 0x2E, 0xFF}}},
	{{{0, -386, 54},0, {624, -16},{0x0, 0xCF, 0x75, 0xFF}}},
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
	{{{-8, 220, -25},0, {155, 240},{0x85, 0xFF, 0xE2, 0xFF}}},
	{{{0, 405, -23},0, {-16, 496},{0x1, 0x5, 0x7F, 0xFF}}},
	{{{-8, 404, -36},0, {155, 496},{0x92, 0xFC, 0xC1, 0xFF}}},
	{{{0, 33, -12},0, {-16, 240},{0x2C, 0x7, 0x77, 0xFF}}},
	{{{-8, -338, 6},0, {155, -16},{0x91, 0xFB, 0xC3, 0xFF}}},
	{{{0, -337, 19},0, {-16, -16},{0x0, 0xB, 0x7F, 0xFF}}},
	{{{8, 404, -36},0, {496, 496},{0x6E, 0xFB, 0xC1, 0xFF}}},
	{{{-8, 220, -25},0, {325, 240},{0x85, 0xFF, 0xE2, 0xFF}}},
	{{{-8, 404, -36},0, {325, 496},{0x92, 0xFC, 0xC1, 0xFF}}},
	{{{8, 33, -25},0, {496, 240},{0x56, 0xFB, 0xA2, 0xFF}}},
	{{{-8, -338, 6},0, {325, -16},{0x91, 0xFB, 0xC3, 0xFF}}},
	{{{8, -338, 6},0, {496, -16},{0x6F, 0xFB, 0xC3, 0xFF}}},
	{{{0, 33, -12},0, {837, 240},{0x2C, 0x7, 0x77, 0xFF}}},
	{{{8, 404, -36},0, {667, 496},{0x6E, 0xFB, 0xC1, 0xFF}}},
	{{{0, 405, -23},0, {837, 496},{0x1, 0x5, 0x7F, 0xFF}}},
	{{{8, 33, -25},0, {667, 240},{0x56, 0xFB, 0xA2, 0xFF}}},
	{{{0, 33, -12},0, {837, 240},{0x2C, 0x7, 0x77, 0xFF}}},
	{{{8, -338, 6},0, {667, -16},{0x6F, 0xFB, 0xC3, 0xFF}}},
	{{{8, 33, -25},0, {667, 240},{0x56, 0xFB, 0xA2, 0xFF}}},
	{{{0, -337, 19},0, {837, -16},{0x0, 0xB, 0x7F, 0xFF}}},
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



