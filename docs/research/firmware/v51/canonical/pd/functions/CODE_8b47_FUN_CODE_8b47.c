/* Address: CODE:8b47; name: FUN_CODE_8b47; body bytes: 43 */

void FUN_CODE_8b47(char param_1,char param_2,char param_3)

{
  undefined1 uVar1;
  
  FUN_CODE_ae2a(0x54e);
  FUN_CODE_54ca();
  if ((param_2 != '\0' || param_1 != '\0') || param_3 != '\0') {
    uVar1 = BANK0_R5;
    FUN_CODE_54ca();
    FUN_CODE_ae33();
    FUN_CODE_a99c(uVar1);
    FUN_CODE_54ca();
    FUN_CODE_aafc(0,1,1);
    return;
  }
  FUN_CODE_9137(BANK0_R5);
  return;
}

