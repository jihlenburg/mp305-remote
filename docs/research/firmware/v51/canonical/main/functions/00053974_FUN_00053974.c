/* Address: 00053974; name: FUN_00053974; body bytes: 650 */

void FUN_00053974(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  
  FUN_0004aa6e(DAT_1ffe03b8,1);
  FUN_0004aa6e(DAT_1ffe05b4,1);
  if (current_mode == '\0') {
    FUN_0004aa6e(DAT_1ffe0344,0x10);
    FUN_0004aa6e(DAT_1ffe03b4,1);
    FUN_0004aa4c(DAT_1ffe035c,0x65e35,7,DAT_1ffe0354);
    FUN_0004aa4c(DAT_1ffe036c,0x65e35,7,DAT_1ffe0364);
    FUN_0004aa4c(DAT_1ffe0354,0x65e35,7);
    FUN_0004aa4c(DAT_1ffe0364,0x65e35,7);
  }
  else if (current_mode == '\x03') {
    FUN_0004aa6e(DAT_1ffe0628,1);
  }
  if (DAT_1ffe0330 == DAT_1ffe0478) {
    if (DAT_1fffaadb == '\0') goto LAB_00053ba6;
    FUN_0004e00e(DAT_1ffe03bc,1);
    uVar5 = 0x10;
    uVar2 = DAT_1ffe0344;
  }
  else {
    if (DAT_1ffe0330 != DAT_1ffe06a0) {
      if ((DAT_1ffe0330 == DAT_1ffe0450) && (DAT_1ffe0242 != -1)) {
        uVar2 = FUN_0004037c(0xffffff);
        uVar5 = FUN_0004b9de(DAT_1ffe0458,(int)DAT_1ffe0242);
        FUN_0004e8b2(uVar5,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        FUN_0004e8b2(DAT_1ffe045c,uVar2,0);
        uVar2 = FUN_0004037c(0xffffff);
        FUN_0004e8b2(DAT_1ffe0460,uVar2,0);
        DAT_1ffe0242 = -1;
      }
      else if (DAT_1ffe0330 == DAT_1ffe03c8) {
        if (DAT_1fffaafb == '\x01') {
          uVar2 = DAT_1ffe0354;
          if (DAT_1fffaad7 != '\0') {
            uVar2 = DAT_1ffe0364;
          }
          FUN_0004e00e(uVar2,1);
          if (DAT_1fffaad7 == '\0') {
            puVar3 = &DAT_1ffe0358;
          }
          else {
            puVar3 = &DAT_1ffe0368;
          }
          FUN_0004aa6e(*puVar3,1);
          uVar2 = DAT_1ffe03c0;
        }
        else {
          uVar5 = FUN_0004037c(0x333333);
          uVar2 = DAT_1ffe0354;
          if (DAT_1fffaad7 != '\0') {
            uVar2 = DAT_1ffe0364;
          }
          FUN_0004e8b2(uVar2,uVar5,0);
          uVar2 = DAT_1ffe0354;
          if (DAT_1fffaad7 != '\0') {
            uVar2 = DAT_1ffe0364;
          }
          uVar2 = FUN_0004b9de(uVar2,0);
          FUN_0004e00e(uVar2,1);
          uVar2 = DAT_1ffe0354;
          if (DAT_1fffaad7 != '\0') {
            uVar2 = DAT_1ffe0364;
          }
          uVar2 = FUN_0004b9de(uVar2,1);
          FUN_0004e00e(uVar2,1);
          uVar2 = DAT_1ffe0354;
          if (DAT_1fffaad7 != '\0') {
            uVar2 = DAT_1ffe0364;
          }
          uVar2 = FUN_0004b9de(uVar2,2);
        }
        FUN_0004aa6e(uVar2,1);
        FUN_0004aa6e(DAT_1ffe03c0,1);
        FUN_000499de(DAT_1ffe03d4,&DAT_00053c68);
        if ((((DAT_1fffab03 != '\0') && (DAT_1fffaad6 != '\0')) && ((DAT_1fffaae4 & 1) != 0)) ||
           (((DAT_1fffab04 != '\0' && (DAT_1fffaad7 != '\0')) &&
            ((int)((uint)DAT_1fffaae4 << 0x1e) < 0)))) {
          uVar1 = FUN_00050710(DAT_1ffe03d8);
          FUN_0005833c(uVar1);
        }
        DAT_1fffaad6 = '\0';
        DAT_1fffaad7 = '\0';
        DAT_1fffaad9 = 0;
        DAT_1ffe024c = 0;
        FUN_0001ae8c(DAT_1fffa130);
      }
      else if ((DAT_1ffe0330 != DAT_1ffe0468) && (DAT_1ffe0330 == DAT_1ffe0550)) {
        DAT_1fffaad8 = 0;
        DAT_1ffe024b = 0;
      }
      goto LAB_00053ba6;
    }
    DAT_1fffab10 = 0;
    if (remote_granted != '\x01') goto LAB_00053ba6;
    uVar5 = 1;
    uVar2 = DAT_1ffe03c4;
  }
  FUN_0004e00e(uVar2,uVar5);
LAB_00053ba6:
  DAT_1ffe02b4 = 0;
  FUN_0001814c();
  iVar4 = FUN_0004fe9c();
  if (iVar4 != DAT_1ffe0590) {
    if (((DAT_1ffe04f4 == 0) || (iVar4 = FUN_0004cd1e(), iVar4 != 0)) ||
       ((iVar4 = FUN_0004cd1e(DAT_1ffe0540), iVar4 == 0 ||
        (iVar4 = FUN_0004cd1e(DAT_1ffe05a8), iVar4 == 0)))) {
      FUN_00018114(DAT_1ffe0348);
    }
    else {
      FUN_00017cf8();
    }
    FUN_0001cb8c(0xf);
  }
  DAT_1ffe0248 = 0;
  DAT_1ffe02bc = 0;
  DAT_1ffe0330 = 0;
  return;
}

