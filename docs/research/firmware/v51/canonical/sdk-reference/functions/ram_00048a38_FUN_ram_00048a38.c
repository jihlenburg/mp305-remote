/* Address: ram:00048a38; name: FUN_ram_00048a38; body bytes: 86 */

undefined4
FUN_ram_00048a38(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_0004df14();
  if (iVar2 == 0) {
    return 1;
  }
  uVar1 = DAT_ram_20001d51;
  if (*(char *)(iVar2 + 0xc) == '\b') {
    uVar1 = DAT_ram_20001d52;
  }
  uVar3 = FUN_ram_000487a4(uVar1,param_1,param_2,param_3,param_4);
  return uVar3;
}

