/* Address: 000598bc; name: FUN_000598bc; body bytes: 226 */

void FUN_000598bc(int param_1)

{
  int iVar1;
  uint uVar2;
  
  enter_critical();
  DAT_1ffe0008 = DAT_1ffe0008 + 1;
  if (DAT_1ffe0000 == 0) {
    DAT_1ffe0000 = param_1;
    if (DAT_1ffe0008 == 1) {
      uVar2 = 0;
      do {
        FUN_000656b6(&DAT_1ffe0d9c + uVar2 * 5);
        uVar2 = uVar2 + 1;
      } while (uVar2 < 5);
      FUN_000656b6(&DAT_1ffe0e00);
      FUN_000656b6(&DAT_1ffe0e14);
      FUN_000656b6(&DAT_1ffe0e28);
      FUN_000656b6(&DAT_1ffe0e3c);
      FUN_000656b6(&DAT_1ffe0e50);
      DAT_1ffe0038 = &DAT_1ffe0e00;
      DAT_1ffe003c = &DAT_1ffe0e14;
    }
  }
  else if ((DAT_1ffe0014 == 0) && (*(uint *)(DAT_1ffe0000 + 0x2c) <= *(uint *)(param_1 + 0x2c))) {
    DAT_1ffe0000 = param_1;
  }
  DAT_1ffe0024 = DAT_1ffe0024 + 1;
  DAT_1ffe0010 = 1 << (*(uint *)(param_1 + 0x2c) & 0xff) | DAT_1ffe0010;
  iVar1 = *(int *)(&DAT_1ffe0da0 + *(uint *)(param_1 + 0x2c) * 0x14);
  *(int *)(param_1 + 8) = iVar1;
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(iVar1 + 8);
  *(int *)(*(int *)(iVar1 + 8) + 4) = param_1 + 4;
  *(int *)(iVar1 + 8) = param_1 + 4;
  iVar1 = *(int *)(param_1 + 0x2c);
  *(undefined4 **)(param_1 + 0x14) = &DAT_1ffe0d9c + iVar1 * 5;
  (&DAT_1ffe0d9c)[iVar1 * 5] = (&DAT_1ffe0d9c)[iVar1 * 5] + 1;
  exit_critical();
  if ((DAT_1ffe0014 != 0) && (*(uint *)(DAT_1ffe0000 + 0x2c) < *(uint *)(param_1 + 0x2c))) {
    DAT_e000ed04 = 0x10000000;
    DataSynchronizationBarrier(0xf);
    InstructionSynchronizationBarrier(0xf);
  }
  return;
}

