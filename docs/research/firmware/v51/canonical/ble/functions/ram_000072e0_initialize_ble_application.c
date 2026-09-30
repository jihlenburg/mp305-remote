/* Address: ram:000072e0; name: initialize_ble_application; body bytes: 390 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Registers BLE task, services, advertising and scan response data. */

void initialize_ble_application(void)

{
  undefined1 uStack_19;
  undefined1 uStack_18;
  undefined1 uStack_17;
  ushort uStack_16;
  undefined4 auStack_14 [2];
  
  gp = &DAT_ram_20002000;
  DAT_ram_20002f44 = (*_DAT_ram_00040080)(FUN_ram_00006cb0);
  uStack_17 = 0;
  uStack_16 = 6;
  auStack_14[0] = CONCAT22(auStack_14[0]._2_2_,0x28);
  (*_DAT_ram_00040174)(0x305,1,&uStack_17);
  (*_DAT_ram_00040174)(0x307,0x1f,&DAT_ram_20002e98);
  (*_DAT_ram_00040174)(0x306,0x1f,&DAT_ram_20002e78);
  (*_DAT_ram_00040174)(0x311,2,&uStack_16);
  (*_DAT_ram_00040174)(0x312,2,auStack_14);
  (*_DAT_ram_00040154)(3,800);
  (*_DAT_ram_00040154)(4,800);
  (*_DAT_ram_00040154)(0x1e,1);
  auStack_14[0] = 0;
  uStack_19 = 1;
  uStack_18 = 1;
  uStack_17 = 1;
  uStack_16 = uStack_16 & 0xff00;
  (*_DAT_ram_00040168)(0x407,4,auStack_14);
  (*_DAT_ram_00040168)(0x400,1,&uStack_19);
  (*_DAT_ram_00040168)(0x401,1,&uStack_18);
  (*_DAT_ram_00040168)(0x402,1,&uStack_16);
  (*_DAT_ram_00040168)(0x405,1,&uStack_17);
  (*_DAT_ram_00040150)(0xffffffff);
  (*_DAT_ram_00040134)(0xffffffff);
  FUN_ram_00003126();
  FUN_ram_00002c6a(&LAB_ram_000072a6);
  FUN_ram_00002efc(&PTR_LAB_ram_00006cae_ram_20002f38);
  _DAT_ram_20002ffc = 0xfffe;
  _DAT_ram_20003000 = 0;
  FUN_ram_00003144(&PTR_FUN_ram_000070e6_ram_20002f40);
  (*_DAT_ram_000401dc)(&DAT_ram_20002fe0);
  (*_DAT_ram_00040050)(DAT_ram_20002f44,1);
  FUN_ram_00004b14();
  FUN_ram_00002764(1);
  return;
}

