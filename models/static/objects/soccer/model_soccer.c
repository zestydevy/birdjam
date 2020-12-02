#include <ultra64.h>

Lights1 zedball_Material_001_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx zedball_zedball_i8_aligner[] = {gsSPEndDisplayList()};
u8 zedball_zedball_i8[] = {
	0x0, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0xFF, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0xFF, 
	0x0, 0x0, 0x0, 0xFF, 0xFF, 0x0, 0x0, 0xFF, 0x0, 
	0x0, 0x0, 0xFF, 0xFF, 0x0, 0xFF, 0xFF, 0x0, 0x0, 
	0x0, 0xFF, 0xFF, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0xFF, 0xFF, 0x0, 
	0x0, 
};

Vtx zedball_Zedball_mesh_vtx_0[45] = {
	{{{160, -160, 160},0, {132, 123},{0x4B, 0xB9, 0x4B, 0xFF}}},
	{{{266, 0, 0},0, {186, -10},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{192, 0, 192},0, {226, 108},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{202, -202, 0},0, {71, 47},{0x5A, 0xA6, 0x0, 0xFF}}},
	{{{0, -266, 0},0, {-10, 147},{0x0, 0x81, 0x0, 0xFF}}},
	{{{0, -202, 202},0, {99, 215},{0x0, 0xA6, 0x5A, 0xFF}}},
	{{{0, 0, 266},0, {226, 233},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{160, 160, 160},0, {132, 123},{0x4B, 0x47, 0x4B, 0xFF}}},
	{{{202, 202, 0},0, {71, 47},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{160, 160, -160},0, {132, 123},{0x4B, 0x47, 0xB5, 0xFF}}},
	{{{192, 0, -192},0, {226, 108},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{160, -160, -160},0, {132, 123},{0x4B, 0xB9, 0xB5, 0xFF}}},
	{{{0, -202, -202},0, {99, 215},{0x0, 0xA6, 0xA6, 0xFF}}},
	{{{-160, -160, -160},0, {132, 123},{0xB5, 0xB9, 0xB5, 0xFF}}},
	{{{-202, -202, 0},0, {71, 47},{0xA6, 0xA6, 0x0, 0xFF}}},
	{{{-160, -160, 160},0, {132, 123},{0xB5, 0xB9, 0x4B, 0xFF}}},
	{{{0, 0, 266},0, {226, 233},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-192, 0, 192},0, {226, 108},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-160, -160, 160},0, {132, 123},{0xB5, 0xB9, 0x4B, 0xFF}}},
	{{{-160, 160, 160},0, {132, 123},{0xB5, 0x47, 0x4B, 0xFF}}},
	{{{0, 202, 202},0, {99, 215},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{160, 160, 160},0, {132, 123},{0x4B, 0x47, 0x4B, 0xFF}}},
	{{{0, 266, 0},0, {-10, 147},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{202, 202, 0},0, {71, 47},{0x5A, 0x5A, 0x0, 0xFF}}},
	{{{160, 160, -160},0, {132, 123},{0x4B, 0x47, 0xB5, 0xFF}}},
	{{{0, 202, -202},0, {99, 215},{0x0, 0x5A, 0xA6, 0xFF}}},
	{{{0, 0, -266},0, {226, 233},{0x0, 0x0, 0x81, 0xFF}}},
	{{{192, 0, -192},0, {226, 108},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{160, -160, -160},0, {132, 123},{0x4B, 0xB9, 0xB5, 0xFF}}},
	{{{0, -202, -202},0, {99, 215},{0x0, 0xA6, 0xA6, 0xFF}}},
	{{{-160, -160, -160},0, {132, 123},{0xB5, 0xB9, 0xB5, 0xFF}}},
	{{{-192, 0, -192},0, {226, 108},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-160, -160, -160},0, {132, 123},{0xB5, 0xB9, 0xB5, 0xFF}}},
	{{{-266, 0, 0},0, {186, -10},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-192, 0, -192},0, {226, 108},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-202, -202, 0},0, {71, 47},{0xA6, 0xA6, 0x0, 0xFF}}},
	{{{-160, -160, 160},0, {132, 123},{0xB5, 0xB9, 0x4B, 0xFF}}},
	{{{-192, 0, 192},0, {226, 108},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-160, 160, 160},0, {132, 123},{0xB5, 0x47, 0x4B, 0xFF}}},
	{{{-202, 202, 0},0, {71, 47},{0xA6, 0x5A, 0x0, 0xFF}}},
	{{{0, 266, 0},0, {-10, 147},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{0, 202, 202},0, {99, 215},{0x0, 0x5A, 0x5A, 0xFF}}},
	{{{-160, 160, -160},0, {132, 123},{0xB5, 0x47, 0xB5, 0xFF}}},
	{{{0, 202, -202},0, {99, 215},{0x0, 0x5A, 0xA6, 0xFF}}},
	{{{0, 0, -266},0, {226, 233},{0x0, 0x0, 0x81, 0xFF}}},
};

