/* Address: ram:0004c892; name: FUN_ram_0004c892; body bytes: 334 */

void FUN_ram_0004c892(undefined1 param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  byte bVar3;
  
  gp = 0x20004000;
  DAT_ram_20001a62 = 0;
  DAT_ram_20001a5c = 0;
  DAT_ram_20001cc9 = 1;
  DAT_ram_20001a65 = 0;
  DAT_ram_20001a5e = 0;
  DAT_ram_20001a60 = 0;
  DAT_ram_20001a61 = '\0';
  DAT_ram_20001a58 = 0;
  DAT_ram_20001a63 = 0;
  DAT_ram_20001cc8 = param_1;
  tmos_memset(&DAT_ram_20001ccc,0,0x30);
  FUN_ram_0004de6a();
  if (DAT_ram_20001cfc != 0) {
    DAT_ram_20001cc4 = FUN_ram_20000040((uint)DAT_ram_20001cfc << 4,0x4c04);
    if (DAT_ram_20001cc4 != 0) {
      DAT_ram_20001a63 = DAT_ram_20001cfc;
      DAT_ram_20001a61 = DAT_ram_20001cfd;
      tmos_memset(DAT_ram_20001cc4,0,(uint)DAT_ram_20001cfc << 4);
    }
  }
  DAT_ram_20001a60 = DAT_ram_20001d54 + DAT_ram_20001a61;
  DAT_ram_20001a58 = FUN_ram_20000040((uint)DAT_ram_20001a60 << 4,0x4c05);
  if (DAT_ram_20001a58 == 0) {
    DAT_ram_20001a60 = 0;
    DAT_ram_20001a61 = '\0';
  }
  else {
    tmos_memset(DAT_ram_20001a58,0,(uint)DAT_ram_20001a60 << 4);
    bVar1 = DAT_ram_20001a60;
    puVar2 = (undefined1 *)(DAT_ram_20001a58 + 9);
    for (bVar3 = 0; bVar1 != bVar3; bVar3 = bVar3 + 1) {
      *puVar2 = 0xff;
      puVar2 = puVar2 + 0x10;
    }
  }
  linkDB_Register(&LAB_ram_0004c70a);
  return;
}

