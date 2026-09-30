/* Address: 000165a8; name: FUN_000165a8; body bytes: 158 */

void FUN_000165a8(void)

{
  int iVar1;
  
  FUN_00016988(&DAT_4004e400,8,0);
  if (DAT_1fff8f54 == 0) {
    iVar1 = FUN_00016932(&DAT_4004e400,0x40000);
    if (iVar1 != 1) {
      return;
    }
    iVar1 = FUN_00016932(&DAT_4004e400,0x1000);
    if (iVar1 == 0) {
      FUN_00016988(&DAT_4004e400,0x80,1);
      DAT_4004e424 = FUN_000160b0(DAT_1fff8f44);
      return;
    }
    FUN_00016988(&DAT_4004e400,0x1000,0);
  }
  else if (DAT_1fff8f39 == '\x01') {
    DAT_1fff8f54 = 0;
    DAT_1fff8f38 = 1;
    DAT_1fff8f48 = DAT_1fff8f50;
    DAT_1fff8f44 = DAT_1fff8f40;
    FUN_00016834(&DAT_4004e400,1);
    FUN_00016988(&DAT_4004e400,1);
    DAT_4004e400 = DAT_4004e400 | 0x80;
    return;
  }
  FUN_00016988(&DAT_4004e400,0x10,1);
  FUN_00016928(&DAT_4004e400);
  return;
}

