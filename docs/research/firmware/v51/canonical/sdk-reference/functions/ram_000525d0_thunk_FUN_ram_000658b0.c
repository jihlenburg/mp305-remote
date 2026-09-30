/* Address: ram:000525d0; name: thunk_FUN_ram_000658b0; body bytes: 4 */

undefined1 thunk_FUN_ram_000658b0(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00067342();
  thunk_FUN_ram_000521a0(0x203e,1,auStack_11);
  return auStack_11[0];
}

