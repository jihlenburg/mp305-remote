/* Address: CODE:94ae; name: FUN_CODE_94ae; body bytes: 30 */

byte FUN_CODE_94ae(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  
  IEN1 = param_1;
  T1 = _1_5 & 1;
  WR = 1;
  do {
    cVar2 = T0;
  } while (cVar2 == '\0');
  cVar2 = IPH1;
  bVar1 = IPL1;
  WR = 0;
  return bVar1 >> 4 | cVar2 << 4;
}

