/* Address: 0001de1e; name: FUN_0001de1e; body bytes: 14 */

void FUN_0001de1e(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 1 << ((param_2 & 0xf) << 4);
  return;
}

