/* Address: 000526c4; name: FUN_000526c4; body bytes: 34 */

uint FUN_000526c4(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_000526e6();
  if (iVar1 == 0) {
    uVar2 = FUN_0004f04c(0x11);
  }
  else {
    uVar2 = *(uint *)(iVar1 + 0x10);
  }
  return uVar2 & 0xffffff;
}

