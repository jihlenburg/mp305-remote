/* Address: ram:00048b8c; name: FUN_ram_00048b8c; body bytes: 90 */

void FUN_ram_00048b8c(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined2 auStack_14 [4];
  
  gp = 0x20004000;
  FUN_ram_0004df14();
  iVar2 = FUN_ram_00043274(param_1,param_2);
  if (iVar2 == 0) {
    auStack_14[0] = (undefined2)param_2;
    iVar2 = FUN_ram_0004df14(param_1);
    if (iVar2 != 0) {
      uVar1 = DAT_ram_20001d51;
      if (*(char *)(iVar2 + 0xc) == '\b') {
        uVar1 = DAT_ram_20001d52;
      }
      FUN_ram_000487a4(uVar1,param_1,0,0x7f,auStack_14);
    }
  }
  return;
}