Gfx zedball_Zedball_mesh_tri_0[] = {
	gsSPVertex(zedball_Zedball_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 0, 5, 0),
	gsSP1Triangle(6, 5, 0, 0),
	gsSP1Triangle(6, 0, 2, 0),
	gsSP1Triangle(6, 2, 7, 0),
	gsSP1Triangle(7, 2, 1, 0),
	gsSP1Triangle(7, 1, 8, 0),
	gsSP1Triangle(9, 8, 1, 0),
	gsSP1Triangle(9, 1, 10, 0),
	gsSP1Triangle(11, 10, 1, 0),
	gsSP1Triangle(11, 1, 3, 0),
	gsSP1Triangle(4, 11, 3, 0),
	gsSP1Triangle(4, 12, 11, 0),
	gsSP1Triangle(4, 13, 12, 0),
	gsSP1Triangle(4, 14, 13, 0),
	gsSP1Triangle(4, 15, 14, 0),
	gsSP1Triangle(4, 5, 15, 0),
	gsSP1Triangle(6, 15, 5, 0),
	gsSPVertex(zedball_Zedball_mesh_vtx_0 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(0, 4, 3, 0),
	gsSP1Triangle(0, 5, 4, 0),
	gsSP1Triangle(6, 4, 5, 0),
	gsSP1Triangle(6, 5, 7, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(10, 9, 8, 0),
	gsSP1Triangle(10, 8, 11, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 12, 13, 0),
	gsSP1Triangle(10, 13, 14, 0),
	gsSP1Triangle(10, 14, 15, 0),
	gsSPVertex(zedball_Zedball_mesh_vtx_0 + 32, 13, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 1, 3, 0),
	gsSP1Triangle(4, 5, 1, 0),
	gsSP1Triangle(6, 1, 5, 0),
	gsSP1Triangle(6, 7, 1, 0),
	gsSP1Triangle(8, 7, 6, 0),
	gsSP1Triangle(8, 6, 9, 0),
	gsSP1Triangle(8, 10, 7, 0),
	gsSP1Triangle(8, 11, 10, 0),
	gsSP1Triangle(12, 10, 11, 0),
	gsSP1Triangle(12, 2, 10, 0),
	gsSP1Triangle(10, 2, 1, 0),
	gsSP1Triangle(10, 1, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_zedball_Material_001_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsDPSetTextureConvert(G_TC_CONV),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b, 8, zedball_zedball_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 28, 28),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 28),
	gsSPSetLights1(zedball_Material_001_f3d_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_zedball_Material_001_f3d[] = {
	gsDPPipeSync(),
	gsDPSetTextureConvert(G_TC_FILT),
	gsSPEndDisplayList(),
};


Gfx zedball_Zedball_mesh[] = {
	gsSPDisplayList(mat_zedball_Material_001_f3d),
	gsSPDisplayList(zedball_Zedball_mesh_tri_0),
	gsSPDisplayList(mat_revert_zedball_Material_001_f3d),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



