/* Address: 00060540; name: FUN_00060540; body bytes: 432 */

void FUN_00060540(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00046688();
  if (iVar1 == 7) {
    if (DAT_1fffab6a == 0) {
      FUN_0001d6fc(DAT_1fffac90,DAT_1fffac94);
      DAT_1fffab44 = 0;
      DAT_1ffe0249 = 5;
      FUN_0001cb8c(0xf);
      return;
    }
  }
  else if (iVar1 == 1) {
    DAT_1ffe0249 = 5;
    return;
  }
  if (((DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') && DAT_1ffe0330 == 0) &&
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
          if (DAT_1ffe0249 != 0) {
            DAT_1ffe0249 = DAT_1ffe0249 - 1;
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else {
          iVar1 = FUN_0004ba5c(DAT_1ffe0624);
          if ((uint)DAT_1ffe0249 < iVar1 - 1U) {
            DAT_1ffe0249 = DAT_1ffe0249 + 1;
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
        FUN_0004e960(uVar3,uVar2,0);
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
      FUN_0004e960(uVar3,uVar2,0);
      return;
    }
  }
  return;
}

