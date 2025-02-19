#ifndef texcache_h_
# define texcache_h_

#include "mio.hpp"
#include "polymost.h"
#include "mdsprite.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "vfs.h"

#ifdef USE_OPENGL

#define TEXCACHEMAGIC "LZ41"
#define GLTEXCACHEADSIZ 8192
#define TEXCACHEHASHSIZE 1024

enum texcacherr_t
{
    TEXCACHERR_NOERROR,
    TEXCACHERR_OUTOFMEMORY,  /* unused */
    TEXCACHERR_BUFFERUNDERRUN,
    TEXCACHERR_DEDXT,
    TEXCACHERR_COMPTEX,
    TEXCACHERR_GETTEXLEVEL,
    TEXCACHEERRORS
};

typedef struct texcacheitem_
{
    char    *name;
    int32_t offset;
    int32_t len;

    struct texcacheitem_ *next;
} texcacheindex;

typedef struct {
    mio::mmap_sink rw_mmap;
    buildvfs_FILE  indexFilePtr;
    buildvfs_FILE  dataFilePtr;

    texcacheindex * first;
    texcacheindex * current;
    texcacheindex **entries;

    pthtyp *list[GLTEXCACHEADSIZ];

    hashtable_t hashes;

    int32_t numentries;
    int32_t entrybufsiz;
    bsize_t dataFilePos;
} globaltexcache;

extern globaltexcache texcache;

extern char TEXCACHEFILE[BMAX_PATH];

extern int32_t texcache_enabled(void);
extern void texcache_freeptrs(void);
extern void texcache_syncmemcache(void);
extern void texcache_init(void);
int texcache_loadoffsets(void);
int texcache_readdata(void *outBuf, int32_t len);
extern pthtyp *texcache_fetch(uint16_t dapicnum, int32_t dapalnum, int32_t dashade, int32_t dameth);
extern int32_t texcache_loadskin(const texcacheheader *head, int32_t *doalloc, GLuint *glpic, vec2_t *siz);
extern int32_t texcache_loadtile(const texcacheheader *head, int32_t *doalloc, pthtyp *pth);
extern char const * texcache_calcid(char *outbuf, const char *filename, int32_t len, int32_t dameth, char effect);
extern void texcache_prewritetex(texcacheheader *head);
void texcache_postwritetex(char const * cacheid, int32_t offset);
extern void texcache_writetex_fromdriver(char const * cacheid, texcacheheader *head);
extern int texcache_readtexheader(char const * cacheid, texcacheheader *head, int32_t modelp);
extern void texcache_openfiles(void);
extern void texcache_setupmemcache(void);
extern void texcache_checkgarbage(void);
extern void texcache_setupindex(void);

extern voxmodel_t* voxcache_fetchvoxmodel(const char* const cacheid);
extern void voxcache_writevoxmodel(const char* const cacheid, voxmodel_t* vm);

#endif

#ifdef __cplusplus
}
#endif

#endif
