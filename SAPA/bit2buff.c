#include "bit2buff.h"

#ifdef __WATCOMC__
#include <float.h>	/* _finite() */
#endif
//#include "platform.h"

static const unsigned char mask[9]={0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};


/**********************************************************************/
/*
 * Reihenfolge der Bits/Bytes im Byte Stream:
 * -------------- -------- -------- -------- -------- -------- -------- -------- --------
 * Stream bit*10  00000000 00111111 11112222 22222233 33333333 44444444 44555555 55556666
 * Stream bit*1   01234567 89012345 67890123 45678901 23456789 01234567 89012345 67890123
 * -------------- -------- -------- -------- -------- -------- -------- -------- --------
 * buffer byte         [0]      [1]      [2]      [3]      [4]      [5]      [6]      [7]
 * buffer bit     76543210 76543210 76543210 76543210 76543210 76543210 76543210 76543210
 * -------------- -------- -------- -------- -------- -------- -------- -------- --------
 */
/**********************************************************************/

/* Bits in den Puffer schieben */
void gn_add_long_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONG value)
{	// Schiebt alle Werte bis 32 Bits (signed, unsigned in Buffer)
#if 0
	
	/* check for out-of-range condition, AB 2010-08-23 */
	if(1) {		/* noch nicht nicht getestet */
		const GN_LONG chk=n<32?-1<<n:0;	/* in chk sind alle n bits gesetzt */
		if(abs(value)&chk) {		/* value passt nicht in n bits! */
			value=1<<(n-1);	/* set to min possible negative value, ie. 'data not available' (in RTCM3 defined only for signed ints! Macht aber auch Sinn fuer zu grosse unsigneds) */
		}
	}
#endif
	while(n) {
		const int m=8-(*bit_pos);		// soviel Bits sind noch frei im aktuellen Byte
		if(*bit_pos==0) buffer[*byte_pos]='\0';		// neues Byte angefangen, mit 0 initialisieren
		if(m>n) {	// Byte wird nicht voll, noch genug Platz im aktuellen Byte fuer alle Bits
			const int k=m-n;	// Restbits, bleiben nach dem Schreiben noch frei
			*bit_pos += n;
			buffer[*byte_pos]|=(((unsigned char)(value))&mask[n])<<k;
			break;
		}
		else { // Byte wird voll
			*bit_pos=0;
			buffer[*byte_pos]|=(((unsigned char)(value>>(n-m)))&mask[m]);
			(*byte_pos)++;
			n -= m;
		}
	}
} /* gn_add_long_to_buffer() */

/**********************************************************************/
#define gn_add_ulong_to_buffer(a,b,c,d,e)		gn_add_long_to_buffer((a), (b), (c), (d), (e))

/**********************************************************************/

void gn_add_longS_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONG value)
{	// Signed Magnitude Integer to BUFFER
	const GN_LONG valueM=abs(value);
	if(value<0) {
		gn_add_long_to_buffer(buffer,byte_pos,bit_pos,1,1);	/* sign bit set */
	}
	else {
		gn_add_long_to_buffer(buffer,byte_pos,bit_pos,1,0);	/* sign bit not set */
	}
	gn_add_long_to_buffer(buffer,byte_pos,bit_pos,n-1,valueM);	/* Absolut-Wert schreiben */
} /* add_longS_to_buffer() */

/**********************************************************************/

GN_ULONG gn_get_ulong_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n)
{
	GN_ULONG v=0;
	while(n) {
		const int m=8-(*bit_pos);
		if(m>n) {	// Byte wird nicht voll
			const int k=m-n;	// Restbits
			*bit_pos += n;
			v |= ((GN_ULONG)((buffer[*byte_pos]>>k)&mask[n]));
			break;
		}
		else { // Byte wird voll
			*bit_pos=0;
			v |= ((GN_ULONG)((buffer[*byte_pos])&mask[m]))<<(n-m);
			(*byte_pos)++;
			n -= m;
		}
	}
	return(v);
} /* gn_get_ulong_from_buffer() */

/**********************************************************************/

GN_LONG gn_get_long_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n)
{
	const int ms=(32-n);
	const GN_LONG v=gn_get_ulong_from_buffer(buffer,byte_pos,bit_pos,n);
	return ((v<<ms)>>ms);	// VZ reinschiften (ACHTUNG: ">>" ist implementationsabhaengig fuer signed types!)
} /* gn_get_long_from_buffer() */

