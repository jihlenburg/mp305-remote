/* Address: 00016988; name: FUN_00016988; body bytes: 16 */

void FUN_00016988(int param_1,uint param_2,int param_3)

{
  if (param_3 == 1) {
    param_2 = *(uint *)(param_1 + 4) | param_2;
  }
  else {
    param_2 = *(uint *)(param_1 + 4) & ~param_2;
  }
  *(uint *)(param_1 + 4) = param_2;
  return;
}

