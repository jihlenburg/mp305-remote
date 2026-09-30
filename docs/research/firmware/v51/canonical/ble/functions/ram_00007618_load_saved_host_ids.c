/* Address: ram:00007618; name: load_saved_host_ids; body bytes: 126 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Reads 80 bytes at nonvolatile offset 0x6f00 and counts non-ff 16-byte slots. */

void load_saved_host_ids(void)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined1 auStack_30 [28];
  
  gp = &DAT_ram_20002000;
  (*_DAT_ram_00040048)(auStack_30,0xff,0x10,in_a3,in_a4,_DAT_ram_00040048);
  FUN_ram_200028d6(0xb,0x6f00,&DAT_ram_200042b0,0x50);
  puVar2 = &DAT_ram_200042b0;
  cVar1 = '\0';
  do {
    iVar3 = (*_DAT_ram_0004003c)(auStack_30,puVar2,0x10);
    if (iVar3 == 0) {
      cVar1 = cVar1 + '\x01';
    }
    puVar2 = puVar2 + 0x10;
  } while (puVar2 != (undefined1 *)0x20004300);
  DAT_ram_20002fee = cVar1;
  return;
}

