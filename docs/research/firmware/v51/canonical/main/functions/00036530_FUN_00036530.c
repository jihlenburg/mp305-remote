/* Address: 00036530; name: FUN_00036530; body bytes: 522 */

int FUN_00036530(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  code *pcVar4;
  code *pcVar5;
  int iVar6;
  undefined4 uVar7;
  int local_58 [6];
  int local_40;
  int local_3c;
  int local_34;
  int iStack_30;
  int iStack_2c;
  int local_28;
  
  local_34 = param_1;
  iStack_30 = param_2;
  iStack_2c = param_3;
  local_28 = param_4;
  iVar1 = FUN_0004cbf0(param_1,0);
  iVar2 = FUN_0004c6d8(local_34,0);
  uVar3 = (uint)*(byte *)(param_2 + 3);
  if ((int)(uVar3 << 0x1e) < 0) {
    if ((*(byte *)(param_2 + 3) & 1) == 0) {
      if (iVar2 == 0x3fffffff) goto LAB_0003656a;
      goto LAB_00036578;
    }
    if (iVar1 == 0x3fffffff) {
LAB_0003656a:
      uVar3 = uVar3 & 0xfffffffd;
      *(char *)(param_2 + 3) = (char)uVar3;
      goto LAB_00036570;
    }
  }
  else {
LAB_00036570:
    if ((uVar3 & 1) == 0) {
LAB_00036578:
      pcVar4 = (code *)0x4bbf3;
      goto LAB_0003657a;
    }
  }
  pcVar4 = (code *)0x4ccff;
LAB_0003657a:
  if ((*(byte *)(param_2 + 3) & 1) == 0) {
    pcVar5 = (code *)0x4ccff;
  }
  else {
    pcVar5 = (code *)0x4bbf3;
  }
  param_6[1] = 0;
  param_6[2] = 0;
  param_6[5] = 0;
  *param_6 = 0;
  param_6[3] = 0;
  param_6[4] = 0;
  local_58[0] = param_3;
  do {
    iVar1 = FUN_0004b9de(local_34,local_58[0]);
    if ((iVar1 == 0) ||
       ((local_58[0] != param_3 && (iVar2 = FUN_0004cd84(iVar1,0x200000), iVar2 != 0)))) break;
    iVar2 = FUN_0004cd92(iVar1,0x60001);
    if (iVar2 == 0) {
      local_40 = FUN_0004c6c0(iVar1,0);
      if (local_40 == 0) {
        iVar2 = (*pcVar4)(iVar1);
        if (((int)((uint)*(byte *)(param_2 + 3) << 0x1e) < 0) && (local_28 < param_6[2] + iVar2))
        break;
        param_6[2] = iVar2 + param_5 + param_6[2];
      }
      else {
        iVar2 = param_6[5];
        param_6[5] = iVar2 + 1;
        param_6[2] = param_6[2] + param_5;
        if ((*(byte *)(param_6 + 6) & 1) != 0) {
          local_3c = FUN_0004f588(param_6[4],(iVar2 + 1) * 0x18);
          if (local_3c == 0) {
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          *(int *)(local_3c + param_6[5] * 0x18 + -0x18) = iVar1;
          if ((*(byte *)(param_2 + 3) & 1) == 0) {
            uVar7 = 6;
          }
          else {
            uVar7 = 4;
          }
          uVar7 = FUN_0004c924(iVar1,0,uVar7);
          *(undefined4 *)(local_3c + param_6[5] * 0x18 + -0x14) = uVar7;
          if ((*(byte *)(param_2 + 3) & 1) == 0) {
            uVar7 = 7;
          }
          else {
            uVar7 = 5;
          }
          uVar7 = FUN_0004c924(iVar1,0,uVar7);
          *(undefined4 *)(local_3c + param_6[5] * 0x18 + -0x10) = uVar7;
          *(int *)(local_3c + param_6[5] * 0x18 + -8) = local_40;
          *(undefined4 *)(local_3c + param_6[5] * 0x18 + -4) = 0;
          param_6[4] = local_3c;
        }
      }
      iVar2 = (*pcVar5)(iVar1);
      iVar6 = *param_6;
      if (iVar6 < iVar2) {
        iVar6 = (*pcVar5)(iVar1);
      }
      *param_6 = iVar6;
      param_6[3] = param_6[3] + 1;
    }
    if ((int)((uint)*(byte *)(param_2 + 3) << 0x1d) < 0) {
      iVar2 = -1;
    }
    else {
      iVar2 = 1;
    }
    local_58[0] = iVar2 + local_58[0];
  } while (-1 < local_58[0]);
  if (0 < param_6[2]) {
    param_6[2] = param_6[2] - param_5;
  }
  iVar2 = local_28;
  if (param_6[5] == 0) {
    iVar2 = param_6[2];
  }
  param_6[1] = iVar2;
  if ((iVar1 != 0) && (local_58[0] == param_3)) {
    iVar1 = *(int *)(**(int **)(local_34 + 8) + local_58[0] * 4);
    FUN_000377d4(local_34,(*(byte *)(param_2 + 3) & 7) >> 2,local_58);
    if (iVar1 != 0) {
      iVar2 = (*pcVar5)(iVar1);
      *param_6 = iVar2;
      iVar1 = (*pcVar4)(iVar1);
      param_6[1] = iVar1;
      param_6[3] = 1;
    }
  }
  return local_58[0];
}

