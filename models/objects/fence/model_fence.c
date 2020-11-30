#include <ultra64.h>

Lights1 fence_fence_f3d_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx fence_fence_ci4_aligner[] = {gsSPEndDisplayList()};
u8 fence_fence_ci4[] = {
	0x0, 0x0, 0x1, 0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 
	0x0, 0x1, 0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 
	0x1, 0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 
	0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 0x22, 
	0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 0x22, 0x21, 
	0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 0x22, 0x21, 0x22, 
	0x21, 0x22, 0x0, 0x0, 0x1, 0x22, 0x21, 0x22, 0x21, 
	0x22, 0x0, 0x0, 0x1, 0x22, 0x21, 0x22, 0x21, 0x22, 
	0x0, 0x0, 0x1, 0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 
	0x0, 0x1, 0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 
	0x1, 0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 
	0x22, 0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 0x22, 
	0x21, 0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 0x22, 0x21, 
	0x22, 0x21, 0x22, 0x0, 0x0, 0x1, 0x22, 0x21, 0x22, 
	0x21, 0x22, 
};

Gfx fence_fence_ci4_pal_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 fence_fence_ci4_pal_rgba16[] = {
	0x61, 0x8B, 0x72, 0xF, 0x8A, 0x8F, 
};

Vtx fence_Fence_mesh_vtx_0[47] = {
	{{{-6, 249, -276},0, {143, 20},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-6, 249, -277},0, {-15, 15},{0xB7, 0x4B, 0xB7, 0xFF}}},
	{{{-6, -10, -281},0, {-10, 495},{0xB7, 0xB8, 0xB6, 0xFF}}},
	{{{6, -10, -281},0, {-8, 203},{0x49, 0xB8, 0xB6, 0xFF}}},
	{{{-6, -10, -281},0, {-2, 203},{0xB7, 0xB8, 0xB6, 0xFF}}},
	{{{-6, 249, -277},0, {-8, 368},{0xB7, 0x4B, 0xB7, 0xFF}}},
	{{{6, -10, -281},0, {0, 495},{0x49, 0xB8, 0xB6, 0xFF}}},
	{{{-6, 249, -277},0, {-5, 24},{0xB7, 0x4B, 0xB7, 0xFF}}},
	{{{6, 249, -276},0, {-4, 20},{0x4A, 0x49, 0xB8, 0xFF}}},
	{{{-6, 249, 32},0, {-15, 15},{0xB2, 0x32, 0x57, 0xFF}}},
	{{{-6, 263, 8},0, {5, -15},{0xB3, 0x65, 0x1, 0xFF}}},
	{{{-6, 249, -18},0, {143, 20},{0x9E, 0x4E, 0xEB, 0xFF}}},
	{{{-6, -10, 32},0, {-10, 495},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-6, -10, -147},0, {494, 495},{0xA6, 0xA6, 0x0, 0xFF}}},
	{{{-6, 249, -147},0, {494, 13},{0xA6, 0x59, 0x0, 0xFF}}},
	{{{-6, -10, -281},0, {140, 495},{0xB7, 0xB8, 0xB6, 0xFF}}},
	{{{-6, 263, 8},0, {31, 410},{0xB3, 0x65, 0x1, 0xFF}}},
	{{{6, 249, 32},0, {25, 368},{0x4E, 0x32, 0x57, 0xFF}}},
	{{{6, 263, 8},0, {25, 410},{0x4D, 0x65, 0x1, 0xFF}}},
	{{{-6, 249, 32},0, {31, 368},{0xB2, 0x32, 0x57, 0xFF}}},
	{{{-6, -10, 32},0, {31, 203},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{6, -10, 32},0, {25, 203},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-6, -10, -147},0, {20, 246},{0xA6, 0xA6, 0x0, 0xFF}}},
	{{{-6, -10, -281},0, {20, 83},{0xB7, 0xB8, 0xB6, 0xFF}}},
	{{{6, -10, -281},0, {25, 83},{0x49, 0xB8, 0xB6, 0xFF}}},
	{{{6, -10, -147},0, {25, 246},{0x5A, 0xA6, 0x0, 0xFF}}},
	{{{-6, -10, 32},0, {20, 83},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{6, -10, 32},0, {25, 83},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{6, 249, -18},0, {143, 20},{0x62, 0x4E, 0xEB, 0xFF}}},
	{{{6, 263, 8},0, {5, -15},{0x4D, 0x65, 0x1, 0xFF}}},
	{{{6, 249, 32},0, {-15, 15},{0x4E, 0x32, 0x57, 0xFF}}},
	{{{6, -10, 32},0, {-10, 495},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{6, -10, 32},0, {-10, 495},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{6, -10, -147},0, {494, 495},{0x5A, 0xA6, 0x0, 0xFF}}},
	{{{6, 249, -18},0, {143, 20},{0x62, 0x4E, 0xEB, 0xFF}}},
	{{{6, 249, -147},0, {494, 13},{0x5A, 0x59, 0x0, 0xFF}}},
	{{{6, 249, -276},0, {143, 20},{0x4A, 0x49, 0xB8, 0xFF}}},
	{{{6, -10, -281},0, {147, 495},{0x49, 0xB8, 0xB6, 0xFF}}},
	{{{-6, 249, -147},0, {14, 290},{0xA6, 0x59, 0x0, 0xFF}}},
	{{{-6, 249, -277},0, {14, 363},{0xB7, 0x4B, 0xB7, 0xFF}}},
	{{{-6, 249, -276},0, {20, 363},{0x81, 0x0, 0x0, 0xFF}}},
	{{{6, 249, -276},0, {20, 363},{0x4A, 0x49, 0xB8, 0xFF}}},
	{{{6, 249, -147},0, {20, 290},{0x5A, 0x59, 0x0, 0xFF}}},
	{{{6, 249, -18},0, {20, 363},{0x62, 0x4E, 0xEB, 0xFF}}},
	{{{-6, 249, -18},0, {14, 363},{0x9E, 0x4E, 0xEB, 0xFF}}},
	{{{6, 263, 8},0, {20, 402},{0x4D, 0x65, 0x1, 0xFF}}},
	{{{-6, 263, 8},0, {14, 402},{0xB3, 0x65, 0x1, 0xFF}}},
};

