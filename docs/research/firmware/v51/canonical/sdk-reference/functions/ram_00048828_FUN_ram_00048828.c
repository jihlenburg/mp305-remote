/* Address: ram:00048828; name: FUN_ram_00048828; body bytes: 82 */

void FUN_ram_00048828(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  int iVar2;
  undefined1 uStack_14;
  undefined1 uStack_13;
  
  gp = 0x20004000;
  uStack_14 = param_2;
  uStack_13 = param_3;
  iVar2 = FUN_ram_0004df14();
  if (iVar2 != 0) {
    uVar1 = DAT_ram_20001d51;
    if (*(char *)(iVar2 + 0xc) == '\b') {
      uVar1 = DAT_ram_20001d52;
    }
    FUN_ram_000487a4(uVar1,param_1,0,0x7e,&uStack_14);
  }
  return;
}

