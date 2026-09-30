/* Address: 00066214; name: FUN_00066214; body bytes: 620 */

void FUN_00066214(undefined4 param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  iVar3 = FUN_00046688();
  uVar4 = FUN_0004675a(param_1);
  if (iVar3 == 7) {
    FUN_0001814c();
    iVar3 = FUN_000104f0(uVar4,&DAT_00066494);
    if (iVar3 == 0) {
      uVar5 = FUN_0004b9de(DAT_1ffe071c,0);
      FUN_0004eae2(uVar5,100);
      uVar5 = FUN_0004b9de(DAT_1ffe071c,0);
      uVar5 = FUN_0004b9de(uVar5,0);
      FUN_00049974(uVar5,"Web Link");
      FUN_00047d8e(DAT_1ffe0724,&DAT_00082b14);
      uVar5 = 0x30;
    }
    else {
      uVar5 = FUN_0004b9de(DAT_1ffe071c,0);
      FUN_0004eae2(uVar5,0x82);
      uVar5 = FUN_00015a5c(0x31);
      uVar6 = FUN_0004b9de(DAT_1ffe071c,0);
      uVar6 = FUN_0004b9de(uVar6,0);
      FUN_000499de(uVar6,&DAT_000664a4,uVar5);
      FUN_00047d8e(DAT_1ffe0724,&DAT_00082b14);
      uVar5 = 0x32;
    }
    uVar5 = FUN_00015a5c(uVar5);
    FUN_000499de(DAT_1ffe0728,&DAT_000664a4,uVar5);
    FUN_0004eb0e(DAT_1ffe071c,0);
    cVar2 = FUN_0004ba5c(DAT_1ffe05b0);
    iVar3 = FUN_000104f0(uVar4,&DAT_00066494);
    if (iVar3 == 0) {
      cVar1 = '\x05';
    }
    else {
      cVar1 = '\x04';
    }
    DAT_1ffe0244 = cVar2 - cVar1;
    FUN_0001cb8c(0xf);
    return;
  }
  if (iVar3 == 1) {
    cVar2 = FUN_0004ba5c(DAT_1ffe05b0);
    iVar3 = FUN_000104f0(uVar4,&DAT_00066494);
    if (iVar3 == 0) {
      cVar1 = '\x05';
    }
    else {
      cVar1 = '\x04';
    }
    DAT_1ffe0244 = cVar2 - cVar1;
  }
  else if (((DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') && DAT_1ffe0330 == 0) &&
          (DAT_1fffaae6 != '\x01')) {
    if (iVar3 == 0xe) {
      iVar3 = FUN_00046700(param_1);
      if (iVar3 != 0x1c) {
        if (iVar3 == 0x1d) {
          FUN_0001814c();
          uVar4 = FUN_00046756(param_1);
          FUN_0004e5a6(uVar4,7,0);
          return;
        }
        if (iVar3 + -100 < 1) {
          if (DAT_1ffe0244 != 0) {
            DAT_1ffe0244 = DAT_1ffe0244 - 1;
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else {
          iVar3 = FUN_0004ba5c(DAT_1ffe05b0);
          if ((uint)DAT_1ffe0244 < iVar3 - 1U) {
            DAT_1ffe0244 = DAT_1ffe0244 + 1;
            FUN_000471d8(DAT_1ffe0144);
            return;
          }
        }
      }
    }
    else if (iVar3 == 0x10) {
      if (DAT_1ffe0128 == 0) {
        DAT_1ffe02b0 = (uint)DAT_1ffe0128;
        uVar4 = FUN_0004037c(0xffa600);
        uVar5 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar5,uVar4,4);
        uVar4 = FUN_0004037c(0);
        uVar5 = FUN_00046756(param_1);
        FUN_0004ea90(uVar5,uVar4,4);
        uVar4 = FUN_0004037c(0);
        uVar5 = FUN_00046756(param_1);
        uVar5 = FUN_0004b9de(uVar5,0);
        FUN_0004e960(uVar5,uVar4,0);
        uVar4 = FUN_0004037c(0);
        uVar5 = FUN_00046756(param_1);
        uVar5 = FUN_0004b9de(uVar5,1);
        FUN_0004e960(uVar5,uVar4,0);
        uVar4 = FUN_00046756(param_1);
        FUN_0004e4b2(uVar4,0);
        return;
      }
    }
    else if (iVar3 == 0x11) {
      uVar4 = FUN_0004037c(0);
      uVar5 = FUN_00046756(param_1);
      FUN_0004e8b2(uVar5,uVar4,0);
      uVar4 = FUN_0004037c(0xffffff);
      uVar5 = FUN_00046756(param_1);
      FUN_0004ea90(uVar5,uVar4,0);
      uVar4 = FUN_0004037c(0xffffff);
      uVar5 = FUN_00046756(param_1);
      uVar5 = FUN_0004b9de(uVar5,0);
      FUN_0004e960(uVar5,uVar4,0);
      uVar4 = FUN_0004037c(0x999999);
      uVar5 = FUN_00046756(param_1);
      uVar5 = FUN_0004b9de(uVar5,1);
      FUN_0004e960(uVar5,uVar4,0);
      return;
    }
  }
  return;
}

