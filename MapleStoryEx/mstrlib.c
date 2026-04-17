#include "mstrlib.h"

#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
    MSTR_BLOCK16 = 0,
    MSTR_BLOCK32 = 1,
    MSTR_BLOCK64 = 2,
    MSTR_BLOCK128 = 3,
    MSTR_BLOCK_COUNT = 4
};

typedef struct mstrllocator {
    volatile long lock;
    void *free_head[MSTR_BLOCK_COUNT];
    void *block_head[MSTR_BLOCK_COUNT];
} mstrllocator;

static mstrllocator g_mstr_alloc_a;

static void mstr_lock(volatile long *lock)
{
    while (InterlockedCompareExchange(lock, 1, 0) != 0) {
        Sleep(0);
    }
}

static void mstr_unlock(volatile long *lock)
{
    InterlockedExchange(lock, 0);
}

static size_t mstr_max_size_flag(void)
{
    return ((size_t)1) << ((sizeof(size_t) * CHAR_BIT) - 1);
}

static size_t mstr_block_size(size_t element_size, size_t capacity)
{
    return (element_size * capacity) + sizeof(MStrData) + element_size;
}

static size_t mstr_block_size_by_index(size_t element_size, int index, int *alloc_blocks)
{
    switch (index) {
    case MSTR_BLOCK16:
        *alloc_blocks = 64;
        return mstr_block_size(element_size, 16);
    case MSTR_BLOCK32:
        *alloc_blocks = 32;
        return mstr_block_size(element_size, 32);
    case MSTR_BLOCK64:
        *alloc_blocks = 16;
        return mstr_block_size(element_size, 64);
    case MSTR_BLOCK128:
        *alloc_blocks = 8;
        return mstr_block_size(element_size, 128);
    default:
        *alloc_blocks = 0;
        return 0;
    }
}

static int mstr_block_index_for_size(size_t element_size, size_t size)
{
    if (size <= mstr_block_size(element_size, 16)) {
        return MSTR_BLOCK16;
    }

    if (size <= mstr_block_size(element_size, 32)) {
        return MSTR_BLOCK32;
    }

    if (size <= mstr_block_size(element_size, 64)) {
        return MSTR_BLOCK64;
    }

    if (size <= mstr_block_size(element_size, 128)) {
        return MSTR_BLOCK128;
    }

    return -1;
}

static int mstr_block_index_for_exact_size(size_t element_size, size_t size)
{
    if (size == mstr_block_size(element_size, 16)) {
        return MSTR_BLOCK16;
    }

    if (size == mstr_block_size(element_size, 32)) {
        return MSTR_BLOCK32;
    }

    if (size == mstr_block_size(element_size, 64)) {
        return MSTR_BLOCK64;
    }

    if (size == mstr_block_size(element_size, 128)) {
        return MSTR_BLOCK128;
    }

    return -1;
}

static void **mstr_alloc_raw_blocks(size_t block_size, unsigned int block_count)
{
    unsigned int i;
    size_t stride = block_size + sizeof(void *);
    size_t total_size = (block_count * stride) + (sizeof(void *) * 2);
    unsigned char *raw = (unsigned char *)HeapAlloc(GetProcessHeap(), 0, total_size);
    void **block;

    if (raw == NULL) {
        return NULL;
    }

    ((void **)raw)[0] = (void *)(uintptr_t)(total_size - sizeof(void *));
    ((void **)raw)[1] = NULL;

    block = (void **)(raw + (sizeof(void *) * 3));
    block[-1] = (void *)(uintptr_t)block_size;

    for (i = 0; i + 1 < block_count; ++i) {
        void **next = (void **)(((unsigned char *)block) + stride);
        *block = next;
        next[-1] = (void *)(uintptr_t)block_size;
        block = next;
    }

    *block = NULL;
    return (void **)(raw + (sizeof(void *) * 3));
}

