/* Address: 00042462; name: FUN_00042462; body bytes: 48 */

void FUN_00042462(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_0004a57a(param_1,0,0x40,param_4,param_4);
  *(undefined4 *)(param_1 + 0x30) = 1;
  *(undefined1 *)(param_1 + 0x3c) = 0xff;
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x2c) = (short)uVar1;
  *(char *)(param_1 + 0x2e) = (char)((uint)uVar1 >> 0x10);
  *(undefined4 *)(param_1 + 0x14) = 0x40;
  return;
}

