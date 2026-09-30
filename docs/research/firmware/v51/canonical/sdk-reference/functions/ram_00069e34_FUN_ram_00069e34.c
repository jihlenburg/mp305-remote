/* Address: ram:00069e34; name: FUN_ram_00069e34; body bytes: 216 */

void FUN_ram_00069e34(void)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 auStack_6c [16];
  undefined1 auStack_5c [16];
  undefined1 auStack_4c [27];
  char cStack_31;
  
  gp = 0x20004000;
  thunk_FUN_ram_00065732();
  if (DAT_ram_200019cb != '\0') {
    for (uVar2 = 0; uVar2 < DAT_ram_20001a8d; uVar2 = uVar2 + 1 & 0xff) {
      iVar5 = uVar2 * 0x10;
      iVar3 = tmos_isbufset(DAT_ram_20001a88 + iVar5,0xff,6);
      if (iVar3 == 0) {
        uVar4 = uVar2 * 6 & 0xff;
        iVar3 = tmos_snv_read(uVar4 + 0x21 & 0xff,0x1c,auStack_4c);
        if ((iVar3 == 0) && (cStack_31 == -1)) {
          bVar1 = *(byte *)(DAT_ram_20001a88 + iVar5 + 5);
          tmos_snv_read(uVar4 + 0x23 & 0xff,0x10,auStack_6c);
          tmos_snv_read(2,0x10,auStack_5c);
          thunk_FUN_ram_0006570c
                    ((bVar1 & 0xc0) != 0x80,DAT_ram_20001a88 + iVar5,auStack_6c,auStack_5c);
        }
      }
    }
  }
  return;
}

