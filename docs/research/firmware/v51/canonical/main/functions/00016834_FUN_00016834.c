/* Address: 00016834; name: FUN_00016834; body bytes: 10 */

void FUN_00016834(uint *param_1,uint param_2)

{
  *param_1 = *param_1 & 0xfffffffe | param_2 & 1;
  return;
}

