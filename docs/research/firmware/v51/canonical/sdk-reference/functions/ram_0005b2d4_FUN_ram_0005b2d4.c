/* Address: ram:0005b2d4; name: FUN_ram_0005b2d4; body bytes: 80 */

undefined4 FUN_ram_0005b2d4(int param_1)

{
  gp = 0x20004000;
  if (*(int *)(param_1 + 0x110) != 0) {
    *(undefined1 *)(param_1 + 0x15) = 9;
    *(undefined1 *)(*(int *)(param_1 + 0x110) + 2) = 9;
    tmos_memcpy(*(int *)(param_1 + 0x110) + 3,param_1 + 0xf8,8);
    *(undefined1 *)(param_1 + 0x2a) = 0;
    *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x20;
    *(undefined1 *)(param_1 + 0x10) = 1;
    return 0;
  }
  return 1;
}

