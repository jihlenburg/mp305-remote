/* Address: 0001dbfc; name: FUN_0001dbfc; body bytes: 388 */

void FUN_0001dbfc(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar2 = FUN_00046688();
  if ((iVar2 == 7) || (iVar2 == 1)) {
    cVar1 = FUN_0004ba5c(DAT_1ffe05b0);
    DAT_1ffe0244 = cVar1 - 1;
  }
  else if (((DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') && DAT_1ffe0330 == 0) &&
          (DAT_1fffaae6 != '\x01')) {
    if (iVar2 == 0xe) {
      iVar2 = FUN_00046700(param_1);
      if (iVar2 != 0x1c) {
        if (iVar2 == 0x1d) {
          uVar3 = FUN_00046756(param_1);
          FUN_0004e5a6(uVar3,7,0);
          return;
        }
        if (iVar2 + -100 < 1) {
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
      if (DAT_1ffe0128 == 0) {
        DAT_1ffe02b0 = (uint)DAT_1ffe0128;
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
        FUN_0004ea90(uVar4,uVar3,0);
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
      FUN_0004ea90(uVar4,uVar3,0);
      return;
    }
  }
  return;
}

