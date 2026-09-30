/* Address: 0001e284; name: FUN_0001e284; body bytes: 1242 */

void FUN_0001e284(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  char cVar6;
  undefined1 uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  
  enter_critical();
  DAT_1fffab50 = DAT_1fffa9e4;
  DAT_1fffab54 = DAT_1fffa9e6;
  DAT_1fffab52 = DAT_1fffa9e8;
  DAT_1fffab56 = DAT_1fffa9ea;
  DAT_1fffab58 = DAT_1fffa9ec;
  DAT_1fffab5c = DAT_1fffa9ee;
  DAT_1fffab5a = DAT_1fffa9f0;
  DAT_1fffab5e = DAT_1fffa9f2;
  DAT_1fffabb4 = DAT_1fffa964;
  DAT_1fffabb8 = DAT_1fffa968;
  DAT_1fffab47 = FUN_00015f98();
  DAT_1fffab46 = FUN_00015494();
  DAT_1fffab45 = FUN_00015448();
  DAT_1fffaba4 = FUN_00015f74();
  DAT_1fffaba8 = FUN_00015f8c();
  DAT_1fffab80 = FUN_00015ba4();
  iVar8 = FUN_00015bb8();
  uVar9 = FUN_00015f80();
  uVar10 = FUN_00010388((int)((ulonglong)uVar9 * (ulonglong)DAT_1ffe0160),
                        uVar9 * DAT_1ffe0164 +
                        (int)((ulonglong)uVar9 * (ulonglong)DAT_1ffe0160 >> 0x20),100000,0);
  uVar7 = DAT_1fffaa41;
  DAT_1fffab05 = DAT_1fffaa26;
  DAT_1fffab07 = DAT_1fffaa28;
  DAT_1fffab08 = DAT_1fffaa29;
  DAT_1fffab06 = DAT_1fffaa23;
  DAT_1fffaae5 = DAT_1fffaa54;
  DAT_1fffab4a = DAT_1fffa9dc;
  DAT_1fffaad5 = DAT_1fffaa2e;
  DAT_1fffab0b = DAT_1fffa00d;
  DAT_1fffab6a = DAT_1fffaa1e;
  DAT_1fffac88 = DAT_1fffaa55;
  DAT_1fffac8c = DAT_1fffaa58;
  DAT_1fffaca8 = FUN_00015488();
  cVar6 = DAT_1fffaa40;
  cVar5 = DAT_1fffaa2f;
  iVar4 = DAT_1fffa98c;
  iVar3 = DAT_1fffa978;
  iVar2 = DAT_1fffa974;
  uVar11 = (uint)DAT_1fffaa08;
  uVar12 = FUN_00010388((int)((ulonglong)DAT_1fffa980 * (ulonglong)DAT_1ffe0160),
                        DAT_1fffa980 * DAT_1ffe0164 +
                        (int)((ulonglong)DAT_1fffa980 * (ulonglong)DAT_1ffe0160 >> 0x20),100000,0);
  uVar1 = current_requested_raw;
  uVar9 = voltage_requested_raw;
  DAT_1fffab98 = DAT_1fffa9b0;
  if (DAT_1fffaacf == '\0') {
    remote_granted = '\0';
LAB_0001e3e2:
    DAT_1fffaa4f = '\0';
  }
  else {
    if (DAT_1fffaacf != '\x02') goto LAB_0001e3e2;
    DAT_1fffaa4f = '\x01';
  }
  if (remote_granted == '\0') {
    DAT_1fffab0c = 0;
    if (DAT_1ffe0220 == '\x01') {
      remote_request = 0;
      FUN_0004aa6e(DAT_1ffe03c4,1);
    }
    DAT_1ffe0220 = 0;
  }
  else {
    DAT_1ffe0220 = 1;
  }
  if (((DAT_1fff9b9b != '\x02') || (cVar5 == '\0')) ||
     (DAT_1fffaaf7 = DAT_1fff9ba2, current_mode != '\x02')) {
    DAT_1fffaaf7 = 0xff;
  }
  exit_critical();
  if (device_state != '\0') {
    device_state = '\0';
    DAT_1fffabc4 = 0;
    FUN_0001814c();
    if (DAT_1ffe02a8 != 0) {
      FUN_000528ac();
      DAT_1ffe02a8 = 0;
    }
    if (DAT_1ffe02a4 != 0) {
      FUN_000528ac();
      DAT_1ffe02a4 = 0;
    }
    if (DAT_1ffe02a0 != 0) {
      FUN_000528ac();
      DAT_1ffe02a0 = 0;
    }
    if (DAT_1ffe02ac != 0) {
      FUN_000528ac();
      DAT_1ffe02ac = 0;
    }
    if (DAT_1ffe02c0 != 0) {
      FUN_000528ac();
      DAT_1ffe02c0 = 0;
    }
    if (DAT_1ffe0344 != 0) {
      FUN_00049a70();
      FUN_0004b288();
      FUN_0004b288(DAT_1ffe0344);
      FUN_0002e158(0);
      FUN_0004ef90(DAT_1ffe0344);
      FUN_0005689c();
      FUN_00021a50();
      FUN_0004fea8(DAT_1ffe0344);
    }
    if (DAT_1ffe04f4 == 0) {
      FUN_00018114(DAT_1ffe0348);
    }
    else {
      FUN_00017cf8();
    }
    DAT_1ffe0247 = 0;
  }
  if (((DAT_1fffaa42 == '\x01') && (DAT_1fffaa4f == '\0')) && (DAT_1fffaae5 == '\x03')) {
    uVar7 = 2;
  }
  if (((DAT_1fffaad5 != '\0') || (DAT_1fffaacf != '\0')) ||
     ((DAT_1fffaad0 != '\0' || (DAT_1fffa00c == '\x01')))) {
    DAT_1fffab88 = 0;
    DAT_1fffab8c = 0;
    DAT_1fffab90 = 0;
  }
  DAT_1fffaada = uVar7;
  if (DAT_1fffaad1 != cVar5) {
    DAT_1fffaad1 = cVar5;
    if (cVar5 == '\0') {
      DAT_1fffaace = '\0';
      DAT_1fffaad2 = '\0';
      if (current_mode == '\x01') {
        FUN_00058ba4(0);
      }
      else if ((current_mode == '\x02') && (DAT_1fff9b9b == '\x02')) {
        DAT_1fff9bbb = 1;
      }
    }
    else {
      DAT_1fffaace = '\x01';
    }
    FUN_00052a82(DAT_1ffe02a4);
  }
  if (DAT_1fffaad1 == '\0') {
LAB_0001e5ba:
    if (current_mode == '\0') {
      if (DAT_1fffab74 != uVar9) {
        FUN_00058268(uVar9 & 0xffff);
      }
      if (DAT_1fffab76 != uVar1) {
        FUN_000569b8(uVar1 & 0xffff);
      }
    }
    else if (((current_mode == '\x01') && (DAT_1fffaad2 != '\0')) && (DAT_1fffaad1 == '\0')) {
      DAT_1fffaad2 = '\0';
      FUN_00058ba4(1);
    }
  }
  else {
    if (cVar6 == '\x03') {
      if (DAT_1fffaace != '\x03') {
        DAT_1fffaace = '\x03';
        goto LAB_0001e5a0;
      }
      goto LAB_0001e5ba;
    }
    if (cVar6 == '\x02') {
      if (DAT_1fffaace != '\x02') {
        DAT_1fffaace = '\x02';
        goto LAB_0001e5a0;
      }
      goto LAB_0001e5ba;
    }
    if ((cVar6 != '\x01') || (DAT_1fffaace == '\x01')) goto LAB_0001e5ba;
    DAT_1fffaace = '\x01';
LAB_0001e5a0:
    if (current_mode != '\x02') goto LAB_0001e5ba;
    DAT_1fff9bbd = 1;
  }
  if ((((DAT_1fffaae0 != '\0') || (control_dirty != '\0')) ||
      ((settings_dirty != '\0' || (DAT_1fffab19 != '\0')))) ||
     ((DAT_1fffab17 == '\x01' && (iVar13 = FUN_0004cd1e(DAT_1ffe0770), iVar13 != 0)))) {
    control_dirty = '\0';
    FUN_00052a82(DAT_1ffe02a4);
  }
  if (((DAT_1ffe0620 != 0) && (iVar13 = FUN_0004cd1e(DAT_1ffe0654), iVar13 != 0)) &&
     (DAT_1fffaad5 != '\0')) {
    FUN_00052a82(DAT_1ffe02a4);
  }
  if (DAT_1fffaad1 == '\0') {
    if (DAT_1fffabb4 < 0x1f5) {
      DAT_1fffab78 = 0;
    }
    else {
      DAT_1fffab78 = (undefined2)((DAT_1fffabb4 + 5) / 10);
    }
    DAT_1fffab7a = 0;
    DAT_1fffab7c = 0;
  }
  else {
    uVar9 = (DAT_1fffabb4 + 5) / 10;
    DAT_1fffab78 = (undefined2)uVar9;
    iVar13 = DAT_1fffabb8;
    if (DAT_1fffabb8 < 0) {
      iVar13 = 0;
    }
    uVar14 = (iVar13 + 500) / 1000;
    if (((DAT_1fffaace == '\x02') && (uVar14 != uVar1)) &&
       ((uVar14 <= uVar1 + 1 && (uVar1 <= uVar14 + 1)))) {
      if ((uVar14 == uVar1 + 1) || (uVar14 + 1 == uVar1)) {
        DAT_1fffab7a = (short)uVar1;
      }
    }
    else {
      DAT_1fffab7a = (short)uVar14;
    }
    DAT_1fffab7c = (undefined2)((iVar2 + 5000U) / 10000);
    if ((DAT_1fffab7a == 0) || ((uVar9 & 0xffff) == 0)) {
      DAT_1fffab7c = 0;
    }
    if (DAT_1fffaae4 == '\0') {
      if (DAT_1fffab60 == 200) goto LAB_0001e75a;
      DAT_1fffab60 = 200;
    }
    else {
      if (DAT_1fffab60 == 100) goto LAB_0001e75a;
      DAT_1fffab60 = 100;
    }
    FUN_00052abe(DAT_1ffe02a4);
  }
LAB_0001e75a:
  DAT_1fffab82 = (short)((int)(iVar8 * (uint)DAT_1fffab80) / 10000);
  DAT_1fffab7e = (short)((iVar8 + 5U) / 10);
  DAT_1fffaba0 = (iVar3 + 0x32U) / 100;
  DAT_1fffab9c = uVar12 / 1000;
  DAT_1fffab4c = (short)((iVar4 + 500U) / 1000);
  DAT_1fffab4e = (short)((uVar11 + 0x32) / 100);
  DAT_1fffabac = uVar10 / 1000;
  return;
}

