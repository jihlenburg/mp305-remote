/* Address: CODE:9b51; name: FUN_CODE_9b51; body bytes: 21 */

void FUN_CODE_9b51(byte *param_1)

{
  char cVar1;
  
  cVar1 = DAT_INTMEM_b3;
  FUN_CODE_345a(DAT_INTMEM_b3);
  *param_1 = *param_1 + 1;
  FUN_CODE_345c(cVar1 + -0x2c);
  *param_1 = *param_1 & 7;
  return;
}

