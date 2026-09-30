/* Address: ram:0004e5a2; name: FUN_ram_0004e5a2; body bytes: 96 */

void FUN_ram_0004e5a2(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 *puVar2;
  
  gp = 0x20004000;
  iVar1 = FUN_ram_0004df14();
  if ((iVar1 != 0) && (puVar2 = *(undefined2 **)(iVar1 + 0x34), puVar2 != (undefined2 *)0x0)) {
    FUN_ram_00044cd6(param_2,*(undefined1 *)(puVar2 + 1),*puVar2,*(undefined1 *)(puVar2 + 3),
                     *(undefined4 *)(puVar2 + 0x38),*(undefined4 *)(puVar2 + 0x3a),
                     *(undefined4 *)(puVar2 + 0x3c),*(undefined4 *)(puVar2 + 0x3e));
    FUN_ram_0004e524(iVar1);
    iVar1 = FUN_ram_0004e400();
    if (iVar1 != 0) {
      tmos_set_event(DAT_ram_20001d4f,1);
      return;
    }
  }
  return;
}

