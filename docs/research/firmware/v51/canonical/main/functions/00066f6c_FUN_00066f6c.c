/* Address: 00066f6c; name: FUN_00066f6c; body bytes: 278 */

undefined4 FUN_00066f6c(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar4 = 0;
  uVar5 = 0;
  enter_critical(DAT_1ffe0034);
  DAT_1ffe0034 = DAT_1ffe0034 + -1;
  if ((DAT_1ffe0034 == 0) && (DAT_1ffe0008 != 0)) {
    while (DAT_1ffe0e28 != 0) {
      iVar4 = *(int *)(DAT_1ffe0e34 + 0xc);
      piVar1 = *(int **)(iVar4 + 0x28);
      *(undefined4 *)(*(int *)(iVar4 + 0x1c) + 8) = *(undefined4 *)(iVar4 + 0x20);
      *(undefined4 *)(*(int *)(iVar4 + 0x20) + 4) = *(undefined4 *)(iVar4 + 0x1c);
      if (piVar1[1] == iVar4 + 0x18) {
        piVar1[1] = *(int *)(iVar4 + 0x20);
      }
      *(undefined4 *)(iVar4 + 0x28) = 0;
      *piVar1 = *piVar1 + -1;
      piVar1 = *(int **)(iVar4 + 0x14);
      *(undefined4 *)(*(int *)(iVar4 + 8) + 8) = *(undefined4 *)(iVar4 + 0xc);
      *(undefined4 *)(*(int *)(iVar4 + 0xc) + 4) = *(undefined4 *)(iVar4 + 8);
      iVar3 = iVar4 + 4;
      if (piVar1[1] == iVar3) {
        piVar1[1] = *(int *)(iVar4 + 0xc);
      }
      *(undefined4 *)(iVar4 + 0x14) = 0;
      *piVar1 = *piVar1 + -1;
      DAT_1ffe0010 = 1 << (*(uint *)(iVar4 + 0x2c) & 0xff) | DAT_1ffe0010;
      iVar2 = *(int *)(&DAT_1ffe0da0 + *(uint *)(iVar4 + 0x2c) * 0x14);
      *(int *)(iVar4 + 8) = iVar2;
      *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar2 + 8);
      *(int *)(*(int *)(iVar2 + 8) + 4) = iVar3;
      *(int *)(iVar2 + 8) = iVar3;
      iVar3 = *(int *)(iVar4 + 0x2c);
      *(undefined4 **)(iVar4 + 0x14) = &DAT_1ffe0d9c + iVar3 * 5;
      (&DAT_1ffe0d9c)[iVar3 * 5] = (&DAT_1ffe0d9c)[iVar3 * 5] + 1;
      if (*(uint *)(DAT_1ffe0000 + 0x2c) <= *(uint *)(iVar4 + 0x2c)) {
        DAT_1ffe001c = 1;
      }
    }
    if (iVar4 != 0) {
      FUN_00059e24();
    }
    iVar4 = DAT_1ffe0018;
    if (DAT_1ffe0018 != 0) {
      do {
        iVar3 = FUN_00066c28();
        if (iVar3 != 0) {
          DAT_1ffe001c = 1;
        }
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      DAT_1ffe0018 = 0;
    }
    if (DAT_1ffe001c != 0) {
      uVar5 = 1;
      DAT_e000ed04 = 0x10000000;
      DataSynchronizationBarrier(0xf);
      InstructionSynchronizationBarrier(0xf);
    }
  }
  exit_critical();
  return uVar5;
}

