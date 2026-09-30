/* Address: 000166dc; name: FUN_000166dc; body bytes: 16 */

void FUN_000166dc(uint *param_1,uint param_2)

{
  *param_1 = *param_1 & 0xfffffbff | param_2 & 0x400;
  return;
}

