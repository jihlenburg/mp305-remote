/* Address: ram:0005b324; name: FUN_ram_0005b324; body bytes: 80 */

undefined4 FUN_ram_0005b324(int param_1)

{
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0x15) = 9;
  if (*(int *)(param_1 + 0x110) != 0) {
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 2) = 0xe;
    tmos_memcpy(*(int *)(param_1 + 0x110) + 3,param_1 + 0xf8,8);
    *(byte *)(param_1 + 0x29) = *(byte *)(param_1 + 0x29) | 4;
    *(undefined1 *)(param_1 + 0x10) = 0x30;
    return 0;
  }
  return 1;
}

