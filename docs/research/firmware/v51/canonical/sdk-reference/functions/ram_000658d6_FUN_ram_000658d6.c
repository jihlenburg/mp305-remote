/* Address: ram:000658d6; name: FUN_ram_000658d6; body bytes: 38 */

undefined1 FUN_ram_000658d6(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00067434();
  thunk_FUN_ram_000521a0(0x203f,1,auStack_11);
  return auStack_11[0];
}

