/* Address: 00014e38; name: FUN_00014e38; body bytes: 266 */

/* WARNING: Removing unreachable block (ram,0x0004e6ba) */
/* WARNING: Removing unreachable block (ram,0x0004e6c4) */

void FUN_00014e38(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  undefined4 unaff_r7;
  undefined4 unaff_r8;
  undefined4 unaff_lr;
  
  iVar1 = FUN_0004675a();
  iVar2 = FUN_00046688(param_1);
  if (DAT_1ffe0245 == '\0' && DAT_1ffe0246 == '\0') {
    if (iVar2 == 0xe) {
      iVar2 = FUN_00046700(param_1);
      if (iVar2 != 0x1c) {
        if (iVar2 == 0x1d) {
          if (((((iVar1 == DAT_1ffe048c) || (iVar1 == DAT_1ffe0498)) || (iVar1 == DAT_1ffe04a4)) ||
              (iVar1 == DAT_1ffe04b0)) && ((DAT_1fffaadb == '\0' && (DAT_1fffaace == '\0')))) {
            FUN_0004e5a6(iVar1,7,0);
            return;
          }
        }
        else if (iVar2 + -100 < 1) {
          if (iVar1 != DAT_1ffe048c) {
            FUN_00047298(DAT_1ffe0144);
            return;
          }
        }
        else if (iVar1 != DAT_1ffe04b0) {
          FUN_000471d8(DAT_1ffe0144);
          return;
        }
      }
    }
    else {
      if (iVar2 == 0x10) {
        DAT_1ffe02b0 = 0;
        DAT_1ffe02b4 = 0;
        DAT_1ffe02bc = iVar1;
        FUN_0004e91a(iVar1,6,4);
        uVar3 = FUN_0004037c(0xffa600);
        FUN_0004e8e6(iVar1,uVar3,4);
        FUN_0004e9dc(iVar1,0,4);
        FUN_000637cc(iVar1,0,0x38,0,unaff_r4,unaff_r5,unaff_r6,unaff_r7,unaff_r8,unaff_lr);
        uVar3 = FUN_00037610(iVar1,4);
        FUN_00050ef2(uVar3,0x38,0);
        FUN_0004dedc(iVar1,4,0x38);
        return;
      }
      if ((iVar2 == 0x11) &&
         (((iVar1 == DAT_1ffe048c || (iVar1 == DAT_1ffe0498)) ||
          ((iVar1 == DAT_1ffe04a4 || (iVar1 == DAT_1ffe04b0)))))) {
        FUN_0004e91a(iVar1,0);
        return;
      }
    }
  }
  return;
}

