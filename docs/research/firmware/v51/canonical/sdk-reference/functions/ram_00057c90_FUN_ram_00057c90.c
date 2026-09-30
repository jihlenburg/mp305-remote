/* Address: ram:00057c90; name: FUN_ram_00057c90; body bytes: 192 */

undefined2 FUN_ram_00057c90(void)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  
  gp = 0x20004000;
  puVar3 = (undefined4 *)FUN_ram_20000040(0x1d0,0x20a);
  tmos_memset(puVar3,0,0x1d0);
  puVar1 = DAT_ram_20001df4;
  uVar2 = 0;
  if (puVar3 != (undefined4 *)0x0) {
    if (DAT_ram_20001df0 != (undefined4 *)0x0) {
      uVar6 = (uint)*(ushort *)(DAT_ram_20001df4 + 2);
      do {
        uVar4 = uVar6 + 1;
        uVar6 = uVar4 & 0xffff;
        puVar5 = DAT_ram_20001df0;
        if ((int)(uVar4 * 0x10000) < 0) {
          uVar6 = 1;
        }
        while (*(ushort *)(puVar5 + 2) != uVar6) {
          puVar5 = (undefined4 *)*puVar5;
          if (puVar5 == (undefined4 *)0x0) {
            *(short *)(puVar3 + 2) = (short)uVar6;
            if (uVar6 == 0) {
              FUN_ram_20000104(puVar3);
              goto LAB_ram_00057d42;
            }
            *puVar1 = puVar3;
            DAT_ram_20001e04 = DAT_ram_20001e04 + 1;
            DAT_ram_20001df4 = puVar3;
            goto LAB_ram_00057d26;
          }
        }
      } while( true );
    }
    *(undefined2 *)(puVar3 + 2) = 1;
    DAT_ram_20001e04 = 1;
    DAT_ram_20001df0 = puVar3;
    DAT_ram_20001df4 = puVar3;
    FUN_ram_00057bf0(0);
LAB_ram_00057d26:
    *DAT_ram_20001df4 = 0;
    *(undefined1 *)((int)puVar3 + 10) = 0;
    *(undefined1 *)((int)puVar3 + 0xe) = 0;
LAB_ram_00057d42:
    uVar2 = *(undefined2 *)(puVar3 + 2);
  }
  return uVar2;
}

