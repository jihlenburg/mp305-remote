/* Address: ram:000450ea; name: FUN_ram_000450ea; body bytes: 42 */

undefined4 FUN_ram_000450ea(undefined4 param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_14 [12];
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if (iVar1 == 0) {
    uVar2 = 0x14;
  }
  else {
    auStack_14[0] = param_2;
    uVar2 = FUN_ram_0004e7e6(param_1,auStack_14);
  }
  return uVar2;
}

