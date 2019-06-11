/*
 * Copyright 2015 Geo++ GmbH, Germany, www.geopp.de
 * All rights reserved
 */

#ifndef GPP_COMPILER_H
#define GPP_COMPILER_H

/* Basic Type Dfinitions */

#if defined __GNUC__

  #if (__GNUC__ >= 3)
    #define HAVE_PRAGMA_PACK
  #endif

  //#if defined(__GLIBC__) || defined(ANDROID)
  #define __STDC_CONSTANT_MACROS
  #define __STDC_LIMIT_MACROS
  #include <stdint.h>  // defines all the nice types like int8_t, uint8_t, int16_t, ... according C99 std
  #include <math.h>    // defines float_t and 
_t according C99 std
  #define DEFINE_PER_C99

  #ifndef __cplusplus
    #ifndef min
    #define min(a,b) (((a)<=(b))?(a):(b))
    #endif // min
    #ifndef max
    #define max(a,b) (((a)>=(b))?(a):(b))
    #endif
  #endif

  #if defined(_WIN32)

    #define GPP_API_CALLING_CONVENTION __cdecl

    #if defined GPP_DLL_EXPORT	/* gesetzt in dbtrafo.c */
      /* Funktion wird von DLL exportiert, ersetzt die "EXPORT" Linker Directive: */
      #define GPP_API __declspec(dllexport)
    #elif defined GPP_DLL_IMPORT
      #define GPP_API __declspec(dllimport)
    #else   // ! GPP_DLL_EXPORT
      /* Funktion wird aus DLL importiert: */
      #define GPP_API
    #endif  // GPP_DLL_EXPORT

  #else

    #define GPP_API_CALLING_CONVENTION
	#define GPP_API

  #endif

#elif defined __SUNPRO_C

  #include <stdint.h>  // defines all the nice types like int8_t, uint8_t, int16_t, ... according C99 std
  #include <math.h>    // defines float_t and double_t according C99 std
  #define DEFINE_PER_C99

  #define GPP_API
  #define GPP_API_CALLING_CONVENTION __global

#elif defined __WATCOMC__

  #define DEFINE_PER_SIZE
  #define COMPILER32
  #define INTBYTES4
  #define SHORTBYTES2
  #define LONGBYTES4
  #define LONGLONG8
  #define LONGLONG8_TYPE	__int64
  #define ULONGLONG8_TYPE	unsigned __int64
  #define FLOATBYTES4
  #define DOUBLEBYTES8
  #define HAVE_PRAGMA_PACK

  #if defined GPP_DLL_EXPORT	/* gesetzt in dbtrafo.c */
    /* Funktion wird von DLL exportiert, ersetzt die "EXPORT" Linker Directive: */
    #define GPP_API __declspec(dllexport)
  #elif defined GPP_DLL_IMPORT
    #define GPP_API __declspec(dllimport)
  #else   // ! GPP_DLL_EXPORT
    /* Funktion wird aus DLL importiert: */
    #define GPP_API
  #endif  // GPP_DLL_EXPORT

  #if defined (HAB_NT) || defined(WINNT) || defined(__NT__)
    #define GPP_API_CALLING_CONVENTION __cdecl	/* DLL fuer alle neuen DLLs mit MSVC compilierte NT-EXEs */
  #else
    #ifdef __OS2__
      #define GPP_API_CALLING_CONVENTION _System	/* DLL fuer alle neuen DLLs mit MSVC compilierte NT-EXEs */
    #else
      #define GPP_API_CALLING_CONVENTION __cdecl	/* DLL fuer alle neuen DLLs mit MSVC compilierte NT-EXEs */
    #endif
  #endif

#elif defined (_MSC_VER)

