/* Address: ram:00004964; name: FUN_ram_00004964; body bytes: 340 */

void FUN_ram_00004964(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  gp = &DAT_ram_20002000;
  if ((0x5f < DAT_ram_20002fa4) && (DAT_ram_20002fa0 != 0)) {
    uVar4 = 0;
    uVar5 = 0;
    uVar3 = 0;
    do {
      uVar2 = (&DAT_ram_200043c0)[uVar4] & 0xffffff;
      if (uVar2 < 100) {
        uVar1 = (uint)(&DAT_ram_200043c0)[uVar4] >> 0x19 & 1;
        if ((uVar1 != 0) && (uVar5 < 0x18)) {
          uVar3 = uVar3 << 1;
          if (0x28 < uVar2) {
            uVar3 = uVar3 | 1;
          }
          uVar5 = uVar5 + 1;
        }
        if (DAT_ram_20002f2c == uVar1) {
          DAT_ram_20002fa8 = DAT_ram_20002fa8 + 1;
          FUN_ram_000079ac(0x2d);
        }
        DAT_ram_20002f2c = uVar1;
        FUN_ram_00007968("%d,%d,%d,%d\n",uVar1,uVar2,uVar5,uVar3);
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < DAT_ram_20002fa4);
    FUN_ram_00007968("------------%d,%d\n",DAT_ram_20002fac,DAT_ram_20002fa8);
    DAT_ram_20002fa8 = 0;
    DAT_ram_20002f2c = 2;
    DAT_ram_20002fa4 = 0;
    FUN_ram_00004916(uVar3);
    return;
  }
  return;
}

