/* Address: CODE:5e73; name: FUN_CODE_5e73; body bytes: 64 */

void FUN_CODE_5e73(char param_1)

{
  byte bVar1;
  short sVar2;
  
  _1_6 = 0;
  DAT_EXTMEM_04c5 = param_1;
  FUN_CODE_a727();
  if (DAT_EXTMEM_04c5 != param_1) {
    bVar1 = DAT_EXTMEM_04c5 - 1;
    if ((bVar1 < 9) << 7 < '\0') {
      sVar2 = 0x5e9a;
      if (CARRY1(bVar1,bVar1)) {
        sVar2 = 0x5f9a;
      }
                    /* WARNING: Could not recover jumptable at 0x5e99. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(sVar2 + (ushort)(bVar1 * '\x02')))();
      return;
    }
    FUN_CODE_a72d(DAT_EXTMEM_04c5);
  }
  return;
}

