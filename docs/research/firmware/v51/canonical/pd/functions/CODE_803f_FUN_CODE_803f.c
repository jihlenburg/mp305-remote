/* Address: CODE:803f; name: FUN_CODE_803f; body bytes: 63 */

void FUN_CODE_803f(char *param_1,char param_2)

{
  byte bVar1;
  
  FUN_CODE_342b(0xb9);
  if (*param_1 == '\0') {
    FUN_CODE_3442(param_2 + '<');
    if (*param_1 == '\x01') {
      FUN_CODE_343f();
      *param_1 = '\0';
      FUN_CODE_957e(0xe,3);
      return;
    }
    bVar1 = FUN_CODE_33e9();
    if ((bVar1 >> 3 & 1) != 0) {
      FUN_CODE_3472();
      bVar1 = FUN_CODE_33df();
      bVar1 = FUN_CODE_3439(bVar1 & 0xf7);
      FUN_CODE_a99c(bVar1 | 0x10);
      FUN_CODE_957e(0x10,3);
    }
    FUN_CODE_9cdd();
  }
  return;
}

