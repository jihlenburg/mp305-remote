/* Address: CODE:84ad; name: FUN_CODE_84ad; body bytes: 57 */

void FUN_CODE_84ad(void)

{
  byte bVar1;
  undefined1 uVar2;
  char in_PSW;
  char cVar3;
  
  FUN_CODE_a335();
  bVar1 = DAT_INTMEM_b3;
  if (in_PSW < '\0') {
    *(undefined1 *)(DAT_INTMEM_b3 + 0x23) = 2;
    uVar2 = 0xe7;
  }
  else {
    *(undefined1 *)(DAT_INTMEM_b3 + 0x23) = 1;
    uVar2 = 0xf1;
  }
  cVar3 = (0xdc < bVar1) << 7;
  FUN_CODE_87aa(uVar2,0xb0,0xff);
  FUN_CODE_9bf3();
  if (-1 < cVar3) {
    FUN_CODE_87aa(0xf9,0xb0,0xff);
    FUN_CODE_6406();
  }
  _1_5 = 1;
  FUN_CODE_6c35();
  return;
}

