/* Address: 0001de0e; name: FUN_0001de0e; body bytes: 16 */

void FUN_0001de0e(int param_1,uint param_2,int param_3)

{
  if (param_3 == 1) {
    param_2 = *(uint *)(param_1 + 0x10) | param_2;
  }
  else {
    param_2 = *(uint *)(param_1 + 0x10) & ~param_2;
  }
  *(uint *)(param_1 + 0x10) = param_2;
  return;
}

