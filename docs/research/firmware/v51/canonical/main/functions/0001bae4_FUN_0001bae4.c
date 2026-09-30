/* Address: 0001bae4; name: FUN_0001bae4; body bytes: 292 */

void FUN_0001bae4(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0001814c();
  if (DAT_1ffe034c == 0) {
    if (DAT_1ffe04f4 == 0) {
      if (DAT_1ffe05b8 == 0) {
        if (DAT_1ffe0620 == 0) goto LAB_0001bb5e;
        uVar3 = FUN_00037604();
        FUN_0004eb0e(DAT_1ffe0680,uVar3);
        uVar3 = FUN_00037604();
        puVar1 = &DAT_1ffe0654;
      }
      else {
        uVar3 = FUN_00037604();
        FUN_0004eb0e(DAT_1ffe0614,uVar3);
        uVar3 = FUN_00037604();
        puVar1 = &DAT_1ffe0608;
      }
    }
    else {
      FUN_000527f0(DAT_1ffe0504,DAT_1ffe0508,0);
      uVar3 = FUN_00037604();
      puVar1 = &DAT_1ffe0540;
    }
    FUN_0004eb0e(*puVar1,uVar3);
  }
  else {
    FUN_000527f0(DAT_1ffe0344,DAT_1ffe0348,0);
  }
LAB_0001bb5e:
  iVar2 = FUN_0004cd1e(DAT_1ffe0700);
  if (iVar2 == 0) {
    FUN_0004e5a6(DAT_1ffe0704,7,0);
  }
  iVar2 = FUN_0004cd1e(DAT_1ffe072c);
  if (iVar2 == 0) {
    FUN_0004e5a6(DAT_1ffe0730,7,0);
  }
  iVar2 = FUN_0004cd1e(DAT_1ffe071c);
  if (iVar2 == 0) {
    FUN_0004e5a6(DAT_1ffe0720,7,0);
  }
  uVar3 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe04c8,uVar3);
  uVar3 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe05a8,uVar3);
  uVar3 = FUN_00037604();
  FUN_0004eb0e(DAT_1ffe0774,uVar3);
  uVar3 = FUN_0004b9de(DAT_1ffe0590,1);
  FUN_0004eae2(uVar3,0);
  uVar3 = FUN_0004b9de(DAT_1ffe0774,1);
  FUN_0004eae2(uVar3,0);
  DAT_1fffaad3 = 0;
  FUN_0001ba58();
  if (DAT_1ffe04f4 != 0) {
    FUN_00017cf8();
    return;
  }
  FUN_00018114(DAT_1ffe0348);
  return;
}

