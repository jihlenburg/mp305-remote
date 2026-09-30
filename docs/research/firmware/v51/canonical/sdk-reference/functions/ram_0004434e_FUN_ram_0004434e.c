/* Address: ram:0004434e; name: FUN_ram_0004434e; body bytes: 74 */

void FUN_ram_0004434e(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0x38);
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x20) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x24) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x28) != 0) {
      FUN_ram_20000104();
    }
    FUN_ram_20000104(iVar1);
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  return;
}

