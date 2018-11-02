/*
 * $Id: $
 * $Copyright: (c) 2016 Broadcom.
 * Broadcom Proprietary and Confidential. All rights reserved.$
 */
#include <shared/bsl.h>

#include "sbTypes.h"
#include <soc/sbx/sbWrappers.h>
#include "sbZfFabBm9600NmEgressRankerEntryConsole.hx"



/* Print members in struct */
void
sbZfFabBm9600NmEgressRankerEntry_Print(sbZfFabBm9600NmEgressRankerEntry_t *pFromStruct) {
  LOG_WARN(BSL_LS_SOC_COMMON,
           (BSL_META("FabBm9600NmEgressRankerEntry:: seed=0x%02x"), (unsigned int)  pFromStruct->m_uSeed));
  LOG_WARN(BSL_LS_SOC_COMMON,
           (BSL_META("\n")));

}

/* SPrint members in struct */
char *
sbZfFabBm9600NmEgressRankerEntry_SPrint(sbZfFabBm9600NmEgressRankerEntry_t *pFromStruct, char *pcToString, uint32 lStrSize) {
  uint32 WrCnt = 0x0;

  WrCnt += SB_SPRINTF(&pcToString[WrCnt],"FabBm9600NmEgressRankerEntry:: seed=0x%02x", (unsigned int)  pFromStruct->m_uSeed);
  WrCnt += SB_SPRINTF(&pcToString[WrCnt],"\n");

  /* assert if we've overrun the buffer */
  SB_ASSERT(WrCnt < lStrSize);
  return(pcToString);

}

/* validate members in struct (1 = PASS, 0 = FAIL) */
int
sbZfFabBm9600NmEgressRankerEntry_Validate(sbZfFabBm9600NmEgressRankerEntry_t *pZf) {

  if (pZf->m_uSeed > 0x7f) return 0;

  return 1; /* success */

}

/* populate field from string and value */
int
sbZfFabBm9600NmEgressRankerEntry_SetField(sbZfFabBm9600NmEgressRankerEntry_t *s, char* name, int value) {

  if (SB_STRCMP(name, "") == 0 ) {
    return -1;
  } else if (SB_STRCMP(name, "m_useed") == 0) {
    s->m_uSeed = value;
  } else {
    /* string failed to match any field--ignored */
    return -1;
  }

  return(0);

}
