/* Address: 000453c0; name: FUN_000453c0; body bytes: 292 */

void FUN_000453c0(undefined4 *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  FUN_0004a602(param_1,0x38);
  if ((param_3 == param_5) && (param_6 == 3)) {
    param_5 = param_5 + -1;
    param_3 = param_3 + -1;
  }
  iVar5 = param_5;
  iVar8 = param_4;
  if (param_5 < param_3) {
    iVar5 = param_3;
    param_3 = param_5;
    iVar8 = param_2;
    param_2 = param_4;
  }
  FUN_0004f266(param_1 + 2,param_2,param_3);
  FUN_0004f266(param_1 + 4,iVar8,iVar5);
  *(char *)(param_1 + 6) = (char)param_6;
  FUN_0004f266(param_1 + 7,param_2,param_3);
  iVar3 = iVar8 - param_2;
  iVar6 = iVar3;
  if (iVar3 < 1) {
    iVar6 = param_2 - iVar8;
  }
  iVar7 = iVar5 - param_3;
  iVar8 = iVar7;
  if (iVar7 < 1) {
    iVar8 = param_3 - iVar5;
  }
  if (iVar8 < iVar6) {
    bVar2 = *(byte *)(param_1 + 0xd) | 1;
  }
  else {
    bVar2 = *(byte *)(param_1 + 0xd) & 0xfe;
  }
  *(byte *)(param_1 + 0xd) = bVar2;
  param_1[10] = 0;
  *param_1 = 0x426e3;
  param_1[9] = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  if ((bVar2 & 1) == 0) {
    if (iVar7 != 0) {
      param_1[9] = iVar3 * (0x100000 / iVar7) >> 10;
    }
    if (iVar3 != 0) {
      param_1[10] = iVar7 * (0x100000 / iVar3) >> 10;
    }
    uVar4 = param_1[9];
  }
  else {
    if (iVar3 != 0) {
      param_1[10] = iVar7 * (0x100000 / iVar3) >> 10;
    }
    if (iVar7 != 0) {
      param_1[9] = iVar3 * (0x100000 / iVar7) >> 10;
    }
    uVar4 = param_1[10];
  }
  param_1[0xb] = uVar4;
  bVar1 = *(byte *)(param_1 + 6);
  if ((bVar1 & 3) == 0) {
LAB_000454b4:
    bVar2 = bVar2 & 0xfd;
  }
  else {
    if ((bVar1 & 3) != 1) {
      if ((bVar1 & 3) == 2) {
        if ((int)param_1[0xb] < 1) goto LAB_000454b4;
      }
      else {
        if ((~bVar1 & 3) != 0) goto LAB_000454c2;
        if (0 < (int)param_1[0xb]) goto LAB_000454b4;
      }
    }
    bVar2 = bVar2 | 2;
  }
  *(byte *)(param_1 + 0xd) = bVar2;
LAB_000454c2:
  iVar5 = (int)param_1[0xb] >> 2;
  param_1[0xc] = iVar5;
  if ((int)param_1[0xb] < 0) {
    param_1[0xc] = -iVar5;
  }
  return;
}

