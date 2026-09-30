/* Address: 00018728; name: FUN_00018728; body bytes: 396 */

void FUN_00018728(void)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  bool bVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined4 local_28;
  undefined4 local_24;
  
  if (2 < DAT_1fffaae5 - 7) {
    if ((DAT_1fffaae5 == 3) && (iVar1 = FUN_0001868c(), iVar1 != 0)) {
      DAT_1fffab90 = 0;
    }
    return;
  }
  iVar1 = FUN_0001868c();
  if (iVar1 == 0) {
    return;
  }
  if ((remote_granted != '\0') && (iVar1 = get_output_enabled(), iVar1 == 0)) {
    if ((DAT_1ffe0330 == 0) && (iVar1 = FUN_0004cd1e(DAT_1ffe06a0), iVar1 != 0)) {
      DAT_1fffab0d = 1;
    }
    goto LAB_00018890;
  }
  if (current_mode == '\0') {
    iVar1 = get_output_enabled();
    if (iVar1 != 0) goto LAB_00018786;
    if (DAT_1ffe0330 == DAT_1ffe03c8) {
      local_28 = 0;
      local_24 = 0;
      uVar2 = FUN_000491e8(DAT_1ffe03d4);
      FUN_0001050c(&local_28,uVar2);
      uVar6 = FUN_00020160(&local_28);
      fVar3 = (float)FUN_00010b48((int)uVar6,(int)((ulonglong)uVar6 >> 0x20));
      if ((DAT_1fffab03 == '\0') && (DAT_1fffaad6 != '\0')) {
        iVar1 = FUN_000104f0(&local_28,&DAT_000188cc);
        if (iVar1 == 0) {
          uVar5 = (uint)DAT_1fffab74;
        }
        else {
          uVar5 = VectorFloatToUnsigned(fVar3 * 1000.0 + 5.0,3);
          uVar5 = uVar5 / 10;
        }
LAB_000187ee:
        set_voltage_raw(uVar5);
      }
      else {
        if (DAT_1fffab04 == '\0') {
          if (DAT_1fffaad7 == '\0') goto LAB_00018844;
          iVar1 = FUN_000104f0(&local_28,&DAT_000188cc);
          if (iVar1 == 0) {
            uVar5 = (uint)DAT_1fffab76;
          }
          else {
            uVar5 = VectorFloatToUnsigned(fVar3 * 10000.0 + 5.0,3);
            uVar5 = uVar5 / 10;
          }
        }
        else {
          if (DAT_1fffaad7 == '\0') {
LAB_00018844:
            uVar5 = FUN_00050710(DAT_1ffe03d8);
            goto LAB_000187ee;
          }
          uVar5 = FUN_00050710(DAT_1ffe03d8);
        }
        set_current_raw(uVar5);
      }
    }
    uVar2 = 1;
  }
  else {
    if (current_mode == '\x02') {
      iVar1 = get_output_enabled();
      bVar4 = iVar1 == 0;
    }
    else {
      if (current_mode == '\x03') {
        if (DAT_1fffab47 == '\0') {
          if (DAT_1fffab6a == 0) {
            FUN_0001d6fc(DAT_1fffac90,DAT_1fffac94);
            DAT_1fffab44 = 0;
          }
        }
        else {
          FUN_0001d858();
        }
        goto LAB_00018890;
      }
      if (current_mode != '\x01') goto LAB_00018890;
      iVar1 = get_output_enabled();
      bVar4 = false;
      if (iVar1 == 0) {
        DAT_1fffaad2 = 1;
        goto LAB_00018890;
      }
    }
    if (bVar4) {
      DAT_1fffaaf6 = 1;
      DAT_1fffaaf8 = 0;
      DAT_1fff9bb9 = 1;
      goto LAB_00018890;
    }
LAB_00018786:
    uVar2 = 0;
  }
  FUN_0001aebc(uVar2);
LAB_00018890:
  FUN_0001cb8c(1);
  return;
}

