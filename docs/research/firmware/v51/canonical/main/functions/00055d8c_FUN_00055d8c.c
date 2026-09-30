/* Address: 00055d8c; name: FUN_00055d8c; body bytes: 90 */

void FUN_00055d8c(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 < 0x28) {
    if ((DAT_1ffe028a != 0xffff) || (DAT_1ffe028c != 0xffff)) {
      DAT_1ffe028a = 0xffff;
      DAT_1ffe028c = 0xffff;
      FUN_000499de(DAT_1ffe04d8,&DAT_00055df0,&DAT_1ffe028a,param_4);
      return;
    }
  }
  else if ((DAT_1ffe028a != param_1) || (DAT_1ffe028c != param_2)) {
    DAT_1ffe028a = (ushort)param_1;
    DAT_1ffe028c = (ushort)param_2;
    FUN_000499de(DAT_1ffe04d8,"%02d.%01dV/%dW",param_1 / 10,param_1 % 10,param_2);
  }
  return;
}

