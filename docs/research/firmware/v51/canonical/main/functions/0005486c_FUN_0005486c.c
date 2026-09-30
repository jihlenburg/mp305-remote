/* Address: 0005486c; name: FUN_0005486c; body bytes: 170 */

void FUN_0005486c(uint param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  uVar1 = (uint)DAT_1ffe0252;
  if (DAT_1ffe034c == 0) {
    if (DAT_1ffe04f4 != 0) {
      if (uVar1 == param_1) {
        return;
      }
      puVar2 = &DAT_1ffe04f8;
      goto LAB_000548a0;
    }
    if (DAT_1ffe05b8 != 0) {
      if (uVar1 == param_1) {
        return;
      }
      puVar2 = &DAT_1ffe05d0;
      goto LAB_000548a0;
    }
    if (DAT_1ffe0620 == 0) {
      DAT_1ffe0252 = 0xff;
      return;
    }
    if (uVar1 == param_1) {
      return;
    }
    if (param_1 == 1) {
      uVar3 = FUN_0004b9de(DAT_1ffe062c,0);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004e00e(uVar3,1);
      uVar3 = DAT_1ffe0630;
      goto LAB_000548fe;
    }
    uVar3 = FUN_0004b9de(DAT_1ffe062c,0);
    uVar3 = FUN_0004b9de(uVar3,0);
    FUN_0004aa6e(uVar3,1);
    uVar3 = DAT_1ffe0630;
  }
  else {
    if (uVar1 == param_1) {
      return;
    }
    puVar2 = &DAT_1ffe03b0;
LAB_000548a0:
    uVar3 = *puVar2;
    if (param_1 == 1) {
LAB_000548fe:
      uVar3 = FUN_0004b9de(uVar3,0);
      uVar3 = FUN_0004b9de(uVar3,0);
      FUN_0004e00e(uVar3,1);
      goto LAB_00054882;
    }
  }
  uVar3 = FUN_0004b9de(uVar3,0);
  uVar3 = FUN_0004b9de(uVar3,0);
  FUN_0004aa6e(uVar3,1);
LAB_00054882:
  DAT_1ffe0252 = (char)param_1;
  return;
}

