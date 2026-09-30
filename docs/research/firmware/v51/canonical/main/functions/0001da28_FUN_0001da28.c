/* Address: 0001da28; name: FUN_0001da28; body bytes: 184 */

undefined8 FUN_0001da28(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  uint local_20;
  undefined1 local_1c;
  undefined1 uStack_1b;
  undefined2 uStack_1a;
  uint local_18;
  undefined4 local_14;
  
  local_1c = (undefined1)param_2;
  uStack_1b = (undefined1)((uint)param_2 >> 8);
  uStack_1a = (undefined2)((uint)param_2 >> 0x10);
  local_20 = param_1;
  local_18 = param_3;
  local_14 = param_4;
  FUN_00013be8(0x7777777,0x112210);
  FUN_0001c2fc(0xf,1);
  FUN_0001c2fc(4,0);
  FUN_00014904(5);
  FUN_00013b24(&local_20);
  local_20 = local_20 & 0xffffff00;
  local_1c = 0x80;
  uStack_1b = 0x3b;
  uStack_1a = 0x3330;
  FUN_00013ae8(&local_20);
  FUN_00013bc4(&local_18);
  local_14 = 0x11403b01;
  local_18 = local_18 & 0xffffff00;
  FUN_00013ba0(&local_18);
  FUN_000153f4(0x4000);
  FUN_00013c04(5);
  FUN_000146d0(1);
  FUN_000146d0(0);
  FUN_0001472c(1);
  FUN_000146dc(1);
  FUN_00014720(1);
  return CONCAT26(uStack_1a,CONCAT15(uStack_1b,CONCAT14(local_1c,local_20)));
}

