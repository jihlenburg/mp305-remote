/* Address: CODE:9301; name: FUN_CODE_9301; body bytes: 32 */

void FUN_CODE_9301(void)

{
  char in_PSW;
  
  FUN_CODE_a6a1(99);
  if (in_PSW < '\0') {
    return;
  }
  FUN_CODE_a607(0x23);
  if (in_PSW < '\0') {
    return;
  }
  FUN_CODE_a6a8(0xf);
  return;
}

