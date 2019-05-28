
#ifndef __GN_TYPES__
#define __GN_TYPES__

#if defined(__WATCOMC__) || (defined(USING_GPP_OS2INCLUDE) && defined(__OS2__))

  #if defined(__OS2__)				// Windows, Watcom mit os2win32 und OS2 Headern

	#ifndef OS2_INCLUDED
	 #define  INCL_DOSSEMAPHORES
	 #include <os2.h>
	#endif

	#ifndef __OS2DEF__
	 #include <os2def.h>
	#endif

	#ifndef INCL_DOSSEMAPHORES
	 typedef  ULONG    HMUX;
	 typedef  HMUX     *PHMUX;
	#endif

  #elif defined(__NT__)				// Windows, Watcom mit os2win32 und NT Headern

	#include <windows.h>
	typedef unsigned long	PID;
	typedef unsigned long	TID;
	typedef unsigned long	HEV;
	typedef unsigned long	HSEM;
	typedef unsigned long	HMUX;
	typedef unsigned long	HMTX;
	typedef struct _PSEMRECORD
	{
	  HSEM        hsemCur;
	  ULONG       ulUser;
	} SEMRECORD;
	typedef SEMRECORD *PSEMRECORD;
  #endif

#elif defined(_WIN32) || defined(_WIN64)			 	// Windows 32/64 mit MSVC oder GNU gcc oder ...

  // include <windows.h> defines min(), max() Macro in WinDef.h which collides with STL templates !
  // Workaround here:
  //      http://stackoverflow.com/questions/4913922/possible-problems-with-nominmax-on-visual-c
  #ifdef __cplusplus
    #ifndef NOMINMAX
      #define NOMINMAX
    #endif
  #endif

  #include <windows.h>
  typedef unsigned long	PID;
  typedef unsigned long	TID;
  typedef unsigned long	HEV;
  typedef unsigned long	HSEM;
  typedef unsigned long	HMUX;
  typedef unsigned long	HMTX;
	typedef struct _PSEMRECORD
	{
	  HSEM        hsemCur;
	  ULONG       ulUser;
	} SEMRECORD;
  typedef SEMRECORD *PSEMRECORD;
  typedef const char *PCSZ;

#else								// Linux, Unix oder alles andere


  typedef unsigned long	PID;
  typedef unsigned long	TID;
  typedef unsigned long	HEV;
  typedef unsigned long	HMUX;

  #ifndef FALSE
    #define FALSE   0
  #endif

  #ifndef TRUE
    #define TRUE    1
  #endif

  #ifndef NULL
    #ifdef __cplusplus
      #define NULL 0
    #else
	  #if defined(__GNUC__)
        #define NULL 0
      #else
        #define NULL ((void *)0)
      #endif
    #endif
  #endif

  #define CHAR		char
  #define SHORT		short
  #define LONG		long
  #define VOID		void
  #define INT		int

  typedef unsigned char  UCHAR;
  typedef unsigned short USHORT;
  typedef unsigned long  ULONG;
  typedef unsigned int   UINT;
  typedef unsigned char  BYTE;

  typedef unsigned char *PSZ;
  typedef unsigned char *NPSZ;
  typedef unsigned char *PCH;
  typedef unsigned char *NPCH;
  typedef unsigned char *PCSZ;

  typedef BYTE *PBYTE;
  typedef BYTE *NPBYTE;

  typedef CHAR *PCHAR;
  typedef SHORT *PSHORT;
  typedef LONG *PLONG;

  typedef INT *PINT;

  typedef UCHAR *PUCHAR;
  typedef USHORT *PUSHORT;
  typedef ULONG *PULONG;

  typedef UINT *PUINT;

  typedef VOID   *PVOID;
  typedef PVOID  *PPVOID;

  typedef unsigned long BOOL;
  typedef BOOL *PBOOL;

  typedef unsigned short  BOOL16;

  #define BOOL32    BOOL
  #define PBOOL32   PBOOL

#endif

/******** GN_TYPES fuer alle Systeme/Compiler ***********/


#define GN_CHAR  CHAR		/* ch  */
#define GN_SHORT SHORT		/* s   */
#define GN_LONG  LONG		/* l   */
#define GN_INT   INT		/* i*4 */
#define GN_VOID  VOID		/* void */
#define GN_BOOL	 BOOL		/* ULONG */

typedef UCHAR 		GN_UCHAR;		/* uch */
typedef USHORT		GN_USHORT;		/* us  */
typedef ULONG		GN_ULONG;		/* ul  */
typedef BYTE		GN_BYTE;		/* b   */

/****** GN_LONGLONG, GN_ULONGLONG  ***********************/

#if defined(__WATCOMC__)

  #ifdef __WATCOM_INT64__
	typedef __int64           GN_LONGLONG;
	typedef unsigned __int64  GN_ULONGLONG;
  #endif


#elif defined(_MSC_VER)

  #if _MSC_VER <= 1200
   typedef __int64          GN_LONGLONG;
   typedef unsigned __int64 GN_ULONGLONG;
  #elif defined(_WIN64)
	typedef __int64          GN_LONGLONG;
	typedef unsigned __int64 GN_ULONGLONG;
//   typedef long				GN_LONGLONG;
 //  typedef unsigned long		GN_ULONGLONG;
  #else
   typedef long long		  GN_LONGLONG;
   typedef unsigned long long GN_ULONGLONG;
  #endif

#elif defined(__GNUC__)

  #ifndef __STDC_CONSTANT_MACROS
    #define __STDC_CONSTANT_MACROS
  #endif
  #ifndef __STDC_LIMIT_MACROS
    #define __STDC_LIMIT_MACROS
  #endif

  #include <stdint.h>  // defines all the nice types like int8_t, uint8_t, int16_t, ... according C99 std
  typedef int64_t 	GN_LONGLONG;
  typedef uint64_t    GN_ULONGLONG;

#else

   typedef long long int GN_LONGLONG;
   typedef unsigned long long int GN_ULONGLONG;

#endif

/************ der Rest ...  ****************/

#define GN_DOUBLE	double
#define GN_FLOAT	float

typedef TID		 	GN_TID;  // Thread ID
typedef HEV			GN_HEV;	 // Event Sempaphore
typedef HMUX        GN_HMUX; // Mutex Semaphore

#endif // __GN_TYPES__
