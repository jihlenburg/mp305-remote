/* Address: 00040ce4; name: FUN_00040ce4; body bytes: 46 */

void FUN_00040ce4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_0004a57a(param_1,0,0x40,param_4,param_4);
  *(undefined4 *)(param_1 + 0x20) = 1;
  *(undefined1 *)(param_1 + 0x3c) = 0xff;
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x1c) = (short)uVar1;
  *(char *)(param_1 + 0x1e) = (char)((uint)uVar1 >> 0x10);
  *(undefined4 *)(param_1 + 0x14) = 0x40;
  return;
}

