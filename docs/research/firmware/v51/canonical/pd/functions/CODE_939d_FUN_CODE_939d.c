/* Address: CODE:939d; name: FUN_CODE_939d; body bytes: 31 */

void FUN_CODE_939d(char *param_1)

{
  char cVar1;
  
  cVar1 = DAT_INTMEM_b3;
  FUN_CODE_3401(DAT_INTMEM_b3 + 'V',DAT_INTMEM_b3);
  if (*param_1 == BANK0_R7) {
    FUN_CODE_3469(cVar1 + -0x28);
    *param_1 = '\x01';
    return;
  }
  FUN_CODE_3464();
  *param_1 = '\0';
  return;
}

