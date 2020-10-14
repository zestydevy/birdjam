#include <ultra64.h>

Lights1 logo_logo_blue_lights = gdSPDefLights1(
	0xE, 0x0, 0x7F,
	0x1C, 0x0, 0xFE, 0x28, 0x28, 0x28);

Lights1 logo_logo_green_lights = gdSPDefLights1(
	0x0, 0x7F, 0xB,
	0x0, 0xFE, 0x16, 0x28, 0x28, 0x28);

Lights1 logo_logo_yellow_lights = gdSPDefLights1(
	0x7F, 0x7E, 0x0,
	0xFE, 0xFC, 0x0, 0x28, 0x28, 0x28);

Lights1 logo_logo_red_lights = gdSPDefLights1(
	0x7F, 0x0, 0x0,
	0xFE, 0x1, 0x0, 0x28, 0x28, 0x28);

Vtx logo_N64_Logo_mesh_vtx_0[70] = {
	{{{-586, 0, 584},0, {-16, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-586, 529, 251},0, {1008, 1008},{0x84, 0x18, 0xF7, 0xFF}}},
	{{{-586, 2, 251},0, {1008, -16},{0xB1, 0xA6, 0xD6, 0xFF}}},
	{{{586, 1, -261},0, {-16, 1008},{0x4F, 0xA6, 0x2A, 0xFF}}},
	{{{586, 1119, 251},0, {1008, 1008},{0x4F, 0x59, 0xD5, 0xFF}}},
	{{{586, 580, 251},0, {1008, -16},{0x41, 0xE0, 0x97, 0xFF}}},
	{{{586, 1119, 251},0, {-16, 1008},{0x4F, 0x59, 0xD5, 0xFF}}},
	{{{586, 0, 251},0, {1008, 1008},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-586, 0, -261},0, {-16, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-586, 581, -261},0, {1008, 1008},{0xEA, 0xD6, 0x76, 0xFF}}},
	{{{-586, 1119, -261},0, {1008, -16},{0xB1, 0x5A, 0x2A, 0xFF}}},
	{{{-257, 579, 584},0, {-16, 1008},{0x27, 0xCE, 0x6E, 0xFF}}},
	{{{-257, 510, 251},0, {1008, 1008},{0x7D, 0x16, 0xF8, 0xFF}}},
	{{{-257, 599, 251},0, {1008, -16},{0x8, 0xEA, 0x83, 0xFF}}},
	{{{-586, 1124, 584},0, {1008, 1008},{0xB7, 0x4A, 0x4A, 0xFF}}},
	{{{-586, 1124, 251},0, {1008, -16},{0xB7, 0x4A, 0xB6, 0xFF}}},
	{{{-586, 0, 584},0, {-16, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-586, 1124, 251},0, {1008, -16},{0xB7, 0x4A, 0xB6, 0xFF}}},
	{{{-586, 529, 251},0, {-16, -16},{0x84, 0x18, 0xF7, 0xFF}}},
	{{{586, 0, 251},0, {-16, 1008},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{586, 1119, 251},0, {1008, 1008},{0x4F, 0x59, 0xD5, 0xFF}}},
	{{{586, 1124, 584},0, {1008, -16},{0x4A, 0x4A, 0x49, 0xFF}}},
	{{{586, 0, 584},0, {-16, -16},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{586, 510, -261},0, {-16, 1008},{0x7D, 0x17, 0x8, 0xFF}}},
	{{{586, 0, -592},0, {1008, 1008},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{586, 1124, -592},0, {1008, -16},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{586, 1124, -261},0, {-16, -16},{0x49, 0x49, 0x49, 0xFF}}},
	{{{257, 510, -261},0, {-16, 1008},{0x83, 0x17, 0x8, 0xFF}}},
	{{{257, 0, -592},0, {1008, 1008},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{257, 1, -261},0, {1008, -16},{0xB1, 0xA6, 0x29, 0xFF}}},
	{{{257, 600, 251},0, {-16, -16},{0x83, 0xEA, 0xF8, 0xFF}}},
	{{{257, 600, 251},0, {-16, 1008},{0x83, 0xEA, 0xF8, 0xFF}}},
	{{{257, 1124, 584},0, {1008, 1008},{0xB6, 0x4A, 0x49, 0xFF}}},
	{{{257, 1120, 251},0, {1008, -16},{0xB1, 0x59, 0xD5, 0xFF}}},
	{{{257, 510, -261},0, {-16, -16},{0x83, 0x17, 0x8, 0xFF}}},
	{{{257, 1124, 584},0, {-16, 1008},{0xB6, 0x4A, 0x49, 0xFF}}},
	{{{257, 600, 251},0, {1008, 1008},{0x83, 0xEA, 0xF8, 0xFF}}},
	{{{257, 510, 251},0, {1008, -16},{0xF8, 0x16, 0x83, 0xFF}}},
	{{{256, 531, 584},0, {-16, -16},{0xF7, 0x18, 0x7C, 0xFF}}},
	{{{586, 1, -261},0, {-16, 1008},{0x4F, 0xA6, 0x2A, 0xFF}}},
	{{{586, 0, -592},0, {1008, 1008},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{586, 510, -261},0, {1008, -16},{0x7D, 0x17, 0x8, 0xFF}}},
	{{{586, 1119, 251},0, {-16, -16},{0x4F, 0x59, 0xD5, 0xFF}}},
	{{{257, 0, -592},0, {-16, 1008},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{257, 510, -261},0, {1008, 1008},{0x83, 0x17, 0x8, 0xFF}}},
	{{{257, 600, -261},0, {1008, -16},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{257, 600, -592},0, {-16, -16},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{-586, 1124, -592},0, {-16, 1008},{0xB6, 0x4A, 0xB7, 0xFF}}},
	{{{-586, 0, -592},0, {1008, 1008},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-586, 0, -261},0, {1008, -16},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-586, 1119, -261},0, {-16, -16},{0xB1, 0x5A, 0x2A, 0xFF}}},
	{{{-586, 581, -261},0, {-16, 1008},{0xEA, 0xD6, 0x76, 0xFF}}},
	{{{-586, 2, 251},0, {1008, 1008},{0xB1, 0xA6, 0xD6, 0xFF}}},
	{{{-586, 529, 251},0, {1008, -16},{0x84, 0x18, 0xF7, 0xFF}}},
	{{{-257, 510, 251},0, {-16, 1008},{0x7D, 0x16, 0xF8, 0xFF}}},
	{{{-257, 0, 584},0, {1008, 1008},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-257, 1, 251},0, {1008, -16},{0x4F, 0xA6, 0xD7, 0xFF}}},
	{{{-257, 600, -261},0, {-16, -16},{0x7D, 0xE9, 0x8, 0xFF}}},
	{{{-257, 600, -261},0, {-16, 1008},{0x7D, 0xE9, 0x8, 0xFF}}},
	{{{-257, 1124, -592},0, {1008, 1008},{0x4A, 0x4A, 0xB7, 0xFF}}},
	{{{-257, 1121, -261},0, {1008, -16},{0x50, 0x5A, 0x2A, 0xFF}}},
	{{{-257, 510, 251},0, {-16, -16},{0x7D, 0x16, 0xF8, 0xFF}}},
	{{{-257, 600, -261},0, {-16, 1008},{0x7D, 0xE9, 0x8, 0xFF}}},
	{{{-257, 511, -261},0, {1008, 1008},{0x8, 0x17, 0x7D, 0xFF}}},
	{{{-257, 511, -592},0, {1008, -16},{0x8, 0x17, 0x83, 0xFF}}},
	{{{-257, 1124, -592},0, {-16, -16},{0x4A, 0x4A, 0xB7, 0xFF}}},
	{{{-257, 579, 584},0, {-16, 1008},{0x27, 0xCE, 0x6E, 0xFF}}},
	{{{-256, 1119, 584},0, {1008, 1008},{0x2A, 0x5A, 0x4F, 0xFF}}},
	{{{-257, 510, 251},0, {-16, -16},{0x7D, 0x16, 0xF8, 0xFF}}},
	{{{-257, 0, 584},0, {1008, -16},{0x49, 0xB7, 0x49, 0xFF}}},
};

