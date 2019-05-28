#ifndef BIT2BUFF_H_
#define BIT2BUFF_H_

#include "gn_types.h"

#ifdef __cpluscplus
extern "C" {
#endif

extern void gn_add_long_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONG value);
#define gn_add_ulong_to_buffer(a,b,c,d,e)		gn_add_long_to_buffer((a), (b), (c), (d), (e))
extern GN_ULONG gn_get_ulong_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n);
extern GN_LONG gn_get_long_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n);
extern void gn_add_longlong_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONGLONG value);
extern GN_ULONGLONG gn_get_ulonglong_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n);
extern GN_LONGLONG gn_get_longlong_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n);
extern void gn_add_longS_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONG value);
extern GN_LONG gn_get_longS_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n);
extern void gn_add_longlongS_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONGLONG value);
extern GN_LONGLONG gn_get_longlongS_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n);
extern void gn_bits_skip_buffer_pos(long *byte_pos,long *bit_pos,long numbits);
extern GN_LONG gn_add_val_long_to_buffer(char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, long value);
extern GN_LONG gn_add_val_longlong_to_buffer(char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, GN_LONGLONG value);
extern GN_LONG gn_add_val_double_to_buffer(char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, double value, double factor);
extern GN_DOUBLE gn_get_val_double_from_buffer(const char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, double factor);

// new, untested NM 2019-01-11 -- do we have them somewhere else already ??? probably yes ...
double gn_get_double_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos);
float gn_get_float_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos);
void gn_add_double_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,double value);
void gn_add_float_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,float value);

#ifdef __cpluscplus
}
#endif
#endif

