/* Address: 0003608c; name: FUN_0003608c; body bytes: 612 */

void FUN_0003608c(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 auStack_80 [72];
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  iVar2 = FUN_00046688();
  if (iVar2 == 7) {
    cVar1 = FUN_0004ba5c(DAT_1ffe05b0);
    DAT_1ffe0244 = cVar1 - 2;
    if (DAT_1fffa00c == '\0') {
      FUN_0001814c();
      uVar3 = FUN_0004037c(0x4c3200);
      uVar4 = FUN_00046756(param_1);
      FUN_0004e8b2(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0xffffff);
      uVar4 = FUN_00046756(param_1);
      FUN_0004ea90(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0xffffff);
      uVar4 = FUN_00046756(param_1);
      uVar4 = FUN_0004b9de(uVar4,0);
      FUN_0004e960(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0x999999);
      uVar4 = FUN_00046756(param_1);
      uVar4 = FUN_0004b9de(uVar4,1);
      FUN_0004ea90(uVar4,uVar3,0);
      uVar3 = FUN_00037604();
      local_38 = FUN_0004675a(param_1);
      local_28 = 0x53ed9;
      uStack_24 = 0x53cf5;
      local_2c = 0x23969;
      uStack_30 = 0;
      uStack_34 = uVar3;
      FUN_0001046a(auStack_80,&DAT_1fffbad0,0x48);
      FUN_00058430(DAT_1fffbac0,DAT_1fffbac4,DAT_1fffbac8,DAT_1fffbacc);
    }
  }
  else if (iVar2 == 1) {
    cVar1 = FUN_0004ba5c(DAT_1ffe05b0);
    DAT_1ffe0244 = cVar1 - 2;
  }
  else if (((DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') && DAT_1ffe0330 == 0) &&
          (DAT_1fffaae6 != '\x01')) {
    if (iVar2 == 0xe) {
      iVar2 = FUN_00046700(param_1);
      if (iVar2 != 0x1c) {
        if (iVar2 == 0x1d) {
          if (DAT_1fffa00c == '\0') {
            FUN_0001814c();
            uVar3 = FUN_00046756(param_1);
            FUN_0004e5a6(uVar3,7,0);
            return;
          }
        }
        else if (iVar2 + -100 < 1) {
          if (DAT_1ffe0244 != 0) {
            DAT_1ffe0244 = DAT_1ffe0244 - 1;
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else {
          iVar2 = FUN_0004ba5c(DAT_1ffe05b0);
          if ((uint)DAT_1ffe0244 < iVar2 - 1U) {
            DAT_1ffe0244 = DAT_1ffe0244 + 1;
            FUN_000471d8(DAT_1ffe0144);
            return;
          }
        }
      }
    }
    else if (iVar2 == 0x10) {
      if (DAT_1ffe0128 == '\0') {
        DAT_1ffe02b0 = 0;
        uVar3 = FUN_0004037c(0xffa600);
        uVar4 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar4,uVar3,4);
        uVar3 = FUN_0004037c(0);
        uVar4 = FUN_00046756(param_1);
        FUN_0004ea90(uVar4,uVar3,4);
        uVar3 = FUN_0004037c(0);
        uVar4 = FUN_00046756(param_1);
        uVar4 = FUN_0004b9de(uVar4,0);
        FUN_0004e960(uVar4,uVar3,0);
        uVar3 = FUN_0004037c(0);
        uVar4 = FUN_00046756(param_1);
        uVar4 = FUN_0004b9de(uVar4,1);
        FUN_0004e960(uVar4,uVar3,0);
        uVar3 = FUN_00046756(param_1);
        FUN_0004e4b2(uVar3,0);
        return;
      }
    }
    else if (iVar2 == 0x11) {
      uVar3 = FUN_0004037c(0);
      uVar4 = FUN_00046756(param_1);
      FUN_0004e8b2(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0xffffff);
      uVar4 = FUN_00046756(param_1);
      FUN_0004ea90(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0xffffff);
      uVar4 = FUN_00046756(param_1);
      uVar4 = FUN_0004b9de(uVar4,0);
      FUN_0004e960(uVar4,uVar3,0);
      uVar3 = FUN_0004037c(0x999999);
      uVar4 = FUN_00046756(param_1);
      uVar4 = FUN_0004b9de(uVar4,1);
      FUN_0004e960(uVar4,uVar3,0);
      return;
    }
  }
  return;
}

