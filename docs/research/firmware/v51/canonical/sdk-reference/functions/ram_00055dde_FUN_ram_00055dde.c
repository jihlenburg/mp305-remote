/* Address: ram:00055dde; name: FUN_ram_00055dde; body bytes: 40 */

undefined4 FUN_ram_00055dde(int param_1)

{
  gp = 0x20004000;
  if ((((int)(uint)**(byte **)(param_1 + 0x114) >> 2 ^ (int)(uint)*(byte *)(param_1 + 0xc) >> 3) &
      1U) != 0) {
    *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) ^ 8;
    return 0;
  }
  return 1;
}

