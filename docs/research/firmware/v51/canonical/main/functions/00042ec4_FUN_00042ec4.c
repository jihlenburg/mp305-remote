/* Address: 00042ec4; name: FUN_00042ec4; body bytes: 154 */

void FUN_00042ec4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_0004a5ea(param_1,0x70,param_3,param_4,param_4);
  uVar1 = FUN_0004059e();
  *(short *)(param_1 + 0x21) = (short)uVar1;
  *(char *)(param_1 + 0x23) = (char)((uint)uVar1 >> 0x10);
  uVar1 = FUN_0004059e();
  *(short *)(param_1 + 0x24) = (short)uVar1;
  *(char *)(param_1 + 0x26) = (char)((uint)uVar1 >> 0x10);
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x29) = (short)uVar1;
  *(char *)(param_1 + 0x2b) = (char)((uint)uVar1 >> 0x10);
  *(undefined1 *)(param_1 + 0x2d) = 0xff;
  *(undefined1 *)(param_1 + 0x2e) = 2;
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x3e) = (short)uVar1;
  *(char *)(param_1 + 0x40) = (char)((uint)uVar1 >> 0x10);
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x59) = (short)uVar1;
  *(char *)(param_1 + 0x5b) = (char)((uint)uVar1 >> 0x10);
  *(undefined **)(param_1 + 0x34) = &DAT_0006a6dc;
  *(undefined1 *)(param_1 + 0x20) = 0xff;
  *(undefined1 *)(param_1 + 0x3b) = 0xff;
  *(undefined1 *)(param_1 + 0x58) = 0xff;
  *(undefined1 *)(param_1 + 0x48) = 0xff;
  *(undefined1 *)(param_1 + 0x6c) = 0xff;
  *(byte *)(param_1 + 0x49) = (*(byte *)(param_1 + 0x49) & 0xe0) + 0xf;
  return;
}

