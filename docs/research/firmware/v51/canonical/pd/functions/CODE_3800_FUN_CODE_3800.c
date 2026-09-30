/* Address: CODE:3800; name: FUN_CODE_3800; body bytes: 59 */

void FUN_CODE_3800(char param_1,char param_2)

{
  byte bVar1;
  undefined *puVar2;
  
  _1_4 = 0;
  DAT_EXTMEM_04b3 = param_2;
  DAT_EXTMEM_04b4 = param_1;
  if (param_1 == param_2) {
    if (param_2 == '\x01') {
      _1_4 = 1;
    }
  }
  else {
    bVar1 = param_1 - 1;
    if ((bVar1 < 8) << 7 < '\0') {
      puVar2 = &UNK_CODE_3822;
      if (CARRY1(bVar1,bVar1)) {
        puVar2 = &UNK_CODE_3922;
      }
                    /* WARNING: Could not recover jumptable at 0x3821. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(puVar2 + bVar1 * '\x02'))();
      return;
    }
    FUN_CODE_6293(0x754,param_1);
  }
  return;
}