#if !defined(_WIN64)
#define COMPILER32
#else
#define COMPILER64
#endif
  #define DEFINE_PER_SIZE
  #define INTBYTES4
  #define SHORTBYTES2
  #define LONGBYTES4
  #define LONGLONG8
  #define LONGLONG8_TYPE	__int64
  #define ULONGLONG8_TYPE	unsigned __int64
  #define FLOATBYTES4
  #define DOUBLEBYTES8
  #define HAVE_PRAGMA_PACK

  #if defined GPP_DLL_EXPORT	/* gesetzt in dbtrafo.c */
    /* Funktion wird von DLL exportiert, ersetzt die "EXPORT" Linker Directive: */
    #define GPP_API __declspec(dllexport)
  #elif defined GPP_DLL_IMPORT
    #define GPP_API __declspec(dllimport)
  #else   // ! GPP_DLL_EXPORT
    /* Funktion wird aus DLL importiert: */
    #define GPP_API
  #endif  // GPP_DLL_EXPORT

  #define GPP_API_CALLING_CONVENTION __cdecl	/* DLL fuer alle neuen DLLs mit MSVC compilierte NT-EXEs */

#elif defined(SWIG)

	typedef int GPPINT4;
	typedef int GPPLONG;
	typedef unsigned int GPPUINT4;
	typedef unsigned int GPPULONG;
	typedef unsigned int GPPBOOL;
	typedef unsigned int GPPBOOL4;

	typedef short GPPINT2;
	typedef short GPPSHORT;
	typedef unsigned short GPPUINT2;
	typedef unsigned short GPPUSHORT;
	typedef unsigned short GPPBOOL2;

	typedef	signed char		GPPINT1;
	typedef	unsigned char	GPPUINT1;
	typedef	signed char		GPPBYTE;
	typedef	signed char		GPPCHAR;
	typedef unsigned char 	GPPUCHAR;

	typedef	signed char*	PGPPINT1;
	typedef	unsigned char*	PGPPUINT1;
	typedef	signed char*	PGPPBYTE;
	typedef	signed char*	PGPPCHAR;
	typedef unsigned char* 	PGPPUCHAR;

	typedef float	GPPFLOAT;
	typedef float	GPPREAL4;
	typedef double	GPPDOUBLE;
	typedef	double	GPPREAL8;

	%ignore GPPSYSVOID;
	struct GPPSYSVOID {
	} GPPSYSVOID;
	typedef GPPSYSVOID* GPPHANDLE;

  #if !defined(SWIGWORDSIZE32) && \
      (defined(SWIGWORDSIZE64) || defined(__x86_64) || defined(__x86_64__) || (__WORDSIZE == 64))
	typedef long GPPLONGLONG;
	typedef unsigned long GPPULONGLONG;
	typedef long GPPINT8;
	typedef unsigned long GPPUINT8;

  #else
	typedef long long GPPLONGLONG;
	typedef unsigned long long GPPULONGLONG;
	typedef long long GPPINT8;
	typedef unsigned long long GPPUINT8;
  #endif

#else

  #error "compiler.h lacks support for your compiler !"

#endif


#ifdef DEFINE_PER_C99  // works with C99 standard int types

typedef int64_t 	GPPLONGLONG;
typedef uint64_t 	GPPULONGLONG;
typedef int64_t 	GPPINT8;
typedef uint64_t 	GPPUINT8;

typedef int32_t 	GPPINT4;
typedef int32_t 	GPPLONG;
typedef uint32_t 	GPPUINT4;
typedef uint32_t 	GPPULONG;
typedef uint32_t 	GPPBOOL;
typedef uint32_t 	GPPBOOL4;

typedef int16_t 	GPPINT2;
typedef int16_t 	GPPSHORT;
typedef uint16_t 	GPPUINT2;
typedef uint16_t 	GPPUSHORT;
typedef uint16_t 	GPPBOOL2;

typedef int8_t		GPPINT1;
typedef uint8_t		GPPUINT1;
typedef int8_t		GPPBYTE;
typedef int8_t		GPPCHAR;
typedef uint8_t		GPPUCHAR;

