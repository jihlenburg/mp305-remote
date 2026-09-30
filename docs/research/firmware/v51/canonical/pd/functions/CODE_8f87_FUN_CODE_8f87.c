/* Address: CODE:8f87; name: FUN_CODE_8f87; body bytes: 35 */

void FUN_CODE_8f87(char *param_1,char *param_2)

{
  undefined1 uVar1;
  char cVar2;
  
  FUN_CODE_50a8();
  if (*param_1 != '\0') {
    cVar2 = *param_2;
    FUN_CODE_50ab();
    *param_1 = '\0';
    if (cVar2 == '\0') {
      uVar1 = 0;
    }
    else {
      if (DAT_INTMEM_b3 != '\x01') {
        return;
      }
      uVar1 = 1;
    }
    FUN_CODE_8800(uVar1,0x18,3);
  }
  return;
}

