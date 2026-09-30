/* Address: ram:0004d99c; name: FUN_ram_0004d99c; body bytes: 62 */

undefined4 FUN_ram_0004d99c(void)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004d752(5);
  if ((((iVar1 == 0) && (iVar1 = FUN_ram_0004d752(6), iVar1 == 0)) &&
      (iVar1 = FUN_ram_0004d752(4), iVar1 == 0)) && (iVar1 = FUN_ram_0004d752(7), iVar1 == 0)) {
    uVar2 = 0;
    if (DAT_ram_20001a61 != '\0') {
      uVar2 = FUN_ram_0004d8d0();
      return uVar2;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

