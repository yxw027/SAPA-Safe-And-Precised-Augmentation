#include "compiler.h"
#ifndef GPPTIME_H_
#define GPPTIME_H_


#ifdef __cplusplus
	extern "C" {
#endif

#if defined(_WIN32)
#pragma pack(push,1)
#endif



typedef struct GPPT_WNT {	// Zeitdarstellung in Wochen (GPS) und Sekunden in der Woche
	GPPINT2		wn;
	GPPDOUBLE 	t;
} GPPT_WNT,*pGPPT_WNT;

#define INTRN_CORRECT_ROLLOVER(w,t,rollover) \
if((t<0.0)||(t>=rollover)) { \
int nw=floor((t)/rollover); \
t -= nw*rollover; \
w += nw; \
}

#define GPPT_WNT_ADJUST(pt) INTRN_CORRECT_ROLLOVER(pt->wn,pt->t,604800.0e0)

#define GPP_T_DIFF(w1,t1,w2,t2) (((w1)!=(w2))?(((w2)-(w1))*604800.0e0+(t2)-(t1)):((t2)-(t1)))

#ifdef __cplusplus
	}
#endif

#endif
