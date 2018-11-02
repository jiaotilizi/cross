/*
 * $Id: sbZfKaEpIpPriExpTosRewrite.c,v 1.2 Broadcom SDK $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 */


#include "sbTypes.h"
#include "sbZfKaEpIpPriExpTosRewrite.hx"
#include "sbWrappers.h"
#include <sal/types.h>



/* Pack from struct into array of bytes */
uint32
sbZfKaEpIpPriExpTosRewrite_Pack(sbZfKaEpIpPriExpTosRewrite_t *pFrom,
                                uint8 *pToData,
                                uint32 nMaxToDataIndex) {
#ifdef SAND_BIG_ENDIAN_HOST
  int i;
  int size = SB_ZF_ZFKAEPIPPRIEXPTOSREWRITE_SIZE_IN_BYTES;

  if (size % 4) {
    size += (4 - size %4);
  }

  for ( i=0; i<size; i++ ) {
    (pToData)[i] = 0;
  }
  i = 0;

  /* Pack operation based on bigword endian */

  /* Pack Member: m_nTos */
  (pToData)[3] |= ((pFrom)->m_nTos) & 0xFF;
#else
  int i;
  int size = SB_ZF_ZFKAEPIPPRIEXPTOSREWRITE_SIZE_IN_BYTES;

  if (size % 4) {
    size += (4 - size %4);
  }

  for ( i=0; i<size; i++ ) {
    (pToData)[i] = 0;
  }
  i = 0;

  /* Pack operation based on little endian */

  /* Pack Member: m_nTos */
  (pToData)[0] |= ((pFrom)->m_nTos) & 0xFF;
#endif

  return SB_ZF_ZFKAEPIPPRIEXPTOSREWRITE_SIZE_IN_BYTES;
}




/* Unpack from array of bytes into struct */
void
sbZfKaEpIpPriExpTosRewrite_Unpack(sbZfKaEpIpPriExpTosRewrite_t *pToStruct,
                                  uint8 *pFromData,
                                  uint32 nMaxToDataIndex) {
  COMPILER_UINT64 tmp;

  (void) tmp;

#ifdef SAND_BIG_ENDIAN_HOST

  /* Unpack operation based on bigword endian */

  /* Unpack Member: m_nTos */
  (pToStruct)->m_nTos =  (uint32)  (pFromData)[3] ;
#else

  /* Unpack operation based on little endian */

  /* Unpack Member: m_nTos */
  (pToStruct)->m_nTos =  (uint32)  (pFromData)[0] ;
#endif

}



/* initialize an instance of this zframe */
void
sbZfKaEpIpPriExpTosRewrite_InitInstance(sbZfKaEpIpPriExpTosRewrite_t *pFrame) {

  pFrame->m_nTos =  (unsigned int)  0;

}
