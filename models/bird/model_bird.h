typedef struct {
   short ob[3]; /* x, y, z */
} VtxPos_t;
typedef union {
   VtxPos_t v; /* for color */
   long long int 
      force_structure_alignment;
} VtxPos;

extern Vtx bird_Bird_mesh_vtx_0[636];
extern Gfx bird_Bird_mesh_tri_0[];
extern Vtx bird_Bird_mesh_vtx_1[162];
extern Gfx bird_Bird_mesh_tri_1[];
extern Vtx bird_Bird_mesh_vtx_2[180];
extern Gfx bird_Bird_mesh_tri_2[];
extern Vtx bird_Bird_mesh_vtx_3[18];
extern Gfx bird_Bird_mesh_tri_3[];

extern int bird_Bird_FlyFlap_Length;
extern VtxPos* bird_Bird_FlyFlap_0[];
extern VtxPos* bird_Bird_FlyFlap_1[];
extern VtxPos* bird_Bird_FlyFlap_2[];
extern VtxPos* bird_Bird_FlyFlap_3[];

extern int bird_Bird_FlyStart_Length;
extern VtxPos* bird_Bird_FlyStart_0[];
extern VtxPos* bird_Bird_FlyStart_1[];
extern VtxPos* bird_Bird_FlyStart_2[];
extern VtxPos* bird_Bird_FlyStart_3[];

extern int bird_Bird_Walk_Length;
extern VtxPos* bird_Bird_Walk_0[];
extern VtxPos* bird_Bird_Walk_1[];
extern VtxPos* bird_Bird_Walk_2[];
extern VtxPos* bird_Bird_Walk_3[];

extern Gfx bird_Bird_mesh[];