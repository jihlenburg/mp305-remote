/* Address: 0005651c; name: FUN_0005651c; body bytes: 192 */

void FUN_0005651c(int param_1)

{
  undefined4 uVar1;
  undefined4 unaff_r4;
  undefined4 unaff_r6;
  
  if (param_1 == 0) {
    unaff_r6 = FUN_0004037c(0xff5500);
    uVar1 = 0xffffff;
  }
  else {
    if (param_1 != 1) goto LAB_00056546;
    unaff_r6 = FUN_0004037c(0xff00);
    uVar1 = 0;
  }
  unaff_r4 = FUN_0004037c(uVar1);
LAB_00056546:
  uVar1 = FUN_0004b9de(DAT_1ffe0654,0);
  FUN_0004e8b2(uVar1,unaff_r6,0);
  FUN_0004ea90(DAT_1ffe0658,unaff_r4,0);
  uVar1 = FUN_0004bc8c(DAT_1ffe0658);
  uVar1 = FUN_0004b9de(uVar1,1);
  FUN_0004ea90(uVar1,unaff_r4,0);
  FUN_0004ea90(DAT_1ffe065c,unaff_r4,0);
  FUN_0004ea90(DAT_1ffe0660,unaff_r4,0);
  FUN_0004ea90(DAT_1ffe0668,unaff_r6,0);
  FUN_0004ea90(DAT_1ffe066c,unaff_r6,0);
  FUN_0004ea90(DAT_1ffe0670,unaff_r6,0);
  FUN_0004ea90(DAT_1ffe0674,unaff_r6,0);
  FUN_0004ea90(DAT_1ffe0678,unaff_r6,0);
  FUN_0004ea90(DAT_1ffe067c,unaff_r6,0);
  return;
}

