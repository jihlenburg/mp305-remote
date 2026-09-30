/* Address: CODE:8cc7; name: FUN_CODE_8cc7; body bytes: 41 */

void FUN_CODE_8cc7(void)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char in_PSW;
  
  bVar2 = 9;
  FUN_CODE_9ba3();
  FUN_CODE_a153();
  if (-1 < in_PSW) {
    thunk_FUN_CODE_a560();
    cVar3 = bVar2 - 2;
    bVar1 = (bVar2 < 2) << 7 < '\0';
    if (bVar1) {
      cVar3 = '\0';
    }
    FUN_CODE_3b3c(cVar3,!bVar1);
    return;
  }
  FUN_CODE_3b3c(7);
  FUN_CODE_4d85(DAT_INTMEM_b3);
  return;
}

