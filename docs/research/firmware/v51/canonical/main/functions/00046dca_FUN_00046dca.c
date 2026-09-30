/* Address: 00046dca; name: FUN_00046dca; body bytes: 346 */

int FUN_00046dca(undefined4 *param_1,int param_2,uint param_3,uint *param_4)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint local_3c [2];
  undefined4 *puStack_34;
  int local_30;
  uint uStack_2c;
  uint *puStack_28;
  
  puVar1 = (uint *)param_1[2];
  uVar3 = puVar1[1];
  uVar6 = puVar1[2];
  uVar8 = puVar1[3];
  iVar2 = param_1[1];
  uVar5 = *(uint *)(iVar2 + 4);
  puStack_34 = param_1;
  local_30 = param_2;
  uStack_2c = param_3;
  puStack_28 = param_4;
  if ((uVar6 < *puVar1) || (uVar3 < uVar6)) {
    (**(code **)(iVar2 + 0x1c))(iVar2,*param_1,uVar6,0);
    if (uVar5 < param_3) {
      iVar2 = (**(code **)(param_1[1] + 0x14))(param_1[1],*param_1,local_30,param_3,param_4);
    }
    else {
      if (uVar8 == 0) {
        uVar8 = FUN_0004a318(uVar5);
        *(uint *)(param_1[2] + 0xc) = uVar8;
        if (uVar8 == 0) {
          do {
                    /* WARNING: Do nothing block with infinite loop */
          } while( true );
        }
      }
      local_3c[0] = 0;
      iVar2 = (**(code **)(param_1[1] + 0x14))(param_1[1],*param_1,uVar8,uVar5,local_3c);
      *(uint *)param_1[2] = uVar6;
      *(uint *)(param_1[2] + 4) = (local_3c[0] - 1) + uVar6;
      uVar3 = local_3c[0];
      if (param_3 < local_3c[0]) {
        uVar3 = param_3;
      }
      *param_4 = uVar3;
      FUN_0004a404(local_30,uVar8);
    }
  }
  else {
    uVar7 = (uVar3 - uVar6) + 1;
    if ((uVar5 == 0xffffffff) && (uVar7 < param_3)) {
      param_3 = uVar3 - uVar6;
    }
    iVar2 = uVar8 + ((uVar3 - *puVar1) - uVar7) + 1;
    if (param_3 <= uVar7) {
      FUN_0004a404(param_2,iVar2,param_3);
      *param_4 = param_3;
      goto LAB_00046f10;
    }
    FUN_0004a404(param_2,iVar2,uVar7);
    (**(code **)(param_1[1] + 0x1c))(param_1[1],*param_1,*(int *)(param_1[2] + 4) + 1,0);
    uVar3 = param_3 - uVar7;
    local_3c[0] = 0;
    if (uVar5 < uVar3) {
      iVar2 = (**(code **)(param_1[1] + 0x14))(param_1[1],*param_1,local_30 + uVar7,uVar3);
    }
    else {
      iVar2 = (**(code **)(param_1[1] + 0x14))(param_1[1],*param_1,uVar8,uVar5,local_3c);
      iVar4 = ((int *)param_1[2])[1] + 1;
      *(int *)param_1[2] = iVar4;
      *(uint *)(param_1[2] + 4) = iVar4 + (local_3c[0] - 1);
      uVar5 = local_3c[0];
      if (uVar3 < local_3c[0]) {
        uVar5 = uVar3;
      }
      FUN_0004a404(local_30 + uVar7,uVar8,uVar5 & 0xffff);
    }
    if (local_3c[0] + uVar7 < param_3) {
      param_3 = local_3c[0] + uVar7;
    }
    *param_4 = param_3;
  }
  if (iVar2 != 0) {
    return iVar2;
  }
LAB_00046f10:
  *(uint *)(param_1[2] + 8) = *param_4 + *(int *)(param_1[2] + 8);
  return 0;
}

