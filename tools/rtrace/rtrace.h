/* range trace (test only): per-leaf statistics of every field, global and object while AxisRC runs */
#ifndef RT_U8
#define RT_U8
typedef unsigned char rt_u8;
#endif
typedef struct { const char *name; char kind; int esz, slen; } Leaf;
extern Leaf rt_leaves[];
extern const int rt_leafCount;
extern const char *const rt_structNames[];
extern const int rt_structCount;
void rt_O(int id, const rt_u8 *p, int n, int esz);      /* n scalars of esz bytes */
void rt_S(int id, const rt_u8 *p, int n, int slen);     /* n strings of slen bytes */
void rt_root(const rt_u8 *p, int type, unsigned size);    /* a pointer to a record: snapshot and walk */
void rt_walk_static(void);
void rt_walk_scene(const rt_u8 *sc);
void rt_walk_any(int t, const rt_u8 *p);
const rt_u8 *rt_scene(void);
void rt_walk_textures(void);
