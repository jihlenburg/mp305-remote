/* Address: CODE:a111; name: FUN_CODE_a111; body bytes: 14 */

void FUN_CODE_a111(void)

{
  char in_PSW;
  
  FUN_CODE_a607(0x22);
  if (in_PSW < '\0') {
    FUN_CODE_9200();
    return;
  }
  FUN_CODE_4000();
  return;
}

