/* Address: 00055040; name: FUN_00055040; body bytes: 70 */

void FUN_00055040(uint param_1)

{
  undefined4 uVar1;
  
  if (DAT_1ffe034c == 0) {
    DAT_1ffe0276 = 0xffff;
  }
  else if (DAT_1ffe0276 != param_1) {
    uVar1 = FUN_0004b9de(DAT_1ffe0360,1);
    FUN_000499de(uVar1,"%01d.%03d",param_1 / 1000,param_1 % 1000);
    DAT_1ffe0276 = (ushort)param_1;
  }
  return;
}

