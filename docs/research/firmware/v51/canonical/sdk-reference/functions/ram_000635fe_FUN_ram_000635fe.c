/* Address: ram:000635fe; name: FUN_ram_000635fe; body bytes: 302 */

void FUN_ram_000635fe(void)

{
  byte bVar1;
  int iVar2;
  char cVar3;
  
  bVar1 = DAT_ram_20001eb4;
  gp = 0x20004000;
  if ((DAT_ram_20001ee0 & 2) != 0) {
    DAT_ram_20001eb4 = DAT_ram_20001eb4 | 9;
    cVar3 = '\0';
    while( true ) {
      do {
        RF_Tx(0,0,(undefined1)DAT_ram_20001ed4,DAT_ram_20001ed4._1_1_);
      } while ((DAT_ram_20001e96 & 1) == 0);
      DAT_ram_20001e96 = 0;
      FUN_ram_00062030((int)(uint)DAT_ram_20001eb4 >> 4 & 3,0xff,0);
      iVar2 = 0x1e;
      do {
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      FUN_ram_200011be(1,(int)(uint)DAT_ram_20001eb4 >> 4 & 3,0xff);
      if ((DAT_ram_20001e97 & 1) != 0) {
        DAT_ram_20001e97 = 0;
        FUN_ram_000628b8();
        DAT_ram_20001ee0 = DAT_ram_20001ee0 | 0x80;
        tmos_set_event(DAT_ram_20001ee4,1);
        gp = 0x20004000;
        DAT_ram_20001eb4 = bVar1;
        return;
      }
      FUN_ram_000628b8();
      cVar3 = cVar3 + '\x01';
      if (cVar3 == '\b') break;
      *(undefined4 *)(DAT_ram_20001eb0 + 0xc) = 0xd00f;
      iVar2 = DAT_ram_20001eb0;
      fence.i();
      *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x2000;
      DAT_ram_20001e98 = 0x80;
      *(undefined4 *)(iVar2 + 100) = 0xf92;
      *(undefined4 *)(iVar2 + 0xc) = 0xf00f;
      do {
      } while (*(int *)(DAT_ram_20001eb0 + 100) != 0);
    }
    RF_FrequencyHoppingShut();
  }
  DAT_ram_20001eb4 = bVar1;
  return;
}

