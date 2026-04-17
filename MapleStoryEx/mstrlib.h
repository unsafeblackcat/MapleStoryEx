#ifndef MSTRLIB_H
#define MSTRLIB_H

#include <stddef.h>
#include <wchar.h>
#include <windows.h>

typedef struct MStrData {
    volatile long nRef;
    size_t nCap;
    size_t nByteLen;
} MStrData;

typedef struct mstr {
    char *m_pStr;
} mstr;
  
void mstr_init(mstr *str);
void mstr_init_cstr(mstr *str, const char *value, int length);
void mstr_destroy(mstr *str);
void mstr_empty(mstr *str);
size_t mstr_length(const mstr *str);
BOOL mstr_is_empty(const mstr *str);
const char *mstr_c_str(const mstr *str);
MStrData *mstr_data(const mstr *str);
void mstr_assign(mstr *dst, const mstr *src);
void mstr_assign_cstr(mstr *dst, const char *value, int length);
BOOL mstr_compare(const mstr *lhs, const mstr *rhs);
BOOL mstr_compare_cstr(const mstr *lhs, const char *rhs);
BOOL mstr_compare_no_case(const mstr *lhs, const char *rhs);
mstr *mstr_concat(mstr *dst, const char *value, int length);
char *mstr_get_buffer(mstr *str, size_t min_length, BOOL retain);
void mstr_release_buffer(mstr *str, size_t length);
void mstr_format(mstr *str, const char *format, ...);

#endif
