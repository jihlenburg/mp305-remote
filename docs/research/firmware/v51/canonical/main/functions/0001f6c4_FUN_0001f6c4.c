/* Address: 0001f6c4; name: FUN_0001f6c4; body bytes: 126 */

void FUN_0001f6c4(undefined4 param_1)

{
  ushort uVar1;
  
  switch(DAT_1fffaaac) {
  case 1:
    DAT_1fffaa5d = 1;
    DAT_1fffaa5e = 1;
    FUN_0001f5c0(param_1);
    break;
  case 2:
    DAT_1fffaa5d = 1;
    DAT_1fffaa5e = 1;
    FUN_0001f880(param_1);
    break;
  case 3:
    DAT_1fffaa5d = 1;
    DAT_1fffaa5e = 1;
    FUN_0001f7c4(param_1);
    break;
  case 4:
    DAT_1fffaa5d = 1;
    DAT_1fffaa5e = 1;
    FUN_0001f808(param_1);
    break;
  case 6:
    DAT_1fffaa5d = 0;
    DAT_1fffaa5e = 0;
    FUN_0001fb4c(param_1);
  }
  FUN_0001fb28(param_1);
  FUN_0001fa78(param_1);
  uVar1 = DAT_1fffaa78;
  if (DAT_1fffaa6e <= DAT_1fffaa78) {
    uVar1 = DAT_1fffaa6e;
  }
  FUN_0001f734(uVar1);
  DAT_1fffaa86 = FUN_0001f760();
  return;
}

