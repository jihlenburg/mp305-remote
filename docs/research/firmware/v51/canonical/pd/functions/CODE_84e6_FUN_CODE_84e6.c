/* Address: CODE:84e6; name: FUN_CODE_84e6; body bytes: 57 */

void FUN_CODE_84e6(undefined1 *param_1,char param_2)

{
  undefined1 uVar1;
  char cVar2;
  char *pcVar3;
  undefined1 *puVar4;
  
  uVar1 = BANK0_R7;
  FUN_CODE_8000();
  FUN_CODE_3401();
  *param_1 = 0;
  pcVar3 = &DAT_EXTMEM_0390;
  if (DAT_EXTMEM_0390 != '\0') {
    FUN_CODE_34e6();
    cVar2 = *pcVar3;
    if ((cVar2 != 'c') && (cVar2 + 0x9fU < 5)) {
      FUN_CODE_3401(param_2 + 'V');
      *pcVar3 = cVar2;
    }
  }
  puVar4 = &DAT_EXTMEM_0390;
  if (DAT_EXTMEM_0390 == '\x01') {
    FUN_CODE_34e6();
    *puVar4 = uVar1;
  }
  return;
}

