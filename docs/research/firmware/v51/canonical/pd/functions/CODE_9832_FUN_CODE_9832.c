/* Address: CODE:9832; name: FUN_CODE_9832; body bytes: 25 */

void FUN_CODE_9832(void)

{
  undefined1 uVar1;
  byte in_PSW;
  byte bVar2;
  
  bVar2 = in_PSW & 0xdd;
  if ((DAT_INTMEM_cb & 3) != 0) {
    FUN_CODE_9a39();
  }
  FUN_CODE_a153();
  if ((char)bVar2 < '\0') {
    uVar1 = 0x29;
  }
  else {
    uVar1 = 0x28;
  }
  FUN_CODE_a03c(uVar1);
  return;
}

