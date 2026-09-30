/* Address: CODE:9526; name: FUN_CODE_9526; body bytes: 30 */

void FUN_CODE_9526(void)

{
  char in_PSW;
  
  FUN_CODE_a6a8(10);
  if (in_PSW < '\0') {
    return;
  }
  FUN_CODE_a6a8(0xb);
  if (in_PSW < '\0') {
    FUN_CODE_90d1(0x38,0);
    return;
  }
  return;
}

