/* Address: ram:00065758; name: FUN_ram_00065758; body bytes: 38 */

undefined1 FUN_ram_00065758(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_00066a88();
  thunk_FUN_ram_000521a0(0x202d,1,auStack_11);
  return auStack_11[0];
}

