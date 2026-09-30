/* Address: 00012272; name: FUN_00012272; body bytes: 10 */

void FUN_00012272(uint *param_1,uint param_2)

{
  *param_1 = *param_1 & 0xfffffe00 | param_2 & 0x1ff;
  return;
}

