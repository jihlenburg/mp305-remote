/* Address: ram:00055e06; name: FUN_ram_00055e06; body bytes: 40 */

undefined4 FUN_ram_00055e06(int param_1)

{
  gp = 0x20004000;
  if ((((int)(uint)**(byte **)(param_1 + 0x114) >> 3 ^ (int)(uint)*(byte *)(param_1 + 0xc) >> 2) &
      1U) == 0) {
    *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) ^ 4;
    return 0;
  }
  return 1;
}

