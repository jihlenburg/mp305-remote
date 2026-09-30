/* Address: ram:0004bdb6; name: FUN_ram_0004bdb6; body bytes: 280 */

undefined4 FUN_ram_0004bdb6(void)

{
  uint uVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  uint uVar4;
  undefined2 *puVar5;
  
  gp = 0x20004000;
  DAT_ram_20001a4c = (undefined2 *)0x0;
  DAT_ram_20001a50 = (undefined2 *)0x0;
  DAT_ram_20001a40 = (undefined2 *)0x0;
  if (DAT_ram_20001d55 != 0) {
    DAT_ram_20001a4c = (undefined2 *)FUN_ram_20000040((ushort)DAT_ram_20001d55 * 0xc2 + 6,0x4701);
    tmos_memset(DAT_ram_20001a4c,0,(uint)DAT_ram_20001d55 * 0xc2 + 6);
    puVar5 = DAT_ram_20001a4c;
    uVar4 = (uint)DAT_ram_20001d55;
    puVar3 = DAT_ram_20001a4c;
    for (uVar1 = 0; uVar1 < uVar4; uVar1 = uVar1 + 1) {
      *puVar3 = 0xffff;
      puVar2 = puVar3 + 2;
      do {
        *puVar2 = 0;
        *(undefined4 *)(puVar2 + 4) = 0;
        puVar2 = puVar2 + 6;
      } while (puVar2 != puVar3 + 0x5c);
      puVar3 = puVar3 + 0x5c;
    }
    uVar1 = 0;
    puVar5 = puVar5 + uVar4 * 0x5c;
    puVar3 = puVar5;
    DAT_ram_20001a50 = puVar5;
    do {
      *puVar3 = 0xffff;
      *(undefined1 *)((int)puVar3 + 3) = 0xff;
      *(undefined1 *)(puVar3 + 1) = 0xff;
      *(undefined1 *)(puVar3 + 2) = 0;
      uVar1 = uVar1 + 1;
      puVar3 = puVar3 + 3;
    } while (uVar1 < uVar4 + 1);
    *puVar5 = 0xfffe;
    DAT_ram_20001a40 = puVar5 + (uVar4 + 1) * 3;
  }
  FUN_ram_00048b82(FUN_ram_0004a48c);
  FUN_ram_000431d6(FUN_ram_0004a65c);
  linkDB_Register(FUN_ram_0004a3f4);
  return 0;
}

