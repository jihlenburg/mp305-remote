/* Address: CODE:9924; name: FUN_CODE_9924; body bytes: 24 */

void FUN_CODE_9924(void)

{
  byte bVar1;
  
  bVar1 = FIFLG1;
  FIFLG1 = bVar1 & 0xfb;
  DAT_INTMEM_cf = 0;
  DAT_INTMEM_d0 = 0;
  DAT_INTMEM_ce = 0;
  DAT_INTMEM_d1 = 0;
  DAT_SFR_c6 = 0;
  DAT_SFR_ce = 0;
  DAT_SFR_d6 = 0;
  HPSTAT = 0;
  return;
}

