/* Address: 00059638; name: FUN_00059638; body bytes: 344 */

void FUN_00059638(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  ushort uVar3;
  int iVar4;
  
  if ((DAT_1ffe04f4 != 0) && (uVar3 = (ushort)(byte)(&DAT_1fffa3f4)[DAT_1fffa408], uVar3 != 0)) {
    if (0 < DAT_1fffab48) {
      DAT_1fffab48 = DAT_1fffab48 + -1;
    }
    if ((DAT_1fffab48 < (short)uVar3) && (1 < uVar3)) {
      if (DAT_1fffaad1 == '\0') {
        uVar1 = FUN_0004037c(0x261f00);
        uVar2 = FUN_0004b9de(DAT_1ffe04fc,(int)DAT_1fffab48);
        FUN_0004e8b2(uVar2,uVar1,0);
        uVar1 = FUN_0004037c(0xffa600);
        uVar2 = FUN_0004b9de(DAT_1ffe04fc,(int)DAT_1fffab48);
        FUN_0004e8e6(uVar2,uVar1,0);
        uVar1 = FUN_0004037c(0x333333);
        uVar2 = FUN_0004b9de(DAT_1ffe04fc,DAT_1fffab48 + 1);
        FUN_0004e8b2(uVar2,uVar1,0);
        uVar1 = FUN_0004037c(0);
        uVar2 = FUN_0004b9de(DAT_1ffe04fc,DAT_1fffab48 + 1);
        FUN_0004e8e6(uVar2,uVar1,0);
      }
      else {
        uVar1 = FUN_0004675a(param_1);
        FUN_00026470(uVar1,(char)DAT_1fffab48,1);
        uVar1 = FUN_0004675a(param_1);
        FUN_00026470(uVar1,(char)DAT_1fffab48 + '\x01',0);
      }
    }
    iVar4 = (int)DAT_1fffab48;
    if (iVar4 < 1) {
      iVar4 = 0;
    }
    else if (iVar4 < (int)((byte)(&DAT_1fffa3f4)[DAT_1fffa408] - 1)) {
      iVar4 = iVar4 + -1;
    }
    FUN_0004b9de(DAT_1ffe04fc,iVar4);
    FUN_00047208();
    DAT_1fffab94 = 0;
    DAT_1fffaaf5 = 1;
    FUN_000499de(DAT_1ffe0514,&DAT_000597ac);
    set_voltage_raw(((uint)*(ushort *)(&DAT_1fffa414 + DAT_1fffab48 * 3) << 0x11) / 0x140000);
    set_current_raw((&DAT_1fffa418)[DAT_1fffab48 * 3]);
    FUN_00052a98(DAT_1ffe02c0);
    FUN_0001cb8c(0xf);
    return;
  }
  return;
}

