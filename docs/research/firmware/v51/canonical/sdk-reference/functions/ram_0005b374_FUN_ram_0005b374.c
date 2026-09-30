/* Address: ram:0005b374; name: FUN_ram_0005b374; body bytes: 170 */

undefined4 FUN_ram_0005b374(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 0x18;
  iVar1 = *(int *)(param_1 + 0x110);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 2) = 0xf;
    *(undefined1 *)(iVar1 + 3) = *(undefined1 *)(param_1 + 0x72);
    *(char *)(iVar1 + 4) = (char)((ushort)*(undefined2 *)(param_1 + 0x72) >> 8);
    *(undefined1 *)(iVar1 + 5) = *(undefined1 *)(param_1 + 0x74);
    *(undefined1 *)(iVar1 + 6) = *(undefined1 *)(param_1 + 0x75);
    *(undefined1 *)(iVar1 + 7) = *(undefined1 *)(param_1 + 0x58);
    *(undefined1 *)(iVar1 + 8) = *(undefined1 *)(param_1 + 0x59);
    *(undefined1 *)(iVar1 + 9) = *(undefined1 *)(param_1 + 0x5a);
    *(char *)(iVar1 + 10) = (char)((ushort)*(undefined2 *)(param_1 + 0x5a) >> 8);
    *(char *)(iVar1 + 0xb) = (char)*(undefined2 *)(param_1 + 0x62);
    *(undefined1 *)(iVar1 + 0xc) = *(undefined1 *)(param_1 + 100);
    *(undefined1 *)(iVar1 + 0xd) = *(undefined1 *)(param_1 + 0x65);
    tmos_memcpy(iVar1 + 0xe,param_1 + 0x66,0xc);
    *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
    *(undefined1 *)(param_1 + 0x10) = 0x40;
    return 0;
  }
  return 1;
}

