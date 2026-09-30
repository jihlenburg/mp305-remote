/* Address: 0004fd02; name: FUN_0004fd02; body bytes: 12 */

void FUN_0004fd02(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xbfffffff | (param_2 & 1) << 0x1e;
  FUN_0004d3d8();
  return;
}

