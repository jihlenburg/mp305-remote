/* Address: 00041b74; name: FUN_00041b74; body bytes: 68 */

void FUN_00041b74(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  FUN_0004a57a(param_1,0,0x6c,param_4,param_4);
  uVar1 = FUN_0004029c();
  *(short *)(param_1 + 0x48) = (short)uVar1;
  *(char *)(param_1 + 0x4a) = (char)((uint)uVar1 >> 0x10);
  *(undefined1 *)(param_1 + 0x4c) = 0xff;
  *(undefined4 *)(param_1 + 0x30) = 0x100;
  *(undefined4 *)(param_1 + 0x34) = 0x100;
  *(ushort *)(param_1 + 0x4c) = *(ushort *)(param_1 + 0x4c) | 0x1000;
  *(undefined4 *)(param_1 + 0x5c) = 0xe0000001;
  *(undefined4 *)(param_1 + 0x14) = 0x6c;
  return;
}

