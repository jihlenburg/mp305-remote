/* Address: CODE:4153; name: FUN_CODE_4153; body bytes: 68 */

void FUN_CODE_4153(byte param_1)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  
  FUN_CODE_974d(0);
  FUN_CODE_ae2a(0x4b4);
  cVar3 = '\x01';
  FUN_CODE_974d();
  FUN_CODE_ae2a(0x4b7);
  bVar4 = FUN_CODE_4736(0x4b4);
  cVar2 = '\x06';
  do {
    bVar1 = bVar4 >> 1;
    bVar4 = bVar1 | param_1 << 7;
    cVar2 = cVar2 + -1;
    param_1 = param_1 >> 1;
  } while (cVar2 != '\0');
  if ((bVar1 & 3) != 1) {
    FUN_CODE_8229();
    return;
  }
  FUN_CODE_a146();
  if (cVar3 != '\x01') {
    return;
  }
                    /* WARNING: Subroutine does not return */
  thunk_FUN_CODE_adf3(0x4b7);
}

