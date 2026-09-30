/* Address: ram:0005fea2; name: FUN_ram_0005fea2; body bytes: 324 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_0005fea2(void)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  char cVar5;
  
  puVar2 = DAT_ram_20001eb0;
  iVar1 = DAT_ram_20001dd8;
  gp = 0x20004000;
  if ((*DAT_ram_20001eb0 & 3) != 0) {
    DAT_ram_20001eb0[0x14] = DAT_ram_20001eb0[0x14] & 0xfffffff8;
    *puVar2 = *puVar2 | 8;
  }
  puVar2 = DAT_ram_20001e88;
  DAT_ram_20001e88[2] = 0x8e89bed6;
  puVar2[1] = 0x555555;
  if (*(char *)(iVar1 + 0x22) != -1) {
    *(char *)(iVar1 + 0x21) = *(char *)(iVar1 + 0x22);
    *(undefined1 *)(iVar1 + 0x22) = 0xff;
  }
  cVar5 = *(char *)(iVar1 + 0x21);
  if (cVar5 != '\x02') {
    cVar5 = '\0';
  }
  DAT_ram_20001eb0[1] = DAT_ram_20001eb0[1] | 1;
  *(undefined1 *)(iVar1 + 10) = 0xa1;
  if ((DAT_ram_20001e9d != '\0') && (DAT_ram_20001e9c == '\x06')) {
    _DAT_ram_20001e9c = _DAT_ram_20001e9c & 0xff;
  }
  if (DAT_ram_20001e9b == '\b') {
    _DAT_ram_20001e9c = 0x108;
  }
  DAT_ram_20001e94 = 0;
  DAT_ram_20001e9b = 6;
  DAT_ram_20001e98 = 0;
  FUN_ram_00062030(cVar5,0xff,0);
  puVar3 = DAT_ram_20001eb0;
  DAT_ram_20001e99 = 0;
  DAT_ram_20001e95 = 0;
  *DAT_ram_20001eb0 = 1;
  puVar2 = DAT_ram_20001e88;
  *DAT_ram_20001e88 = *DAT_ram_20001e88 & 0xfffffe7f;
  *puVar2 = *puVar2 & 0xfffffe7f | 0x100;
  iVar4 = DAT_ram_20001efc;
  *(uint *)(DAT_ram_20001efc + 8) = *(uint *)(DAT_ram_20001efc + 8) | 0x330000;
  puVar3[0x14] = 0xd9;
  *(uint *)(iVar4 + 0x2c) = *(uint *)(iVar4 + 0x2c) & 0xfffffffd;
  *puVar2 = *puVar2 & 0xffffff80 | *(byte *)(iVar1 + 9) & 0x7f;
  return;
}

