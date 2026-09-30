/* Address: CODE:8601; name: FUN_CODE_8601; body bytes: 55 */

void FUN_CODE_8601(char *param_1,char param_2,char param_3)

{
  char cVar1;
  byte bVar2;
  
  cVar1 = DAT_INTMEM_b3;
  FUN_CODE_342d(DAT_INTMEM_b3);
  if (*param_1 != param_3) {
    FUN_CODE_342f(cVar1 + -0x26);
    *param_1 = param_3;
    if (param_3 == '\x05') {
      FUN_CODE_a377();
      FUN_CODE_33d6();
      bVar2 = FUN_CODE_33df();
      FUN_CODE_33d3(bVar2 & 0xef);
      bVar2 = FUN_CODE_33e2(param_2 + '\\');
      FUN_CODE_a99c(bVar2 | 3);
      return;
    }
    if (param_3 == '\b') {
      FUN_CODE_a53c();
    }
  }
  return;
}

