/* Address: 0005e7c0; name: FUN_0005e7c0; body bytes: 786 */

void FUN_0005e7c0(undefined4 param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  
  iVar2 = FUN_00046688(param_1);
  if (iVar2 == 7) {
    uVar9 = 0;
    while( true ) {
      FUN_00046756(param_1);
      FUN_0004bc8c();
      uVar5 = FUN_0004ba5c();
      if (uVar5 <= uVar9) break;
      FUN_00046756(param_1);
      uVar3 = FUN_0004bc8c();
      iVar2 = FUN_0004b9de(uVar3,uVar9);
      iVar6 = FUN_00046756(param_1);
      if (iVar2 == iVar6) {
        uVar3 = FUN_0004037c(0xffa600);
        uVar4 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar4,uVar3,0);
        uVar1 = (undefined1)uVar9;
        if (DAT_1ffe0330 != DAT_1ffe06c8) {
          FUN_00046756(param_1);
          iVar2 = FUN_0004bc8c();
          if (iVar2 != DAT_1ffe06cc) {
            if (DAT_1ffe0330 != DAT_1ffe06d0) {
              FUN_00046756(param_1);
              iVar2 = FUN_0004bc8c();
              if (iVar2 != DAT_1ffe06d4) {
                if (DAT_1ffe0330 != DAT_1ffe06d8) {
                  FUN_00046756(param_1);
                  iVar2 = FUN_0004bc8c();
                  if (iVar2 != DAT_1ffe06dc) {
                    if (DAT_1ffe0330 != DAT_1ffe06e0) {
                      FUN_00046756(param_1);
                      iVar2 = FUN_0004bc8c();
                      if (iVar2 != DAT_1ffe06e4) {
                        if (DAT_1ffe0330 != DAT_1ffe06e8) {
                          FUN_00046756(param_1);
                          iVar2 = FUN_0004bc8c();
                          if (iVar2 != DAT_1ffe06ec) {
                            if (DAT_1ffe0330 != DAT_1ffe06f8) {
                              FUN_00046756(param_1);
                              iVar2 = FUN_0004bc8c();
                              if (iVar2 != DAT_1ffe06fc) {
                                if (DAT_1ffe0330 != DAT_1ffe06f0) {
                                  FUN_00046756(param_1);
                                  iVar2 = FUN_0004bc8c();
                                  if (iVar2 != DAT_1ffe06f4) goto LAB_0005e9aa;
                                }
                                DAT_1fffab64 = (&DAT_1ffe0798)[uVar9];
                                DAT_1ffe0867 = uVar1;
                                FUN_00056d0c();
                                goto LAB_0005e9aa;
                              }
                            }
                            DAT_1fffab70 = (&DAT_1ffe07a4)[uVar9];
                            DAT_1ffe0866 = uVar1;
                            FUN_000581ac();
                            goto LAB_0005e9aa;
                          }
                        }
                        DAT_1fffab62 = (&DAT_1ffe0784)[uVar9];
                        DAT_1ffe0865 = uVar1;
                        FUN_00056fc0();
                        goto LAB_0005e9aa;
                      }
                    }
                    DAT_1fffaaff = (&DAT_1ffe077d)[uVar9];
                    DAT_1ffe0864 = uVar1;
                    FUN_00057288();
                    goto LAB_0005e9aa;
                  }
                }
                DAT_1fffaafa = uVar1;
                FUN_00057204();
                goto LAB_0005e9aa;
              }
            }
            DAT_1fffaafe = uVar1;
            FUN_0005836c();
            goto LAB_0005e9aa;
          }
        }
        DAT_1fffaaf9 = (&DAT_1ffe0778)[uVar9];
        DAT_1ffe032c = uVar1;
        FUN_000564b4();
      }
      else {
        uVar3 = FUN_0004037c(0xffffff);
        FUN_00046756(param_1);
        uVar4 = FUN_0004bc8c();
        uVar4 = FUN_0004b9de(uVar4,uVar9);
        FUN_0004e8b2(uVar4,uVar3,0);
      }
LAB_0005e9aa:
      uVar9 = uVar9 + 1 & 0xff;
    }
    FUN_0004e5a6(DAT_1ffe0330,7,0);
    DAT_1ffe02b4 = 0;
    if (DAT_1fffaacf != '\0') {
      DAT_1fff9550 = DAT_1fff9550 | 0x1000;
    }
  }
  else if (DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') {
    if (iVar2 == 0xe) {
      iVar2 = FUN_00046700(param_1);
      if (iVar2 != 0x1c) {
        if (iVar2 == 0x1d) {
          uVar3 = FUN_00046756(param_1);
          FUN_0004e5a6(uVar3,7,0,param_1);
          return;
        }
        uVar9 = 0;
        while( true ) {
          FUN_00046756(param_1);
          FUN_0004bc8c();
          uVar8 = FUN_0004ba5c();
          uVar5 = 0;
          if (uVar8 <= uVar9) break;
          FUN_00046756(param_1);
          uVar3 = FUN_0004bc8c();
          iVar6 = FUN_0004b9de(uVar3,uVar9);
          iVar7 = FUN_00046756(param_1);
          uVar5 = uVar9;
          if (iVar6 == iVar7) break;
          uVar9 = uVar9 + 1 & 0xff;
        }
        if (iVar2 + -100 < 1) {
          if (uVar5 != 0) {
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else {
          FUN_00046756(param_1);
          FUN_0004bc8c();
          iVar2 = FUN_0004ba5c();
          if (uVar5 < iVar2 - 1U) {
            FUN_000471d8(DAT_1ffe0144);
            return;
          }
        }
      }
    }
    else {
      if (iVar2 == 0x10) {
        DAT_1ffe02b4 = 0;
        uVar3 = FUN_0004037c(0xffa600);
        uVar4 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar4,uVar3,2);
        uVar3 = FUN_0004037c(0xffa600);
        uVar4 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar4,uVar3,4);
        uVar3 = FUN_0004037c(0);
        uVar4 = FUN_00046756(param_1);
        FUN_0004ea90(uVar4,uVar3,4);
        uVar3 = FUN_00046756(param_1);
        FUN_0004e4b2(uVar3,0);
        return;
      }
      if (iVar2 == 0x11) {
        uVar3 = FUN_0004037c(0xffffff);
        uVar4 = FUN_00046756(param_1);
        FUN_0004e8b2(uVar4,uVar3,0,param_1);
        return;
      }
    }
  }
  return;
}

