/* Address: CODE:64a1; name: FUN_CODE_64a1; body bytes: 154 */

void FUN_CODE_64a1(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char *pcVar4;
  
  FUN_CODE_9281();
  if ((DAT_EXTMEM_03ec >> 6 & 1) != 0) {
    DAT_EXTMEM_03a3 = DAT_EXTMEM_03a3 + '\x01';
    FUN_CODE_960e(0xff,0xff);
    FUN_CODE_957e(0x80,0x12);
  }
  if ((DAT_EXTMEM_03ec >> 3 & 1) != 0) {
    FUN_CODE_9d4f();
    FUN_CODE_803f();
  }
  if ((char)DAT_EXTMEM_03ec < '\0') {
    FUN_CODE_957e(3,4);
    FUN_CODE_3472();
    bVar1 = FUN_CODE_33e2();
    FUN_CODE_3439(bVar1 | 1);
    FUN_CODE_a99c();
    FUN_CODE_9cdd();
  }
  if ((DAT_EXTMEM_03ec & 3) != 0) {
    FUN_CODE_9d4f();
    FUN_CODE_3472();
    bVar2 = FUN_CODE_a94d(0x59);
    FUN_CODE_33e2();
    FUN_CODE_a99c();
    bVar1 = FUN_CODE_33e9();
    bVar1 = bVar1 >> 1 & 3;
    pcVar4 = (char *)0x5a;
    bVar3 = FUN_CODE_a94d();
    if (((bVar3 & 3) == bVar1) &&
       (((bVar2 >> 6 & 1) == 1 || (pcVar4 = &DAT_EXTMEM_03ec, (DAT_EXTMEM_03ec & 1) != 0)))) {
      FUN_CODE_342d(DAT_INTMEM_b9);
      if (*pcVar4 == '\0') {
        FUN_CODE_42a5();
      }
    }
  }
  return;
}

