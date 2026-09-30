/* Address: 00015060; name: FUN_00015060; body bytes: 186 */

/* WARNING: Removing unreachable block (ram,0x0004e6ba) */
/* WARNING: Removing unreachable block (ram,0x0004e6c4) */

void FUN_00015060(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  
  iVar1 = FUN_00046688();
  if (DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') {
    if (iVar1 == 0xe) {
      iVar1 = FUN_00046700(param_1);
      if (iVar1 != 0x1c) {
        if (iVar1 == 0x1d) {
          uVar2 = FUN_00046756(param_1);
          FUN_0004e5a6(uVar2,7,0);
          return;
        }
        if (0 < iVar1 + -100) {
          FUN_000471d8(DAT_1ffe0144);
          return;
        }
        FUN_00047298();
        return;
      }
    }
    else {
      if (iVar1 == 0x10) {
        DAT_1ffe02b4 = 0;
        DAT_1ffe02b0 = 0;
        uVar2 = FUN_0004037c(0xff);
        uVar3 = FUN_00046756(param_1);
        FUN_0004e8e6(uVar3,uVar2,4);
        uVar2 = FUN_00046756(param_1);
        FUN_0004e9dc(uVar2,0,4);
        uVar2 = FUN_00046756(param_1);
        FUN_000637cc(uVar2,0,0x38,0,unaff_r4,unaff_r5,unaff_r6);
        uVar3 = FUN_00037610(uVar2,4);
        FUN_00050ef2(uVar3,0x38,0);
        FUN_0004dedc(uVar2,4,0x38);
        return;
      }
      if (iVar1 == 0x11) {
        uVar2 = FUN_0004037c(0);
        uVar3 = FUN_00046756(param_1);
        FUN_0004e8e6(uVar3,uVar2,0);
        return;
      }
    }
  }
  return;
}

