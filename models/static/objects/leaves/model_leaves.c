#include <ultra64.h>

#include "models/ovl/world/model_world.h"

Lights1 leaves_leaves_f3d_lights = gdSPDefLights1(
	0x14, 0x28, 0xE,
	0x28, 0x51, 0x1C, 0x28, 0x28, 0x28);

Vtx leaves_Leaves_mesh_vtx_0[26] = {
	{{{21, -125, 17},0, {263, 1008},{0x14, 0x83, 0xE, 0xFF}}},
	{{{-124, -75, 5},0, {171, 863},{0x9F, 0xAE, 0xFB, 0xFF}}},
	{{{32, -75, -118},0, {436, 862},{0x17, 0xB2, 0x9F, 0xFF}}},
	{{{-82, 43, -109},0, {310, 712},{0xB4, 0x23, 0xA1, 0xFF}}},
	{{{-148, 18, 48},0, {125, 734},{0x8D, 0x1C, 0x2F, 0xFF}}},
	{{{-27, 126, -18},0, {170, 605},{0xE8, 0x7C, 0xF8, 0xFF}}},
	{{{57, 42, -129},0, {474, 725},{0x39, 0x2E, 0x98, 0xFF}}},
	{{{-27, 126, -18},0, {344, 586},{0xE8, 0x7C, 0xF8, 0xFF}}},
	{{{84, 93, 43},0, {638, 647},{0x4E, 0x5F, 0x1F, 0xFF}}},
	{{{-27, 126, -18},0, {519, 565},{0xE8, 0x7C, 0xF8, 0xFF}}},
	{{{140, -31, 14},0, {657, 803},{0x7B, 0xE2, 0xD, 0xFF}}},
	{{{30, 41, 136},0, {844, 729},{0x16, 0x2B, 0x76, 0xFF}}},
	{{{-4, -62, 120},0, {868, 847},{0xFE, 0xBE, 0x6C, 0xFF}}},
	{{{-148, 18, 48},0, {993, 712},{0x8D, 0x1C, 0x2F, 0xFF}}},
	{{{-27, 126, -18},0, {939, 566},{0xE8, 0x7C, 0xF8, 0xFF}}},
	{{{84, 93, 43},0, {868, 605},{0x4E, 0x5F, 0x1F, 0xFF}}},
	{{{21, -125, 17},0, {809, 947},{0x14, 0x83, 0xE, 0xFF}}},
	{{{140, -31, 14},0, {657, 803},{0x7B, 0xE2, 0xD, 0xFF}}},
	{{{-4, -62, 120},0, {868, 847},{0xFE, 0xBE, 0x6C, 0xFF}}},
	{{{32, -75, -118},0, {453, 862},{0x17, 0xB2, 0x9F, 0xFF}}},
	{{{57, 42, -129},0, {474, 725},{0x39, 0x2E, 0x98, 0xFF}}},
	{{{21, -125, 17},0, {636, 927},{0x14, 0x83, 0xE, 0xFF}}},
	{{{-124, -75, 5},0, {123, 880},{0x9F, 0xAE, 0xFB, 0xFF}}},
	{{{-4, -62, 120},0, {-16, 847},{0xFE, 0xBE, 0x6C, 0xFF}}},
	{{{-148, 18, 48},0, {125, 734},{0x8D, 0x1C, 0x2F, 0xFF}}},
	{{{21, -125, 17},0, {54, 967},{0x14, 0x83, 0xE, 0xFF}}},
};

Gfx leaves_Leaves_mesh_tri_0[] = {
	gsSPVertex(leaves_Leaves_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 1, 3, 0),
	gsSP1Triangle(3, 1, 4, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(2, 3, 6, 0),
	gsSP1Triangle(6, 3, 7, 0),
	gsSP1Triangle(8, 6, 9, 0),
	gsSP1Triangle(10, 6, 8, 0),
	gsSP1Triangle(11, 10, 8, 0),
	gsSP1Triangle(12, 10, 11, 0),
	gsSP1Triangle(12, 11, 13, 0),
	gsSP1Triangle(13, 11, 14, 0),
	gsSP1Triangle(14, 11, 15, 0),
	gsSPVertex(leaves_Leaves_mesh_vtx_0 + 16, 10, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 1, 0),
	gsSP1Triangle(1, 5, 3, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 7, 6, 0),
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
	gsSPDisplayList(mat_leaves_leaves_f3d),
	gsSPDisplayList(leaves_Leaves_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



