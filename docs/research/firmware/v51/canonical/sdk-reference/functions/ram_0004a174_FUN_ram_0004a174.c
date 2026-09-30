/* Address: ram:0004a174; name: FUN_ram_0004a174; body bytes: 22 */

undefined4 FUN_ram_0004a174(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004a156();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 8);
  }
  return uVar2;
}

