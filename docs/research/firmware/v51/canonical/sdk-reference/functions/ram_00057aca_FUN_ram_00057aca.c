/* Address: ram:00057aca; name: FUN_ram_00057aca; body bytes: 216 */

void FUN_ram_00057aca(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  gp = 0x20004000;
  while (*(int *)(param_1 + 0x118) != 0) {
    if (*(int *)(*(int *)(param_1 + 0x118) + 4) != 0) {
      FUN_ram_20000104();
    }
    puVar2 = *(undefined4 **)(param_1 + 0x118);
    *(ushort *)((int)puVar2 + 10) = *(ushort *)((int)puVar2 + 10) | 0xff00;
    *(undefined4 *)(param_1 + 0x118) = *puVar2;
  }
  while (iVar1 = *(int *)(param_1 + 0x120), iVar1 != 0) {
    *(ushort *)(iVar1 + 10) = *(ushort *)(iVar1 + 10) | 0xff00;
    if (*(int *)(iVar1 + 4) != 0) {
      FUN_ram_20000104();
    }
    *(undefined4 *)(param_1 + 0x120) = **(undefined4 **)(param_1 + 0x120);
  }
  if (*(int *)(param_1 + 0x110) != 0) {
    FUN_ram_20000104();
  }
  if (*(char *)(param_1 + 0x27) != -1) {
    FUN_ram_00042494();
  }
  if (*(char *)(param_1 + 0x26) != -1) {
    FUN_ram_00042494();
  }
  if (*(char *)(param_1 + 0x28) != -1) {
    FUN_ram_00042494();
  }
  FUN_ram_00057d86(*(undefined2 *)(param_1 + 8));
  if (((DAT_ram_20001bc4 != 0) && (DAT_ram_20001e04 == 0)) && (DAT_ram_20001b84 != 0)) {
    FUN_ram_20000104();
    DAT_ram_20001b84 = 0;
    DAT_ram_20001b88 = 0;
  }
  return;
}

