/* Address: ram:00045036; name: FUN_ram_00045036; body bytes: 74 */

undefined4 FUN_ram_00045036(undefined4 param_1,undefined1 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_50 [72];
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if (iVar1 == 0) {
    uVar2 = 0x14;
  }
  else {
    uVar2 = 0x12;
    if (*(char *)(iVar1 + 0xc) == '\x04') {
      if (*(int *)(iVar1 + 0x38) != 0) {
        param_2 = *(undefined1 *)(*(int *)(iVar1 + 0x38) + 0x16);
      }
      auStack_50[0] = param_2;
      uVar2 = FUN_ram_0004e78a(param_1,2,auStack_50,&LAB_ram_000501f8);
    }
  }
  return uVar2;
}

