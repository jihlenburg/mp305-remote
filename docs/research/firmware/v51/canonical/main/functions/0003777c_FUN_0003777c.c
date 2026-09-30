/* Address: 0003777c; name: FUN_0003777c; body bytes: 88 */

char FUN_0003777c(uint param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = param_2 + -1;
  if (iVar2 < 0) {
    param_1 = param_1 - 1;
    iVar2 = param_2 + 0xb;
  }
  if (0xb < iVar2) {
    param_1 = param_1 + 1;
    iVar2 = iVar2 + -0xc;
  }
  if (iVar2 == 1) {
    if (((param_1 & 3) == 0) &&
       ((param_1 != (param_1 / 100) * 100 || (param_1 == (param_1 / 400) * 400)))) {
      cVar1 = '\x01';
    }
    else {
      cVar1 = '\0';
    }
    cVar1 = cVar1 + '\x1c';
  }
  else {
    cVar1 = '\x1f' - (char)((iVar2 % 7) % 2);
  }
  return cVar1;
}

