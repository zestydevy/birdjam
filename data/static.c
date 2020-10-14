
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*---------------------------------------------------------------------*
        Copyright (C) 1997 Nintendo. (Originated by SGI)
        
        $RCSfile: static.c,v $
        $Revision: 1.6 $
        $Date: 1998/09/25 21:47:45 $
 *---------------------------------------------------------------------*/

/*
 * File:	static.c
 * Creator:	hsa@sgi.com
 * Create Date:	Sun Jun  4 18:49:42 PDT 1995
 *
 *
 * This file holds tiny display list segments that are 'static' data.
 *
 */

#include <ultra64.h>
#include "letters.h"

/*
 * Remember, viewport structures have 2 bits of fraction in them.
 */
static Vp vp = {
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* scale */
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* translate */
};

Gfx rspinit_dl[] = {
    gsSPViewport(&vp),
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
			  G_FOG | G_LIGHTING | G_TEXTURE_GEN |
			  G_TEXTURE_GEN_LINEAR | G_LOD ),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx rdpinit_dl[] = {
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetBlendMask(0xff),
    gsDPSetColorDither(G_CD_ENABLE),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};


Lights2 litc2 = gdSPDefLights2(0x5, 0x5, 0x5,		/* ambient color */
			       100, 100, 0,		/* light color */
			       -32, -64, -32, 			/* normal */
			       50, 50, 0,		/* light color */
			       15, 30, 120); 			/* normal */


Gfx letters_setup_dl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH | 
			G_CULL_BACK | G_LIGHTING),
    gsSPSetLights2(litc2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};


Gfx setting_setup_dl[] = {

    gsDPPipeSync (),
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH |
			  G_ZBUFFER | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
			  G_TEXTURE_GEN_LINEAR | G_LOD ),
    gsSPSetGeometryMode(G_SHADING_SMOOTH | G_SHADE ),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),

    gsSPEndDisplayList(),
};

static Vtx v[] = {
	/* Ground */
	{	 -16, -16, 0, 0, 0<<6,   0<<6,   255, 255, 255, 255 },
	{	  16, -16, 0, 0, 0<<6,   31<<6, 255, 255, 255, 255 },
	{	  16,  16, 0, 0, 31<<6, 31<<6, 255, 255, 255, 255 },
	{	 -16,  16, 0, 0, 31<<6, 0<<6,   255, 255, 255, 255 },
};


