#include <ultra64.h>

Lights1 mailbox_metal_f3d_lights = gdSPDefLights1(
	0x27, 0x2A, 0x33,
	0x4F, 0x55, 0x67, 0x28, 0x28, 0x28);

Lights1 mailbox_post_f3d_lights = gdSPDefLights1(
	0x45, 0x40, 0x37,
	0x8A, 0x81, 0x6F, 0x28, 0x28, 0x28);

Lights1 mailbox_flag_f3d_lights = gdSPDefLights1(
	0x7F, 0x0, 0x3,
	0xFE, 0x0, 0x6, 0x28, 0x28, 0x28);

Vtx mailbox_Mailbox_mesh_vtx_0[41] = {
	{{{20, 179, 20},0, {624, 240},{0x2D, 0x92, 0x2E, 0xFF}}},
	{{{61, 184, -164},0, {624, 496},{0x4A, 0xB8, 0xB5, 0xFF}}},
	{{{61, 184, 58},0, {624, 240},{0x4B, 0xBB, 0x4B, 0xFF}}},
	{{{20, 179, -20},0, {624, 496},{0x2F, 0x91, 0xD9, 0xFF}}},
	{{{-20, 179, -20},0, {624, 752},{0xD1, 0x91, 0xD9, 0xFF}}},
	{{{0, 184, -164},0, {624, 624},{0x0, 0xA8, 0xA5, 0xFF}}},
	{{{-61, 184, -164},0, {624, 752},{0xB6, 0xB8, 0xB5, 0xFF}}},
	{{{-61, 184, 58},0, {624, 880},{0xB5, 0xBB, 0x4B, 0xFF}}},
	{{{-20, 179, 20},0, {624, 1008},{0xD3, 0x92, 0x2E, 0xFF}}},
	{{{-61, 260, 58},0, {624, 880},{0xA3, 0x15, 0x54, 0xFF}}},
	{{{-61, 260, -164},0, {624, 752},{0xA3, 0x15, 0xAC, 0xFF}}},
	{{{-41, 305, 58},0, {624, 880},{0xC0, 0x4B, 0x4F, 0xFF}}},
	{{{-41, 305, -164},0, {624, 752},{0xC0, 0x4B, 0xB1, 0xFF}}},
	{{{0, 316, -164},0, {624, 624},{0x0, 0x60, 0xAD, 0xFF}}},
	{{{61, 260, -164},0, {624, 496},{0x5D, 0x15, 0xAC, 0xFF}}},
	{{{41, 305, -164},0, {624, 496},{0x40, 0x4B, 0xB1, 0xFF}}},
	{{{61, 260, 58},0, {624, 368},{0x5D, 0x15, 0x54, 0xFF}}},
	{{{61, 260, -164},0, {624, 496},{0x5D, 0x15, 0xAC, 0xFF}}},
	{{{41, 305, -164},0, {624, 496},{0x40, 0x4B, 0xB1, 0xFF}}},
	{{{41, 305, 58},0, {624, 368},{0x40, 0x4B, 0x4F, 0xFF}}},
	{{{0, 316, 58},0, {752, 368},{0x0, 0x60, 0x53, 0xFF}}},
	{{{0, 316, -164},0, {752, 496},{0x0, 0x60, 0xAD, 0xFF}}},
	{{{-41, 305, 58},0, {880, 368},{0xC0, 0x4B, 0x4F, 0xFF}}},
	{{{-41, 305, -164},0, {880, 496},{0xC0, 0x4B, 0xB1, 0xFF}}},
	{{{61, 184, 58},0, {624, 368},{0x4B, 0xBB, 0x4B, 0xFF}}},
	{{{61, 184, -164},0, {624, 496},{0x4A, 0xB8, 0xB5, 0xFF}}},
	{{{0, 184, -164},0, {624, 624},{0x0, 0xA8, 0xA5, 0xFF}}},
	{{{-61, 184, -164},0, {624, 752},{0xB6, 0xB8, 0xB5, 0xFF}}},
	{{{-61, 260, -164},0, {624, 752},{0xA3, 0x15, 0xAC, 0xFF}}},
	{{{0, 316, 58},0, {624, 112},{0x0, 0x60, 0x53, 0xFF}}},
	{{{61, 260, 58},0, {624, 240},{0x5D, 0x15, 0x54, 0xFF}}},
	{{{41, 305, 58},0, {624, 240},{0x40, 0x4B, 0x4F, 0xFF}}},
	{{{61, 184, 58},0, {624, 240},{0x4B, 0xBB, 0x4B, 0xFF}}},
	{{{61, 260, 58},0, {624, 240},{0x5D, 0x15, 0x54, 0xFF}}},
	{{{0, 316, 58},0, {624, 112},{0x0, 0x60, 0x53, 0xFF}}},
	{{{-61, 260, 58},0, {624, -16},{0xA3, 0x15, 0x54, 0xFF}}},
	{{{-41, 305, 58},0, {624, -16},{0xC0, 0x4B, 0x4F, 0xFF}}},
	{{{-61, 184, 58},0, {624, -16},{0xB5, 0xBB, 0x4B, 0xFF}}},
	{{{61, 184, 58},0, {624, 112},{0x4B, 0xBB, 0x4B, 0xFF}}},
	{{{-20, 179, 20},0, {624, -16},{0xD3, 0x92, 0x2E, 0xFF}}},
	{{{20, 179, 20},0, {624, 240},{0x2D, 0x92, 0x2E, 0xFF}}},
};

