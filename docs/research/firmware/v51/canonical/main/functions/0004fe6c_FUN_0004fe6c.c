/* Address: 0004fe6c; name: FUN_0004fe6c; body bytes: 12 */

void FUN_0004fe6c(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xc0007fff | (param_2 & 0x7fff) << 0xf;
  FUN_0004d3d8();
  return;
}

