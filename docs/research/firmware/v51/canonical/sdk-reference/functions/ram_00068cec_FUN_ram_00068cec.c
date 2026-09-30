/* Address: ram:00068cec; name: FUN_ram_00068cec; body bytes: 168 */

void FUN_ram_00068cec(void)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  
  gp = 0x20004000;
  thunk_FUN_ram_00065732();
  for (uVar2 = 0; uVar2 < DAT_ram_20001a8d; uVar2 = uVar2 + 1 & 0xff) {
    iVar4 = uVar2 * 0x10;
    iVar3 = tmos_isbufset(DAT_ram_20001a88 + iVar4,0xff,6);
    if (iVar3 == 0) {
      bVar1 = *(byte *)(DAT_ram_20001a88 + iVar4 + 5);
      tmos_snv_read(uVar2 * 6 + 0x23 & 0xff,0x10,auStack_40);
      tmos_snv_read(2,0x10,auStack_30);
      thunk_FUN_ram_0006570c((bVar1 & 0xc0) != 0x80,DAT_ram_20001a88 + iVar4,auStack_40,auStack_30);
    }
  }
  return;
}