Gfx logo_N64_Logo_mesh_tri_0[] = {
	gsSPVertex(logo_N64_Logo_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(0, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_0 + 16, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(3, 5, 6, 0),
	gsSP1Triangle(7, 8, 9, 0),
	gsSP1Triangle(7, 9, 10, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(11, 13, 14, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_0 + 31, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_0 + 47, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 3, 0),
	gsSP1Triangle(7, 8, 9, 0),
	gsSP1Triangle(7, 9, 10, 0),
	gsSP1Triangle(11, 12, 13, 0),
	gsSP1Triangle(11, 13, 14, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_0 + 62, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(5, 7, 6, 0),
	gsSPEndDisplayList(),
};Vtx logo_N64_Logo_mesh_vtx_1[95] = {
	{{{257, 1124, 584},0, {-16, 1008},{0xB6, 0x4A, 0x49, 0xFF}}},
	{{{256, 531, 584},0, {1008, 1008},{0xF7, 0x18, 0x7C, 0xFF}}},
	{{{586, 1124, 584},0, {1008, -16},{0x4A, 0x4A, 0x49, 0xFF}}},
	{{{586, 510, -261},0, {-16, 1008},{0x7D, 0x17, 0x8, 0xFF}}},
	{{{257, 510, -261},0, {1008, 1008},{0x83, 0x17, 0x8, 0xFF}}},
	{{{586, 1119, 251},0, {1008, -16},{0x4F, 0x59, 0xD5, 0xFF}}},
	{{{257, 510, -261},0, {-16, 1008},{0x83, 0x17, 0x8, 0xFF}}},
	{{{257, 1120, 251},0, {1008, 1008},{0xB1, 0x59, 0xD5, 0xFF}}},
	{{{257, 510, 251},0, {-16, 1008},{0xF8, 0x16, 0x83, 0xFF}}},
	{{{586, 0, 251},0, {1008, 1008},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{256, 1, 251},0, {1008, -16},{0xD7, 0xA6, 0xB1, 0xFF}}},
	{{{-257, 599, 251},0, {-16, -16},{0x8, 0xEA, 0x83, 0xFF}}},
	{{{-257, 599, 251},0, {-16, 1008},{0x8, 0xEA, 0x83, 0xFF}}},
	{{{-586, 1124, 251},0, {1008, 1008},{0xB7, 0x4A, 0xB6, 0xFF}}},
	{{{-257, 1120, 251},0, {1008, -16},{0x2A, 0x5A, 0xB0, 0xFF}}},
	{{{257, 510, 251},0, {-16, -16},{0xF8, 0x16, 0x83, 0xFF}}},
	{{{-586, 1124, 251},0, {-16, 1008},{0xB7, 0x4A, 0xB6, 0xFF}}},
	{{{-257, 599, 251},0, {1008, 1008},{0x8, 0xEA, 0x83, 0xFF}}},
	{{{-257, 510, 251},0, {1008, -16},{0x7D, 0x16, 0xF8, 0xFF}}},
	{{{-586, 529, 251},0, {-16, -16},{0x84, 0x18, 0xF7, 0xFF}}},
	{{{256, 2, 584},0, {-16, 1008},{0xD6, 0xA6, 0x4F, 0xFF}}},
	{{{256, 1, 251},0, {1008, 1008},{0xD7, 0xA6, 0xB1, 0xFF}}},
	{{{586, 0, 251},0, {1008, -16},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{586, 0, 584},0, {-16, -16},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{586, 580, 251},0, {-16, 1008},{0x41, 0xE0, 0x97, 0xFF}}},
	{{{586, 0, 251},0, {1008, 1008},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{257, 510, 251},0, {1008, -16},{0xF8, 0x16, 0x83, 0xFF}}},
	{{{257, 600, 251},0, {-16, -16},{0x83, 0xEA, 0xF8, 0xFF}}},
	{{{256, 531, 584},0, {-16, 1008},{0xF7, 0x18, 0x7C, 0xFF}}},
	{{{256, 2, 584},0, {1008, 1008},{0xD6, 0xA6, 0x4F, 0xFF}}},
	{{{586, 0, 584},0, {1008, -16},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{586, 1124, 584},0, {-16, -16},{0x4A, 0x4A, 0x49, 0xFF}}},
	{{{586, 0, -592},0, {-16, 1008},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{586, 1, -261},0, {1008, 1008},{0x4F, 0xA6, 0x2A, 0xFF}}},
	{{{257, 1, -261},0, {1008, -16},{0xB1, 0xA6, 0x29, 0xFF}}},
	{{{257, 0, -592},0, {-16, -16},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{257, 0, -592},0, {-16, 1008},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{257, 600, -592},0, {1008, 1008},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{586, 1124, -592},0, {1008, -16},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{586, 0, -592},0, {-16, -16},{0x49, 0xB7, 0xB7, 0xFF}}},
	{{{-256, 2, -592},0, {-16, 1008},{0x2A, 0xA6, 0xB1, 0xFF}}},
	{{{-586, 0, -592},0, {1008, 1008},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-257, 511, -592},0, {1008, -16},{0x8, 0x17, 0x83, 0xFF}}},
	{{{257, 600, -592},0, {-16, -16},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{256, 1121, -592},0, {-16, 1008},{0xD5, 0x59, 0xB1, 0xFF}}},
	{{{586, 1124, -592},0, {1008, 1008},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{257, 600, -592},0, {1008, -16},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{-257, 511, -592},0, {-16, -16},{0x8, 0x17, 0x83, 0xFF}}},
	{{{257, 600, -261},0, {-16, 1008},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{586, 1124, -261},0, {1008, 1008},{0x49, 0x49, 0x49, 0xFF}}},
	{{{256, 1121, -261},0, {1008, -16},{0xD5, 0x59, 0x4F, 0xFF}}},
	{{{-257, 511, -261},0, {-16, -16},{0x8, 0x17, 0x7D, 0xFF}}},
	{{{-257, 511, -261},0, {-16, 1008},{0x8, 0x17, 0x7D, 0xFF}}},
	{{{-586, 0, -261},0, {1008, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-256, 2, -261},0, {1008, -16},{0x2A, 0xA6, 0x4F, 0xFF}}},
	{{{257, 600, -261},0, {-16, -16},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{586, 1124, -261},0, {-16, 1008},{0x49, 0x49, 0x49, 0xFF}}},
	{{{257, 600, -261},0, {1008, 1008},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{257, 510, -261},0, {1008, -16},{0x83, 0x17, 0x8, 0xFF}}},
	{{{586, 510, -261},0, {-16, -16},{0x7D, 0x17, 0x8, 0xFF}}},
	{{{-586, 1124, -592},0, {-16, 1008},{0xB6, 0x4A, 0xB7, 0xFF}}},
	{{{-257, 1124, -592},0, {1008, 1008},{0x4A, 0x4A, 0xB7, 0xFF}}},
	{{{-257, 511, -592},0, {1008, -16},{0x8, 0x17, 0x83, 0xFF}}},
	{{{-586, 0, -592},0, {-16, -16},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-256, 2, -592},0, {-16, 1008},{0x2A, 0xA6, 0xB1, 0xFF}}},
	{{{-256, 2, -261},0, {1008, 1008},{0x2A, 0xA6, 0x4F, 0xFF}}},
	{{{-586, 0, -261},0, {1008, -16},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-586, 0, -592},0, {-16, -16},{0xB7, 0xB7, 0xB7, 0xFF}}},
	{{{-586, 0, -261},0, {-16, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-257, 511, -261},0, {1008, 1008},{0x8, 0x17, 0x7D, 0xFF}}},
	{{{-257, 600, -261},0, {1008, -16},{0x7D, 0xE9, 0x8, 0xFF}}},
	{{{-586, 581, -261},0, {-16, -16},{0xEA, 0xD6, 0x76, 0xFF}}},
	{{{-257, 0, 584},0, {-16, 1008},{0x49, 0xB7, 0x49, 0xFF}}},
	{{{-586, 0, 584},0, {1008, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-586, 2, 251},0, {1008, -16},{0xB1, 0xA6, 0xD6, 0xFF}}},
	{{{-257, 1, 251},0, {-16, -16},{0x4F, 0xA6, 0xD7, 0xFF}}},
	{{{-257, 599, 251},0, {-16, 1008},{0x8, 0xEA, 0x83, 0xFF}}},
	{{{256, 1, 251},0, {1008, 1008},{0xD7, 0xA6, 0xB1, 0xFF}}},
	{{{256, 2, 584},0, {1008, -16},{0xD6, 0xA6, 0x4F, 0xFF}}},
	{{{-257, 579, 584},0, {-16, -16},{0x27, 0xCE, 0x6E, 0xFF}}},
	{{{-257, 579, 584},0, {-16, 1008},{0x27, 0xCE, 0x6E, 0xFF}}},
	{{{256, 2, 584},0, {1008, 1008},{0xD6, 0xA6, 0x4F, 0xFF}}},
	{{{256, 531, 584},0, {1008, -16},{0xF7, 0x18, 0x7C, 0xFF}}},
	{{{-256, 1119, 584},0, {-16, -16},{0x2A, 0x5A, 0x4F, 0xFF}}},
	{{{-256, 2, -261},0, {-16, 1008},{0x2A, 0xA6, 0x4F, 0xFF}}},
	{{{-256, 2, -592},0, {1008, 1008},{0x2A, 0xA6, 0xB1, 0xFF}}},
	{{{257, 600, -592},0, {1008, -16},{0xF7, 0xE9, 0x83, 0xFF}}},
	{{{257, 600, -261},0, {-16, -16},{0xF7, 0xE9, 0x7D, 0xFF}}},
	{{{-586, 1119, -261},0, {-16, 1008},{0xB1, 0x5A, 0x2A, 0xFF}}},
	{{{-586, 529, 251},0, {1008, 1008},{0x84, 0x18, 0xF7, 0xFF}}},
	{{{-257, 510, 251},0, {1008, -16},{0x7D, 0x16, 0xF8, 0xFF}}},
	{{{-257, 1121, -261},0, {-16, -16},{0x50, 0x5A, 0x2A, 0xFF}}},
	{{{-586, 1124, 584},0, {-16, 1008},{0xB7, 0x4A, 0x4A, 0xFF}}},
	{{{-586, 0, 584},0, {1008, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
	{{{-257, 0, 584},0, {1008, -16},{0x49, 0xB7, 0x49, 0xFF}}},
};

Gfx logo_N64_Logo_mesh_tri_1[] = {
	gsSPVertex(logo_N64_Logo_mesh_vtx_1 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(3, 4, 5, 0),
	gsSP1Triangle(6, 7, 5, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_1 + 16, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_1 + 32, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_1 + 48, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_1 + 64, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_1 + 80, 15, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 3, 0),
	gsSPEndDisplayList(),
};Vtx logo_N64_Logo_mesh_vtx_2[24] = {
	{{{257, 1124, 584},0, {-16, 1008},{0xB6, 0x4A, 0x49, 0xFF}}},
	{{{586, 1124, 584},0, {1008, 1008},{0x4A, 0x4A, 0x49, 0xFF}}},
	{{{586, 1119, 251},0, {1008, -16},{0x4F, 0x59, 0xD5, 0xFF}}},
	{{{257, 1120, 251},0, {-16, -16},{0xB1, 0x59, 0xD5, 0xFF}}},
	{{{586, 1124, -261},0, {-16, 1008},{0x49, 0x49, 0x49, 0xFF}}},
	{{{586, 1124, -592},0, {1008, 1008},{0x49, 0x49, 0xB7, 0xFF}}},
	{{{256, 1121, -592},0, {1008, -16},{0xD5, 0x59, 0xB1, 0xFF}}},
	{{{256, 1121, -261},0, {-16, -16},{0xD5, 0x59, 0x4F, 0xFF}}},
	{{{257, 600, 251},0, {-16, 1008},{0x83, 0xEA, 0xF8, 0xFF}}},
	{{{257, 1, -261},0, {1008, 1008},{0xB1, 0xA6, 0x29, 0xFF}}},
	{{{586, 1, -261},0, {1008, -16},{0x4F, 0xA6, 0x2A, 0xFF}}},
	{{{586, 580, 251},0, {-16, -16},{0x41, 0xE0, 0x97, 0xFF}}},
	{{{-257, 1124, -592},0, {-16, 1008},{0x4A, 0x4A, 0xB7, 0xFF}}},
	{{{-586, 1124, -592},0, {1008, 1008},{0xB6, 0x4A, 0xB7, 0xFF}}},
	{{{-586, 1119, -261},0, {1008, -16},{0xB1, 0x5A, 0x2A, 0xFF}}},
	{{{-257, 1121, -261},0, {-16, -16},{0x50, 0x5A, 0x2A, 0xFF}}},
	{{{-256, 1119, 584},0, {-16, 1008},{0x2A, 0x5A, 0x4F, 0xFF}}},
	{{{-257, 1120, 251},0, {1008, 1008},{0x2A, 0x5A, 0xB0, 0xFF}}},
	{{{-586, 1124, 251},0, {1008, -16},{0xB7, 0x4A, 0xB6, 0xFF}}},
	{{{-586, 1124, 584},0, {-16, -16},{0xB7, 0x4A, 0x4A, 0xFF}}},
	{{{-586, 581, -261},0, {-16, 1008},{0xEA, 0xD6, 0x76, 0xFF}}},
	{{{-257, 600, -261},0, {1008, 1008},{0x7D, 0xE9, 0x8, 0xFF}}},
	{{{-257, 1, 251},0, {1008, -16},{0x4F, 0xA6, 0xD7, 0xFF}}},
	{{{-586, 2, 251},0, {-16, -16},{0xB1, 0xA6, 0xD6, 0xFF}}},
};

Gfx logo_N64_Logo_mesh_tri_2[] = {
	gsSPVertex(logo_N64_Logo_mesh_vtx_2 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(logo_N64_Logo_mesh_vtx_2 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};Vtx logo_N64_Logo_mesh_vtx_3[8] = {
	{{{-257, 1120, 251},0, {-16, 1008},{0x2A, 0x5A, 0xB0, 0xFF}}},
	{{{-256, 1119, 584},0, {1008, 1008},{0x2A, 0x5A, 0x4F, 0xFF}}},
	{{{256, 531, 584},0, {1008, -16},{0xF7, 0x18, 0x7C, 0xFF}}},
	{{{257, 510, 251},0, {-16, -16},{0xF8, 0x16, 0x83, 0xFF}}},
	{{{-257, 511, -261},0, {-16, 1008},{0x8, 0x17, 0x7D, 0xFF}}},
	{{{256, 1121, -261},0, {1008, 1008},{0xD5, 0x59, 0x4F, 0xFF}}},
	{{{256, 1121, -592},0, {1008, -16},{0xD5, 0x59, 0xB1, 0xFF}}},
	{{{-257, 511, -592},0, {-16, -16},{0x8, 0x17, 0x83, 0xFF}}},
};

Gfx logo_N64_Logo_mesh_tri_3[] = {
	gsSPVertex(logo_N64_Logo_mesh_vtx_3 + 0, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_logo_logo_blue[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(logo_logo_blue_lights),
	gsSPEndDisplayList(),
};


Gfx mat_logo_logo_green[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(logo_logo_green_lights),
	gsSPEndDisplayList(),
};


Gfx mat_logo_logo_yellow[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(logo_logo_yellow_lights),
	gsSPEndDisplayList(),
};


Gfx mat_logo_logo_red[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPSetLights1(logo_logo_red_lights),
	gsSPEndDisplayList(),
};


Gfx logo_N64_Logo_mesh[] = {
	gsSPDisplayList(mat_logo_logo_blue),
	gsSPDisplayList(logo_N64_Logo_mesh_tri_0),
	gsSPDisplayList(mat_logo_logo_green),
	gsSPDisplayList(logo_N64_Logo_mesh_tri_1),
	gsSPDisplayList(mat_logo_logo_yellow),
	gsSPDisplayList(logo_N64_Logo_mesh_tri_2),
	gsSPDisplayList(mat_logo_logo_red),
	gsSPDisplayList(logo_N64_Logo_mesh_tri_3),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



