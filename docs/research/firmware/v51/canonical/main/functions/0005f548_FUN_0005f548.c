/* Address: 0005f548; name: FUN_0005f548; body bytes: 670 */

void FUN_0005f548(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined1 auStack_80 [72];
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  iVar1 = FUN_00046688();
  if (iVar1 == 7) {
    iVar1 = FUN_0004675a(param_1);
    if (iVar1 != DAT_1ffe0868) {
      uVar2 = FUN_0004037c(0x4c3200);
      uVar3 = FUN_00046756(param_1);
      FUN_0004e8b2(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0xffffff);
      uVar3 = FUN_00046756(param_1);
      FUN_0004ea90(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0xffffff);
      uVar3 = FUN_00046756(param_1);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004e960(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0x999999);
      uVar3 = FUN_00046756(param_1);
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_0004ea90(uVar3,uVar2,0);
      uVar2 = FUN_00037604();
      local_38 = FUN_0004675a(param_1);
      local_24 = 0x53cf5;
      local_2c = 0x23969;
      uStack_28 = 0x53ed9;
      uStack_30 = 0;
      uStack_34 = uVar2;
      FUN_0001046a(auStack_80,&DAT_1fffbad0,0x48);
      FUN_00058430(DAT_1fffbac0,DAT_1fffbac4,DAT_1fffbac8,DAT_1fffbacc);
    }
    for (uVar5 = 0; iVar1 = FUN_0004ba5c(DAT_1ffe05b0), uVar5 < iVar1 - 6U; uVar5 = uVar5 + 1 & 0xff
        ) {
      iVar1 = FUN_00046756(param_1);
      iVar4 = FUN_0004b9de(DAT_1ffe05b0,uVar5);
      if (iVar1 == iVar4) goto LAB_0005f6c0;
    }
  }
  else if (iVar1 == 1) {
    for (uVar5 = 0; iVar1 = FUN_0004ba5c(DAT_1ffe05b0), uVar5 < iVar1 - 6U; uVar5 = uVar5 + 1 & 0xff
        ) {
      iVar1 = FUN_00046756(param_1);
      iVar4 = FUN_0004b9de(DAT_1ffe05b0,uVar5);
      if (iVar1 == iVar4) {
LAB_0005f6c0:
        DAT_1ffe0244 = (char)uVar5;
        return;
      }
    }
  }
  else if (((DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') && DAT_1ffe0330 == 0) &&
          (DAT_1fffaae6 != '\x01')) {
    if (iVar1 == 0xe) {
      iVar1 = FUN_00046700(param_1);
      if (iVar1 != 0x1c) {
        if (iVar1 == 0x1d) {
          FUN_0001814c();
          uVar2 = FUN_00046756(param_1);
          FUN_0004e5a6(uVar2,7,0);
          return;
        }
        if (iVar1 + -100 < 1) {
          if (DAT_1ffe0244 != 0) {
            DAT_1ffe0244 = DAT_1ffe0244 - 1;
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else {
          iVar1 = FUN_0004ba5c(DAT_1ffe05b0);
          if ((uint)DAT_1ffe0244 < iVar1 - 1U) {
            DAT_1ffe0244 = DAT_1ffe0244 + 1;
            FUN_000471d8(DAT_1ffe0144);
            return;
          }
        }
      }
    }
    else if (iVar1 == 0x10) {
      if (DAT_1ffe0128 == '\0') {
        DAT_1ffe02b0 = 0;
        uVar2 = FUN_0004037c(0xffa600);
        uVar3 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar3,uVar2,4);
        uVar2 = FUN_0004037c(0);
        uVar3 = FUN_00046756(param_1);
        FUN_0004ea90(uVar3,uVar2,4);
        uVar2 = FUN_0004037c(0);
        uVar3 = FUN_00046756(param_1);
        uVar3 = FUN_0004b9de(uVar3,0);
        FUN_0004e960(uVar3,uVar2,0);
        uVar2 = FUN_0004037c(0);
        uVar3 = FUN_00046756(param_1);
        uVar3 = FUN_0004b9de(uVar3,1);
        FUN_0004ea90(uVar3,uVar2,0);
        uVar2 = FUN_00046756(param_1);
        FUN_0004e4b2(uVar2,0);
        return;
      }
    }
    else if (iVar1 == 0x11) {
      uVar2 = FUN_0004037c(0);
      uVar3 = FUN_00046756(param_1);
      FUN_0004e8b2(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0xffffff);
      uVar3 = FUN_00046756(param_1);
      FUN_0004ea90(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0xffffff);
      uVar3 = FUN_00046756(param_1);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004e960(uVar3,uVar2,0);
      uVar2 = FUN_0004037c(0x999999);
      uVar3 = FUN_00046756(param_1);
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_0004ea90(uVar3,uVar2,0);
      return;
    }
  }
  return;
}

