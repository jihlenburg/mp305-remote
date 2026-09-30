/* Address: 0005982c; name: FUN_0005982c; body bytes: 136 */

void FUN_0005982c(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = DAT_1ffe000c;
  *(undefined1 *)(DAT_1ffe0000 + 0x4d) = 0;
  iVar3 = FUN_00065666(DAT_1ffe0000 + 4);
  iVar2 = DAT_1ffe0e54;
  if (iVar3 == 0) {
    DAT_1ffe0010 = DAT_1ffe0010 & ~(1 << *(sbyte *)(DAT_1ffe0000 + 0x2c));
  }
  if ((param_1 == -1) && (param_2 != 0)) {
    *(int *)(DAT_1ffe0000 + 8) = DAT_1ffe0e54;
    *(undefined4 *)(DAT_1ffe0000 + 0xc) = *(undefined4 *)(iVar2 + 8);
    *(int *)(*(int *)(iVar2 + 8) + 4) = DAT_1ffe0000 + 4;
    *(int *)(iVar2 + 8) = DAT_1ffe0000 + 4;
    *(int **)(DAT_1ffe0000 + 0x14) = &DAT_1ffe0e50;
    DAT_1ffe0e50 = DAT_1ffe0e50 + 1;
  }
  else {
    uVar4 = param_1 + uVar1;
    *(uint *)(DAT_1ffe0000 + 4) = uVar4;
    if (uVar4 < uVar1) {
      FUN_000656d2(DAT_1ffe003c,DAT_1ffe0000 + 4);
      return;
    }
    FUN_000656d2(DAT_1ffe0038,DAT_1ffe0000 + 4);
    if (uVar4 < DAT_1ffe0028) {
      DAT_1ffe0028 = uVar4;
    }
  }
  return;
}

