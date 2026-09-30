/* Address: CODE:a7de; name: thunk_FUN_CODE_7bca; body bytes: 3 */

void thunk_FUN_CODE_7bca(char param_1)

{
  undefined1 uVar1;
  byte bVar2;
  char cVar3;
  
  if (param_1 == '\x01') {
    uVar1 = 0x3b;
  }
  else {
    uVar1 = 0x48;
  }
  DAT_EXTMEM_04ae = param_1;
  FUN_CODE_87aa(uVar1,0xb1,0xff);
  _1_5 = DAT_EXTMEM_04ae != '\0';
  cVar3 = _1_5 << 7;
  FUN_CODE_9436();
  bVar2 = DAT_INTMEM_b3;
  FUN_CODE_a139();
  if (cVar3 < '\0') {
    FUN_CODE_a521();
    cVar3 = (bVar2 < 4) << 7;
    if (bVar2 == 4) {
      FUN_CODE_9bf3();
      if (cVar3 < '\0') {
        FUN_CODE_87aa(0x56,0xb1,0xff);
        FUN_CODE_a638(3,2);
      }
    }
  }
  return;
}