Gfx mailbox_Mailbox_mesh_tri_0[] = {
	gsSPVertex(mailbox_Mailbox_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(1, 3, 4, 0),
	gsSP1Triangle(4, 5, 1, 0),
	gsSP1Triangle(4, 6, 5, 0),
	gsSP1Triangle(4, 7, 6, 0),
	gsSP1Triangle(4, 8, 7, 0),
	gsSP1Triangle(6, 7, 9, 0),
	gsSP1Triangle(6, 9, 10, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(13, 10, 12, 0),
	gsSP1Triangle(5, 10, 13, 0),
	gsSP1Triangle(1, 5, 13, 0),
	gsSP1Triangle(1, 13, 14, 0),
	gsSP1Triangle(14, 13, 15, 0),
	gsSPVertex(mailbox_Mailbox_mesh_vtx_0 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(2, 4, 3, 0),
	gsSP1Triangle(2, 5, 4, 0),
	gsSP1Triangle(5, 6, 4, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSP1Triangle(8, 1, 0, 0),
	gsSP1Triangle(8, 9, 1, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(13, 14, 15, 0),
	gsSPVertex(mailbox_Mailbox_mesh_vtx_0 + 32, 9, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 2, 4, 0),
	gsSP1Triangle(5, 2, 3, 0),
	gsSP1Triangle(5, 6, 2, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(7, 8, 6, 0),
	gsSPEndDisplayList(),
};Vtx mailbox_Mailbox_mesh_vtx_1[12] = {
	{{{20, -247, 20},0, {368, 240},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-20, 179, 20},0, {624, -16},{0xD3, 0x92, 0x2E, 0xFF}}},
	{{{-20, -247, 20},0, {368, -16},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{20, 179, 20},0, {624, 240},{0x2D, 0x92, 0x2E, 0xFF}}},
	{{{20, -247, -20},0, {368, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-20, -247, -20},0, {112, 496},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-20, -247, 20},0, {112, 240},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{20, 179, -20},0, {624, 496},{0x2F, 0x91, 0xD9, 0xFF}}},
	{{{-20, -247, -20},0, {368, 752},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-20, 179, -20},0, {624, 752},{0xD1, 0x91, 0xD9, 0xFF}}},
	{{{-20, -247, 20},0, {368, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-20, 179, 20},0, {624, 1008},{0xD3, 0x92, 0x2E, 0xFF}}},
};

Gfx mailbox_Mailbox_mesh_tri_1[] = {
	gsSPVertex(mailbox_Mailbox_mesh_vtx_1 + 0, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(5, 4, 0, 0),
	gsSP1Triangle(5, 0, 6, 0),
	gsSP1Triangle(4, 7, 3, 0),
	gsSP1Triangle(8, 7, 4, 0),
	gsSP1Triangle(8, 9, 7, 0),
	gsSP1Triangle(10, 9, 8, 0),
	gsSP1Triangle(10, 11, 9, 0),
	gsSPEndDisplayList(),
};Vtx mailbox_Mailbox_mesh_vtx_2[7] = {
	{{{-64, 255, -89},0, {-16, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-64, 232, -89},0, {1008, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-64, 232, -31},0, {1008, -16},{0x81, 0xFF, 0x2, 0xFF}}},
	{{{-64, 255, -31},0, {-16, -16},{0x81, 0xFF, 0x1, 0xFF}}},
	{{{-63, 255, 1},0, {-16, -16},{0x81, 0xFF, 0x2, 0xFF}}},
	{{{-63, 216, 2},0, {496, -16},{0x81, 0xFF, 0x2, 0xFF}}},
	{{{-63, 216, -31},0, {1008, -16},{0x81, 0xFF, 0x2, 0xFF}}},
};

Gfx mailbox_Mailbox_mesh_tri_2[] = {
	gsSPVertex(mailbox_Mailbox_mesh_vtx_2 + 0, 7, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 3, 2, 0),
	gsSP1Triangle(2, 5, 4, 0),
	gsSP1Triangle(2, 6, 5, 0),
	gsSPEndDisplayList(),
};


Gfx mat_mailbox_metal_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(mailbox_metal_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_mailbox_post_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(mailbox_post_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_mailbox_flag_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(mailbox_flag_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mailbox_Mailbox_mesh[] = {
	gsSPDisplayList(mat_mailbox_metal_f3d),
	gsSPDisplayList(mailbox_Mailbox_mesh_tri_0),
	gsSPDisplayList(mat_mailbox_post_f3d),
	gsSPDisplayList(mailbox_Mailbox_mesh_tri_1),
	gsSPDisplayList(mat_mailbox_flag_f3d),
	gsSPDisplayList(mailbox_Mailbox_mesh_tri_2),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



