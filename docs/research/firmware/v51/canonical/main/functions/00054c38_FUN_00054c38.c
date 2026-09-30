/* Address: 00054c38; name: FUN_00054c38; body bytes: 70 */

void FUN_00054c38(uint param_1)

{
  undefined4 uVar1;
  
  if (DAT_1ffe04f4 == 0) {
    DAT_1ffe0278 = 0xffff;
  }
  else if (DAT_1ffe0278 != param_1) {
    uVar1 = FUN_0004b9de(DAT_1ffe0510,1);
    FUN_000499de(uVar1,"%01d.%03d",param_1 / 1000,param_1 % 1000);
    DAT_1ffe0278 = (ushort)param_1;
  }
  return;
}