/**********************************************************************/

GN_LONG gn_get_longS_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n)
{
	const unsigned int sgn=gn_get_ulong_from_buffer(buffer,byte_pos,bit_pos,1);
	const GN_LONG v=gn_get_ulong_from_buffer(buffer,byte_pos,bit_pos,n-1);
	if(sgn) return(-v);
	else return(v);
} /* get_longS_from_buffer() */

/**********************************************************************/

void gn_add_longlong_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONGLONG value)
{	// Schiebt alle Werte bis 64 Bits (signed, unsigned in Buffer)
#if 0
	/* check for out-of-range condition, AB 2010-08-23 */
	if(1) {		/* noch nicht nicht getestet */
		const GN_LONGLONG chk=n<32?-1<<n:0;	/* in chk sind alle n bits gesetzt */
		if(abs(value)&chk) {		/* value passt nicht in n bits! */
			value=1<<(n-1);	/* set to min possible negative value, ie. 'data not available' (in RTCM3 defined only for signed ints! Macht aber auch Sinn fuer zu grosse unsigneds) */
		}
	}
#endif
	while(n) {
		const int m=8-(*bit_pos);		// soviel Bits sind noch frei im aktuellen Byte
		if(*bit_pos==0) buffer[*byte_pos]='\0';		// neues Byte angefangen, mit 0 initialisieren
		if(m>n) {	// Byte wird nicht voll, noch genug Platz im aktuellen Byte fuer alle Bits
			const int k=m-n;	// Restbits, bleiben nach dem Schreiben noch frei
			*bit_pos += n;
			buffer[*byte_pos]|=(((unsigned char)(value))&mask[n])<<k;
			break;
		}
		else { // Byte wird voll
			*bit_pos=0;
			buffer[*byte_pos]|=(((unsigned char)(value>>(n-m)))&mask[m]);
			(*byte_pos)++;
			n -= m;
		}
	}
} /* gn_add_longlong_to_buffer() */

/**********************************************************************/

void gn_bits_skip_buffer_pos(long *byte_pos,long *bit_pos,long numbits)
{
	int nbytes=numbits/8;
	int nbits=numbits-nbytes*8;
	(*byte_pos) += nbytes;
	(*bit_pos) += nbits;
	if(*bit_pos>=8) {
		(*bit_pos) -= 8;
		(*byte_pos) += 1;
	}
	return;
} /* gn_bits_skip_buffer_pos() */

/**********************************************************************/

void gn_add_longlongS_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,long n,GN_LONGLONG value)
{	// Signed Magnitude Integer to BUFFER
	const GN_LONGLONG valueM= (value>=0 ? value : -value);
	if(value<0) {
		gn_add_long_to_buffer(buffer,byte_pos,bit_pos,1,1);	/* sign bit schreiben */
	}
	else {
		gn_add_long_to_buffer(buffer,byte_pos,bit_pos,1,0);	/* sign bit schreiben */
	}
	gn_add_longlong_to_buffer(buffer,byte_pos,bit_pos,n-1,valueM);	/* Absolut-Wert schreiben */
} /* add_longlongS_to_buffer() */

/**********************************************************************/

GN_ULONGLONG gn_get_ulonglong_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n)
{
	GN_ULONGLONG v=0;
	while(n) {
		const int m=8-(*bit_pos);
		if(m>n) {	// Byte wird nicht voll
			const int k=m-n;	// Restbits
			*bit_pos += n;
			v |= ((GN_ULONGLONG)((buffer[*byte_pos]>>k)&mask[n]));
			break;
		}
		else { // Byte wird voll
			*bit_pos=0;
			v |= ((GN_ULONGLONG)((buffer[*byte_pos])&mask[m]))<<(n-m);
			(*byte_pos)++;
			n -= m;
		}
	}
	return(v);
} /* gn_get_ulonglong_from_buffer() */

/**********************************************************************/

GN_LONGLONG gn_get_longlong_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n)
{
	const int ms=(64-n);
	const GN_LONGLONG v=gn_get_ulonglong_from_buffer(buffer,byte_pos,bit_pos,n);
	return ((v<<ms)>>ms);	// VZ reinschiften (ACHTUNG: ">>" ist implementationsabhaengig fuer signed types!)
} /* gn_get_longlong_from_buffer() */

/**********************************************************************/

