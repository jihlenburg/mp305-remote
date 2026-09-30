/* Address: 000145a8; name: FUN_000145a8; body bytes: 16 */

undefined4 FUN_000145a8(int param_1,int param_2,int param_3)

{
  param_1 = param_1 + param_2 * 0x40;
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xffff | param_3 << 0x10;
  return 0;
}

