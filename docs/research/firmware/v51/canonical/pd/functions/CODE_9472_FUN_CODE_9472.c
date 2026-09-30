/* Address: CODE:9472; name: FUN_CODE_9472; body bytes: 30 */

void FUN_CODE_9472(char param_1)

{
  byte bVar1;
  
  FUN_CODE_33d6();
  bVar1 = FUN_CODE_33e2(param_1 + '[');
  FUN_CODE_33d3(bVar1 & 0xcf);
  bVar1 = FUN_CODE_33e2(param_1 + '_');
  bVar1 = FUN_CODE_3439(bVar1 & 0xbb);
  FUN_CODE_a99c(bVar1 | 0x33);
  return;
}

