/* Address: 000635a0; name: FUN_000635a0; body bytes: 310 */

/* Recovered from stored Thumb pointer at 0004ecfc; callback identification is inferred until
   reviewed. */

void FUN_000635a0(int *param_1,uint param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  bool bVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined2 uVar11;
  int local_24;
  undefined4 local_20;
  
  uVar9 = 0;
  iVar10 = *param_1;
  while( true ) {
    if ((*(ushort *)(iVar10 + 0x2a) & 0x3ff) >> 4 <= uVar9) {
      return;
    }
    uVar4 = *(uint *)(*(int *)(iVar10 + 0xc) + uVar9 * 8 + 4);
    if (((int)(uVar4 << 6) < 0) && ((uVar4 & 0xffffff) == param_1[2])) break;
    uVar9 = uVar9 + 1;
  }
  uVar11 = 0;
  bVar1 = *(byte *)(param_1 + 1);
  local_20 = param_4;
  if (bVar1 == 0x3d) goto LAB_0006369e;
  if (bVar1 < 0x3e) {
    if (bVar1 != 0x34) {
      if (bVar1 < 0x35) {
        if (((bVar1 != 0x1c) && (bVar1 != 0x23)) && (bVar1 != 0x31)) {
LAB_0006361c:
          if (param_2 != 0) {
            if (param_2 == 0xff) goto LAB_00063680;
            iVar5 = param_1[3] + ((int)(param_2 * (param_1[4] - param_1[3])) >> 8);
            goto LAB_0006362e;
          }
          goto LAB_0006367c;
        }
      }
      else {
        if (bVar1 == 0x35) goto LAB_00063684;
        if (bVar1 != 0x39) goto LAB_0006361c;
      }
LAB_0006369e:
      if ((int)param_2 < 1) {
        uVar4 = (uint)*(ushort *)(param_1 + 3);
        uVar3 = *(undefined1 *)((int)param_1 + 0xe);
        local_20 = param_4;
      }
      else if ((int)param_2 < 0xff) {
        local_24 = param_3;
        uVar7 = FUN_000403d2(param_1[4],param_1[3],param_2 & 0xff,param_1[2],0);
        local_20._0_2_ = (undefined2)uVar7;
        uVar4 = CONCAT22(uVar11,(undefined2)local_20);
        local_20._2_1_ = (undefined1)((uint)uVar7 >> 0x10);
        uVar3 = local_20._2_1_;
        local_20 = uVar7;
      }
      else {
        uVar4 = (uint)*(ushort *)(param_1 + 4);
        uVar3 = *(undefined1 *)((int)param_1 + 0x12);
        local_20 = param_4;
      }
      iVar8 = CONCAT13((char)(uVar4 >> 0x18),CONCAT12(uVar3,(short)uVar4));
      goto LAB_00063630;
    }
LAB_00063684:
    if ((int)param_2 < 0xff) {
LAB_0006367c:
      iVar5 = param_1[3];
    }
    else {
LAB_00063680:
      iVar5 = param_1[4];
    }
  }
  else {
    if (bVar1 != 0x61) {
      if (bVar1 < 0x62) {
        if ((bVar1 == 0x45) || (bVar1 == 0x58)) goto LAB_0006369e;
        if (bVar1 == 0x5a) goto LAB_00063684;
      }
      else if ((bVar1 == 0x66) || (bVar1 == 0x67)) goto LAB_00063684;
      goto LAB_0006361c;
    }
    iVar5 = param_1[3];
    if (iVar5 == 0) goto LAB_00063680;
    iVar8 = param_1[4];
    if ((iVar8 != 0) && (0x7f < (int)param_2)) goto LAB_00063630;
  }
LAB_0006362e:
  iVar8 = iVar5;
LAB_00063630:
  local_24 = 0;
  bVar2 = true;
  iVar6 = FUN_00050a74(*(undefined4 *)(*(int *)(iVar10 + 0xc) + uVar9 * 8),(char)param_1[1],
                       &local_24);
  iVar5 = iVar8;
  if (((iVar6 != 0) && (iVar8 == local_24)) &&
     ((iVar6 = FUN_000402f4(iVar8), iVar6 != 0 && (iVar8 == local_24)))) {
    bVar2 = false;
  }
  FUN_00050ef2(*(undefined4 *)(*(int *)(iVar10 + 0xc) + uVar9 * 8),(char)param_1[1],iVar5);
  if (!bVar2) {
    return;
  }
  FUN_0004dedc(*param_1,param_1[2],(char)param_1[1]);
  return;
}

