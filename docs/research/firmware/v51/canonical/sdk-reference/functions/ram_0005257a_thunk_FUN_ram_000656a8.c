/* Address: ram:0005257a; name: thunk_FUN_ram_000656a8; body bytes: 4 */

undefined4 thunk_FUN_ram_000656a8(undefined4 param_1)

{
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  
  gp = 0x20004000;
  uStack_14 = FUN_ram_000661ca();
  uStack_13 = (undefined1)param_1;
  uStack_12 = (undefined1)((uint)param_1 >> 8);
  thunk_FUN_ram_000521a0(0x2021,3,&uStack_14);
  return 0;
}

