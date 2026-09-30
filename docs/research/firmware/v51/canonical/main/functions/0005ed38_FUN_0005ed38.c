/* Address: 0005ed38; name: FUN_0005ed38; body bytes: 368 */

void FUN_0005ed38(undefined4 param_1,undefined2 *param_2,uint param_3,int param_4)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined2 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined2 *puVar9;
  code *local_54 [9];
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  
  iVar8 = param_3 + param_4;
  FUN_0003da10(&local_30,param_1);
  local_28 = ((param_4 + (int)param_3 / 2) - ((int)(param_3 << 0x1f) >> 0x1f)) + -2;
  local_2c = (int)param_3 / 2 + 1;
  local_30 = FUN_0003db28(param_1);
  local_30 = local_28 - local_30;
  local_24 = FUN_0003db0a(param_1);
  local_24 = local_24 + local_2c;
  FUN_000454e8(local_54,&local_30,param_4,0);
  iVar6 = 1;
  if (param_3 != 1) {
    iVar6 = (int)param_3 >> 1;
  }
  pbVar1 = (byte *)FUN_0004a318(iVar8);
  puVar9 = param_2;
  for (iVar2 = 0; iVar2 < iVar8; iVar2 = iVar2 + 1) {
    FUN_0004a57a(pbVar1,0xff,iVar8);
    iVar3 = (*local_54[0])(pbVar1,0,iVar2,iVar8,local_54);
    if (iVar3 == 0) {
      FUN_0004a57a(puVar9,0,iVar8 * 2);
    }
    else {
      *puVar9 = (short)((int)((uint)*pbVar1 << 6) / iVar6);
      for (iVar3 = 1; iVar3 < iVar8; iVar3 = iVar3 + 1) {
        if ((uint)pbVar1[iVar3] == (uint)pbVar1[iVar3 + -1]) {
          uVar5 = puVar9[iVar3 + -1];
        }
        else {
          uVar5 = (undefined2)((int)((uint)pbVar1[iVar3] << 6) / iVar6);
        }
        puVar9[iVar3] = uVar5;
      }
    }
    puVar9 = puVar9 + iVar8;
  }
  FUN_00046bec(pbVar1);
  FUN_00045330(local_54);
  if (iVar6 == 1) {
    for (iVar6 = 0; iVar8 * iVar8 - iVar6 != 0 && iVar6 <= iVar8 * iVar8; iVar6 = iVar6 + 1) {
      *(char *)((int)param_2 + iVar6) = (char)((ushort)param_2[iVar6] >> 6);
    }
  }
  else {
    FUN_0005ec04(iVar8,iVar6,param_2);
    iVar6 = (param_3 & 1) + iVar6;
    if (1 < iVar6) {
      for (uVar4 = 0; uVar4 <= (uint)(iVar8 * iVar8) && iVar8 * iVar8 - uVar4 != 0;
          uVar4 = uVar4 + 1) {
        uVar7 = (uint)(ushort)param_2[uVar4];
        if (uVar7 != 0) {
          if (uVar7 == 0xff) {
            param_2[uVar4] = (short)(0x3fc0 / iVar6);
          }
          else {
            param_2[uVar4] = (short)((int)(uVar7 << 6) / iVar6);
          }
        }
      }
      FUN_0005ec04(iVar8,iVar6,param_2);
    }
    for (iVar6 = 0; iVar8 * iVar8 - iVar6 != 0 && iVar6 <= iVar8 * iVar8; iVar6 = iVar6 + 1) {
      *(undefined1 *)((int)param_2 + iVar6) = *(undefined1 *)(param_2 + iVar6);
    }
  }
  return;
}

