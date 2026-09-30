/* Address: CODE:a449; name: FUN_CODE_a449; body bytes: 10 */

void FUN_CODE_a449(void)

{
  byte bVar1;
  
  DAT_SFR_ce = 0xee;
  bVar1 = DAT_SFR_c2;
  DAT_SFR_c2 = bVar1 | 4;
  bVar1 = FIFLG1;
  FIFLG1 = bVar1 | 4;
  return;
}

