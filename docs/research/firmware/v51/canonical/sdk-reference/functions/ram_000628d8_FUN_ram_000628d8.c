/* Address: ram:000628d8; name: FUN_ram_000628d8; body bytes: 368 */

void FUN_ram_000628d8(void)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char acStack_21 [13];
  
  gp = 0x20004000;
  do {
    if ((DAT_ram_20001eb4 & 1) == 0) goto LAB_ram_00062a1c;
    if ((DAT_ram_20001e96 & 1) != 0) {
      DAT_ram_20001e96 = 0;
      FUN_ram_00062030((int)(uint)DAT_ram_20001eb4 >> 4 & 3,DAT_ram_20001ed0,0);
      FUN_ram_200011be(1,(int)(uint)DAT_ram_20001eb4 >> 4 & 3,0xff);
      FUN_ram_000628b8();
      (*DAT_ram_20001ec4)(1,0,0);
      if ((DAT_ram_20001e97 & 1) != 0) {
        DAT_ram_20001e97 = 0;
        acStack_21[0] = '\0';
        DAT_ram_20001e98 = 0;
        cVar1 = FUN_ram_20001120(DAT_ram_20001eac,0,acStack_21,0);
        uVar3 = (uint)cVar1;
        if ((((uVar3 == 0) && (*DAT_ram_20001eac != -1)) && (DAT_ram_20001ed4._1_1_ != -1)) &&
           (*DAT_ram_20001eac != DAT_ram_20001ed4._1_1_)) {
          uVar3 = 2;
        }
        if (-1 < (char)DAT_ram_20001eb4) {
          *DAT_ram_20001eac = acStack_21[0];
        }
        (*DAT_ram_20001ec4)(2,uVar3 & 0xff,DAT_ram_20001eac);
        if ((DAT_ram_20001ee0 & 2) == 0) {
          gp = 0x20004000;
          return;
        }
        tmos_set_event(DAT_ram_20001ee4,1);
        gp = 0x20004000;
        return;
      }
      if (*(int *)(DAT_ram_20001eb0 + 100) != 0) {
        gp = 0x20004000;
        return;
      }
      uVar2 = 0x12;
      goto LAB_ram_000629f8;
    }
  } while (*(int *)(DAT_ram_20001eb0 + 100) != 0);
  FUN_ram_000628b8();
  FUN_ram_00042954();
  goto LAB_ram_00062a0a;
  while (*(int *)(DAT_ram_20001eb0 + 100) != 0) {
LAB_ram_00062a1c:
    if ((DAT_ram_20001e97 & 1) != 0) {
      FUN_ram_000628b8();
      DAT_ram_20001e97 = 0;
      uVar2 = 1;
      goto LAB_ram_000629f8;
    }
  }
  FUN_ram_000628b8();
LAB_ram_00062a0a:
  uVar2 = 0x11;
LAB_ram_000629f8:
  DAT_ram_20001e98 = 0;
  (*DAT_ram_20001ec4)(uVar2,0,0);
  return;
}

