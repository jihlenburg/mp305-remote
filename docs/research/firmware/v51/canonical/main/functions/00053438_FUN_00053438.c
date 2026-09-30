/* Address: 00053438; name: FUN_00053438; body bytes: 204 */

void FUN_00053438(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  
  if (DAT_1ffe0248 == '\0') {
    FUN_00046756(param_1);
    iVar1 = FUN_000527ec();
    FUN_0001814c();
    if ((iVar1 == DAT_1ffe04f0) && (current_mode == '\0')) {
      if (DAT_1ffe02a0 == 0) {
        DAT_1fffaadd = '\x01';
        DAT_1ffe026c = 0;
        DAT_1ffe0294 = 0;
        FUN_0001049c(&DAT_1fffacc0,800);
        uVar2 = FUN_0004b9de(DAT_1ffe0574,0);
        if (DAT_1fffaadd == '\0') {
          puVar4 = &DAT_0007e988;
        }
        else {
          puVar4 = &DAT_0007ce38;
        }
        FUN_00047d8e(uVar2,puVar4);
        uVar2 = FUN_0004675a(param_1);
        DAT_1ffe02a0 = FUN_0005285c(0x22769,100,uVar2);
      }
    }
    else {
      if (DAT_1ffe02a0 != 0) {
        FUN_000528ac();
        DAT_1ffe02a0 = 0;
        uVar2 = FUN_0004675a(param_1);
        FUN_0003f926(uVar2,DAT_1ffe0334);
        uVar2 = FUN_0004037c(0xffa600);
        uVar3 = FUN_0004675a(param_1);
        DAT_1ffe0334 = FUN_0003f4be(uVar3,uVar2,0);
        FUN_0004675a(param_1);
        thunk_FUN_0004d3d8();
      }
      DAT_1fffaadd = '\0';
    }
    if ((iVar1 == DAT_1ffe0348) && (DAT_1ffe0330 == 0)) {
      FUN_00018114();
      return;
    }
  }
  return;
}

