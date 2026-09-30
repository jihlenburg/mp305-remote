/* Address: ram:0006b77e; name: GAPRole_ReadRssiCmd; body bytes: 4 */

undefined1 GAPRole_ReadRssiCmd(undefined4 param_1)

{
  undefined1 uStack_14;
  undefined1 uStack_13;
  undefined1 uStack_12;
  undefined1 auStack_11 [9];
  
  gp = 0x20004000;
  uStack_14 = FUN_ram_00065e70(param_1,auStack_11);
  uStack_13 = (undefined1)param_1;
  uStack_12 = (undefined1)((uint)param_1 >> 8);
  thunk_FUN_ram_000521a0(0x1405,4,&uStack_14);
  return uStack_14;
}

