/* Address: 0001b634; name: cmd_e0_device_info; body bytes: 202 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 cmd_e0_device_info(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = _Reserved1;
  *param_2 = 0xe1;
  if (param_3 == 6) {
    param_2[1] = 1;
    param_2[2] = 6;
    param_2[3] = 0;
    param_2[4] = 0x33;
    param_2[5] = 0x4d;
    param_2[6] = 0x50;
    param_2[7] = 0x33;
    param_2[8] = 0x30;
    param_2[9] = 0x35;
    param_2[10] = 0x42;
    param_2[0xb] = 0;
    param_2[0xc] = 0;
    param_2[0xd] = 2;
    param_2[0xe] = 0;
    param_2[0xf] = 2;
    param_2[0x10] = 0;
    param_2[0x11] = *(undefined1 *)(param_1 + param_4 + -1);
    uVar2 = 0x12;
  }
  else {
    param_2[1] = 0x4d;
    param_2[2] = 0x50;
    param_2[3] = 0x33;
    param_2[4] = 0x30;
    param_2[5] = 0x35;
    param_2[6] = 0x42;
    param_2[7] = 0;
    param_2[8] = 0;
    param_2[9] = *(undefined1 *)(iVar1 + 0xc);
    param_2[10] = *(undefined1 *)(iVar1 + 0xd);
    param_2[0xb] = *(undefined1 *)(iVar1 + 0xe);
    param_2[0xc] = *(undefined1 *)(iVar1 + 0xf);
    param_2[0xd] = *(undefined1 *)(iVar1 + 0x10);
    param_2[0xe] = *(undefined1 *)(iVar1 + 0x11);
    param_2[0xf] = *(undefined1 *)(iVar1 + 0x12);
    param_2[0x10] = *(undefined1 *)(iVar1 + 0x13);
    param_2[0x11] = 1;
    param_2[0x12] = 6;
    param_2[0x13] = 0;
    param_2[0x14] = 0x33;
    param_2[0x15] = 0x4d;
    param_2[0x16] = 0x50;
    param_2[0x17] = 0x33;
    param_2[0x18] = 0x30;
    param_2[0x19] = 0x35;
    param_2[0x1a] = 0x42;
    param_2[0x1b] = 0;
    param_2[0x1c] = 0;
    param_2[0x1d] = 0;
    param_2[0x1e] = 0;
    uVar2 = 0x1f;
  }
  return uVar2;
}

