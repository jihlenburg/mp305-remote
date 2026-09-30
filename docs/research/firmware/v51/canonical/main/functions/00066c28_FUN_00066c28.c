/* Address: 00066c28; name: FUN_00066c28; body bytes: 306 */

undefined4 FUN_00066c28(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  
  piVar3 = DAT_1ffe0038;
  uVar6 = 0;
  if (DAT_1ffe0034 == 0) {
    uVar5 = DAT_1ffe000c + 1;
    DAT_1ffe000c = uVar5;
    if (uVar5 == 0) {
      DAT_1ffe0038 = DAT_1ffe003c;
      DAT_1ffe003c = piVar3;
      DAT_1ffe0020 = DAT_1ffe0020 + 1;
      FUN_00059e24();
    }
    if (DAT_1ffe0028 <= uVar5) {
      while (*DAT_1ffe0038 != 0) {
        iVar1 = *(int *)(DAT_1ffe0038[3] + 0xc);
        DAT_1ffe0028 = *(uint *)(iVar1 + 4);
        if (uVar5 < DAT_1ffe0028) goto LAB_00066c8a;
        piVar3 = *(int **)(iVar1 + 0x14);
        *(undefined4 *)(*(int *)(iVar1 + 8) + 8) = *(undefined4 *)(iVar1 + 0xc);
        *(undefined4 *)(*(int *)(iVar1 + 0xc) + 4) = *(undefined4 *)(iVar1 + 8);
        iVar2 = iVar1 + 4;
        if (piVar3[1] == iVar2) {
          piVar3[1] = *(int *)(iVar1 + 0xc);
        }
        *(undefined4 *)(iVar1 + 0x14) = 0;
        *piVar3 = *piVar3 + -1;
        piVar3 = *(int **)(iVar1 + 0x28);
        if (piVar3 != (int *)0x0) {
          *(undefined4 *)(*(int *)(iVar1 + 0x1c) + 8) = *(undefined4 *)(iVar1 + 0x20);
          *(undefined4 *)(*(int *)(iVar1 + 0x20) + 4) = *(undefined4 *)(iVar1 + 0x1c);
          if (piVar3[1] == iVar1 + 0x18) {
            piVar3[1] = *(int *)(iVar1 + 0x20);
          }
          *(undefined4 *)(iVar1 + 0x28) = 0;
          *piVar3 = *piVar3 + -1;
        }
        DAT_1ffe0010 = 1 << (*(uint *)(iVar1 + 0x2c) & 0xff) | DAT_1ffe0010;
        iVar4 = *(int *)(&DAT_1ffe0da0 + *(uint *)(iVar1 + 0x2c) * 0x14);
        *(int *)(iVar1 + 8) = iVar4;
        *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)(iVar4 + 8);
        *(int *)(*(int *)(iVar4 + 8) + 4) = iVar2;
        *(int *)(iVar4 + 8) = iVar2;
        iVar2 = *(int *)(iVar1 + 0x2c);
        *(undefined4 **)(iVar1 + 0x14) = &DAT_1ffe0d9c + iVar2 * 5;
        (&DAT_1ffe0d9c)[iVar2 * 5] = (&DAT_1ffe0d9c)[iVar2 * 5] + 1;
        if (*(uint *)(DAT_1ffe0000 + 0x2c) < *(uint *)(iVar1 + 0x2c)) {
          uVar6 = 1;
        }
      }
      DAT_1ffe0028 = 0xffffffff;
    }
LAB_00066c8a:
    if (1 < (uint)(&DAT_1ffe0d9c)[*(int *)(DAT_1ffe0000 + 0x2c) * 5]) {
      uVar6 = 1;
    }
    if (DAT_1ffe0018 == 0) {
      FUN_000656b0();
    }
    if (DAT_1ffe001c != 0) {
      uVar6 = 1;
    }
  }
  else {
    DAT_1ffe0018 = DAT_1ffe0018 + 1;
    FUN_000656b0();
  }
  return uVar6;
}

