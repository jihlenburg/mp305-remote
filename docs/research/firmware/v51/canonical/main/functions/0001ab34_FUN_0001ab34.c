/* Address: 0001ab34; name: FUN_0001ab34; body bytes: 750 */

void FUN_0001ab34(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  bVar1 = DAT_1fffaa54;
  DAT_1fffa9f4 = DAT_1fffa9f4 + (short)param_1;
  switch(DAT_1fffaa54) {
  case 0:
    FUN_00018e00(0);
    FUN_00019b10();
    DAT_1fffaa10 = 10;
    DAT_1fffa9fe = 0;
    DAT_1fffaa47 = 0;
    DAT_1fffaa44 = '\0';
    DAT_1fffaa45 = '\0';
    DAT_1fffaa46 = 0;
    DAT_1fffa9f6 = 0;
    DAT_1fffaa49 = 0;
    DAT_1fffaa22 = 100;
    DAT_1fffaa21 = 100;
    DAT_1fffaa54 = 2;
    goto LAB_0001adb8;
  case 1:
    if (0x10cc < DAT_1fffa9e4) {
      DAT_1fffaa54 = 3;
    }
    DAT_1fffa9fe = 0;
    FUN_00019b10();
    break;
  case 2:
  case 3:
    FUN_00019b10();
    if (DAT_1fffaa45 != '\0') {
      DAT_1fffaa45 = '\0';
      iVar2 = FUN_00018ee0(0);
      if (iVar2 == 0) {
        FUN_00018e00(0);
      }
      FUN_0001cb8c(5);
      DAT_1fffaa04 = 2000;
      DAT_1fffaa54 = 4;
      goto LAB_0001ad36;
    }
    if (DAT_1fffa9e4 < 0x10cd) {
      if (DAT_1fffaa54 != 3) break;
      DAT_1fffaa54 = 1;
    }
    else {
      DAT_1fffa9fe = 0;
      DAT_1fffaa54 = 3;
    }
    goto LAB_0001adb8;
  case 4:
    FUN_00018e00(1);
    FUN_00018f48(1,0x5dc,10000,16000);
    FUN_00018ca4(1,0);
    FUN_000658d4(100);
    FUN_00018ca4(1);
    FUN_0001df40();
    FUN_00019b10();
    iVar2 = FUN_00018ee0(1);
    if ((iVar2 == 0) || (iVar2 = FUN_0001dfb0(), iVar2 == 0)) {
      if ((DAT_1fffaa41 == '\0') || (4999 < DAT_1fffa9e8)) {
        if (1099 < DAT_1fffa9f4) {
          DAT_1fffaa1e = DAT_1fffaa1e | 0x80;
          goto LAB_0001acb6;
        }
      }
      else {
        DAT_1fffa9f4 = 0;
      }
      break;
    }
    DAT_1fffaa1e = DAT_1fffaa1e & 0xff7f;
    DAT_1fffaa54 = 6;
    DAT_1fffaa55 = '\0';
    goto LAB_0001ad36;
  case 5:
    FUN_0001b058(param_1);
    if (DAT_1fffaa55 == '\b') {
LAB_0001acb0:
      DAT_1fffaa54 = 6;
    }
    else {
      if (DAT_1fffaa55 != '\a') break;
LAB_0001acb6:
      DAT_1fffaa54 = 10;
    }
    goto LAB_0001ad36;
  case 6:
    if (DAT_1fffaa37 == '\x02') {
      DAT_1fffaa2e = '\0';
      DAT_1fffa94c = 0;
      DAT_1fffa948 = 0;
      DAT_1fffa950 = 0;
      DAT_1fffaa54 = 8;
      DAT_1fffa954 = 0;
    }
    else if ((DAT_1fffaa37 == '\0') || (DAT_1fffaa37 == '\x01')) {
      FUN_00019dbc();
      DAT_1fffaa54 = 7;
    }
    else if (DAT_1fffaa37 == '\x03') {
      FUN_00019dbc();
      DAT_1fffaa54 = 9;
    }
    goto LAB_0001ad36;
  case 7:
    if ((DAT_1fffaa37 != '\0') && (DAT_1fffaa37 != '\x01')) {
LAB_0001ad0e:
      DAT_1fffaa2e = '\0';
      goto LAB_0001acb0;
    }
    FUN_00019e68(param_1);
    break;
  case 8:
    if (DAT_1fffaa37 != '\x02') goto LAB_0001ad0e;
    FUN_0001b438(param_1);
    break;
  case 9:
    if (DAT_1fffaa37 != '\x03') goto LAB_0001ad0e;
    FUN_00013d00(param_1);
    if (DAT_1fffa950 != voltage_requested_raw) {
      DAT_1fffa950 = voltage_requested_raw;
    }
    if (DAT_1fffa954 != current_requested_raw) {
      DAT_1fffa954 = current_requested_raw;
    }
  }
  if (3 < DAT_1fffaa54) {
LAB_0001ad36:
    if (DAT_1fffaa23 == '\0') {
      uVar4 = (uint)DAT_1fffa9fc;
      DAT_1fffa9fc = (ushort)(uVar4 + param_1);
      if ((uVar4 + param_1 & 0xffff) < 0x2711) goto LAB_0001ad40;
    }
    else {
      DAT_1fffa9fc = 0;
LAB_0001ad40:
      if (DAT_1fffaa44 == '\0') goto LAB_0001adb8;
    }
    DAT_1fff9550 = DAT_1fff9550 | 8;
    DAT_1fffaa44 = '\0';
    DAT_1fffaa2e = '\0';
    DAT_1fffaa00 = 500;
    FUN_00019b10();
    FUN_00018c52(1);
    FUN_00019156(1);
    FUN_0001d958();
    if (DAT_1fffa9e4 < 0x10cd) {
      FUN_00019fc0();
      FUN_00018c52(0);
      FUN_00019156(0);
      DAT_1fffaa54 = 1;
    }
    else {
      DAT_1fffaa54 = 3;
    }
    FUN_0001cb8c(1);
  }
LAB_0001adb8:
  if (DAT_1fffaa51 != '\0') {
    FUN_00019b10();
    FUN_00018c52(1);
    FUN_00019156(1);
    DAT_1fffaa51 = '\0';
  }
  if ((DAT_1fffaa54 == 3) || (DAT_1fffaa54 == 1)) {
    if (0 < DAT_1fffaa00) {
      DAT_1fffaa00 = DAT_1fffaa00 - (short)param_1;
      goto LAB_0001adf8;
    }
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  FUN_00018a40(uVar3);
LAB_0001adf8:
  if (DAT_1fffaa54 != bVar1) {
    DAT_1fffa9f4 = 0;
    DAT_1fffa9fe = 0;
  }
  if (DAT_1fffaa1e != 0) {
    DAT_1fffaa2e = '\0';
  }
  if (DAT_1fffaa30 != DAT_1fffaa2e) {
    DAT_1fffaa30 = DAT_1fffaa2e;
    DAT_1ffe01e8 = 0;
    DAT_1fffa97c = 0;
  }
  return;
}

