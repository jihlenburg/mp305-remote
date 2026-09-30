/* Address: ram:0004e07e; name: FUN_ram_0004e07e; body bytes: 52 */

char FUN_ram_0004e07e(void)

{
  char cVar1;
  char *pcVar2;
  char cVar3;
  
  gp = 0x20004000;
  cVar1 = '\0';
  pcVar2 = (char *)(DAT_ram_20001d00 + 4);
  for (cVar3 = '\0'; DAT_ram_20001d54 != cVar3; cVar3 = cVar3 + '\x01') {
    if (*pcVar2 != '\0') {
      cVar1 = cVar1 + '\x01';
    }
    pcVar2 = pcVar2 + 0x3c;
  }
  return cVar1;
}

