/* Address: ram:00052516; name: thunk_FUN_ram_000656da; body bytes: 4 */

undefined4 thunk_FUN_ram_000656da(undefined4 param_1)

{
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  
  gp = 0x20004000;
  uStack_14 = FUN_ram_0006620a();
  uStack_13 = (undefined1)param_1;
  uStack_12 = (undefined1)((uint)param_1 >> 8);
  thunk_FUN_ram_000521a0(0x2022,3,&uStack_14);
  return 0;
}

