/* Address: ram:0004e38c; name: FUN_ram_0004e38c; body bytes: 116 */

int FUN_ram_0004e38c(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  
  gp = 0x20004000;
  cVar4 = '\0';
  iVar3 = DAT_ram_20001d00;
  do {
    if (DAT_ram_20001d54 == cVar4) {
      return 0;
    }
    if ((*(short *)(iVar3 + 2) != -1) && (iVar2 = *(int *)(iVar3 + 0x34), iVar2 != 0)) {
      cVar1 = *(char *)(iVar2 + 3);
      if (*(char *)(iVar2 + 2) == '\0') {
        if ((byte)(cVar1 - 0x21U) < 6) {
          gp = 0x20004000;
          return iVar3;
        }
        if ((cVar1 + 0xadU & 0xfd) == 0) {
          gp = 0x20004000;
          return iVar3;
        }
      }
      else {
        if ((byte)(cVar1 - 0x27U) < 5) {
          gp = 0x20004000;
          return iVar3;
        }
        if ((cVar1 + 0xadU & 0xfd) == 0) {
          return iVar3;
        }
      }
    }
    cVar4 = cVar4 + '\x01';
    iVar3 = iVar3 + 0x3c;
  } while( true );
}

