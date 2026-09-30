/* Address: ram:0005b1c6; name: FUN_ram_0005b1c6; body bytes: 102 */

bool FUN_ram_0005b1c6(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 8;
  if (iVar1 != 0) {
    *(short *)(param_1 + 0x12e) = *(short *)(param_1 + 0x3e) + *(short *)(param_1 + 0x5e) + 10;
    *(undefined1 *)(iVar1 + 2) = 1;
    tmos_memcpy(iVar1 + 3,param_1 + 0x128,5);
    *(undefined1 *)(iVar1 + 8) = *(undefined1 *)(param_1 + 0x12e);
    *(char *)(iVar1 + 9) = (char)((ushort)*(undefined2 *)(param_1 + 0x12e) >> 8);
    *(undefined1 *)(param_1 + 0x10) = 0x15;
  }
  return iVar1 == 0;
}

