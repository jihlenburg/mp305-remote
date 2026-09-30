/* Address: 00057ea0; name: FUN_00057ea0; body bytes: 704 */

void FUN_00057ea0(uint param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (((DAT_1fffaadb == DAT_1ffe025c) && (DAT_1ffe025d == param_1)) && (param_2 == 0)) {
    return;
  }
  DAT_1ffe025c = DAT_1fffaadb;
  DAT_1ffe025d = (byte)param_1;
  if (DAT_1fffaadb == '\0' && param_1 == 0) {
    FUN_0004e0e6(DAT_1ffe0480,0x80);
    FUN_0004e0e6(DAT_1ffe0484,0x80);
    FUN_0004e0e6(DAT_1ffe0488,0x80);
    FUN_0004e0e6(DAT_1ffe048c,0x80);
    FUN_0004e0e6(DAT_1ffe0498,0x80);
    FUN_0004e0e6(DAT_1ffe04a4,0x80);
    FUN_0004e0e6(DAT_1ffe04b0,0x80);
    uVar2 = 0xffffff;
    uVar1 = 0;
    if (current_mode != '\0') {
      uVar1 = uVar2;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e8b2(DAT_1ffe048c,uVar1,0);
    uVar1 = uVar2;
    if (current_mode != '\0') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e960(DAT_1ffe0490,uVar1,0);
    uVar1 = uVar2;
    if (current_mode != '\0') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004ea90(DAT_1ffe0494,uVar1,0);
    uVar1 = uVar2;
    if (current_mode == '\x01') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e8b2(DAT_1ffe0498,uVar1,0);
    uVar1 = uVar2;
    if (current_mode != '\x01') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e960(DAT_1ffe049c,uVar1,0);
    uVar1 = uVar2;
    if (current_mode != '\x01') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004ea90(DAT_1ffe04a0,uVar1,0);
    uVar1 = uVar2;
    if (current_mode == '\x02') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e8b2(DAT_1ffe04a4,uVar1,0);
    uVar1 = uVar2;
    if (current_mode != '\x02') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e960(DAT_1ffe04a8,uVar1,0);
    uVar1 = uVar2;
    if (current_mode != '\x02') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004ea90(DAT_1ffe04ac,uVar1,0);
    uVar1 = uVar2;
    if (current_mode == '\x03') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e8b2(DAT_1ffe04b0,uVar1,0);
    uVar1 = uVar2;
    if (current_mode != '\x03') {
      uVar1 = 0;
    }
    uVar1 = FUN_0004037c(uVar1);
    FUN_0004e960(DAT_1ffe04b4,uVar1,0);
    if (current_mode != '\x03') {
      uVar2 = 0;
    }
  }
  else {
    FUN_0004aaf6();
    FUN_0004aaf6(DAT_1ffe0484,0x80);
    FUN_0004aaf6(DAT_1ffe0488,0x80);
    FUN_0004aaf6(DAT_1ffe048c,0x80);
    FUN_0004aaf6(DAT_1ffe0498,0x80);
    FUN_0004aaf6(DAT_1ffe04a4,0x80);
    FUN_0004aaf6(DAT_1ffe04b0,0x80);
    uVar1 = FUN_0004037c(0x999999);
    FUN_0004e960(DAT_1ffe0490,uVar1,0);
    uVar1 = FUN_0004037c(0x999999);
    FUN_0004ea90(DAT_1ffe0494,uVar1,0);
    uVar1 = FUN_0004037c(0x999999);
    FUN_0004e960(DAT_1ffe049c,uVar1,0);
    uVar1 = FUN_0004037c(0x999999);
    FUN_0004ea90(DAT_1ffe04a0,uVar1,0);
    uVar1 = FUN_0004037c(0x999999);
    FUN_0004e960(DAT_1ffe04a8,uVar1,0);
    uVar1 = FUN_0004037c(0x999999);
    FUN_0004ea90(DAT_1ffe04ac,uVar1,0);
    uVar1 = FUN_0004037c(0x999999);
    FUN_0004e960(DAT_1ffe04b4,uVar1,0);
    uVar2 = 0x999999;
  }
  uVar1 = FUN_0004037c(uVar2);
  FUN_0004ea90(DAT_1ffe04b8,uVar1,0);
  return;
}

