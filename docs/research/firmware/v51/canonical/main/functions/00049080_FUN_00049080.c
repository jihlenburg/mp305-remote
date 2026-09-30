/* Address: 00049080; name: FUN_00049080; body bytes: 354 */

void FUN_00049080(int param_1,uint param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  int iVar10;
  int local_60;
  int local_5c;
  undefined1 auStack_54 [20];
  undefined4 local_40;
  uint local_3c;
  int local_38;
  int local_34;
  int iStack_30;
  uint local_2c;
  int *piStack_28;
  
  if (param_3 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  pcVar8 = *(char **)(param_1 + 0x2c);
  local_38 = param_1;
  iStack_30 = param_1;
  local_2c = param_2;
  piStack_28 = param_3;
  local_5c = FUN_0004b108(param_1,0,pcVar8);
  if (*pcVar8 != '\0') {
    local_3c = FUN_000375a2(local_38);
    uVar1 = FUN_00051c28(pcVar8,local_2c);
    iVar2 = FUN_0004cb7c(param_1,0);
    iVar3 = FUN_0004cb58(param_1,0);
    uVar4 = FUN_0004cb34(param_1,0);
    iVar5 = FUN_00046bd6();
    FUN_0004bab4(param_1,auStack_54);
    local_40 = FUN_0003db28(auStack_54);
    local_34 = FUN_0003db0a(auStack_54);
    iVar10 = 0;
    uVar9 = 0;
    uVar7 = 0;
    if (*pcVar8 != '\0') {
      while( true ) {
        uVar7 = uVar9;
        if ((local_34 < iVar10 + iVar5 + iVar2 + iVar5) && ((*(byte *)(local_38 + 0x5c) & 7) == 1))
        {
          local_3c = local_3c | 4;
        }
        iVar6 = FUN_0005175c(pcVar8 + uVar7,uVar4,iVar3,local_40,0,local_3c);
        uVar9 = uVar7 + iVar6;
        if ((uVar1 < uVar9) || (pcVar8[uVar9] == '\0')) break;
        iVar10 = iVar10 + iVar5 + iVar2;
      }
    }
    if ((uVar1 != 0) &&
       (((pcVar8[uVar1 - 1] == '\n' || (pcVar8[uVar1 - 1] == '\r')) && (pcVar8[uVar1] == '\0')))) {
      iVar10 = iVar10 + iVar5 + iVar2;
      uVar7 = uVar1;
    }
    local_60 = FUN_00051a28(pcVar8 + uVar7,uVar1 - uVar7,uVar4,iVar3);
    if (local_2c != uVar7) {
      local_60 = local_60 + iVar3;
    }
    FUN_0002641a(&local_60,local_5c,pcVar8 + uVar7,uVar9 - uVar7,uVar4,iVar3,auStack_54);
    *param_3 = local_60;
    param_3[1] = iVar10;
    return;
  }
  iVar2 = 0;
  param_3[1] = 0;
  if (local_5c != 1) {
    if (local_5c == 2) {
      iVar2 = FUN_0004bb1a(param_1);
      *param_3 = iVar2 / 2;
      return;
    }
    if (local_5c != 3) {
      return;
    }
    iVar2 = FUN_0004bb1a(param_1);
  }
  *param_3 = iVar2;
  return;
}

