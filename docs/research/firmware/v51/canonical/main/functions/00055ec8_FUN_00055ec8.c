/* Address: 00055ec8; name: FUN_00055ec8; body bytes: 62 */

void FUN_00055ec8(uint param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0258 = 0xff;
  }
  else if (DAT_1ffe0258 != param_1) {
    DAT_1ffe0258 = (byte)param_1;
    uVar1 = FUN_0004b9de(DAT_1ffe03ac,1);
    if (param_1 == 1) {
      puVar2 = &DAT_0007b7f8;
    }
    else if (param_1 == 2) {
      puVar2 = &DAT_0007f314;
    }
    else {
      puVar2 = (undefined *)0x0;
    }
    FUN_00047d8e(uVar1,puVar2);
    return;
  }
  return;
}

