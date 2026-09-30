/* Address: CODE:937e; name: FUN_CODE_937e; body bytes: 31 */

void FUN_CODE_937e(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  
  bVar1 = 0x30 - (((param_2 < 0xd5) << 7) >> 7);
  cVar2 = param_1 - bVar1;
  if ((param_1 < bVar1) << 7 < '\0') {
    bVar1 = 0xb - (((param_2 < 0xb8) << 7) >> 7);
    cVar2 = param_1 - bVar1;
    if (param_1 < bVar1) {
      param_1 = 0xb;
      param_2 = 0xb8;
    }
  }
  else {
    param_1 = 0x30;
    param_2 = 0xd4;
  }
  FUN_CODE_7af2(cVar2,param_1,param_2);
  return;
}

