/* Address: CODE:807e; name: FUN_CODE_807e; body bytes: 62 */

void FUN_CODE_807e(void)

{
  char cVar1;
  char cVar2;
  
  if (DAT_INTMEM_b2 == '\x10') {
    if ((DAT_INTMEM_b4 == ')') || (DAT_INTMEM_b4 == '(')) {
      thunk_FUN_CODE_a19f();
    }
  }
  else if (DAT_INTMEM_b2 == '\x11') {
    if (DAT_INTMEM_b4 == '\r') {
      cVar2 = '@';
      cVar1 = '\0';
      FUN_CODE_9a0d();
      if (cVar2 == '\0' && cVar1 == '\0') {
        return;
      }
    }
    else if (DAT_INTMEM_b4 == '\f') {
      FUN_CODE_90d1(0,0x40);
      FUN_CODE_9832();
    }
  }
  return;
}