static void *mstr_allocator_alloc(mstrllocator *allocator, size_t element_size, size_t size)
{
    int block_index = mstr_block_index_for_size(element_size, size);
    void **result;
    int alloc_blocks;
    size_t block_size;

    if (block_index < 0) {
        void **large = (void **)HeapAlloc(GetProcessHeap(), 0, size + sizeof(void *));

        if (large == NULL) {
            return NULL;
        }

        *large = (void *)(uintptr_t)size;
        return large + 1;
    }

    block_size = mstr_block_size_by_index(element_size, block_index, &alloc_blocks);

    mstr_lock(&allocator->lock);

    if (allocator->free_head[block_index] == NULL) {
        void **block_head = mstr_alloc_raw_blocks(block_size, (unsigned int)alloc_blocks);

        if (block_head == NULL) {
            mstr_unlock(&allocator->lock);
            return NULL;
        }

        block_head[-2] = allocator->block_head[block_index];
        allocator->block_head[block_index] = block_head;
        allocator->free_head[block_index] = block_head;
    }

    result = (void **)allocator->free_head[block_index];
    allocator->free_head[block_index] = *result;

    mstr_unlock(&allocator->lock);
    return result;
}

static void mstr_allocator_free(mstrllocator *allocator, size_t element_size, void *ptr)
{
    void **block = (void **)ptr;
    size_t size;
    int block_index;

    if (block == NULL) {
        return;
    }

    size = (size_t)(uintptr_t)block[-1];

    if ((size & mstr_max_size_flag()) != 0) {
        size = ~size;
    }

    block_index = mstr_block_index_for_exact_size(element_size, size);

    if (block_index < 0) {
        HeapFree(GetProcessHeap(), 0, block - 1);
        return;
    }

    mstr_lock(&allocator->lock);
    *block = allocator->free_head[block_index];
    allocator->free_head[block_index] = block;
    mstr_unlock(&allocator->lock);
}

static MStrData *mstr_data_from_buffer(const void *buffer)
{
    if (buffer == NULL) {
        return NULL;
    }

    return (MStrData *)(((unsigned char *)buffer) - sizeof(MStrData));
}

static MStrData *mstr_alloc_data(mstrllocator *allocator, size_t element_size, size_t capacity)
{
    size_t total_size = mstr_block_size(element_size, capacity);
    MStrData *data = (MStrData *)mstr_allocator_alloc(allocator, element_size, total_size);

    if (data != NULL) {
        data->nCap = capacity;
    }

    return data;
}

static void mstr_release_data(mstrllocator *allocator, size_t element_size, MStrData *data)
{
    if (data != NULL && InterlockedDecrement(&data->nRef) <= 0) {
        mstr_allocator_free(allocator, element_size, data);
    }
}

static size_t mstr_length_bytes(const void *buffer)
{
    MStrData *data = mstr_data_from_buffer(buffer);
    return data != NULL ? data->nByteLen : 0;
}

static void *mstr_get_buffer_impl(
    void **buffer,
    size_t min_length,
    BOOL retain,
    size_t element_size,
    mstrllocator *allocator)
{
    MStrData *cur_data = NULL;
    MStrData *new_data;
    size_t str_length = 0;

    if (buffer == NULL) {
        return NULL;
    }

    if (*buffer != NULL) {
        cur_data = mstr_data_from_buffer(*buffer);

        if (cur_data != NULL) {
            if (cur_data->nRef <= 1 && cur_data->nCap >= min_length) {
                cur_data->nRef = -1;
                return *buffer;
            }

            str_length = cur_data->nByteLen / element_size;
        }
    }

    if (str_length < min_length) {
        str_length = min_length;
    }

    new_data = mstr_alloc_data(allocator, element_size, str_length);

    if (new_data == NULL) {
        return NULL;
    }

    new_data->nRef = -1;
    *buffer = (void *)(new_data + 1);

    if (retain && cur_data != NULL) {
        size_t copy_size = cur_data->nByteLen + element_size;
        memcpy(new_data + 1, cur_data + 1, copy_size);
        new_data->nByteLen = cur_data->nByteLen;
    } else {
        new_data->nByteLen = 0;
        memset(*buffer, 0, element_size);
    }

    if (cur_data != NULL) {
        mstr_release_data(allocator, element_size, cur_data);
    }

    return *buffer;
}
static void mstr_release_buffer_impl(void *buffer, size_t length, size_t element_size)
{
    MStrData *data = mstr_data_from_buffer(buffer);

    if (data == NULL) {
        return;
    }

    data->nRef = 1;

    if (length == (size_t)-1) {
        if (element_size == sizeof(char)) {
            data->nByteLen = strlen((const char *)(data + 1)) * element_size;
        } else {
            data->nByteLen = wcslen((const wchar_t *)(data + 1)) * element_size;
        }
    } else {
        unsigned char *nul = ((unsigned char *)(data + 1)) + (length * element_size);
        memset(nul, 0, element_size);
        data->nByteLen = length * element_size;
    }
}

