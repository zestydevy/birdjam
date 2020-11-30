#include <ultra64.h>

Lights1 store_e_nr_f3d_lights = gdSPDefLights1(
	0x71, 0x0, 0x35,
	0xE3, 0x0, 0x6B, 0x28, 0x28, 0x28);

Vtx store_e_E_mesh_vtx_0[46] = {
	{{{56, -56, 56},0, {624, 240},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-56, 401, 56},0, {624, -16},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{-56, -56, 56},0, {624, -16},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{56, 401, 56},0, {624, 240},{0x49, 0x49, 0x49, 0xFF}}},
	{{{56, 125, -56},0, {624, 496},{0x73, 0xD9, 0xD9, 0xFF}}},
	{{{56, 56, -56},0, {624, 496},{0x73, 0x27, 0xD9, 0xFF}}},
	{{{-56, 56, -56},0, {624, 752},{0x8D, 0x27, 0xD9, 0xFF}}},
	{{{-56, 56, -266},0, {624, 752},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{56, 56, -266},0, {624, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{56, -56, 56},0, {368, 496},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{56, -56, -266},0, {368, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-56, -56, 56},0, {112, 496},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-56, -56, -266},0, {112, 496},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-56, -56, -266},0, {368, 752},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-56, -56, 56},0, {368, 752},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{56, 401, 56},0, {624, 496},{0x49, 0x49, 0x49, 0xFF}}},
	{{{-56, 401, -266},0, {880, 496},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-56, 401, 56},0, {880, 496},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{56, 401, -266},0, {624, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{56, 293, -56},0, {624, 496},{0x73, 0xD9, 0xD9, 0xFF}}},
	{{{56, 293, -266},0, {624, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-56, 293, -56},0, {624, 752},{0x8D, 0xD9, 0xD9, 0xFF}}},
	{{{-56, 227, -56},0, {624, 752},{0x8D, 0x27, 0xD9, 0xFF}}},
	{{{56, 227, -56},0, {624, 496},{0x73, 0x27, 0xD9, 0xFF}}},
	{{{56, 401, 56},0, {624, 240},{0x49, 0x49, 0x49, 0xFF}}},
	{{{56, 125, -56},0, {624, 496},{0x73, 0xD9, 0xD9, 0xFF}}},
	{{{56, 227, -223},0, {624, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{56, 125, -223},0, {624, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-56, 125, -56},0, {624, 752},{0x8D, 0xD9, 0xD9, 0xFF}}},
	{{{-56, 56, -56},0, {624, 752},{0x8D, 0x27, 0xD9, 0xFF}}},
	{{{-56, -56, 56},0, {624, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-56, -56, 56},0, {624, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-56, 401, 56},0, {624, 1008},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{-56, 227, -56},0, {624, 752},{0x8D, 0x27, 0xD9, 0xFF}}},
	{{{-56, 293, -56},0, {624, 752},{0x8D, 0xD9, 0xD9, 0xFF}}},
	{{{-56, 125, -223},0, {624, 752},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-56, 125, -56},0, {624, 752},{0x8D, 0xD9, 0xD9, 0xFF}}},
	{{{-56, 227, -223},0, {624, 752},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{56, 227, -56},0, {624, 496},{0x73, 0x27, 0xD9, 0xFF}}},
	{{{56, 227, -223},0, {624, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{56, 125, -223},0, {624, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-56, 293, -266},0, {624, 752},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{56, 401, -266},0, {624, 496},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{56, 293, -266},0, {624, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-56, 401, -266},0, {624, 752},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-56, 401, 56},0, {624, 752},{0xB7, 0x49, 0x49, 0xFF}}},
};

Gfx store_e_E_mesh_tri_0[] = {
	gsSPVertex(store_e_E_mesh_vtx_0 + 0, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(5, 4, 0, 0),
	gsSP1Triangle(6, 4, 5, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSP1Triangle(5, 8, 7, 0),
	gsSP1Triangle(9, 8, 5, 0),
	gsSP1Triangle(9, 10, 8, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSP1Triangle(11, 12, 10, 0),
	gsSP1Triangle(7, 8, 10, 0),
	gsSP1Triangle(7, 10, 13, 0),
	gsSP1Triangle(6, 7, 13, 0),
	gsSP1Triangle(6, 13, 14, 0),
	gsSPVertex(store_e_E_mesh_vtx_0 + 15, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 3, 0, 0),
	gsSP1Triangle(4, 5, 3, 0),
	gsSP1Triangle(6, 5, 4, 0),
	gsSP1Triangle(7, 6, 4, 0),
	gsSP1Triangle(7, 4, 8, 0),
	gsSP1Triangle(8, 4, 9, 0),
	gsSP1Triangle(10, 8, 9, 0),
	gsSP1Triangle(10, 11, 8, 0),
	gsSP1Triangle(10, 12, 11, 0),
	gsSP1Triangle(13, 12, 10, 0),
	gsSP1Triangle(14, 13, 10, 0),
	gsSP1Triangle(15, 13, 14, 0),
	gsSP1Triangle(15, 7, 13, 0),
	gsSPVertex(store_e_E_mesh_vtx_0 + 31, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 3, 2, 0),
	gsSP1Triangle(2, 4, 5, 0),
	gsSP1Triangle(2, 6, 4, 0),
	gsSP1Triangle(7, 6, 2, 0),
	gsSP1Triangle(7, 8, 6, 0),
	gsSP1Triangle(4, 6, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),
	gsSP1Triangle(5, 4, 9, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 13, 11, 0),
	gsSP1Triangle(14, 13, 10, 0),
	gsSP1Triangle(14, 10, 3, 0),
	gsSP1Triangle(3, 10, 12, 0),
	gsSPEndDisplayList(),
};


Gfx mat_store_e_nr_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(store_e_nr_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx store_e_E_mesh[] = {
	gsSPDisplayList(mat_store_e_nr_f3d),
	gsSPDisplayList(store_e_E_mesh_tri_0),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};