typedef float		GPPFLOAT;
typedef float		GPPREAL4;
typedef double		GPPDOUBLE;
typedef	double		GPPREAL8;

#if 0
#ifdef FLT_EVAL_METHOD
#if (FLT_EVAL_METHOD == 0) // defined in math.h for C99, says: float is 4 bytes, double is 8 bytes
typedef float_t		GPPFLOAT;
typedef float_t		GPPREAL4;
typedef double_t	GPPDOUBLE;
typedef	double_t	GPPREAL8;
#else
#error "float and double do not have the right size, please fix in compiler.h"
#endif
#else
#error "float and double do may not have the right size, please fix in compiler.h"
#endif
#endif

#elif defined DEFINE_PER_SIZE  // works with all compilers without using special header files


#if defined(LONGBYTES4)
	#define GPPINT4	long
	#define GPPLONG long
	typedef unsigned long GPPUINT4;
	typedef unsigned long GPPULONG;
	typedef unsigned long GPPBOOL;
	typedef unsigned long GPPBOOL4;
#elif defined(INTBYTES4)
	#define GPPINT4	int
	#define GPPLONG int
	typedef unsigned int GPPUINT4;
	typedef unsigned int GPPULONG;
	typedef unsigned int GPPBOOL;
	typedef unsigned int GPPBOOL4;
#else
#error "Need 4 Byte Integer Type in compiler.h"
#endif

#ifdef SHORTBYTES2
	#define GPPINT2 	short
	#define GPPSHORT 	short
	typedef unsigned short GPPUINT2;
	typedef unsigned short GPPUSHORT;
	typedef unsigned short GPPBOOL2;
#else
#error "Need 2 Byte Integer Type in compiler.h"
#endif

typedef	signed char		GPPINT1;
typedef	unsigned char	GPPUINT1;
typedef	signed char		GPPBYTE;
typedef	signed char		GPPCHAR;
typedef unsigned char 	GPPUCHAR;

typedef	signed char*		PGPPINT1;
typedef	unsigned char*		PGPPUINT1;
typedef	signed char*		PGPPBYTE;
typedef	signed char*		PGPPCHAR;
typedef unsigned char* 		PGPPUCHAR;

#ifdef FLOATBYTES4
	#define GPPFLOAT	float
	#define GPPREAL4  	float
#else
#error "Need 4 Byte Float Type in compiler.h"
#endif

#ifdef DOUBLEBYTES8
	#define GPPDOUBLE	double
	#define GPPREAL8  	double
#else
	error "Need 8 Byte Float Type in compiler.h"
#endif

#ifdef LONGLONG8
#define GPPLONGLONG		LONGLONG8_TYPE
#define GPPULONGLONG	ULONGLONG8_TYPE
#define GPPINT8			LONGLONG8_TYPE
#define GPPUINT8		ULONGLONG8_TYPE
#endif

#endif
#undef DEFINE_PER_C99   // only used inside this file
#undef DEFINE_PER_SIZE  // only used inside this file

#if !defined(SWIG)
  // Handles					! ACHTUNG fuer 64 Bit hier ANPASSEN
  #ifdef GPP_64_BIT
    #define GPPHANDLE	GPPULONGLONG
  #else
    #define GPPHANDLE	GPPULONG
  #endif
#endif

/* Void und Pointers */
#define GPPVOID		void
typedef GPPVOID		*PGPPVOID;
typedef PGPPVOID	*PPGPPVOID;
#define GPPINT	int

#if defined(_WIN32)
  #define SNPRINTF		_snprintf
  #define VSNPRINTF		_vsnprintf
  #define FSOPEN		_fsopen
  #define FSOPEN_ARG	1
#else
  #define SNPRINTF		snprintf
  #define VSNPRINTF		vsnprintf
  #define FSOPEN		fopen
#endif




#endif  // GPP_COMPILER_H
