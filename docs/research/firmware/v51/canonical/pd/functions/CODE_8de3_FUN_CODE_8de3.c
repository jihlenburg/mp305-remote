/* Address: CODE:8de3; name: FUN_CODE_8de3; body bytes: 40 */

void FUN_CODE_8de3(char *param_1)

{
  char cVar1;
  char cVar2;
  char in_PSW;
  
  FUN_CODE_9eb9(1,0x12);
  if (-1 < in_PSW) {
    return;
  }
  cVar2 = FUN_CODE_6240();
  FUN_CODE_6215(cVar2);
  cVar1 = *param_1;
  FUN_CODE_6217(cVar2 + '\x04');
  if ((*param_1 == BANK0_R5) && (cVar1 != '\0')) {
    return;
  }
  return;
}

