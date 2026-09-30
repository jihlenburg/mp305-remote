/* Address: CODE:5cfa; name: FUN_CODE_5cfa; body bytes: 189 */

void FUN_CODE_5cfa(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  char *pcVar4;
  
  DAT_EXTMEM_075c = param_2 * '\x02';
  pcVar4 = &DAT_EXTMEM_075d;
  DAT_EXTMEM_075d = 1;
  DAT_EXTMEM_075b = param_1;
  FUN_CODE_344a();
  if (*pcVar4 == 'L') {
    FUN_CODE_a59d();
    param_2 = param_2 == 0;
    DAT_EXTMEM_075c = DAT_EXTMEM_075c & 0xfe | param_2;
    DAT_EXTMEM_075e = ' ';
    do {
      DAT_EXTMEM_075e = DAT_EXTMEM_075e + -1;
    } while (DAT_EXTMEM_075e != '\0');
    DAT_EXTMEM_075e = 0;
  }
  else {
    cVar2 = '\0';
    DAT_EXTMEM_075e = 0;
    while (bVar3 = FUN_CODE_33e9(cVar2), bVar1 = DAT_EXTMEM_075e, (bVar3 >> 6 & 1) != 1) {
      DAT_EXTMEM_075e = DAT_EXTMEM_075e + 1;
      cVar2 = bVar1 + 0x9c;
      if (100 < DAT_EXTMEM_075e) {
        return;
      }
    }
    FUN_CODE_a59d();
    param_2 = param_2 & 1;
    DAT_EXTMEM_075c = DAT_EXTMEM_075c & 0xfe | param_2;
  }
  FUN_CODE_a5a5();
  bVar1 = (param_2 & 1) << 5;
  DAT_EXTMEM_075d = DAT_EXTMEM_075d & 0xdf | bVar1;
  if (DAT_EXTMEM_075b != 1) {
    FUN_CODE_a7f0();
    DAT_EXTMEM_075b = bVar1;
  }
  DAT_EXTMEM_075d = DAT_EXTMEM_075d & 0x3f | DAT_EXTMEM_075b << 6;
  bVar1 = DAT_EXTMEM_075c;
  FUN_CODE_3472(DAT_EXTMEM_075c);
  FUN_CODE_a9ae(bVar1,0x12);
  FUN_CODE_a9ae(DAT_EXTMEM_075d,0x13);
  FUN_CODE_a9ae(0x11,0x58);
  return;
}

