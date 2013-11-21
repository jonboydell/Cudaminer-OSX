#ifndef LEGACY_KERNEL_H
#define LEGACY_KERNEL_H

#include "salsa_kernel.h"

#define EXTRA_WARPS 0

class LegacyKernel : public KernelInterface
{
public:
    LegacyKernel();

    virtual void set_scratchbuf_constants(int MAXWARPS, uint32_t** h_V);
    virtual bool run_kernel(dim3 grid, dim3 threads, int WARPS_PER_BLOCK, int thr_id, cudaStream_t stream, uint32_t* d_idata, uint32_t* d_odata, int *mutex, bool interactive, bool benchmark, int texture_cache);
    virtual bool bindtexture_1D(uint32_t *d_V, size_t size);
    virtual bool bindtexture_2D(uint32_t *d_V, int width, int height, size_t pitch);
    virtual bool unbindtexture_1D();
    virtual bool unbindtexture_2D();

    virtual char get_identifier() { return 'L'; };
#if EXTRA_WARPS
    virtual int max_warps_per_block() { return 8; };
#else
    virtual int max_warps_per_block() { return 3; };
#endif
    virtual int get_texel_width() { return 2; };
    virtual cudaSharedMemConfig shared_mem_config() { return cudaSharedMemBankSizeFourByte; }
};

#endif // #ifndef LEGACY_KERNEL_H