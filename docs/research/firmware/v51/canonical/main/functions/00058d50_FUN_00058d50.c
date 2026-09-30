/* Address: 00058d50; name: FUN_00058d50; body bytes: 718 */

void FUN_00058d50(undefined4 param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  undefined8 uVar6;
  
  if ((DAT_1fffab94 == 0) && (DAT_1fffaaf5 != '\0')) {
    DAT_1ffe02f4 = 0;
    DAT_1fffaaf5 = '\0';
  }
  DAT_1ffe02f4 = DAT_1ffe02f4 + 500;
  uVar6 = FUN_00010388((int)((ulonglong)DAT_1ffe02f4 * (ulonglong)DAT_1ffe0160),
                       DAT_1ffe02f4 * DAT_1ffe0164 +
                       (int)((ulonglong)DAT_1ffe02f4 * (ulonglong)DAT_1ffe0160 >> 0x20),100000,0);
  DAT_1fffab94 = FUN_00010388((int)uVar6,(int)((ulonglong)uVar6 >> 0x20),1000,0);
  uVar1 = FUN_00052960(param_1);
  uVar1 = FUN_0004b9de(uVar1,(int)DAT_1fffab48);
  FUN_0004b9de(uVar1,3);
  FUN_000491e8();
  uVar2 = FUN_000106d4();
  if (uVar2 <= DAT_1fffab94) {
    DAT_1fffab94 = 0;
    DAT_1fffaaf5 = '\x01';
    if ((int)DAT_1fffab48 < (int)((byte)(&DAT_1fffa3f4)[DAT_1fffa408] - 1)) {
      uVar1 = FUN_00052960(param_1);
      FUN_00026470(uVar1,(undefined1)DAT_1fffab48,2);
      DAT_1fffab48 = DAT_1fffab48 + 1;
      iVar3 = (int)DAT_1fffab48;
      if ((&DAT_1fffa41c)[iVar3 * 3] == 0) {
        if ((&DAT_1fffa414)[iVar3 * 3] != 0) {
          uVar2 = (&DAT_1fffa418)[iVar3 * 3];
          uVar5 = uVar2 >> 0x18;
          if ((uVar2 & 0xffffff) == 0) {
            if ((uVar5 <= (byte)(&DAT_1fffa3f4)[DAT_1fffa408]) && (uVar5 != 0)) goto LAB_00058f06;
          }
          else {
            DAT_1fffab84 = DAT_1fffab84 + -1;
            if ((-1 < DAT_1fffab84) &&
               ((uVar5 <= (byte)(&DAT_1fffa3f4)[DAT_1fffa408] && (uVar5 != 0)))) {
              uVar1 = FUN_00052960(param_1);
              uVar1 = FUN_0004b9de(uVar1,(int)DAT_1fffab48);
              uVar1 = FUN_0004b9de(uVar1,3);
              FUN_000499de(uVar1,&DAT_00059040,DAT_1fffab84);
LAB_00058f06:
              DAT_1fffab48 = (byte)(uVar2 >> 0x18) - 1;
              uVar1 = FUN_00052960(param_1);
              FUN_00026470(uVar1,(undefined1)DAT_1fffab48,1);
              set_voltage_raw((*(ushort *)(&DAT_1fffa414 + DAT_1fffab48 * 3) & 0x7fff) / 10);
              set_current_raw((&DAT_1fffa418)[DAT_1fffab48 * 3]);
              uVar2 = (uint)DAT_1fffab48;
              if (uVar2 == uVar5 - 1) {
                while( true ) {
                  FUN_00052960(param_1);
                  uVar5 = FUN_0004ba5c();
                  if (uVar5 <= uVar2) break;
                  uVar5 = (uint)DAT_1fffab48;
                  if (uVar5 != uVar2) {
                    uVar1 = FUN_00052960(param_1);
                  }
                  else {
                    uVar1 = FUN_00052960(param_1);
                  }
                  FUN_00026470(uVar1,uVar2 & 0xff,uVar5 == uVar2);
                  uVar2 = uVar2 + 1;
                }
              }
              FUN_0004b9de(DAT_1ffe04fc,(int)DAT_1fffab48);
              FUN_00047208();
              goto LAB_00058fda;
            }
          }
        }
        DAT_1fffaaec = '\x01';
        uVar1 = FUN_0004b9de(DAT_1ffe052c,0);
        if (DAT_1fffaaec == '\0') {
          puVar4 = &DAT_0007ce38;
        }
        else {
          puVar4 = &DAT_0007e988;
        }
        FUN_00047d8e(uVar1,puVar4);
        uVar1 = FUN_00052960(param_1);
        FUN_00026470(uVar1,(undefined1)DAT_1fffab48,2);
        FUN_00052a74(DAT_1ffe02c0);
        DAT_1fffab48 = 0;
        FUN_0001aebc(0);
        goto LAB_00059010;
      }
      uVar1 = FUN_00052960(param_1);
      FUN_00026470(uVar1,(undefined1)DAT_1fffab48,1);
      set_voltage_raw((*(ushort *)(&DAT_1fffa414 + DAT_1fffab48 * 3) & 0x7fff) / 10);
      set_current_raw((&DAT_1fffa418)[DAT_1fffab48 * 3]);
    }
    else {
      DAT_1fffaaec = '\x01';
      uVar1 = FUN_0004b9de(DAT_1ffe052c,0);
      if (DAT_1fffaaec == '\0') {
        puVar4 = &DAT_0007ce38;
      }
      else {
        puVar4 = &DAT_0007e988;
      }
      FUN_00047d8e(uVar1,puVar4);
      uVar1 = FUN_00052960(param_1);
      FUN_00026470(uVar1,(undefined1)DAT_1fffab48,2);
      FUN_00052a74(DAT_1ffe02c0);
      DAT_1fffab48 = 0;
      FUN_0001aebc(0);
    }
  }
LAB_00058fda:
  iVar3 = (int)DAT_1fffab48;
  if (iVar3 < 1) {
    iVar3 = 0;
  }
  else if (iVar3 < (int)((byte)(&DAT_1fffa3f4)[DAT_1fffa408] - 1)) {
    iVar3 = iVar3 + 1;
  }
  FUN_0004b9de(DAT_1ffe04fc,iVar3);
  FUN_00047208();
LAB_00059010:
  FUN_000499de(DAT_1ffe0514,&DAT_00059050,DAT_1fffab94,param_1);
  return;
}

