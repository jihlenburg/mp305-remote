/* Address: 00055ab0; name: FUN_00055ab0; body bytes: 678 */

undefined1 * FUN_00055ab0(uint param_1)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  
  FUN_000499de(DAT_1ffe04cc,&DAT_00055d58,param_1);
  uVar7 = 0xff0000;
  uVar2 = param_1 * 0xf;
  uVar1 = (undefined1)param_1;
  if (DAT_1ffe034c == 0) {
    if (DAT_1ffe04f4 == 0) {
      if (DAT_1ffe05b8 != 0) {
        if (DAT_1ffe0250 == param_1) {
          return &DAT_1ffe023c;
        }
        puVar6 = &DAT_1ffe05d0;
        goto LAB_00055ba6;
      }
      if (DAT_1ffe0620 == 0) {
        DAT_1ffe0250 = 0xff;
        return &DAT_1ffe023c;
      }
      if (DAT_1ffe0250 == param_1) {
        return &DAT_1ffe023c;
      }
      DAT_1ffe0250 = uVar1;
      uVar3 = FUN_0004b9de(DAT_1ffe062c,0);
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_0004eae2(uVar3,uVar2 / 100);
      puVar6 = &DAT_1ffe0630;
      uVar3 = FUN_0004b9de(DAT_1ffe0630,0);
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_0004eae2(uVar3,uVar2 / 100);
      if (param_1 < 0xb) {
        if (DAT_1ffe0251 == '\0') {
          return &DAT_1ffe023c;
        }
        DAT_1ffe0251 = 0;
        uVar3 = FUN_0004037c(0xff0000);
        uVar5 = FUN_0004b9de(DAT_1ffe062c,0);
        uVar5 = FUN_0004b9de(uVar5,1);
        FUN_0004e8b2(uVar5,uVar3,0);
        uVar3 = FUN_0004037c(0xff0000);
        uVar5 = FUN_0004b9de(DAT_1ffe062c,0);
        uVar5 = FUN_0004b9de(uVar5,2);
        FUN_0004e8e6(uVar5,uVar3,0);
        uVar3 = FUN_0004037c(0xff0000);
        uVar5 = FUN_0004b9de(DAT_1ffe062c,0);
        uVar5 = FUN_0004b9de(uVar5,3);
        FUN_0004e8b2(uVar5,uVar3,0);
        goto LAB_00055b22;
      }
      if (DAT_1ffe0251 == '\x02') {
        return &DAT_1ffe023c;
      }
      DAT_1ffe0251 = 2;
      uVar7 = FUN_0004037c(0xffffff);
      uVar3 = FUN_0004b9de(DAT_1ffe062c,0);
      uVar3 = FUN_0004b9de(uVar3,1);
      FUN_0004e8b2(uVar3,uVar7,0);
      uVar7 = FUN_0004037c(0xffffff);
      uVar3 = FUN_0004b9de(DAT_1ffe062c,0);
      uVar3 = FUN_0004b9de(uVar3,2);
      FUN_0004e8e6(uVar3,uVar7,0);
      uVar7 = FUN_0004037c(0xffffff);
      uVar3 = FUN_0004b9de(DAT_1ffe062c,0);
      uVar3 = FUN_0004b9de(uVar3,3);
      FUN_0004e8b2(uVar3,uVar7,0);
    }
    else {
      if (DAT_1ffe0250 == param_1) {
        return &DAT_1ffe023c;
      }
      puVar6 = &DAT_1ffe04f8;
LAB_00055ba6:
      DAT_1ffe0250 = uVar1;
      uVar3 = FUN_0004b9de(*puVar6,0);
      uVar3 = FUN_0004b9de(uVar3,1);
      puVar4 = (undefined1 *)FUN_0004eae2(uVar3,uVar2 / 100);
      if (param_1 < 0xb) goto LAB_00055b04;
      if (DAT_1ffe0251 == '\x02') {
        return puVar4;
      }
      DAT_1ffe0251 = 2;
    }
    uVar7 = FUN_0004037c(0);
    uVar3 = FUN_0004b9de(*puVar6,0);
    uVar3 = FUN_0004b9de(uVar3,1);
    FUN_0004e8b2(uVar3,uVar7,0);
    uVar7 = FUN_0004037c(0);
    uVar3 = FUN_0004b9de(*puVar6,0);
    uVar3 = FUN_0004b9de(uVar3,2);
    FUN_0004e8e6(uVar3,uVar7,0);
    uVar7 = 0;
  }
  else {
    if (DAT_1ffe0250 == param_1) {
      return &DAT_1ffe023c;
    }
    puVar6 = &DAT_1ffe03b0;
    DAT_1ffe0250 = uVar1;
    uVar3 = FUN_0004b9de(DAT_1ffe03b0,0);
    uVar3 = FUN_0004b9de(uVar3,1);
    puVar4 = (undefined1 *)FUN_0004eae2(uVar3,uVar2 / 100);
    if (param_1 < 0xb) {
LAB_00055b04:
      if (DAT_1ffe0251 == '\0') {
        return puVar4;
      }
      DAT_1ffe0251 = 0;
    }
    else {
      if (DAT_1ffe0251 == '\x02') {
        return puVar4;
      }
      DAT_1ffe0251 = 2;
      uVar7 = 0xffffff;
    }
LAB_00055b22:
    uVar3 = FUN_0004037c(uVar7);
    uVar5 = FUN_0004b9de(*puVar6,0);
    uVar5 = FUN_0004b9de(uVar5,1);
    FUN_0004e8b2(uVar5,uVar3,0);
    uVar3 = FUN_0004037c(uVar7);
    uVar5 = FUN_0004b9de(*puVar6,0);
    uVar5 = FUN_0004b9de(uVar5,2);
    FUN_0004e8e6(uVar5,uVar3,0);
  }
  uVar7 = FUN_0004037c(uVar7);
  uVar3 = FUN_0004b9de(*puVar6,0);
  uVar3 = FUN_0004b9de(uVar3,3);
  puVar4 = (undefined1 *)FUN_0004e8b2(uVar3,uVar7,0);
  return puVar4;
}

