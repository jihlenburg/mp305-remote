/* Address: 0003f77c; name: FUN_0003f77c; body bytes: 398 */

void FUN_0003f77c(int param_1,int *param_2,uint param_3,uint *param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  
  if (param_1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (param_2 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  if (*(uint *)(param_1 + 0x70) <= param_3) {
    *param_4 = 0;
    param_4[1] = 0;
    return;
  }
  iVar2 = FUN_0004bb1a(param_1);
  iVar3 = FUN_0004baf8(param_1);
  bVar1 = *(byte *)(param_1 + 0x74) & 7;
  if (bVar1 == 1) {
    uVar4 = (iVar2 * param_3) / (*(int *)(param_1 + 0x70) - 1U);
  }
  else if (bVar1 == 3) {
    iVar7 = param_1 + ((int)((uint)*(byte *)(param_2 + 4) << 0x1c) >> 0x1f) * -4;
    uVar4 = FUN_0004a388(*(undefined4 *)(*param_2 + param_3 * 4),*(undefined4 *)(iVar7 + 0x54),
                         *(undefined4 *)(iVar7 + 0x5c),0,iVar2);
  }
  else {
    if (bVar1 != 2) goto LAB_0003f888;
    uVar4 = FUN_0004a120();
    iVar7 = FUN_0004c828(param_1,&LAB_00050000);
    iVar8 = FUN_0004c828(param_1,0);
    uVar5 = *(uint *)(param_1 + 0x70);
    iVar9 = 0;
    uVar10 = ((1 - uVar5) * iVar8 + iVar2) / uVar5;
    *param_4 = (param_3 * (iVar2 - uVar10)) / (uVar5 - 1);
    piVar6 = (int *)FUN_0004a14a(param_1 + 0x2c);
    while ((piVar6 != (int *)0x0 && (piVar6 != param_2))) {
      iVar9 = iVar9 + 1;
      piVar6 = (int *)FUN_0004a144(param_1 + 0x2c);
    }
    uVar4 = (uVar10 * iVar9) / uVar4 + (param_3 * (iVar2 + iVar8)) / *(uint *)(param_1 + 0x70) +
            (int)((iVar7 * (1 - uVar4) + uVar10) / uVar4) / 2;
  }
  *param_4 = uVar4;
LAB_0003f888:
  iVar2 = FUN_0004c696(param_1,0);
  iVar7 = FUN_0004c858(param_1,0);
  *param_4 = iVar7 + iVar2 + *param_4;
  iVar7 = FUN_0004bd90(param_1);
  *param_4 = *param_4 - iVar7;
  if ((int)((uint)*(byte *)(param_1 + 0x74) << 0x1c) < 0) {
    iVar7 = 0;
  }
  else {
    iVar7 = param_2[3];
  }
  iVar8 = param_1 + ((int)((uint)*(byte *)(param_2 + 4) << 0x1b) >> 0x1f) * -4;
  iVar9 = *(int *)(iVar8 + 0x44);
  param_4[1] = iVar3 - (iVar3 * (*(int *)(param_2[1] +
                                         ((iVar7 + param_3) -
                                         *(uint *)(param_1 + 0x70) *
                                         ((iVar7 + param_3) / *(uint *)(param_1 + 0x70))) * 4) -
                                iVar9)) / (*(int *)(iVar8 + 0x4c) - iVar9);
  iVar3 = FUN_0004c8f4(param_1,0);
  param_4[1] = iVar3 + iVar2 + param_4[1];
  iVar2 = FUN_0004bf14(param_1);
  param_4[1] = param_4[1] - iVar2;
  return;
}

