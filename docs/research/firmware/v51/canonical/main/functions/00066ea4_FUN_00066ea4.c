/* Address: 00066ea4; name: FUN_00066ea4; body bytes: 192 */

undefined4 FUN_00066ea4(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0xc) + 0xc);
  piVar2 = *(int **)(iVar1 + 0x28);
  *(undefined4 *)(*(int *)(iVar1 + 0x1c) + 8) = *(undefined4 *)(iVar1 + 0x20);
  *(undefined4 *)(*(int *)(iVar1 + 0x20) + 4) = *(undefined4 *)(iVar1 + 0x1c);
  iVar3 = iVar1 + 0x18;
  if (piVar2[1] == iVar3) {
    piVar2[1] = *(int *)(iVar1 + 0x20);
  }
  *(undefined4 *)(iVar1 + 0x28) = 0;
  *piVar2 = *piVar2 + -1;
  iVar4 = DAT_1ffe0e2c;
  if (DAT_1ffe0034 == 0) {
    piVar2 = *(int **)(iVar1 + 0x14);
    *(undefined4 *)(*(int *)(iVar1 + 8) + 8) = *(undefined4 *)(iVar1 + 0xc);
    *(undefined4 *)(*(int *)(iVar1 + 0xc) + 4) = *(undefined4 *)(iVar1 + 8);
    iVar3 = iVar1 + 4;
    if (piVar2[1] == iVar3) {
      piVar2[1] = *(int *)(iVar1 + 0xc);
    }
    *(undefined4 *)(iVar1 + 0x14) = 0;
    *piVar2 = *piVar2 + -1;
    DAT_1ffe0010 = 1 << (*(uint *)(iVar1 + 0x2c) & 0xff) | DAT_1ffe0010;
    iVar4 = *(int *)(&DAT_1ffe0da0 + *(uint *)(iVar1 + 0x2c) * 0x14);
    *(int *)(iVar1 + 8) = iVar4;
    *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)(iVar4 + 8);
    *(int *)(*(int *)(iVar4 + 8) + 4) = iVar3;
    *(int *)(iVar4 + 8) = iVar3;
    iVar3 = *(int *)(iVar1 + 0x2c);
    *(undefined4 **)(iVar1 + 0x14) = &DAT_1ffe0d9c + iVar3 * 5;
    (&DAT_1ffe0d9c)[iVar3 * 5] = (&DAT_1ffe0d9c)[iVar3 * 5] + 1;
  }
  else {
    *(int *)(iVar1 + 0x1c) = DAT_1ffe0e2c;
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(iVar4 + 8);
    *(int *)(*(int *)(iVar4 + 8) + 4) = iVar3;
    *(int *)(iVar4 + 8) = iVar3;
    *(int **)(iVar1 + 0x28) = &DAT_1ffe0e28;
    DAT_1ffe0e28 = DAT_1ffe0e28 + 1;
  }
  if (*(uint *)(DAT_1ffe0000 + 0x2c) < *(uint *)(iVar1 + 0x2c)) {
    DAT_1ffe001c = 1;
    return 1;
  }
  return 0;
}

