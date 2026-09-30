/* Address: 0004fd10; name: FUN_0004fd10; body bytes: 382 */

void FUN_0004fd10(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  short sVar10;
  uint in_fpscr;
  undefined4 uVar11;
  
  if ((*(char *)(param_1 + 0x3c) == '\b') || (*(char *)(param_1 + 0x3c) == '\x10')) {
    FUN_0004ac0a(param_2,1,0,0,param_4);
    iVar1 = FUN_0004c924(param_1,0,1);
    iVar2 = FUN_0004c924(param_1,0,2);
    if (iVar1 == iVar2) {
      iVar1 = iVar1 / 2;
      iVar9 = iVar1;
      if (((param_3 < iVar1) && (iVar9 = param_3, param_3 < 0)) &&
         (iVar9 = param_3 + iVar1, param_3 + iVar1 < 0)) {
        iVar9 = 0;
      }
      iVar3 = *(int *)(param_1 + 0x40);
      if (param_4 < iVar3) {
        sVar10 = 0;
      }
      else if (*(int *)(param_1 + 0x44) < param_4) {
        sVar10 = (short)*(undefined4 *)(param_1 + 0x50);
      }
      else {
        sVar10 = (short)((uint)((param_4 - iVar3) * *(int *)(param_1 + 0x50)) /
                        (uint)(*(int *)(param_1 + 0x44) - iVar3));
      }
      iVar3 = FUN_00052d00((int)(short)(*(short *)(param_1 + 0x54) + sVar10));
      iVar4 = thunk_FUN_00052d12((int)(short)(*(short *)(param_1 + 0x54) + sVar10));
      iVar5 = FUN_0004a030(param_2);
      if (((iVar5 == 0) || (uVar6 = FUN_0004a01c(param_2), uVar6 < 2)) ||
         (puVar7 = (undefined4 *)FUN_0004a020(param_2), puVar7 == (undefined4 *)0x0)) {
        uVar6 = FUN_0004bb8c(param_2);
        for (uVar8 = 0; uVar8 < uVar6; uVar8 = uVar8 - 1) {
          uVar11 = FUN_0004bb9e(param_2,uVar8);
          iVar5 = FUN_00046678();
          if (iVar5 == 0x5d973) {
            puVar7 = (undefined4 *)FUN_00046680(uVar11);
            if (puVar7 != (undefined4 *)0x0) goto LAB_0004fe10;
            break;
          }
        }
        puVar7 = (undefined4 *)FUN_0004a318(0x10);
        if (puVar7 == (undefined4 *)0x0) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
        FUN_0004aa4c(param_2,0x5d973,0x26,puVar7);
      }
LAB_0004fe10:
      uVar11 = VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
      *puVar7 = uVar11;
      uVar11 = VectorSignedToFloat(iVar2 / 2,(byte)(in_fpscr >> 0x16) & 3);
      puVar7[1] = uVar11;
      uVar11 = VectorSignedToFloat((iVar9 * iVar3 >> 0xf) + iVar1,(byte)(in_fpscr >> 0x16) & 3);
      puVar7[2] = uVar11;
      uVar11 = VectorSignedToFloat((iVar9 * iVar4 >> 0xf) + iVar2 / 2,(byte)(in_fpscr >> 0x16) & 3);
      puVar7[3] = uVar11;
      *(undefined4 **)(param_2 + 0x2c) = puVar7;
      *(undefined4 *)(param_2 + 0x30) = 2;
      *(uint *)(param_2 + 0x34) = *(uint *)(param_2 + 0x34) & 0xfffffffd | 2;
      FUN_0004deac(param_2);
      FUN_0004d3d8(param_2);
      return;
    }
  }
  return;
}

