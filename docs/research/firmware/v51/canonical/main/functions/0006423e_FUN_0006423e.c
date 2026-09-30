/* Address: 0006423e; name: FUN_0006423e; body bytes: 422 */

void FUN_0006423e(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,int param_9,int param_10,int param_11,int param_12)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  uint uVar8;
  int iVar9;
  undefined1 *puVar10;
  int iVar11;
  int iVar12;
  int local_54;
  
  for (iVar11 = 0; iVar11 < param_9; iVar11 = iVar11 + 1) {
    uVar8 = param_5 + (iVar11 * param_7 >> 8);
    uVar4 = param_6 + (iVar11 * param_8 >> 8);
    iVar3 = (int)uVar8 >> 8;
    iVar1 = (int)uVar4 >> 8;
    if ((((iVar3 < 0) || (param_2 <= iVar3)) || (iVar1 < 0)) || (param_3 <= iVar1)) {
      *(undefined1 *)(param_10 + iVar11 * 4 + 3) = 0;
    }
    else {
      uVar8 = uVar8 & 0xff;
      uVar4 = uVar4 & 0xff;
      if (uVar8 < 0x80) {
        iVar12 = -1;
        iVar9 = 0x7f - uVar8;
      }
      else {
        iVar12 = 1;
        iVar9 = uVar8 - 0x80;
      }
      if (uVar4 < 0x80) {
        iVar5 = 0x7f - uVar4;
        local_54 = -1;
      }
      else {
        iVar5 = uVar4 - 0x80;
        local_54 = 1;
      }
      puVar10 = (undefined1 *)(iVar3 * param_12 + iVar1 * param_4 + param_1);
      puVar6 = (undefined4 *)(param_10 + iVar11 * 4);
      *(undefined1 *)((int)puVar6 + 2) = puVar10[2];
      *(undefined1 *)((int)puVar6 + 1) = puVar10[1];
      *(undefined1 *)(param_10 + iVar11 * 4) = *puVar10;
      *(undefined1 *)((int)puVar6 + 3) = 0xff;
      if (((param_11 == 0) || (iVar3 + iVar12 < 0)) ||
         ((param_2 + -1 < iVar3 + iVar12 ||
          ((iVar1 + local_54 < 0 || (param_3 + -1 < iVar1 + local_54)))))) {
        if ((((iVar3 == 0) && (iVar12 < 0)) ||
            (((iVar3 == param_2 + -1 && (0 < iVar12)) ||
             ((iVar9 = iVar5, iVar1 == 0 && (local_54 < 0)))))) ||
           ((iVar1 == param_3 + -1 && (0 < local_54)))) {
          *(char *)((int)puVar6 + 3) = (char)((uint)((0xff - iVar9) * 0xff) >> 8);
        }
      }
      else {
        pbVar7 = puVar10 + iVar12 * param_12;
        uVar4 = (uint)pbVar7[2] << 0x10 | (uint)pbVar7[1] << 8 | (uint)*pbVar7;
        pbVar7 = puVar10 + local_54 * param_4;
        uVar8 = (uint)pbVar7[2] << 0x10 | (uint)pbVar7[1] << 8 | (uint)*pbVar7;
        iVar1 = FUN_0003ff18(*puVar6,uVar8 | 0xff000000);
        if (iVar1 == 0) {
          uVar2 = FUN_0004045a(uVar8 | iVar5 << 0x18,*puVar6);
          *puVar6 = uVar2;
        }
        iVar1 = FUN_0003ff18(*puVar6,uVar4 | 0xff000000);
        if (iVar1 == 0) {
          uVar2 = FUN_0004045a(uVar4 | iVar9 << 0x18,*puVar6);
          *puVar6 = uVar2;
        }
      }
    }
  }
  return;
}

