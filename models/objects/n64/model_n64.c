#include <ultra64.h>

Lights1 n64_nb_f3d_lights = gdSPDefLights1(
	0x9, 0xF, 0x5D,
	0x13, 0x1E, 0xBB, 0x28, 0x28, 0x28);

Lights1 n64_ng_f3d_lights = gdSPDefLights1(
	0x0, 0x68, 0x1A,
	0x0, 0xD0, 0x35, 0x28, 0x28, 0x28);

Lights1 n64_ny_f3d_lights = gdSPDefLights1(
	0x7C, 0x6A, 0x0,
	0xF9, 0xD5, 0x0, 0x28, 0x28, 0x28);

Lights1 n64_nr_f3d_lights = gdSPDefLights1(
	0x71, 0x0, 0x1D,
	0xE3, 0x0, 0x3B, 0x28, 0x28, 0x28);

Vtx n64_N_mesh_vtx_0[72] = {
	{{{117, -28, 233},0, {496, 880},{0xD6, 0x16, 0x76, 0xFF}}},
	{{{117, 51, 233},0, {624, 880},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{117, 51, 117},0, {624, 752},{0x83, 0xE9, 0xF7, 0xFF}}},
	{{{117, -28, 117},0, {496, 752},{0xD6, 0x16, 0x8A, 0xFF}}},
	{{{233, -28, 117},0, {496, 368},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{233, 51, 117},0, {624, 368},{0x7D, 0xE9, 0xF7, 0xFF}}},
	{{{233, 51, 233},0, {624, 240},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{233, -28, 233},0, {496, 240},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{233, -221, 233},0, {368, 368},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{233, -221, 117},0, {368, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{117, 51, 233},0, {624, 1008},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{117, 235, 233},0, {624, 1008},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{117, 235, 117},0, {624, 752},{0xB1, 0x5A, 0xD7, 0xFF}}},
	{{{117, -28, -117},0, {624, 752},{0x8A, 0x16, 0x2A, 0xFF}}},
	{{{117, -221, -117},0, {624, 752},{0xBF, 0xB6, 0x4F, 0xFF}}},
	{{{-117, -28, 117},0, {496, 624},{0x76, 0x16, 0xD6, 0xFF}}},
	{{{-117, 51, 117},0, {624, 624},{0x9, 0xE9, 0x83, 0xFF}}},
	{{{-117, 51, 233},0, {624, 496},{0x9, 0xE9, 0x7D, 0xFF}}},
	{{{-117, -28, 233},0, {496, 496},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{-117, -221, 233},0, {368, 624},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-117, -221, 117},0, {368, 752},{0x41, 0xB6, 0xB1, 0xFF}}},
	{{{-233, -28, 233},0, {496, 112},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-233, 51, 233},0, {624, 112},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-233, 51, 117},0, {624, -16},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-233, -28, 117},0, {496, -16},{0x8A, 0x16, 0xD6, 0xFF}}},
	{{{-233, -221, 233},0, {368, 112},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-233, -221, 117},0, {368, -16},{0xBF, 0xB6, 0xB1, 0xFF}}},
	{{{-233, 235, 233},0, {624, 240},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{-233, 235, 117},0, {624, -16},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-233, 51, 233},0, {624, 240},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{117, -28, -117},0, {496, 624},{0x8A, 0x16, 0x2A, 0xFF}}},
	{{{117, 51, -117},0, {624, 624},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{117, 51, -233},0, {624, 496},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{117, -28, -233},0, {496, 496},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{117, -221, -117},0, {368, 624},{0xBF, 0xB6, 0x4F, 0xFF}}},
	{{{117, -221, -233},0, {368, 496},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{233, -28, -233},0, {496, 112},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{233, 51, -233},0, {624, 112},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{233, 51, -117},0, {624, -16},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{233, -28, -117},0, {496, -16},{0x76, 0x16, 0x2A, 0xFF}}},
	{{{233, -221, -117},0, {368, 112},{0x41, 0xB6, 0x4F, 0xFF}}},
	{{{233, -221, -233},0, {368, 240},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{233, 235, -233},0, {624, 240},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{233, 235, -117},0, {624, -16},{0x49, 0x49, 0x49, 0xFF}}},
	{{{233, 51, -233},0, {624, 240},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{-117, -28, -233},0, {496, 880},{0x2A, 0x16, 0x8A, 0xFF}}},
	{{{-117, 51, -233},0, {624, 880},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{-117, 51, -117},0, {624, 752},{0x7D, 0xE9, 0x9, 0xFF}}},
	{{{-117, -28, -117},0, {496, 752},{0x2A, 0x16, 0x76, 0xFF}}},
	{{{-233, -28, -117},0, {496, 368},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-233, 51, -117},0, {624, 368},{0x83, 0xE9, 0x9, 0xFF}}},
	{{{-233, 51, -233},0, {624, 240},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-233, -28, -233},0, {496, 240},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-233, -221, -117},0, {368, 368},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-233, -221, -233},0, {368, 240},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-117, 51, -233},0, {624, 1008},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{-117, 235, -233},0, {624, 1008},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{-117, 235, -117},0, {624, 752},{0x4F, 0x5A, 0x29, 0xFF}}},
	{{{-117, -28, 117},0, {624, 752},{0x76, 0x16, 0xD6, 0xFF}}},
	{{{-117, -221, 117},0, {624, 752},{0x41, 0xB6, 0xB1, 0xFF}}},
	{{{233, 51, 233},0, {624, 240},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{233, 51, 117},0, {624, 496},{0x7D, 0xE9, 0xF7, 0xFF}}},
	{{{233, 235, 117},0, {624, 496},{0x4F, 0x5A, 0xD7, 0xFF}}},
	{{{233, -221, -117},0, {624, 496},{0x41, 0xB6, 0x4F, 0xFF}}},
	{{{233, -28, -117},0, {624, 496},{0x76, 0x16, 0x2A, 0xFF}}},
	{{{233, 235, 233},0, {624, 240},{0x49, 0x49, 0x49, 0xFF}}},
	{{{-233, 51, -233},0, {624, 240},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-233, 51, -117},0, {624, 496},{0x83, 0xE9, 0x9, 0xFF}}},
	{{{-233, 235, -117},0, {624, 496},{0xB1, 0x5A, 0x29, 0xFF}}},
	{{{-233, -221, 117},0, {624, 496},{0xBF, 0xB6, 0xB1, 0xFF}}},
	{{{-233, -28, 117},0, {624, 496},{0x8A, 0x16, 0xD6, 0xFF}}},
	{{{-233, 235, -233},0, {624, 240},{0xB7, 0x49, 0xB7, 0xFF}}},
};

