/* Address: CODE:7338; name: FUN_CODE_7338; body bytes: 90 */

void FUN_CODE_7338(byte param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  
  cVar4 = '\0';
  FUN_CODE_974d();
  bVar5 = FUN_CODE_4739();
  cVar2 = '\x06';
  do {
    bVar3 = param_1 >> 1;
    bVar1 = bVar5 >> 1;
    bVar5 = bVar1 | param_1 << 7;
    cVar2 = cVar2 + -1;
    param_1 = bVar3;
  } while (cVar2 != '\0');
  if ((bVar1 & 3) == 1) {
    FUN_CODE_a146();
    if (cVar4 == '\x01') {
      cVar2 = '\x01';
      FUN_CODE_974d();
      FUN_CODE_ae2a(0x4a8);
      FUN_CODE_ad03();
      FUN_CODE_acdd(0x10);
      if ((bVar3 == 0x80) && (cVar2 == -0x79)) {
        *(undefined1 *)(DAT_INTMEM_b3 + '=') = 1;
      }
      else {
        *(undefined1 *)(DAT_INTMEM_b3 + '=') = 0;
        FUN_CODE_8229();
      }
                    /* WARNING: Subroutine does not return */
      thunk_FUN_CODE_adf3(0x4a8);
    }
    return;
  }
  FUN_CODE_8229();
  return;
}