static void mstr_empty_impl(void **buffer, size_t element_size, mstrllocator *allocator)
{
    if (buffer != NULL && *buffer != NULL) {
        mstr_release_data(allocator, element_size, mstr_data_from_buffer(*buffer));
        *buffer = NULL;
    }
}

static void mstr_assign_impl(
    void **dst,
    const void *src_buffer,
    size_t element_size,
    mstrllocator *allocator)
{
    MStrData *new_data;

    if (dst == NULL || *dst == src_buffer) {
        return;
    }

    if (src_buffer != NULL) {
        new_data = mstr_data_from_buffer(src_buffer);

        if (new_data != NULL) {
            if (new_data->nRef == -1) {
                size_t src_length = new_data->nByteLen / element_size;
                void *dst_buffer = mstr_get_buffer_impl(dst, src_length, FALSE, element_size, allocator);

                if (dst_buffer != NULL) {
                    memcpy(dst_buffer, src_buffer, new_data->nByteLen);
                    mstr_release_buffer_impl(dst_buffer, src_length, element_size);
                }
            } else {
                InterlockedIncrement(&new_data->nRef);
                mstr_empty_impl(dst, element_size, allocator);
                *dst = (void *)(new_data + 1);
            }

            return;
        }
    }

    mstr_empty_impl(dst, element_size, allocator);
}

static BOOL mstr_compare_impl(const void *lhs_buffer, const void *rhs_buffer, size_t element_size)
{
    size_t lhs_len;
    size_t rhs_len;

    if (lhs_buffer == rhs_buffer) {
        return TRUE;
    }

    lhs_len = mstr_length_bytes(lhs_buffer) / element_size;
    rhs_len = mstr_length_bytes(rhs_buffer) / element_size;

    if (lhs_len == rhs_len && lhs_buffer != NULL && rhs_buffer != NULL) {
        return memcmp(lhs_buffer, rhs_buffer, lhs_len * element_size) == 0;
    }

    return FALSE;
}

void mstr_init(mstr *str)
{
    if (str != NULL) {
        str->m_pStr = NULL;
    }
}

void mstr_init_cstr(mstr *str, const char *value, int length)
{
    mstr_init(str);
    mstr_assign_cstr(str, value, length);
}

void mstr_destroy(mstr *str)
{
    mstr_empty(str);
}

void mstr_empty(mstr *str)
{
    if (str != NULL) {
        mstr_empty_impl((void **)&str->m_pStr, sizeof(char), &g_mstr_alloc_a);
    }
}

size_t mstr_length(const mstr *str)
{
    return (str != NULL && str->m_pStr != NULL)
        ? mstr_data_from_buffer(str->m_pStr)->nByteLen / sizeof(char)
        : 0;
}

BOOL mstr_is_empty(const mstr *str)
{
    return str == NULL || str->m_pStr == NULL || *str->m_pStr == '\0';
}

const char *mstr_c_str(const mstr *str)
{
    return str != NULL ? str->m_pStr : NULL;
}

MStrData *mstr_data(const mstr *str)
{
    return str != NULL ? mstr_data_from_buffer(str->m_pStr) : NULL;
}

void mstr_assign(mstr *dst, const mstr *src)
{
    if (dst == NULL || dst == src) {
        return;
    }

    mstr_assign_impl(
        (void **)&dst->m_pStr,
        src != NULL ? src->m_pStr : NULL,
        sizeof(char),
        &g_mstr_alloc_a);
}

