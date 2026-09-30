/* Address: 000541d4; name: FUN_000541d4; body bytes: 368 */

void FUN_000541d4(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int *piVar7;
  
  if (-1 < (int)((uint)*(ushort *)(param_1 + 0x2a) << 0x13)) {
    *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) | 0x1000;
    iVar2 = FUN_0004e5a6(param_1,0x26,0);
    if (iVar2 != 0) {
      if (*(int *)(param_1 + 8) != 0) {
        FUN_000467c6(*(int *)(param_1 + 8) + 8);
      }
      while (iVar2 = FUN_0004b9de(param_1,0), iVar2 != 0) {
        FUN_000541d4();
      }
      iVar2 = FUN_0004bbe2(param_1);
      for (iVar3 = FUN_00048270(0); iVar3 != 0; iVar3 = FUN_00048270(iVar3)) {
        iVar4 = FUN_000482e0();
        if ((iVar4 == 1) || (iVar4 == 3)) {
          if ((*(int *)(iVar3 + 0x68) == param_1) ||
             ((*(int *)(iVar3 + 0x6c) == param_1 || (*(int *)(iVar3 + 0x70) == param_1)))) {
            FUN_0005434c(iVar3,param_1);
          }
          if (*(int *)(iVar3 + 0x74) == param_1) {
            *(undefined4 *)(iVar3 + 0x74) = 0;
          }
          if (*(int *)(iVar3 + 0x78) == param_1) {
            *(undefined4 *)(iVar3 + 0x78) = 0;
          }
        }
        if ((*(int *)(iVar3 + 0xa8) == iVar2) && (iVar4 = FUN_00048258(), iVar4 == param_1)) {
          FUN_0005434c(iVar3,param_1);
        }
      }
      do {
        iVar2 = FUN_0003df44(0x4b40b,param_1);
      } while (iVar2 == 1);
      FUN_0004b40e(param_1);
      if (*(int *)(param_1 + 4) == 0) {
        iVar2 = FUN_0004bb48(param_1);
        for (uVar5 = 0;
            (uVar5 < *(uint *)(iVar2 + 0x2d0) &&
            (*(int *)(*(int *)(iVar2 + 0x2b4) + uVar5 * 4) != param_1)); uVar5 = uVar5 + 1) {
        }
        for (; uVar5 < *(int *)(iVar2 + 0x2d0) - 1U; uVar5 = uVar5 + 1) {
          *(undefined4 *)(*(int *)(iVar2 + 0x2b4) + uVar5 * 4) =
               *(undefined4 *)(*(int *)(iVar2 + 0x2b4) + uVar5 * 4 + 4);
        }
        iVar3 = *(int *)(iVar2 + 0x2d0) + -1;
        *(int *)(iVar2 + 0x2d0) = iVar3;
        uVar6 = FUN_0004f588(*(undefined4 *)(iVar2 + 0x2b4),iVar3 * 4);
        *(undefined4 *)(iVar2 + 0x2b4) = uVar6;
      }
      else {
        uVar5 = FUN_0004bc12();
        while( true ) {
          uVar5 = uVar5 & 0xffff;
          piVar7 = *(int **)(*(int *)(param_1 + 4) + 8);
          if ((int)(*(ushort *)(piVar7 + 10) - 1) <= (int)uVar5) break;
          *(undefined4 *)(*piVar7 + uVar5 * 4) = *(undefined4 *)(*piVar7 + uVar5 * 4 + 4);
          uVar5 = uVar5 + 1;
        }
        uVar1 = *(short *)(*(int *)(*(int *)(param_1 + 4) + 8) + 0x28) - 1;
        *(ushort *)(piVar7 + 10) = uVar1;
        uVar6 = FUN_0004f588(**(undefined4 **)(*(int *)(param_1 + 4) + 8),(uint)uVar1 << 2);
        **(undefined4 **)(*(int *)(param_1 + 4) + 8) = uVar6;
      }
      FUN_00046bec(param_1);
      return;
    }
    *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) & 0xefff;
  }
  return;
}

