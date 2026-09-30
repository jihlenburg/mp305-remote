/* Address: ram:000694be; name: FUN_ram_000694be; body bytes: 478 */

void FUN_ram_000694be(void)

{
  uint uVar1;
  int iVar2;
  
  gp = 0x20004000;
  DAT_ram_20001a8e = 0xff;
  DAT_ram_20001a8d = 0;
  DAT_ram_20001a88 = 0;
  DAT_ram_20001a88 = FUN_ram_20000040((uint)DAT_ram_20001bca << 4,0x42);
  if (DAT_ram_20001a88 != 0) {
    DAT_ram_20001a8d = DAT_ram_20001bca;
    for (uVar1 = 0; uVar1 < DAT_ram_20001a8d; uVar1 = uVar1 + 1 & 0xff) {
      iVar2 = uVar1 * 0x10;
      tmos_memset(DAT_ram_20001a88 + iVar2,0xff,6);
      tmos_memset(DAT_ram_20001a88 + iVar2 + 6,0xff,6);
      iVar2 = DAT_ram_20001a88 + iVar2;
      *(undefined2 *)(iVar2 + 0xc) = 0;
      *(undefined1 *)(iVar2 + 0xe) = 0;
    }
    if (DAT_ram_20001bc4 == 0) {
      DAT_ram_20001f0f = 0x80;
    }
    else {
      DAT_ram_20001f0f = 0;
    }
  }
  DAT_ram_20001a86 = DAT_ram_20001a8d;
  DAT_ram_20001aa8 = 0;
  DAT_ram_200019ca = 1;
  DAT_ram_20001a99 = 0;
  DAT_ram_20001a9b = 0;
  tmos_memset(&DAT_ram_20001b24,0,0x10);
  DAT_ram_20001a98 = 0;
  DAT_ram_20001a9a = 0x77;
  DAT_ram_20001a9c = 0;
  DAT_ram_200019c7 = 1;
  DAT_ram_20001a90 = 0;
  DAT_ram_20001a91 = 0;
  DAT_ram_20001a93 = 0;
  tmos_memset(&DAT_ram_20001b14,0,0x10);
  DAT_ram_20001a92 = 0x77;
  DAT_ram_20001a94 = 0;
  DAT_ram_20001a8f = 0;
  DAT_ram_200019c5 = 5;
  DAT_ram_200019c9 = 0x10;
  DAT_ram_20001aa0 = 0;
  DAT_ram_200019c6 = 2;
  DAT_ram_20001ab0 = 0;
  DAT_ram_20001aac = 0;
  DAT_ram_20001a85 = 0;
  DAT_ram_20001a8c = 0;
  DAT_ram_200019c4 = 1;
  DAT_ram_200019cb = 1;
  DAT_ram_200019c8 = 1;
  return;
}

