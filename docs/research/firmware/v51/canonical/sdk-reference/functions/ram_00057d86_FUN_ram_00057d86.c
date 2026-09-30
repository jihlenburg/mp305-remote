/* Address: ram:00057d86; name: FUN_ram_00057d86; body bytes: 124 */

void FUN_ram_00057d86(uint param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  gp = 0x20004000;
  puVar1 = (undefined4 *)0x0;
  puVar2 = DAT_ram_20001df0;
  do {
    if (puVar2 == (undefined4 *)0x0) {
LAB_ram_00057df4:
      if (DAT_ram_20001e04 == 0) {
LAB_ram_00057dca:
        FUN_ram_00057d50();
        DAT_ram_20001df0 = (undefined4 *)0x0;
      }
      return;
    }
    if (*(ushort *)(puVar2 + 2) == param_1) {
      if (puVar1 == (undefined4 *)0x0) {
        DAT_ram_20001df0 = (undefined4 *)*DAT_ram_20001df0;
        puVar1 = DAT_ram_20001df4;
      }
      else if (DAT_ram_20001df4 != puVar2) {
        *puVar1 = *puVar2;
        puVar1 = DAT_ram_20001df4;
      }
      DAT_ram_20001df4 = puVar1;
      FUN_ram_20000104(puVar2);
      *DAT_ram_20001df4 = 0;
      if (DAT_ram_20001e04 == 0) goto LAB_ram_00057dca;
      DAT_ram_20001e04 = DAT_ram_20001e04 + -1;
      goto LAB_ram_00057df4;
    }
    puVar1 = puVar2;
    puVar2 = (undefined4 *)*puVar2;
  } while( true );
}

