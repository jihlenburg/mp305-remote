/* Address: CODE:9137; name: FUN_CODE_9137; body bytes: 34 */

char FUN_CODE_9137(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  
  cVar2 = DAT_INTMEM_d1;
  FUN_CODE_770c();
  bVar1 = cVar2 + 1;
  FUN_CODE_a9ae(param_1,BANK0_R6);
  cVar2 = bVar1 + 0x10;
  if (0xef < bVar1) {
    cVar2 = '\0';
  }
  DAT_INTMEM_d1 = BANK0_R6;
  return cVar2;
}

