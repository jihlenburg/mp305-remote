/* Address: ram:00049ce6; name: GATT_InitClient; body bytes: 216 */

undefined4 GATT_InitClient(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  
  gp = 0x20004000;
  DAT_ram_20001a34 = FUN_ram_20000040((uint)DAT_ram_20001d54 * 0x28,0x4706);
  tmos_memset(DAT_ram_20001a34,0,(uint)DAT_ram_20001d54 * 0x28);
  uVar2 = 0x13;
  if (DAT_ram_20001a34 != 0) {
    for (uVar1 = 0; uVar1 < DAT_ram_20001d54; uVar1 = uVar1 + 1 & 0xff) {
      puVar3 = (undefined2 *)(DAT_ram_20001a34 + uVar1 * 0x28);
      *puVar3 = 0xffff;
      *(undefined1 *)(puVar3 + 1) = 0;
      puVar3[4] = 0xffff;
      *(undefined1 *)(puVar3 + 5) = 0;
      *(undefined1 *)(puVar3 + 0x12) = 0;
      tmos_memset(puVar3 + 6,0,0x18);
    }
    FUN_ram_00048b78(FUN_ram_00049af8);
    FUN_ram_000431cc(FUN_ram_00049554);
    linkDB_Register(FUN_ram_0004963c);
    uVar2 = 0;
  }
  return uVar2;
}