Gfx fence_Fence_mesh_tri_0[] = {
	gsSPVertex(fence_Fence_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSP1Triangle(12, 9, 11, 0),
	gsSP1Triangle(13, 12, 11, 0),
	gsSP1Triangle(14, 13, 11, 0),
	gsSP1Triangle(13, 14, 0, 0),
	gsSP1Triangle(15, 13, 0, 0),
	gsSPVertex(fence_Fence_mesh_vtx_0 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(1, 3, 4, 0),
	gsSP1Triangle(1, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(9, 10, 6, 0),
	gsSP1Triangle(9, 11, 10, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(fence_Fence_mesh_vtx_0 + 32, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(3, 1, 4, 0),
	gsSP1Triangle(1, 5, 4, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(9, 7, 6, 0),
	gsSP1Triangle(9, 6, 10, 0),
	gsSP1Triangle(6, 11, 10, 0),
	gsSP1Triangle(6, 12, 11, 0),
	gsSP1Triangle(12, 13, 11, 0),
	gsSP1Triangle(12, 14, 13, 0),
	gsSPEndDisplayList(),
};


Gfx mat_fence_fence_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_RGBA16),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fence_fence_ci4_pal_rgba16),
	gsDPTileSync(),
	gsDPSetTile(0, 0, 0, 256, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTLUTCmd(7, 2),
	gsDPPipeSync(),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b, 8, fence_fence_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 30, 60),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, 0),
	gsDPSetTileSize(0, 0, 0, 60, 60),
	gsSPSetLights1(fence_fence_f3d_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_fence_fence_f3d[] = {
	gsDPPipeSync(),
	gsDPSetTextureLUT(G_TT_NONE),
	gsSPEndDisplayList(),
};


Gfx fence_Fence_mesh[] = {
	gsSPDisplayList(mat_fence_fence_f3d),
	gsSPDisplayList(fence_Fence_mesh_tri_0),
	gsSPDisplayList(mat_revert_fence_fence_f3d),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