Gfx n64_N_mesh_tri_0[] = {
	gsSPVertex(n64_N_mesh_vtx_0 + 0, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 4, 7, 0),
	gsSP1Triangle(9, 4, 8, 0),
	gsSP1Triangle(2, 10, 11, 0),
	gsSP1Triangle(2, 11, 12, 0),
	gsSP1Triangle(2, 12, 13, 0),
	gsSP1Triangle(2, 13, 14, 0),
	gsSPVertex(n64_N_mesh_vtx_0 + 15, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(5, 0, 4, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(10, 6, 9, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(8, 12, 13, 0),
	gsSP1Triangle(8, 14, 12, 0),
	gsSPVertex(n64_N_mesh_vtx_0 + 30, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(4, 3, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(10, 6, 9, 0),
	gsSP1Triangle(11, 6, 10, 0),
	gsSP1Triangle(8, 12, 13, 0),
	gsSP1Triangle(8, 14, 12, 0),
	gsSPVertex(n64_N_mesh_vtx_0 + 45, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 4, 7, 0),
	gsSP1Triangle(8, 7, 9, 0),
	gsSP1Triangle(2, 10, 11, 0),
	gsSP1Triangle(2, 11, 12, 0),
	gsSP1Triangle(2, 12, 13, 0),
	gsSP1Triangle(2, 13, 14, 0),
	gsSPVertex(n64_N_mesh_vtx_0 + 60, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(2, 1, 3, 0),
	gsSP1Triangle(2, 3, 4, 0),
	gsSP1Triangle(0, 2, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(8, 7, 9, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(6, 8, 11, 0),
	gsSPEndDisplayList(),
};Vtx n64_N_mesh_vtx_1[91] = {
	{{{117, -28, 117},0, {496, 624},{0xD6, 0x16, 0x8A, 0xFF}}},
	{{{117, 51, 117},0, {624, 624},{0x83, 0xE9, 0xF7, 0xFF}}},
	{{{233, 51, 117},0, {624, 496},{0x7D, 0xE9, 0xF7, 0xFF}}},
	{{{233, -28, 117},0, {496, 496},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{233, -221, 117},0, {368, 624},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{117, -221, 117},0, {368, 752},{0xB1, 0xB6, 0xBF, 0xFF}}},
	{{{233, -28, 233},0, {496, 112},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{233, 51, 233},0, {624, 112},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{117, 51, 233},0, {624, -16},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{117, -28, 233},0, {496, -16},{0xD6, 0x16, 0x76, 0xFF}}},
	{{{233, -221, 233},0, {368, 112},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{117, -221, 233},0, {368, -16},{0xB1, 0xB6, 0x41, 0xFF}}},
	{{{233, 51, 233},0, {624, 240},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{233, 235, 233},0, {624, 240},{0x49, 0x49, 0x49, 0xFF}}},
	{{{117, 235, 233},0, {624, -16},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{117, -221, 233},0, {368, 880},{0xB1, 0xB6, 0x41, 0xFF}}},
	{{{117, -28, 233},0, {496, 880},{0xD6, 0x16, 0x76, 0xFF}}},
	{{{117, -28, 117},0, {496, 752},{0xD6, 0x16, 0x8A, 0xFF}}},
	{{{117, -221, 117},0, {368, 752},{0xB1, 0xB6, 0xBF, 0xFF}}},
	{{{-233, -28, 117},0, {496, 880},{0x8A, 0x16, 0xD6, 0xFF}}},
	{{{-233, 51, 117},0, {624, 880},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-117, 51, 117},0, {624, 752},{0x9, 0xE9, 0x83, 0xFF}}},
	{{{-117, -28, 117},0, {496, 752},{0x76, 0x16, 0xD6, 0xFF}}},
	{{{-117, -221, 117},0, {368, 880},{0x41, 0xB6, 0xB1, 0xFF}}},
	{{{-233, -221, 117},0, {368, 1008},{0xBF, 0xB6, 0xB1, 0xFF}}},
	{{{-117, -28, 233},0, {496, 368},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{-117, 51, 233},0, {624, 368},{0x9, 0xE9, 0x7D, 0xFF}}},
	{{{-233, 51, 233},0, {624, 240},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-233, -28, 233},0, {496, 240},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-233, -221, 233},0, {368, 368},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-117, -221, 233},0, {368, 496},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-117, 51, 117},0, {624, 752},{0x9, 0xE9, 0x83, 0xFF}}},
	{{{-233, 51, 117},0, {624, 1008},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-233, 235, 117},0, {624, 1008},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-117, 235, 117},0, {624, 752},{0x29, 0x5A, 0xB1, 0xFF}}},
	{{{117, -28, 117},0, {624, 752},{0xD6, 0x16, 0x8A, 0xFF}}},
	{{{117, -221, 117},0, {624, 752},{0xB1, 0xB6, 0xBF, 0xFF}}},
	{{{233, -28, -117},0, {496, 880},{0x76, 0x16, 0x2A, 0xFF}}},
	{{{233, 51, -117},0, {624, 880},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{117, 51, -117},0, {624, 752},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{117, -28, -117},0, {496, 752},{0x8A, 0x16, 0x2A, 0xFF}}},
	{{{233, -221, -117},0, {368, 880},{0x41, 0xB6, 0x4F, 0xFF}}},
	{{{117, -221, -117},0, {368, 752},{0xBF, 0xB6, 0x4F, 0xFF}}},
	{{{117, -28, -233},0, {496, 368},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{117, 51, -233},0, {624, 368},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{233, 51, -233},0, {624, 240},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{233, -28, -233},0, {496, 240},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{117, -221, -233},0, {368, 368},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{117, -28, -233},0, {496, 368},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{233, -28, -233},0, {496, 240},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{233, -221, -233},0, {368, 240},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{117, 51, -117},0, {624, 752},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{233, 51, -117},0, {624, 1008},{0x5A, 0x0, 0x5A, 0xFF}}},
	{{{233, 235, -117},0, {624, 1008},{0x49, 0x49, 0x49, 0xFF}}},
	{{{117, 235, -117},0, {624, 752},{0xD7, 0x5A, 0x4F, 0xFF}}},
	{{{-117, -28, -117},0, {624, 752},{0x2A, 0x16, 0x76, 0xFF}}},
	{{{-117, -221, -117},0, {624, 752},{0x4F, 0xB6, 0x41, 0xFF}}},
	{{{-117, -28, -117},0, {496, 624},{0x2A, 0x16, 0x76, 0xFF}}},
	{{{-117, 51, -117},0, {624, 624},{0x7D, 0xE9, 0x9, 0xFF}}},
	{{{-233, 51, -117},0, {624, 496},{0x83, 0xE9, 0x9, 0xFF}}},
	{{{-233, -28, -117},0, {496, 496},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-117, -221, -117},0, {368, 624},{0x4F, 0xB6, 0x41, 0xFF}}},
	{{{-233, -221, -117},0, {368, 496},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-233, -28, -233},0, {496, 112},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-233, 51, -233},0, {624, 112},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-117, 51, -233},0, {624, -16},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{-117, -28, -233},0, {496, -16},{0x2A, 0x16, 0x8A, 0xFF}}},
	{{{-117, -221, -233},0, {368, 112},{0x4F, 0xB6, 0xBF, 0xFF}}},
	{{{-233, -221, -233},0, {368, 240},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-233, 51, -233},0, {624, 240},{0xA6, 0x0, 0xA6, 0xFF}}},
	{{{-233, 235, -233},0, {624, 240},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-117, 235, -233},0, {624, -16},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{-117, -221, -233},0, {368, 880},{0x4F, 0xB6, 0xBF, 0xFF}}},
	{{{-117, -28, -233},0, {496, 880},{0x2A, 0x16, 0x8A, 0xFF}}},
	{{{-117, -28, -117},0, {496, 752},{0x2A, 0x16, 0x76, 0xFF}}},
	{{{-117, -221, -117},0, {368, 752},{0x4F, 0xB6, 0x41, 0xFF}}},
	{{{-233, 51, 233},0, {624, 240},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-117, 51, 233},0, {624, 496},{0x9, 0xE9, 0x7D, 0xFF}}},
	{{{-117, 235, 233},0, {624, 496},{0x29, 0x5A, 0x4F, 0xFF}}},
	{{{-117, 235, 233},0, {624, 496},{0x29, 0x5A, 0x4F, 0xFF}}},
	{{{-117, 51, 233},0, {624, 496},{0x9, 0xE9, 0x7D, 0xFF}}},
	{{{117, -221, 233},0, {624, 496},{0xB1, 0xB6, 0x41, 0xFF}}},
	{{{117, -28, 233},0, {624, 496},{0xD6, 0x16, 0x76, 0xFF}}},
	{{{-233, 51, 233},0, {624, 240},{0xA6, 0x0, 0x5A, 0xFF}}},
	{{{-233, 235, 233},0, {624, 240},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{233, 51, -233},0, {624, 240},{0x5A, 0x0, 0xA6, 0xFF}}},
	{{{117, 51, -233},0, {624, 496},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{117, 235, -233},0, {624, 496},{0xD7, 0x5A, 0xB1, 0xFF}}},
	{{{-117, -221, -233},0, {624, 496},{0x4F, 0xB6, 0xBF, 0xFF}}},
	{{{-117, -28, -233},0, {624, 496},{0x2A, 0x16, 0x8A, 0xFF}}},
	{{{233, 235, -233},0, {624, 240},{0x49, 0x49, 0xB7, 0xFF}}},
};