GN_LONGLONG gn_get_longlongS_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos,long n)
{
	const unsigned int sgn=gn_get_ulong_from_buffer(buffer,byte_pos,bit_pos,1);		/* sign bit lesen */
	const GN_LONGLONG v=gn_get_ulonglong_from_buffer(buffer,byte_pos,bit_pos,n-1);	/* Absolut-Wert lesen */
	if(sgn) return(-v);
	else return(v);
} /* get_longlongS_from_buffer() */

/**********************************************************************/

/*
 * validate long value and push into buffer if valid, else push invalid bitfield
 */
GN_LONG gn_add_val_long_to_buffer(char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, long value)
{
	const long valid = ((unsigned long)0xffffffff>>(33-bits));				/* alle bits Bits ausser MSB gesetzt */

	/* Sonderfaelle int25 und int26 (Tippfehler in RTCM3 Standard?) Wird wohl in 3.1 Amd.5 korrigiert */
	//if(bits==25) valid = (unsigned long)-(RTCM3_INVALID_INT25+1);	/* 16777203 entspricht 0xFFFFF3 */
	//if(bits==26) valid = (unsigned long)-(RTCM3_INVALID_INT26+1);	/* 33554407 entspricht 0x1FFFFE7 */

	if(value>valid || value<-valid) {	/* does not fit into available bits */
		gn_add_long_to_buffer(buffer, byte_pos, bit_pos, bits, -valid-1);	/* entspricht alle bits Bits gesetzt */
		return -1;
	}
	else {
		gn_add_long_to_buffer(buffer, byte_pos, bit_pos, bits, value);
		return 0;
	}
} /* gn_add_val_long_to_buffer() */

/**********************************************************************/

/*
 * validate long long value and push into buffer if valid, else push invalid bitfield
 */
GN_LONG gn_add_val_longlong_to_buffer(char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, GN_LONGLONG value)
{
	// Integer constant 0xffffffffffffffff requires suffix ULL in GCC, which is unknown in Watcom
	const GN_LONGLONG valid = (((((GN_ULONGLONG)0xffffffff)<<32)|((GN_ULONGLONG)0xffffffff))>>(65-bits));		/* alle bits Bits ausser MSB gesetzt */
	if(value>valid || value<-valid) {	/* does not fit into available bits */
		gn_add_longlong_to_buffer(buffer, byte_pos, bit_pos, bits, -valid-1);	/* entspricht alle bits Bits gesetzt */
		return -1;
	}
	else {
		gn_add_longlong_to_buffer(buffer, byte_pos,  bit_pos, bits, value);
		return 0;
	}
} /* gn_add_val_longlong_to_buffer() */
/*
 * Get double value from buffer using gn_long and gn_longlong data fields based on bits.
 */
extern GN_DOUBLE gn_get_val_double_from_buffer(const char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, double factor)
{
	if (bits < 32) { /* Read 32 bit data from buffer  */
		GN_LONG lval = gn_get_long_from_buffer(buffer, byte_pos, bit_pos, bits);
		return (lval*factor);
	}
	else { /* Read 64 bit data from buffer */
		GN_LONGLONG lval = gn_get_longlong_from_buffer(buffer, byte_pos, bit_pos, bits);
		return (lval*factor);
	}
} /* gn_get_val_double_from_buffer() */

/**********************************************************************/

#include <math.h>	/* floor() */
// Internal Defintions
// Konvertiert einen Double d in LONGLONG mit Faktor 1/s
#define RTCM3X_GN_DOUBLE_TO_GN_LONGLONG(d,s) ((GN_LONGLONG)floor(((d)/(GN_DOUBLE)(s)+0.5)))

// Konvertiert einen Double d in LONG mit Faktor 1/s
#define RTCM3X_GN_DOUBLE_TO_GN_LONG(d,s) ((GN_LONG)floor(((d)/(s)+0.5)))

/**********************************************************************/

/*
 * validate double value and push into buffer if valid, else push invalid bitfield
 */
GN_LONG gn_add_val_double_to_buffer(char *buffer, long *byte_pos, long *bit_pos, unsigned int bits, double value, double factor)
{
	if(bits<32) {
		const long lval = RTCM3X_GN_DOUBLE_TO_GN_LONG(value,factor);
		return gn_add_val_long_to_buffer(buffer, byte_pos, bit_pos, bits, lval);
	}
	else {	/* 64 bit required (long long) */
		const GN_LONGLONG lval = RTCM3X_GN_DOUBLE_TO_GN_LONGLONG(value,factor);
		return gn_add_val_longlong_to_buffer(buffer, byte_pos, bit_pos, bits, lval);
	}
} /* gn_add_val_double_to_buffer() */

