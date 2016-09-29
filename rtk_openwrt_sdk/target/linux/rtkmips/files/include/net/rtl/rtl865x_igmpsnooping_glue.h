/*
* Copyright c                  Realsil Semiconductor Corporation, 2006
* All rights reserved.
* 
* Program :  IGMP glue file
* Abstract : 
* Author :qinjunjie 
* Email:qinjunjie1980@hotmail.com
*
*/

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef SUCCESS
#define SUCCESS 	0
#endif

#ifndef FAILED
#define FAILED -1
#endif

  
#if 0  
#ifndef _RTL_TYPES_H
typedef unsigned int	uint32;
typedef int			int32;
typedef unsigned short	uint16;
typedef short			int16;
typedef unsigned char	uint8;
typedef char			int8;
#endif
#else
#include "rtl_types.h"
#endif

#ifndef RTL_MULTICAST_SNOOPING_GLUE
#define RTL_MULTICAST_SNOOPING_GLUE


#define swapl32(x)\
        ((((x) & 0xff000000U) >> 24) | \
         (((x) & 0x00ff0000U) >>  8) | \
         (((x) & 0x0000ff00U) <<  8) | \
         (((x) & 0x000000ffU) << 24))
#define swaps16(x)        \
        ((((x) & 0xff00) >> 8) | \
         (((x) & 0x00ff) << 8))

#ifdef _LITTLE_ENDIAN

#ifndef ntohs
	#define ntohs(x)   (swaps16(x))
#endif 

#ifndef ntohl
	#define ntohl(x)   (swapl32(x))
#endif

#ifndef htons
	#define htons(x)   (swaps16(x))
#endif

#ifndef htonl
	#define htonl(x)   (swapl32(x))
#endif

#else

#ifndef ntohs
	#define ntohs(x)	(x)
#endif 

#ifndef ntohl
	#define ntohl(x)	(x)
#endif

#ifndef htons
	#define htons(x)	(x)
#endif

#ifndef htonl
	#define htonl(x)	(x)
#endif

#endif

#ifdef __KERNEL__
	#define rtl_gluePrintf printk
#else
	#define rtl_gluePrintf printf 
#endif


void *rtl_glueMalloc(uint32 NBYTES);
void rtl_glueFree(void *memblock);

void rtl_glueMutexLock(void);
void rtl_glueMutexUnlock(void);

#endif



