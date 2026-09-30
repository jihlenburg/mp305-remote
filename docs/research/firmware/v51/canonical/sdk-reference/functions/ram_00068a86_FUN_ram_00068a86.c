/* Address: ram:00068a86; name: FUN_ram_00068a86; body bytes: 88 */

char FUN_ram_00068a86(void)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  
  gp = 0x20004000;
  cVar2 = '\0';
  for (uVar1 = 0; uVar1 < DAT_ram_20001a8d; uVar1 = uVar1 + 1 & 0xff) {
    iVar3 = tmos_isbufset(uVar1 * 0x10 + DAT_ram_20001a88,0xff,6);
    if (iVar3 == 0) {
      cVar2 = cVar2 + '\x01';
    }
  }
  return cVar2;
}

