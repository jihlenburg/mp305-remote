/* Address: ram:00005744; name: FUN_ram_00005744; body bytes: 288 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_00005744(void)

{
  undefined4 extraout_a3;
  undefined1 uStack_19;
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 uStack_16;
  byte bStack_15;
  undefined4 auStack_14 [2];
  
  gp = &DAT_ram_20002000;
  DAT_ram_20002fdc = (*_DAT_ram_00040080)(FUN_ram_00005af0);
  (*_DAT_ram_00040154)(2,0x12c0);
  (*_DAT_ram_00040154)(7,8);
  (*_DAT_ram_00040154)(8,0x28);
  (*_DAT_ram_00040154)(0xd,&LAB_ram_00001770);
  uStack_19 = 2;
  auStack_14[0] = 0;
  uStack_18 = 0;
  uStack_17 = 0;
  uStack_16 = 1;
  (*_DAT_ram_00040168)(0x40f,4,auStack_14);
  (*_DAT_ram_00040168)(0x408,1,&uStack_19);
  (*_DAT_ram_00040168)(0x409,1,&uStack_18);
  (*_DAT_ram_00040168)(0x40a,1,&uStack_17);
  (*_DAT_ram_00040168)(0x40d,1,&uStack_16);
  bStack_15 = 0;
  (*_DAT_ram_0004016c)(0x415,&bStack_15);
  if (2 < bStack_15) {
    (*_DAT_ram_00040168)(0x410,0,0,extraout_a3,bStack_15,_DAT_ram_00040168);
  }
  (*_DAT_ram_000400c4)();
  (*_DAT_ram_000400c8)(DAT_ram_20002fdc);
  (*_DAT_ram_00040150)(0xffffffff);
  (*_DAT_ram_00040134)(0xffffffff);
  FUN_ram_00005710();
  (*_DAT_ram_00040050)(DAT_ram_20002fdc,1);
  return;
}

