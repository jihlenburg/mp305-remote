/* Address: ram:000042ac; name: FUN_ram_000042ac; body bytes: 474 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000042ac(void)

{
  undefined1 uVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  undefined1 *puVar5;
  uint uVar6;
  undefined2 uStack_54;
  undefined1 auStack_52 [34];
  
  gp = &DAT_ram_20002000;
  if ((DAT_ram_20002f98 != DAT_ram_20002ff4) && (DAT_ram_20003c58 == '\0')) {
    if (DAT_ram_20002ff4 == 0) {
      uStack_54 = 0xbd;
      queue_gatt_to_main(&uStack_54,2,0);
    }
    if (DAT_ram_20002ff4 == 2) {
      uStack_54 = 0x1bd;
      queue_gatt_to_main(&uStack_54,2,0);
    }
    DAT_ram_20002f98 = DAT_ram_20002ff4;
  }
  if ((DAT_ram_20002f9c != DAT_ram_20002fdb) && (DAT_ram_20004088 == '\0')) {
    if (DAT_ram_20002f9d != DAT_ram_20002fc8) {
      if (DAT_ram_20002fdb == '\0') {
        uStack_54 = 0xbd;
        FUN_ram_00003810(&uStack_54,2);
      }
      if ((DAT_ram_20002fdb == '\x02') && (DAT_ram_20002fc8 == '\x01')) {
        FUN_ram_00001d1a(auStack_52,0,0x21);
        uVar1 = 1;
        if (DAT_ram_20002fcf == '\0') {
          uVar1 = 2;
        }
        puVar3 = &DAT_ram_20004b40;
        uStack_54 = CONCAT11(uVar1,0xbd);
        puVar5 = &DAT_ram_20004be5;
        uVar2 = 0;
        do {
          uVar6 = uVar2 & 0xff;
          iVar4 = (*_DAT_ram_0004003c)(&DAT_ram_20002f30,puVar5,6);
          if (iVar4 != 0) {
            FUN_ram_00004e1a(&DAT_ram_20004b4a + uVar2 * 0x1f,puVar3[0xc3],99);
            if (puVar3[0xc3] != '\0') {
              (*_DAT_ram_0004004c)(auStack_52,&DAT_ram_20004b4a + uVar2 * 0x1f);
              goto LAB_ram_00004410;
            }
          }
          uVar2 = uVar2 + 1;
          puVar5 = puVar5 + 6;
          puVar3 = puVar3 + 1;
        } while (uVar2 != 5);
        uVar6 = 5;
LAB_ram_00004410:
        FUN_ram_000042a4(&uStack_54,(&DAT_ram_20004c03)[uVar6] + '\x02',0);
        FUN_ram_00001d1a(&DAT_ram_20004b40,0,0xcc);
      }
      DAT_ram_20002f9c = DAT_ram_20002fdb;
      DAT_ram_20002f9d = DAT_ram_20002fc8;
    }
  }
  return;
}

