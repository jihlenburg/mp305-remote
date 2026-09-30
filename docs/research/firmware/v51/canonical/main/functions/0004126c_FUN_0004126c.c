/* Address: 0004126c; name: FUN_0004126c; body bytes: 248 */

void FUN_0004126c(ushort *param_1,undefined4 *param_2,ushort *param_3,undefined4 *param_4)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  
  if (*param_1 >> 8 != *param_3 >> 8) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 == (undefined4 *)0x0) {
    uVar3 = (uint)param_1[2];
LAB_0004129c:
    uVar4 = (uint)(*param_1 >> 8);
    if (uVar4 - 7 < 4) {
      if (uVar4 == 7) {
        iVar5 = 2;
      }
      else if (uVar4 == 8) {
        iVar5 = 4;
      }
      else if (uVar4 == 9) {
        iVar5 = 0x10;
      }
      else if (uVar4 == 10) {
        iVar5 = 0x100;
      }
      else {
        iVar5 = 0;
      }
      FUN_0004a404(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_3 + 8),iVar5 << 2);
    }
    if (param_4 == (undefined4 *)0x0) {
      if (param_3[2] == uVar3) {
        uVar9 = 0;
        uVar8 = 0;
        goto LAB_000412f4;
      }
      goto LAB_000412d2;
    }
  }
  else {
    uVar3 = FUN_0003db28(param_2);
    if (param_4 == (undefined4 *)0x0) goto LAB_0004129c;
  }
  uVar4 = FUN_0003db28(param_4);
  if (uVar4 == uVar3) {
    uVar8 = *param_4;
    uVar9 = param_4[1];
LAB_000412f4:
    iVar5 = FUN_000414c8(param_3,uVar8,uVar9);
    if (param_2 == (undefined4 *)0x0) {
      iVar6 = FUN_000414c8(param_1,0);
      iVar11 = 0;
      iVar10 = (*(uint *)(param_1 + 2) >> 0x10) - 1;
    }
    else {
      iVar6 = FUN_000414c8(param_1,*param_2,param_2[1]);
      iVar11 = param_2[1];
      iVar10 = param_2[3];
    }
    uVar1 = param_1[4];
    uVar2 = param_3[4];
    iVar7 = FUN_00040314(*param_1 >> 8);
    for (; iVar11 <= iVar10; iVar11 = iVar11 + 1) {
      FUN_0004a404(iVar6,iVar5,(int)(uVar3 * iVar7 + 7) >> 3);
      iVar6 = iVar6 + (uint)uVar1;
      iVar5 = iVar5 + (uint)uVar2;
    }
    return;
  }
LAB_000412d2:
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

