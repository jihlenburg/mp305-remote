/* Address: ram:00065676; name: FUN_ram_00065676; body bytes: 50 */

undefined4 FUN_ram_00065676(undefined4 param_1)

{
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  
  gp = 0x20004000;
  uStack_14 = FUN_ram_0006608a();
  uStack_13 = (undefined1)param_1;
  uStack_12 = (undefined1)((uint)param_1 >> 8);
  thunk_FUN_ram_000521a0(0x2020,3,&uStack_14);
  return 0;
}

