/* Address: CODE:88c5; name: FUN_CODE_88c5; body bytes: 48 */

void FUN_CODE_88c5(char *param_1,byte param_2)

{
  byte bVar1;
  
  if (_1_1 != '\0') {
    bVar1 = DAT_INTMEM_b3;
    FUN_CODE_4444();
    if (*param_1 == '\x02') {
      FUN_CODE_109e();
      bVar1 = 0xf - (((bVar1 < 0xa1) << 7) >> 7);
      if (bVar1 <= param_2) {
        _1_1 = '\0';
        FUN_CODE_a638(param_2 - bVar1,1,2);
      }
    }
    if (_1_1 != '\x01') {
      FUN_CODE_87aa(0xf7,0xb7,0xff);
    }
  }
  return;
}

