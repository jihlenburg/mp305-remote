/* Address: 00057740; name: FUN_00057740; body bytes: 112 */

void FUN_00057740(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (DAT_1ffe05b8 == 0) {
    DAT_1ffe0261 = 0xff;
  }
  else if (DAT_1ffe0261 != param_1) {
    if (param_1 == 0) {
      uVar1 = FUN_0004037c(0x808080);
      uVar2 = FUN_0004b9de(DAT_1ffe0600,0);
      FUN_0004e960(uVar2,uVar1,0);
      FUN_0004aaf6(DAT_1ffe0600,0x80);
    }
    else {
      uVar1 = FUN_0004037c(0);
      uVar2 = FUN_0004b9de(DAT_1ffe0600,0);
      FUN_0004e960(uVar2,uVar1,0);
      FUN_0004e0e6(DAT_1ffe0600,0x80);
      FUN_000577c0();
    }
    DAT_1ffe0261 = (byte)param_1;
  }
  return;
}

