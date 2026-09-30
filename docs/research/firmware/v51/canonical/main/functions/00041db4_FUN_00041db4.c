/* Address: 00041db4; name: FUN_00041db4; body bytes: 104 */

void FUN_00041db4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_0004a57a(param_1,0,0x54,param_4,param_4);
  *(undefined1 *)(param_1 + 0x48) = 0xff;
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x2c) = (short)uVar1;
  *(char *)(param_1 + 0x2e) = (char)((uint)uVar1 >> 0x10);
  *(undefined **)(param_1 + 0x20) = &DAT_0006a6dc;
  *(undefined4 *)(param_1 + 0x24) = 0xffff;
  *(undefined4 *)(param_1 + 0x28) = 0xffff;
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x2f) = (short)uVar1;
  *(char *)(param_1 + 0x31) = (char)((uint)uVar1 >> 0x10);
  uVar1 = FUN_0004f04c(5);
  *(short *)(param_1 + 0x32) = (short)uVar1;
  *(char *)(param_1 + 0x34) = (char)((uint)uVar1 >> 0x10);
  *(undefined1 *)(param_1 + 0x49) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0x54;
  return;
}

