/* Address: 00010c24; name: FUN_00010c24; body bytes: 20 */

void FUN_00010c24(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0xc) = param_2;
  *(undefined4 *)(param_3 + 0x14) = 0x10c19;
  *(undefined4 *)(param_3 + 0x20) = 0x10f11;
  *(undefined4 *)(param_3 + 0x10) = 0;
  FUN_00010f24(param_1,param_3);
  return;
}

