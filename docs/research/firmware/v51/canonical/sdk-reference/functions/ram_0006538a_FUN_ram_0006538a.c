/* Address: ram:0006538a; name: FUN_ram_0006538a; body bytes: 48 */

undefined4 FUN_ram_0006538a(undefined4 param_1)

{
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  
  gp = 0x20004000;
  uStack_14 = FUN_ram_00066948();
  uStack_13 = (undefined1)param_1;
  uStack_12 = (undefined1)((uint)param_1 >> 8);
  thunk_FUN_ram_000521a0(0x201b,3,&uStack_14);
  return 0;
}

