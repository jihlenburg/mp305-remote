/* Address: ram:0004a2ae; name: FUN_ram_0004a2ae; body bytes: 24 */

undefined1 FUN_ram_0004a2ae(void)

{
  undefined1 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004a274();
  if (iVar2 == 0) {
    uVar1 = 0x10;
  }
  else {
    uVar1 = *(undefined1 *)(iVar2 + 2);
  }
  return uVar1;
}

