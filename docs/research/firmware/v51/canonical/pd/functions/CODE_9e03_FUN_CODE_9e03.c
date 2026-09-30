/* Address: CODE:9e03; name: FUN_CODE_9e03; body bytes: 18 */

void FUN_CODE_9e03(void)

{
  char in_PSW;
  
  FUN_CODE_a60e(1);
  if (in_PSW < '\0') {
    FUN_CODE_a435();
    if (in_PSW < '\0') {
      return;
    }
  }
  return;
}

