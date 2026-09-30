/* Address: 0005a2a8; name: FUN_0005a2a8; body bytes: 406 */

void FUN_0005a2a8(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int local_34;
  int local_30;
  int iStack_2c;
  int iStack_28;
  
  piVar8 = *(int **)(DAT_2003a430 + 0x2a8);
  *piVar8 = *(int *)(DAT_2003a430 + 0x24);
  if (*(char *)(DAT_2003a430 + 0x39) == '\0') {
    uVar3 = FUN_0003db28(param_1);
    uVar4 = FUN_0003db0a(param_1);
    iVar1 = FUN_00040960(DAT_2003a430);
    iVar2 = param_1[3];
    if (iVar1 <= iVar2) {
      iVar2 = FUN_00040960(DAT_2003a430);
      iVar2 = iVar2 + -1;
    }
    iVar5 = FUN_000376f0(DAT_2003a430,uVar3,uVar4);
    iVar7 = 0;
    iVar1 = param_1[1];
    while( true ) {
      iVar9 = iVar1 + iVar5 + -1;
      if (iVar2 < iVar9) break;
      iVar6 = param_1[2];
      iVar7 = *param_1;
      *piVar8 = *(int *)(DAT_2003a430 + 0x24);
      piVar8[1] = iVar7;
      piVar8[2] = iVar1;
      piVar8[3] = iVar6;
      piVar8[4] = iVar9;
      piVar8[6] = iVar7;
      piVar8[7] = iVar1;
      piVar8[8] = iVar6;
      piVar8[9] = iVar9;
      piVar8[10] = iVar7;
      piVar8[0xb] = iVar1;
      piVar8[0xc] = iVar6;
      piVar8[0xd] = iVar9;
      FUN_0003bf38(piVar8,0);
      iVar7 = iVar9;
      if (iVar2 < iVar9) {
        iVar7 = iVar2;
      }
      if (iVar2 == iVar7) {
        *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) | 2;
      }
      FUN_0005a444(piVar8);
      iVar1 = iVar1 + iVar5;
    }
    if (iVar2 != iVar7) {
      iVar5 = param_1[2];
      iVar7 = *param_1;
      *piVar8 = *(int *)(DAT_2003a430 + 0x24);
      piVar8[1] = iVar7;
      piVar8[2] = iVar1;
      piVar8[3] = iVar5;
      piVar8[4] = iVar2;
      piVar8[6] = iVar7;
      piVar8[7] = iVar1;
      piVar8[8] = iVar5;
      piVar8[9] = iVar2;
      piVar8[10] = iVar7;
      piVar8[0xb] = iVar1;
      piVar8[0xc] = iVar5;
      piVar8[0xd] = iVar2;
      FUN_0003bf38(piVar8,0);
      *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) | 2;
      FUN_0005a444(piVar8);
      return;
    }
  }
  else {
    piVar8[1] = 0;
    piVar8[2] = 0;
    iVar1 = FUN_000408b0(DAT_2003a430);
    piVar8[3] = iVar1 + -1;
    iVar1 = FUN_00040960(DAT_2003a430);
    piVar8[4] = iVar1 + -1;
    iVar1 = FUN_00040960(DAT_2003a430);
    iVar2 = FUN_000408b0(DAT_2003a430);
    FUN_0003ddf0(&local_34,0,0,iVar2 + -1,iVar1 + -1);
    if (*(char *)(DAT_2003a430 + 0x39) == '\x02') {
      *(uint *)(DAT_2003a430 + 0x38) = *(uint *)(DAT_2003a430 + 0x38) | 2;
      FUN_0003bf38(piVar8,*(undefined2 *)(*piVar8 + 8));
      piVar8[6] = local_34;
      piVar8[7] = local_30;
      piVar8[8] = iStack_2c;
      piVar8[9] = iStack_28;
    }
    else {
      if (*(char *)(DAT_2003a430 + 0x39) != '\x01') {
        return;
      }
      *(uint *)(DAT_2003a430 + 0x38) =
           *(uint *)(DAT_2003a430 + 0x38) & 0xfffffffd | (*(uint *)(DAT_2003a430 + 0x38) & 1) << 1;
      FUN_0003bf38(piVar8,*(undefined2 *)(*piVar8 + 8));
      iVar1 = param_1[1];
      iVar2 = param_1[2];
      iVar7 = param_1[3];
      piVar8[6] = *param_1;
      piVar8[7] = iVar1;
      piVar8[8] = iVar2;
      piVar8[9] = iVar7;
      local_34 = *param_1;
      local_30 = param_1[1];
      iStack_2c = param_1[2];
      iStack_28 = param_1[3];
    }
    piVar8[10] = local_34;
    piVar8[0xb] = local_30;
    piVar8[0xc] = iStack_2c;
    piVar8[0xd] = iStack_28;
    FUN_0005a444(piVar8);
  }
  return;
}

