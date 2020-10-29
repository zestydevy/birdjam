typedef struct {
   short ob[3]; /* x, y, z */
} VtxPos_t;
typedef union {
   VtxPos_t v; /* for color */
   long long int 
      force_structure_alignment;
} VtxPos;

extern Vtx wingstest_Bird_mesh_vtx_0[636];
extern Gfx wingstest_Bird_mesh_tri_0[];
extern Vtx wingstest_Bird_mesh_vtx_1[162];
extern Gfx wingstest_Bird_mesh_tri_1[];
extern Vtx wingstest_Bird_mesh_vtx_2[180];
extern Gfx wingstest_Bird_mesh_tri_2[];
extern Vtx wingstest_Bird_mesh_vtx_3[18];
extern Gfx wingstest_Bird_mesh_tri_3[];

extern int wingstest_Bird_WingsOpen_Length;
extern VtxPos* wingstest_Bird_WingsOpen_0[24];
extern VtxPos* wingstest_Bird_WingsOpen_1[24];
extern VtxPos* wingstest_Bird_WingsOpen_2[24];
extern VtxPos* wingstest_Bird_WingsOpen_3[24];

extern Gfx wingstest_Bird_mesh[];