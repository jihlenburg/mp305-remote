/* Address: 0004f0c4; name: FUN_0004f0c4; body bytes: 390 */

void FUN_0004f0c4(int param_1,uint param_2,int param_3,int param_4,int param_5,int *param_6,
                 int param_7)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if (((param_3 != 0) || (param_4 != 0x100)) || (param_5 != 0x100)) {
    for (uVar2 = 0; uVar2 < param_2; uVar2 = uVar2 + 1) {
      *(int *)(param_1 + uVar2 * 8) = *(int *)(param_1 + uVar2 * 8) - *param_6;
      iVar3 = param_1 + uVar2 * 8;
      *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) - param_6[1];
    }
    if (param_3 == 0) {
      for (uVar2 = 0; uVar2 < param_2; uVar2 = uVar2 + 1) {
        *(int *)(param_1 + uVar2 * 8) = *param_6 + (*(int *)(param_1 + uVar2 * 8) * param_4 >> 8);
        iVar3 = param_1 + uVar2 * 8;
        *(int *)(iVar3 + 4) = param_6[1] + (*(int *)(iVar3 + 4) * param_5 >> 8);
      }
    }
    else {
      if (0xe10 < param_3) {
        param_3 = param_3 + -0xe10;
      }
      if (param_3 < 0) {
        param_3 = param_3 + 0xe10;
      }
      iVar8 = param_3 % 10;
      sVar1 = (short)(param_3 / 10);
      iVar3 = thunk_FUN_00052d12((int)sVar1);
      iVar4 = thunk_FUN_00052d12((int)(short)(sVar1 + 1));
      iVar5 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5a));
      iVar6 = thunk_FUN_00052d12((int)(short)(sVar1 + 0x5b));
      iVar3 = (iVar4 * iVar8 + (10 - iVar8) * iVar3) / 10 >> 5;
      iVar4 = (iVar6 * iVar8 + iVar5 * (10 - iVar8)) / 10 >> 5;
      for (uVar2 = 0; uVar2 < param_2; uVar2 = uVar2 + 1) {
        iVar8 = param_1 + uVar2 * 8;
        iVar5 = *(int *)(param_1 + uVar2 * 8);
        iVar6 = *(int *)(iVar8 + 4);
        if ((param_4 == 0x100) && (param_5 == 0x100)) {
          *(int *)(param_1 + uVar2 * 8) = *param_6 + (iVar4 * iVar5 - iVar3 * iVar6 >> 10);
          iVar5 = param_6[1] + (iVar4 * iVar6 + iVar3 * iVar5 >> 10);
        }
        else {
          if (param_7 == 0) {
            *(int *)(param_1 + uVar2 * 8) =
                 *param_6 + ((iVar4 * iVar5 - iVar3 * iVar6) * param_4 >> 0x12);
            iVar7 = (iVar4 * iVar6 + iVar3 * iVar5) * param_5;
          }
          else {
            iVar7 = iVar4 * iVar6 * param_5 + iVar3 * iVar5 * param_4;
            *(int *)(param_1 + uVar2 * 8) =
                 *param_6 + (iVar4 * iVar5 * param_4 - iVar3 * iVar6 * param_5 >> 0x12);
          }
          iVar5 = param_6[1] + (iVar7 >> 0x12);
        }
        *(int *)(iVar8 + 4) = iVar5;
      }
    }
  }
  return;
}

