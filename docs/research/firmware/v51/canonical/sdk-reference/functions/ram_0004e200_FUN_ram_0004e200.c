/* Address: ram:0004e200; name: FUN_ram_0004e200; body bytes: 68 */

char FUN_ram_0004e200(void)

{
  char cVar1;
  char cVar2;
  short *psVar3;
  
  gp = 0x20004000;
  cVar1 = '\0';
  psVar3 = (short *)(DAT_ram_20001d00 + 2);
  for (cVar2 = '\0'; DAT_ram_20001d54 != cVar2; cVar2 = cVar2 + '\x01') {
    if ((*psVar3 != -1) && ((char)psVar3[5] == '\x04')) {
      cVar1 = cVar1 + '\x01';
    }
    psVar3 = psVar3 + 0x1e;
  }
  return cVar1;
}

