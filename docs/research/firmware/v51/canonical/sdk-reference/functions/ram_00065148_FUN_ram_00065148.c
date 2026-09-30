/* Address: ram:00065148; name: FUN_ram_00065148; body bytes: 52 */

undefined1 FUN_ram_00065148(int param_1,int param_2,short *param_3)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  if ((((param_1 != 0) && (param_2 != 0)) && (param_3 != (short *)0x0)) && (*param_3 != 0)) {
    return 0;
  }
  auStack_11[0] = 0x12;
  thunk_FUN_ram_000521a0(0xc35,1,auStack_11);
  return auStack_11[0];
}

