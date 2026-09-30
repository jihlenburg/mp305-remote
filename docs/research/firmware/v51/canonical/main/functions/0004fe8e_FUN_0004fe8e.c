/* Address: 0004fe8e; name: FUN_0004fe8e; body bytes: 12 */

void FUN_0004fe8e(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xffff8000 | param_2 & 0x7fff;
  FUN_0004d3d8();
  return;
}

