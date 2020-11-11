#include <ultra64.h>

Lights1 noodle_poolnoodle_f3d_lights = gdSPDefLights1(
	0xD, 0x7F, 0x1F,
	0x1B, 0xFE, 0x3F, 0x28, 0x28, 0x28);

Gfx noodle_poolnoodle_i4_aligner[] = {gsSPEndDisplayList()};
u8 noodle_poolnoodle_i4[] = {
	0xBA, 0xB8, 0xA7, 0xBB, 0x9B, 0x9B, 0xAB, 0xBB, 0xA9, 
	0xBB, 0xAA, 0xBB, 0x9B, 0xAB, 0xBB, 0xBB, 0xBA, 0xAA, 
	0x9A, 0xB, 0xB9, 0x9B, 0xBA, 0xBB, 0xAB, 0xB7, 0xBA, 
	0xB, 0xA9, 0x97, 0xAB, 0xBB, 
};

Vtx noodle_Noodle_mesh_vtx_0[28] = {
	{{{120, 148, -2153},0, {154, 171},{0x56, 0x34, 0xB3, 0xFF}}},
	{{{120, 4, -2153},0, {154, 215},{0x56, 0xCC, 0xB3, 0xFF}}},
	{{{0, -59, -2153},0, {191, 235},{0x0, 0x9C, 0xB2, 0xFF}}},
	{{{0, 210, -2153},0, {191, 152},{0x0, 0x64, 0xB2, 0xFF}}},
	{{{-120, 148, -2153},0, {228, 171},{0xAA, 0x34, 0xB3, 0xFF}}},
	{{{-120, 4, -2153},0, {228, 215},{0xAA, 0xCC, 0xB3, 0xFF}}},
	{{{0, 210, 2153},0, {191, 151},{0x0, 0x64, 0x4E, 0xFF}}},
	{{{120, 4, 2153},0, {228, 215},{0x56, 0xCC, 0x4D, 0xFF}}},
	{{{120, 148, 2153},0, {228, 171},{0x56, 0x34, 0x4D, 0xFF}}},
	{{{0, -59, 2153},0, {191, 234},{0x0, 0x9C, 0x4E, 0xFF}}},
	{{{-120, 4, 2153},0, {154, 215},{0xAA, 0xCC, 0x4D, 0xFF}}},
	{{{-120, 148, 2153},0, {154, 171},{0xAA, 0x34, 0x4D, 0xFF}}},
	{{{0, -59, -2153},0, {-16, 240},{0x0, 0x9C, 0xB2, 0xFF}}},
	{{{0, -59, 2153},0, {161, 240},{0x0, 0x9C, 0x4E, 0xFF}}},
	{{{-120, 4, 2153},0, {161, 198},{0xAA, 0xCC, 0x4D, 0xFF}}},
	{{{-120, 4, -2153},0, {-16, 198},{0xAA, 0xCC, 0xB3, 0xFF}}},
	{{{-120, 4, -2153},0, {-16, 198},{0xAA, 0xCC, 0xB3, 0xFF}}},
	{{{-120, 4, 2153},0, {161, 198},{0xAA, 0xCC, 0x4D, 0xFF}}},
	{{{-120, 148, 2153},0, {161, 154},{0xAA, 0x34, 0x4D, 0xFF}}},
	{{{-120, 148, -2153},0, {-16, 154},{0xAA, 0x34, 0xB3, 0xFF}}},
	{{{0, 210, 2153},0, {161, 112},{0x0, 0x64, 0x4E, 0xFF}}},
	{{{0, 210, -2153},0, {-16, 112},{0x0, 0x64, 0xB2, 0xFF}}},
	{{{120, 148, -2153},0, {-16, 70},{0x56, 0x34, 0xB3, 0xFF}}},
	{{{120, 148, 2153},0, {161, 70},{0x56, 0x34, 0x4D, 0xFF}}},
	{{{120, 4, -2153},0, {-16, 26},{0x56, 0xCC, 0xB3, 0xFF}}},
	{{{120, 4, 2153},0, {161, 26},{0x56, 0xCC, 0x4D, 0xFF}}},
	{{{0, -59, -2153},0, {-16, -16},{0x0, 0x9C, 0xB2, 0xFF}}},
	{{{0, -59, 2153},0, {161, -16},{0x0, 0x9C, 0x4E, 0xFF}}},
};

Gfx noodle_Noodle_mesh_tri_0[] = {
	gsSPVertex(noodle_Noodle_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 3, 2, 0),
	gsSP1Triangle(4, 2, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 9, 7, 0),
	gsSP1Triangle(6, 10, 9, 0),
	gsSP1Triangle(6, 11, 10, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(noodle_Noodle_mesh_vtx_0 + 16, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(3, 2, 4, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(6, 4, 7, 0),
	gsSP1Triangle(8, 6, 7, 0),
	gsSP1Triangle(8, 7, 9, 0),
	gsSP1Triangle(10, 8, 9, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSPEndDisplayList(),
};


Gfx mat_noodle_poolnoodle_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 4, noodle_poolnoodle_i4),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 14, 28),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 28),
	gsSPSetLights1(noodle_poolnoodle_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx noodle_Noodle_mesh[] = {
	gsSPDisplayList(mat_noodle_poolnoodle_f3d),
	gsSPDisplayList(noodle_Noodle_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



