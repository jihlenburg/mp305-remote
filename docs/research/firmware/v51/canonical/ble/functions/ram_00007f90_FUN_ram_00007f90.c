/* Address: ram:00007f90; name: FUN_ram_00007f90; body bytes: 106 */

void FUN_ram_00007f90(undefined *param_1)

{
  undefined4 uVar1;
  
  gp = &DAT_ram_20002000;
  if (*(int *)(param_1 + 0x18) == 0) {
    *(code **)(param_1 + 0x28) = FUN_ram_00007f40;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined4 *)(param_1 + 0x4c) = 0;
    *(undefined4 *)(param_1 + 0x50) = 0;
    if (param_1 == &DAT_ram_20002eb8) {
      DAT_ram_20002ed0 = 1;
    }
    uVar1 = FUN_ram_00007ffa();
    *(undefined4 *)(param_1 + 4) = uVar1;
    uVar1 = FUN_ram_00007ffa(param_1);
    *(undefined4 *)(param_1 + 8) = uVar1;
    uVar1 = FUN_ram_00007ffa(param_1);
    *(undefined4 *)(param_1 + 0xc) = uVar1;
    FUN_ram_00007ed6(*(undefined4 *)(param_1 + 4),4,0);
    FUN_ram_00007ed6(*(undefined4 *)(param_1 + 8),9,1);
    FUN_ram_00007ed6(*(undefined4 *)(param_1 + 0xc),0x12,2);
    *(undefined4 *)(param_1 + 0x18) = 1;
    return;
  }
  return;
}

