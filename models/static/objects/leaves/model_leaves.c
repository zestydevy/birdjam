#include <ultra64.h>

#include "models/ovl/world/model_world.h"

Lights1 leaves_leaves_f3d_lights = gdSPDefLights1(
	0x14, 0x28, 0xE,
	0x28, 0x51, 0x1C, 0x28, 0x28, 0x28);

Vtx leaves_Leaves_mesh_vtx_0[39] = {
	{{{21, -125, 17},0, {473, 966},{0x13, 0x83, 0xF, 0xFF}}},
	{{{-35, -83, -99},0, {380, 888},{0xE1, 0xAC, 0xA5, 0xFF}}},
	{{{69, -62, -99},0, {495, 847},{0x47, 0xBC, 0xB0, 0xFF}}},
	{{{21, -125, 17},0, {263, 1008},{0x13, 0x83, 0xF, 0xFF}}},
	{{{-99, -86, -34},0, {240, 887},{0xAF, 0xA5, 0xDC, 0xFF}}},
	{{{-35, -83, -99},0, {333, 888},{0xE1, 0xAC, 0xA5, 0xFF}}},
	{{{-82, 43, -109},0, {310, 712},{0xB8, 0x2D, 0xA2, 0xFF}}},
	{{{-145, -6, -1},0, {170, 766},{0x82, 0x4, 0xF0, 0xFF}}},
	{{{-118, -62, 36},0, {123, 847},{0xA5, 0xB7, 0x32, 0xFF}}},
	{{{-124, 43, 70},0, {93, 712},{0x9F, 0x31, 0x42, 0xFF}}},
	{{{-4, -62, 120},0, {-16, 847},{0xF6, 0xBD, 0x6B, 0xFF}}},
	{{{21, -125, 17},0, {54, 967},{0x13, 0x83, 0xF, 0xFF}}},
	{{{-99, -86, -34},0, {124, 927},{0xAF, 0xA5, 0xDC, 0xFF}}},
	{{{-27, 126, -18},0, {170, 605},{0xE4, 0x7B, 0xEE, 0xFF}}},
	{{{-3, 62, 120},0, {869, 686},{0xF6, 0x42, 0x6C, 0xFF}}},
	{{{112, 62, 36},0, {683, 686},{0x65, 0x43, 0x26, 0xFF}}},
	{{{43, 114, 33},0, {729, 605},{0x29, 0x75, 0x1D, 0xFF}}},
	{{{41, 7, 134},0, {822, 766},{0x2A, 0x5, 0x78, 0xFF}}},
	{{{-124, 43, 70},0, {993, 712},{0x9F, 0x31, 0x42, 0xFF}}},
	{{{-27, 126, -18},0, {939, 566},{0xE4, 0x7B, 0xEE, 0xFF}}},
	{{{43, 114, 33},0, {868, 605},{0x29, 0x75, 0x1D, 0xFF}}},
	{{{-4, -62, 120},0, {868, 847},{0xF6, 0xBD, 0x6B, 0xFF}}},
	{{{112, -62, 37},0, {682, 847},{0x65, 0xBD, 0x26, 0xFF}}},
	{{{21, -125, 17},0, {809, 947},{0x13, 0x83, 0xF, 0xFF}}},
	{{{139, 7, -1},0, {636, 766},{0x7F, 0x5, 0xFB, 0xFF}}},
	{{{69, -62, -99},0, {495, 847},{0x47, 0xBC, 0xB0, 0xFF}}},
	{{{21, -125, 17},0, {636, 927},{0x13, 0x83, 0xF, 0xFF}}},
	{{{41, 7, -136},0, {449, 766},{0x24, 0x7, 0x86, 0xFF}}},
	{{{-35, -83, -99},0, {333, 888},{0xE1, 0xAC, 0xA5, 0xFF}}},
	{{{-82, 43, -109},0, {310, 712},{0xB8, 0x2D, 0xA2, 0xFF}}},
	{{{41, 7, -136},0, {449, 766},{0x24, 0x7, 0x86, 0xFF}}},
	{{{-82, 43, -109},0, {310, 712},{0xB8, 0x2D, 0xA2, 0xFF}}},
	{{{68, 62, -99},0, {497, 686},{0x41, 0x47, 0xAE, 0xFF}}},
	{{{-27, 126, -18},0, {344, 586},{0xE4, 0x7B, 0xEE, 0xFF}}},
	{{{139, 7, -1},0, {636, 766},{0x7F, 0x5, 0xFB, 0xFF}}},
	{{{112, 62, 36},0, {683, 686},{0x65, 0x43, 0x26, 0xFF}}},
	{{{43, 114, 33},0, {589, 605},{0x29, 0x75, 0x1D, 0xFF}}},
	{{{-27, 126, -18},0, {519, 565},{0xE4, 0x7B, 0xEE, 0xFF}}},
	{{{41, 7, 134},0, {822, 766},{0x2A, 0x5, 0x78, 0xFF}}},
};

Gfx leaves_Leaves_mesh_tri_0[] = {
	gsSPVertex(leaves_Leaves_mesh_vtx_0 + 0, 14, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(5, 4, 6, 0),
	gsSP1Triangle(6, 4, 7, 0),
	gsSP1Triangle(4, 8, 7, 0),
	gsSP1Triangle(7, 8, 9, 0),
	gsSP1Triangle(8, 10, 9, 0),
	gsSP1Triangle(11, 10, 8, 0),
	gsSP1Triangle(12, 11, 8, 0),
	gsSP1Triangle(7, 9, 6, 0),
	gsSP1Triangle(6, 9, 13, 0),
	gsSPVertex(leaves_Leaves_mesh_vtx_0 + 14, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 1, 0, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 0, 5, 0),
	gsSP1Triangle(5, 0, 6, 0),
	gsSP1Triangle(7, 3, 4, 0),
	gsSP1Triangle(7, 8, 3, 0),
	gsSP1Triangle(9, 8, 7, 0),
	gsSP1Triangle(8, 10, 3, 0),
	gsSP1Triangle(8, 11, 10, 0),
	gsSP1Triangle(8, 12, 11, 0),
	gsSP1Triangle(11, 13, 10, 0),
	gsSP1Triangle(11, 14, 13, 0),
	gsSP1Triangle(14, 15, 13, 0),
	gsSPVertex(leaves_Leaves_mesh_vtx_0 + 30, 9, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 1, 3, 0),
	gsSP1Triangle(4, 0, 2, 0),
	gsSP1Triangle(4, 2, 5, 0),
	gsSP1Triangle(5, 2, 6, 0),
	gsSP1Triangle(6, 2, 7, 0),
	gsSP1Triangle(8, 4, 5, 0),
	gsSPEndDisplayList(),
};


Gfx mat_leaves_leaves_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(leaves_leaves_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx leaves_Leaves_mesh[] = {
	gsSPDisplayList(mat_world_leaves_f3d),
	gsSPDisplayList(leaves_Leaves_mesh_tri_0),
	gsSPDisplayList(mat_revert_world_leaves_f3d),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



