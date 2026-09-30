/* Address: ram:000471e2; name: FUN_ram_000471e2; body bytes: 110 */

undefined4 FUN_ram_000471e2(uint param_1)

{
  undefined4 uVar1;
  undefined1 uStack_11;
  
  gp = 0x20004000;
  uVar1 = 0x12;
  if (DAT_ram_200019e4 != (byte *)0x0) {
    uVar1 = 3;
    if (*DAT_ram_200019e4 == param_1) {
      tmos_stop_task(DAT_ram_20001d4c,2);
      DAT_ram_20001a10 = 0;
      tmos_stop_task(DAT_ram_20001d4c,4);
      DAT_ram_200019e4[1] = 3;
      uStack_11 = 1;
      uVar1 = thunk_FUN_ram_0006588a(0,1,&uStack_11,0,0);
    }
  }
  return uVar1;
}

