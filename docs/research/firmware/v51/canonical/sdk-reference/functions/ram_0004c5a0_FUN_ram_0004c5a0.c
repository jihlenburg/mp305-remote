/* Address: ram:0004c5a0; name: FUN_ram_0004c5a0; body bytes: 74 */

char FUN_ram_0004c5a0(int param_1)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  
  gp = 0x20004000;
  cVar3 = '\0';
  pcVar1 = DAT_ram_20001a58;
  for (cVar2 = '\0'; DAT_ram_20001a60 != cVar2; cVar2 = cVar2 + '\x01') {
    if (((*pcVar1 != '\0') && (*(int *)(pcVar1 + 0xc) != 0)) &&
       (param_1 == (uint)*(byte *)(*(int *)(pcVar1 + 0xc) + 0x1c) * 0x10 + DAT_ram_20001cc4)) {
      cVar3 = cVar3 + '\x01';
    }
    pcVar1 = pcVar1 + 0x10;
  }
  return cVar3;
}