void mstr_assign_cstr(mstr *dst, const char *value, int length)
{
    char *buffer;
    size_t char_count;

    if (dst == NULL) {
        return;
    }

    if (value == NULL) {
        mstr_empty(dst);
        return;
    }

    char_count = length < 0 ? strlen(value) : (size_t)length;
    buffer = mstr_get_buffer(dst, char_count, FALSE);

    if (buffer == NULL) {
        return;
    }

    memcpy(buffer, value, char_count * sizeof(char));
    mstr_release_buffer(dst, char_count);
}

BOOL mstr_compare(const mstr *lhs, const mstr *rhs)
{
    return mstr_compare_impl(
        lhs != NULL ? lhs->m_pStr : NULL,
        rhs != NULL ? rhs->m_pStr : NULL,
        sizeof(char));
}

BOOL mstr_compare_cstr(const mstr *lhs, const char *rhs)
{
    if (lhs == NULL || lhs->m_pStr == NULL) {
        return rhs == NULL;
    }

    if (rhs == NULL) {
        return FALSE;
    }

    return strcmp(lhs->m_pStr, rhs) == 0;
}

BOOL mstr_compare_no_case(const mstr *lhs, const char *rhs)
{
    if (lhs == NULL || lhs->m_pStr == NULL) {
        return rhs == NULL;
    }

    if (rhs == NULL) {
        return FALSE;
    }

    return _stricmp(lhs->m_pStr, rhs) == 0;
}

mstr *mstr_concat(mstr *dst, const char *value, int length)
{
    size_t append_len;
    size_t old_len;
    size_t required_len;
    size_t capacity;
    char *buffer;
    MStrData *data;

    if (dst == NULL || value == NULL) {
        return dst;
    }

    append_len = length < 0 ? strlen(value) : (size_t)length;

    if (append_len == 0) {
        return dst;
    }

    if (mstr_is_empty(dst)) {
        mstr_assign_cstr(dst, value, (int)append_len);
        return dst;
    }

    data = mstr_data_from_buffer(dst->m_pStr);
    old_len = data->nByteLen / sizeof(char);
    required_len = old_len + append_len;
    capacity = data->nCap;

    while (capacity < required_len) {
        capacity = capacity == 0 ? required_len : capacity * 2;
    }

    buffer = mstr_get_buffer(dst, capacity, TRUE);

    if (buffer == NULL) {
        return dst;
    }

    old_len = mstr_data_from_buffer(buffer)->nByteLen / sizeof(char);
    memcpy(buffer + old_len, value, append_len * sizeof(char));
    mstr_release_buffer(dst, required_len);
    return dst;
}

char *mstr_get_buffer(mstr *str, size_t min_length, BOOL retain)
{
    if (str == NULL) {
        return NULL;
    }

    return (char *)mstr_get_buffer_impl(
        (void **)&str->m_pStr,
        min_length,
        retain,
        sizeof(char),
        &g_mstr_alloc_a);
}

void mstr_release_buffer(mstr *str, size_t length)
{
    if (str != NULL) {
        mstr_release_buffer_impl(str->m_pStr, length, sizeof(char));
    }
}
void mstr_format(mstr *str, const char *format, ...)
{
    int written = -1;
    int capacity;
    va_list args;

    if (str == NULL) {
        return;
    }

    if (format == NULL) {
        mstr_empty(str);
        return;
    }

    va_start(args, format);

    for (capacity = 16; capacity <= 1024; capacity *= 2) {
        char *buffer = mstr_get_buffer(str, (size_t)capacity, FALSE);
        va_list copy;

        if (buffer == NULL) {
            break;
        }

#if defined(va_copy)
        va_copy(copy, args);
#elif defined(__va_copy)
        __va_copy(copy, args);
#else
        copy = args;
#endif

        written = _vsnprintf_s(buffer, (size_t)capacity + 1, _TRUNCATE, format, copy);
        va_end(copy);

        if (written >= 0) {
            mstr_release_buffer(str, (size_t)written);
            break;
        }

        mstr_release_buffer(str, 0);
    }

    va_end(args);

    if (written < 0) {
        mstr_empty(str);
    }
}