Gfx n64_N_mesh_tri_1[] = {
	gsSPVertex(n64_N_mesh_vtx_1 + 0, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(5, 0, 4, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(10, 6, 9, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(8, 12, 13, 0),
	gsSP1Triangle(8, 13, 14, 0),
	gsSPVertex(n64_N_mesh_vtx_1 + 15, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 4, 7, 0),
	gsSP1Triangle(9, 4, 8, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 12, 13, 0),
	gsSP1Triangle(14, 10, 13, 0),
	gsSP1Triangle(15, 10, 14, 0),
	gsSPVertex(n64_N_mesh_vtx_1 + 31, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(0, 3, 4, 0),
	gsSP1Triangle(0, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 8, 9, 0),
	gsSP1Triangle(10, 6, 9, 0),
	gsSP1Triangle(10, 9, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(n64_N_mesh_vtx_1 + 47, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(4, 7, 8, 0),
	gsSP1Triangle(4, 8, 9, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 12, 13, 0),
	gsSP1Triangle(14, 10, 13, 0),
	gsSP1Triangle(14, 13, 15, 0),
	gsSPVertex(n64_N_mesh_vtx_1 + 63, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 3, 0),
	gsSP1Triangle(5, 0, 4, 0),
	gsSP1Triangle(2, 6, 7, 0),
	gsSP1Triangle(2, 7, 8, 0),
	gsSP1Triangle(9, 10, 11, 0),
	gsSP1Triangle(9, 11, 12, 0),
	gsSP1Triangle(13, 14, 15, 0),
	gsSPVertex(n64_N_mesh_vtx_1 + 79, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 0, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(8, 7, 9, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(6, 8, 11, 0),
	gsSPEndDisplayList(),
};Vtx n64_N_mesh_vtx_2[34] = {
	{{{-117, -221, 117},0, {112, 368},{0x41, 0xB6, 0xB1, 0xFF}}},
	{{{-233, -221, 233},0, {240, 240},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-233, -221, 117},0, {112, 240},{0xBF, 0xB6, 0xB1, 0xFF}}},
	{{{-117, -221, 117},0, {112, 496},{0x41, 0xB6, 0xB1, 0xFF}}},
	{{{-117, -221, 233},0, {240, 496},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-233, -221, 233},0, {240, 368},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{233, 235, 117},0, {624, 496},{0x4F, 0x5A, 0xD7, 0xFF}}},
	{{{117, 235, 233},0, {880, 240},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{233, 235, 233},0, {624, 240},{0x49, 0x49, 0x49, 0xFF}}},
	{{{117, 235, 117},0, {880, 496},{0xB1, 0x5A, 0xD7, 0xFF}}},
	{{{117, -221, 117},0, {112, 496},{0xB1, 0xB6, 0xBF, 0xFF}}},
	{{{233, -221, 117},0, {240, 496},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{233, -221, 233},0, {240, 368},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{117, -221, 233},0, {112, 368},{0xB1, 0xB6, 0x41, 0xFF}}},
	{{{-117, 235, 233},0, {624, 496},{0x29, 0x5A, 0x4F, 0xFF}}},
	{{{-233, 235, 117},0, {880, 240},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-233, 235, 233},0, {624, 240},{0xB7, 0x49, 0x49, 0xFF}}},
	{{{-117, 235, 117},0, {880, 496},{0x29, 0x5A, 0xB1, 0xFF}}},
	{{{233, -221, -117},0, {240, 368},{0x41, 0xB6, 0x4F, 0xFF}}},
	{{{117, -221, -233},0, {368, 368},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{233, -221, -233},0, {368, 240},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{117, -221, -117},0, {240, 496},{0xBF, 0xB6, 0x4F, 0xFF}}},
	{{{117, 235, -233},0, {624, 496},{0xD7, 0x5A, 0xB1, 0xFF}}},
	{{{233, 235, -117},0, {880, 240},{0x49, 0x49, 0x49, 0xFF}}},
	{{{233, 235, -233},0, {624, 240},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{117, 235, -117},0, {880, 496},{0xD7, 0x5A, 0x4F, 0xFF}}},
	{{{-117, -221, -233},0, {240, 368},{0x4F, 0xB6, 0xBF, 0xFF}}},
	{{{-233, -221, -117},0, {368, 368},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-233, -221, -233},0, {368, 240},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-117, -221, -117},0, {240, 496},{0x4F, 0xB6, 0x41, 0xFF}}},
	{{{-233, 235, -117},0, {624, 496},{0xB1, 0x5A, 0x29, 0xFF}}},
	{{{-117, 235, -233},0, {880, 240},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{-233, 235, -233},0, {624, 240},{0xB7, 0x49, 0xB7, 0xFF}}},
	{{{-117, 235, -117},0, {880, 496},{0x4F, 0x5A, 0x29, 0xFF}}},
};

Gfx n64_N_mesh_tri_2[] = {
	gsSPVertex(n64_N_mesh_vtx_2 + 0, 14, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 8, 0),
	gsSP1Triangle(6, 9, 7, 0),
	gsSP1Triangle(10, 11, 12, 0),
	gsSP1Triangle(10, 12, 13, 0),
	gsSPVertex(n64_N_mesh_vtx_2 + 14, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 5, 4, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 11, 9, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(15, 13, 12, 0),
	gsSPVertex(n64_N_mesh_vtx_2 + 30, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 3, 1, 0),
	gsSPEndDisplayList(),
};Vtx n64_N_mesh_vtx_3[32] = {
	{{{117, 235, 117},0, {880, 496},{0xB1, 0x5A, 0xD7, 0xFF}}},
	{{{233, 235, 117},0, {624, 496},{0x4F, 0x5A, 0xD7, 0xFF}}},
	{{{233, -28, -117},0, {624, 496},{0x76, 0x16, 0x2A, 0xFF}}},
	{{{117, -28, -117},0, {880, 496},{0x8A, 0x16, 0x2A, 0xFF}}},
	{{{233, 51, 117},0, {624, 496},{0x7D, 0xE9, 0xF7, 0xFF}}},
	{{{117, 51, 117},0, {624, 752},{0x83, 0xE9, 0xF7, 0xFF}}},
	{{{117, -221, -117},0, {624, 752},{0xBF, 0xB6, 0x4F, 0xFF}}},
	{{{233, -221, -117},0, {624, 496},{0x41, 0xB6, 0x4F, 0xFF}}},
	{{{-117, 235, 117},0, {880, 496},{0x29, 0x5A, 0xB1, 0xFF}}},
	{{{-117, 235, 233},0, {624, 496},{0x29, 0x5A, 0x4F, 0xFF}}},
	{{{117, -28, 233},0, {624, 496},{0xD6, 0x16, 0x76, 0xFF}}},
	{{{117, -28, 117},0, {880, 496},{0xD6, 0x16, 0x8A, 0xFF}}},
	{{{-117, 51, 233},0, {624, 496},{0x9, 0xE9, 0x7D, 0xFF}}},
	{{{-117, 51, 117},0, {624, 752},{0x9, 0xE9, 0x83, 0xFF}}},
	{{{117, -221, 117},0, {624, 752},{0xB1, 0xB6, 0xBF, 0xFF}}},
	{{{117, -221, 233},0, {624, 496},{0xB1, 0xB6, 0x41, 0xFF}}},
	{{{117, 235, -117},0, {880, 496},{0xD7, 0x5A, 0x4F, 0xFF}}},
	{{{117, 235, -233},0, {624, 496},{0xD7, 0x5A, 0xB1, 0xFF}}},
	{{{-117, -28, -233},0, {624, 496},{0x2A, 0x16, 0x8A, 0xFF}}},
	{{{-117, -28, -117},0, {880, 496},{0x2A, 0x16, 0x76, 0xFF}}},
	{{{117, 51, -233},0, {624, 496},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{117, 51, -117},0, {624, 752},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{-117, -221, -117},0, {624, 752},{0x4F, 0xB6, 0x41, 0xFF}}},
	{{{-117, -221, -233},0, {624, 496},{0x4F, 0xB6, 0xBF, 0xFF}}},
	{{{-117, 235, -117},0, {880, 496},{0x4F, 0x5A, 0x29, 0xFF}}},
	{{{-233, 235, -117},0, {624, 496},{0xB1, 0x5A, 0x29, 0xFF}}},
	{{{-233, -28, 117},0, {624, 496},{0x8A, 0x16, 0xD6, 0xFF}}},
	{{{-117, -28, 117},0, {880, 496},{0x76, 0x16, 0xD6, 0xFF}}},
	{{{-233, 51, -117},0, {624, 496},{0x83, 0xE9, 0x9, 0xFF}}},
	{{{-117, 51, -117},0, {624, 752},{0x7D, 0xE9, 0x9, 0xFF}}},
	{{{-117, -221, 117},0, {624, 752},{0x41, 0xB6, 0xB1, 0xFF}}},
	{{{-233, -221, 117},0, {624, 496},{0xBF, 0xB6, 0xB1, 0xFF}}},
};

Gfx n64_N_mesh_tri_3[] = {
	gsSPVertex(n64_N_mesh_vtx_3 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(n64_N_mesh_vtx_3 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPEndDisplayList(),
};


Gfx mat_n64_nb_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(n64_nb_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_n64_ng_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(n64_ng_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_n64_ny_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(n64_ny_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx mat_n64_nr_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(n64_nr_f3d_lights),
	gsSPEndDisplayList(),
};


Gfx n64_N_mesh[] = {
	gsSPDisplayList(mat_n64_nb_f3d),
	gsSPDisplayList(n64_N_mesh_tri_0),
	gsSPDisplayList(mat_n64_ng_f3d),
	gsSPDisplayList(n64_N_mesh_tri_1),
	gsSPDisplayList(mat_n64_ny_f3d),
	gsSPDisplayList(n64_N_mesh_tri_2),
	gsSPDisplayList(mat_n64_nr_f3d),
	gsSPDisplayList(n64_N_mesh_tri_3),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



