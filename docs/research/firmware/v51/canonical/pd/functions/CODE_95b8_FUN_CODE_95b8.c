/* Address: CODE:95b8; name: FUN_CODE_95b8; body bytes: 29 */

undefined1 FUN_CODE_95b8(byte param_1)

{
  bool bVar1;
  char cVar2;
  
  if (DAT_INTMEM_b3 == '\x01') {
    bVar1 = 0xc3 < param_1;
    cVar2 = param_1 + 0x3c;
  }
  else {
    bVar1 = 0xc6 < param_1;
    cVar2 = param_1 + 0x39;
  }
  return *(undefined1 *)CONCAT11('\a' - ((bVar1 << 7) >> 7),cVar2);
}

