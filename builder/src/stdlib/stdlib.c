/* stdlib.c */
#include "stdlib.h"
#include "string.h" /* for memset in calloc */

static unsigned char *heap_ptr = 0;
static unsigned char *heap_end = 0;

/* In a real environment, these might be provided by the linker or runtime. */
extern unsigned char __heap_base; /* symbol marking start of free memory in Wasm */
extern unsigned char __heap_end;  /* optional symbol marking end. */

static void init_heap(void) {
    if (!heap_ptr) {
        heap_ptr = &__heap_base;
        if (&__heap_end > &__heap_base) {
            heap_end = &__heap_end;
        } else {
            /* fallback: pick some arbitrary limit, e.g. 1MB */
            heap_end = heap_ptr + 1024*1024;
        }
    }
}

void *malloc(size_t size) {
    init_heap();
    if (size == 0) return 0;

    /* align to 8 bytes */
    size_t align_mask = 7;
    size_t aligned = (size + align_mask) & ~align_mask;
    if (heap_ptr + aligned > heap_end) {
        /* out of memory */
        return 0;
    }
    unsigned char *p = heap_ptr;
    heap_ptr += aligned;
    return p;
}

void free(void *ptr) {
    /* no-op for a bump allocator */
    (void)ptr;
}

void *calloc(size_t nmemb, size_t size) {
    size_t total = nmemb * size;
    void *p = malloc(total);
    if (p) {
        memset(p, 0, total);
    }
    return p;
}

void *realloc(void *ptr, size_t size) {
    /* naive: always alloc new block, copy old data. real usage would store block sizes. */
    if (!ptr) return malloc(size);
    void *newp = malloc(size);
    if (!newp) return 0;
    /* we have no idea how large ptr was, let's just do a blind copy of size. */
    memcpy(newp, ptr, size);
    return newp;
}

