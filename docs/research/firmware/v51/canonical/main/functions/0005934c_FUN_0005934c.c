/* Address: 0005934c; name: FUN_0005934c; body bytes: 696 */

void FUN_0005934c(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  if ((DAT_1ffe04f4 == 0) || ((byte)(&DAT_1fffa3f4)[DAT_1fffa408] == 0)) {
    return;
  }
  if ((int)DAT_1fffab48 < (int)((byte)(&DAT_1fffa3f4)[DAT_1fffa408] - 1)) {
    DAT_1fffab48 = DAT_1fffab48 + 1;
  }
  else {
    FUN_0001aebc(0);
    if (DAT_1ffe02c0 != 0) {
      FUN_00052a74();
    }
  }
  iVar1 = (int)DAT_1fffab48;
  if ((&DAT_1fffa41c)[iVar1 * 3] == 0) {
    if ((&DAT_1fffa414)[iVar1 * 3] == 0) {
      FUN_0001aebc(0);
      if (DAT_1ffe02c0 != 0) {
        FUN_00052a74();
      }
    }
    else {
      uVar2 = (&DAT_1fffa418)[iVar1 * 3];
      uVar5 = uVar2 >> 0x18;
      if ((uVar2 & 0xffffff) == 0) {
        if ((uVar5 <= (byte)(&DAT_1fffa3f4)[DAT_1fffa408]) && (uVar5 != 0)) goto LAB_00059440;
LAB_00059490:
        DAT_1fffab48 = 0;
        FUN_0001aebc(0);
        if (DAT_1ffe02c0 != 0) {
          FUN_00052a74();
        }
      }
      else {
        DAT_1fffab84 = DAT_1fffab84 + -1;
        if ((DAT_1fffab84 < 0) || (((byte)(&DAT_1fffa3f4)[DAT_1fffa408] < uVar5 || (uVar5 == 0))))
        goto LAB_00059490;
        uVar3 = FUN_0004675a(param_1);
        uVar3 = FUN_0004b9de(uVar3,(int)DAT_1fffab48);
        uVar3 = FUN_0004b9de(uVar3,3);
        FUN_000499de(uVar3,&DAT_0005961c,DAT_1fffab84);
LAB_00059440:
        DAT_1fffab48 = (byte)(uVar2 >> 0x18) - 1;
        set_voltage_raw((*(ushort *)(&DAT_1fffa414 + (uVar5 - 1) * 3) & 0x7fff) / 10);
        set_current_raw((&DAT_1fffa418)[DAT_1fffab48 * 3]);
        FUN_0004b9de(DAT_1ffe04fc,(int)DAT_1fffab48);
        FUN_00047208();
      }
      uVar2 = (uint)DAT_1fffab48;
      if (uVar2 == uVar5 - 1) {
        for (; (int)uVar2 < (int)(uint)(byte)(&DAT_1fffa3f4)[DAT_1fffa408]; uVar2 = uVar2 + 1) {
          if (((int)DAT_1fffab48 == uVar2) && (DAT_1fffaad1 != '\0')) {
            uVar3 = FUN_0004675a(param_1);
            uVar4 = 1;
          }
          else {
            uVar3 = FUN_0004675a(param_1);
            uVar4 = 0;
          }
          FUN_00026470(uVar3,uVar2 & 0xff,uVar4);
        }
      }
    }
  }
  else {
    set_voltage_raw((*(ushort *)(&DAT_1fffa414 + iVar1 * 3) & 0x7fff) / 10);
    set_current_raw((&DAT_1fffa418)[DAT_1fffab48 * 3]);
  }
  if (DAT_1fffab48 < 1) {
    if (DAT_1fffaad1 != '\0') goto LAB_0005956a;
    uVar3 = FUN_0004037c(0x261f00);
    uVar4 = FUN_0004b9de(DAT_1ffe04fc,(int)DAT_1fffab48);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar3 = FUN_0004037c(0xffa600);
  }
  else {
    if (DAT_1fffaad1 != '\0') {
      uVar3 = FUN_0004675a(param_1);
      FUN_00026470(uVar3,(char)DAT_1fffab48 + -1,2);
LAB_0005956a:
      uVar3 = FUN_0004675a(param_1);
      FUN_00026470(uVar3,(char)DAT_1fffab48,1);
      goto LAB_000595b0;
    }
    uVar3 = FUN_0004037c(0x333333);
    uVar4 = FUN_0004b9de(DAT_1ffe04fc,DAT_1fffab48 + -1);
    FUN_0004e8b2(uVar4,uVar3,0);
    local_30 = FUN_0004037c(0);
    uVar3 = FUN_0004b9de(DAT_1ffe04fc,DAT_1fffab48 + -1);
    FUN_0004e8e6(uVar3,local_30,0);
    uVar3 = FUN_0004037c(0x261f00);
    uVar4 = FUN_0004b9de(DAT_1ffe04fc,(int)DAT_1fffab48);
    FUN_0004e8b2(uVar4,uVar3,0);
    uVar3 = FUN_0004037c(0xffa600);
  }
  uVar4 = FUN_0004b9de(DAT_1ffe04fc,(int)DAT_1fffab48);
  FUN_0004e8e6(uVar4,uVar3,0);
LAB_000595b0:
  iVar1 = (int)DAT_1fffab48;
  if (iVar1 < 1) {
    iVar1 = 0;
  }
  else if (iVar1 < (int)((byte)(&DAT_1fffa3f4)[DAT_1fffa408] - 1)) {
    iVar1 = iVar1 + 1;
  }
  FUN_0004b9de(DAT_1ffe04fc,iVar1);
  FUN_00047208();
  DAT_1fffab94 = 0;
  DAT_1fffaaf5 = 1;
  FUN_000499de(DAT_1ffe0514,&DAT_0005962c,0);
  FUN_00052a98(DAT_1ffe02c0);
  FUN_0001cb8c(0xf,local_30,uStack_2c,param_1);
  return;
}