/**********************************************************************/

/* functions for float & double -- 1zu1 aus gnzdm.c,  NM 2019-01-11 */
static int gn_add_float_to_buffer_intern(float v,unsigned char **buffer);
static int gn_get_float_from_buffer_intern(float *v,const unsigned char **buffer);
static int gn_add_double_to_buffer_intern(double v,unsigned char **buffer);
static int gn_get_double_from_buffer_intern(double *v,const unsigned char **buffer);

double gn_get_double_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos)
{
	GN_ULONGLONG ull;
	double v=0.0;
	unsigned char *uc = (unsigned char *)&ull;
	ull = gn_get_ulonglong_from_buffer(buffer,byte_pos,bit_pos,64);
	gn_get_double_from_buffer_intern(&v,&uc);
	return v;
}

float gn_get_float_from_buffer(const unsigned char *buffer,long *byte_pos,long *bit_pos)
{
	GN_ULONG ul;
	float v=0.0;
	unsigned char *uc = (unsigned char *)&ul;
	ul = gn_get_ulong_from_buffer(buffer,byte_pos,bit_pos,32);
	gn_get_float_from_buffer_intern(&v,&uc);
	return v;
}

void gn_add_double_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,double value)
{
	GN_LONGLONG ull;
	unsigned char *uc = (unsigned char *)&ull;
	gn_add_double_to_buffer_intern(value,&uc);
	gn_add_longlong_to_buffer(buffer, byte_pos, bit_pos, 64, ull);
}

void gn_add_float_to_buffer(unsigned char *buffer,long *byte_pos,long *bit_pos,float value)
{
	GN_ULONG ul;
	unsigned char *uc = (unsigned char *)&ul;
	gn_add_float_to_buffer_intern(value,&uc);
	gn_add_ulong_to_buffer(buffer, byte_pos, bit_pos, 32, ul);
}

#if BYTE_ORDER==BIG_ENDIAN
static void b2b_swapn(void *buffer,int n)
{
	if(n>=2) {
		unsigned char *i, *j;
		i=buffer;
		j=buffer;
		j += n-1;
		while(i<j) {
			unsigned char c=*i;
			*i++ = *j;
			*j-- = c;
		}
	}
}
#else
  #define b2b_swapn(b,n) {}
  //static void b2b_swapn(void *buffer,int n) { return; }
#endif

static int gn_add_float_to_buffer_intern(float v,unsigned char **buffer)
{
	GN_FLOAT vf=v;
	memcpy(*buffer,&vf,sizeof(GN_FLOAT));
	b2b_swapn(*buffer,sizeof(GN_FLOAT));
	*buffer += sizeof(GN_FLOAT);
	return(sizeof(GN_FLOAT));
}

static int gn_get_float_from_buffer_intern(float *v,const unsigned char **buffer)
{
	GN_FLOAT vf;
	memcpy(&vf,*buffer,sizeof(GN_FLOAT));
	b2b_swapn(&vf,sizeof(GN_FLOAT));
	*buffer += sizeof(GN_FLOAT);
	*v = vf;
	return(sizeof(GN_FLOAT));
}

static int gn_add_double_to_buffer_intern(double v,unsigned char **buffer)
{
	GN_DOUBLE vf=v;
	memcpy(*buffer,&vf,sizeof(GN_DOUBLE));
	b2b_swapn(*buffer,sizeof(GN_DOUBLE));
	*buffer += sizeof(GN_DOUBLE);
	return(sizeof(GN_DOUBLE));
}

static int gn_get_double_from_buffer_intern(double *v,const unsigned char **buffer)
{
	GN_DOUBLE vf;
	memcpy(&vf,*buffer,sizeof(GN_DOUBLE));
	b2b_swapn(&vf,sizeof(GN_DOUBLE));
	*buffer += sizeof(GN_DOUBLE);
#ifdef __WATCOMC__
	if(_finite(vf)) 	// extra check to avoid FPE crash with illegal input data, AB 2010-01-15
#endif
		*v = vf;
	return(sizeof(GN_DOUBLE));
}

