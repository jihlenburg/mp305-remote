/* Address: 00065b08; name: FUN_00065b08; body bytes: 156 */

void FUN_00065b08(uint *param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
  *param_1 = param_2 | 0x80000000;
  uVar2 = param_1[3];
  piVar3 = (int *)param_1[4];
  *(uint *)(param_1[1] + 8) = param_1[2];
  *(uint *)(param_1[2] + 4) = param_1[1];
  if ((uint *)piVar3[1] == param_1) {
    piVar3[1] = param_1[2];
  }
  param_1[4] = 0;
  *piVar3 = *piVar3 + -1;
  piVar3 = *(int **)(uVar2 + 0x14);
  *(undefined4 *)(*(int *)(uVar2 + 8) + 8) = *(undefined4 *)(uVar2 + 0xc);
  *(undefined4 *)(*(int *)(uVar2 + 0xc) + 4) = *(undefined4 *)(uVar2 + 8);
  iVar4 = uVar2 + 4;
  if (piVar3[1] == iVar4) {
    piVar3[1] = *(int *)(uVar2 + 0xc);
  }
  *(undefined4 *)(uVar2 + 0x14) = 0;
  *piVar3 = *piVar3 + -1;
  DAT_1ffe0010 = 1 << (*(uint *)(uVar2 + 0x2c) & 0xff) | DAT_1ffe0010;
  iVar1 = *(int *)(&DAT_1ffe0da0 + *(uint *)(uVar2 + 0x2c) * 0x14);
  *(int *)(uVar2 + 8) = iVar1;
  *(undefined4 *)(uVar2 + 0xc) = *(undefined4 *)(iVar1 + 8);
  *(int *)(*(int *)(iVar1 + 8) + 4) = iVar4;
  *(int *)(iVar1 + 8) = iVar4;
  iVar4 = *(int *)(uVar2 + 0x2c);
  *(undefined4 **)(uVar2 + 0x14) = &DAT_1ffe0d9c + iVar4 * 5;
  (&DAT_1ffe0d9c)[iVar4 * 5] = (&DAT_1ffe0d9c)[iVar4 * 5] + 1;
  if (*(uint *)(DAT_1ffe0000 + 0x2c) < *(uint *)(uVar2 + 0x2c)) {
    DAT_1ffe001c = 1;
  }
  return;
}

