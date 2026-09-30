/* Address: ram:00065864; name: FUN_ram_00065864; body bytes: 38 */

undefined1 FUN_ram_00065864(void)

{
  undefined1 auStack_11 [13];
  
  gp = 0x20004000;
  auStack_11[0] = FUN_ram_0006700c();
  thunk_FUN_ram_000521a0(0x2038,1,auStack_11);
  return auStack_11[0];
}

