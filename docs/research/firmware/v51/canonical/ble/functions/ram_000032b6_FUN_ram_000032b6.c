/* Address: ram:000032b6; name: FUN_ram_000032b6; body bytes: 282 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000032b6(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined **ppuVar3;
  undefined1 local_54 [8];
  undefined *puStack_4c;
  ushort uStack_48;
  undefined4 uStack_44;
  undefined1 uStack_3d;
  undefined2 uStack_3c;
  undefined1 uStack_3a;
  undefined4 uStack_38;
  undefined1 auStack_32 [6];
  undefined1 *puStack_2c;
  undefined1 *puStack_28;
  code *pcStack_24;
  code *pcStack_20;
  code *pcStack_18;
  code *pcStack_14;
  
  gp = &DAT_ram_20002000;
  iVar1 = (*_DAT_ram_0004003c)
                    (_DAT_ram_00040034,"CH58x_BLE_LIB_V1.8",0x12,in_a3,in_a4,_DAT_ram_0004003c);
  if (iVar1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  DAT_ram_e000f010 = 0xfffffffe;
  DAT_ram_e000f014 = 0xffffffff;
  DAT_ram_e000e100 = 0x1000;
  DAT_ram_e000f000 = 0x2f;
  DAT_ram_e000e180 = 0x1000;
  (*_DAT_ram_00040048)(&puStack_4c,0,0x3c,&DAT_ram_e000f000,0x1000,_DAT_ram_00040048);
  puStack_4c = &DAT_ram_20005160;
  uStack_48 = 0x1c00;
  uStack_3c = 0xfb;
  uStack_3d = 5;
  uStack_3a = 1;
  uStack_44 = 0x7e00;
  pcStack_18 = FUN_ram_0000315c;
  pcStack_14 = FUN_ram_00003178;
  puStack_2c = &LAB_ram_0000275a;
  pcStack_24 = FUN_ram_000031b8;
  pcStack_20 = FUN_ram_00003156;
  uStack_38 = 0xd022e3d;
  puStack_28 = &LAB_ram_000034a6;
  FUN_ram_200028d6(6,0x7f018,local_54,0);
  iVar1 = 0;
  ppuVar3 = &puStack_4c;
  do {
    puVar2 = local_54 + iVar1;
    iVar1 = iVar1 + 1;
    *(undefined1 *)((int)ppuVar3 + 0x1a) = *puVar2;
    ppuVar3 = (undefined **)((int)ppuVar3 + 1);
  } while (iVar1 != 6);
  if ((puStack_4c != (undefined *)0x0) && (0xfff < uStack_48)) {
    iVar1 = (*_DAT_ram_000400a4)(&puStack_4c);
    if (iVar1 != 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

