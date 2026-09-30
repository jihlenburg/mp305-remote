/* Address: ram:0004e524; name: FUN_ram_0004e524; body bytes: 126 */

void FUN_ram_0004e524(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0x34);
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x28) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x70) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x74) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x78) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x7c) != 0) {
      FUN_ram_20000104();
    }
    if (*(int *)(iVar1 + 0x80) != 0) {
      FUN_ram_20000104();
    }
    FUN_ram_20000104(iVar1);
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  tmos_stop_task(DAT_ram_20001d4f,*(undefined2 *)(param_1 + 0x30));
  return;
}

