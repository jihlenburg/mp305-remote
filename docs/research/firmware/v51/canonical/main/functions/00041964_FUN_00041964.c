/* Address: 00041964; name: FUN_00041964; body bytes: 22 */

void FUN_00041964(int param_1)

{
  FUN_0004a5ea(param_1,0x30);
  *(undefined1 *)(param_1 + 0x20) = 0xff;
  *(undefined4 *)(param_1 + 0x14) = 0x30;
  return;
}

