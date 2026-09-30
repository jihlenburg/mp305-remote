/* Address: 00016ad2; name: FUN_00016ad2; body bytes: 10 */

void FUN_00016ad2(uint *param_1,uint param_2)

{
  *param_1 = *param_1 & 0xffff7fff | (param_2 & 1) << 0xf;
  return;
}

