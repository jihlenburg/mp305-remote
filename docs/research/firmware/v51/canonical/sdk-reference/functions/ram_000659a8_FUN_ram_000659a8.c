/* Address: ram:000659a8; name: FUN_ram_000659a8; body bytes: 38 */

undefined1 FUN_ram_000659a8(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00067fce();
  thunk_FUN_ram_000521a0(0x2051,1,auStack_11);
  return auStack_11[0];
}

