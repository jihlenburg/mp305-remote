/* Address: 000550a0; name: FUN_000550a0; body bytes: 52 */

void FUN_000550a0(uint param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0257 = 0xff;
  }
  else if (DAT_1ffe0257 != param_1) {
    DAT_1ffe0257 = (byte)param_1;
    uVar1 = FUN_0004b9de(DAT_1ffe03ac,0);
    if (param_1 == 0) {
      puVar2 = &LAB_0007be3c;
    }
    else {
      puVar2 = &DAT_0007bef8;
    }
    FUN_00047d8e(uVar1,puVar2);
    return;
  }
  return;
}

