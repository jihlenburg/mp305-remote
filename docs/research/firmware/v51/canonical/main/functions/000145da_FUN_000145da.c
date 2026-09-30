/* Address: 000145da; name: FUN_000145da; body bytes: 16 */

void FUN_000145da(int param_1,uint param_2,int param_3)

{
  if (param_3 == 0) {
    param_2 = *(uint *)(param_1 + 0x10) | param_2;
  }
  else {
    param_2 = *(uint *)(param_1 + 0x10) & ~param_2;
  }
  *(uint *)(param_1 + 0x10) = param_2;
  return;
}

