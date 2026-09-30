/* Address: ram:000651a6; name: FUN_ram_000651a6; body bytes: 38 */

undefined1 FUN_ram_000651a6(void)

{
  undefined1 uStack_18;
  undefined1 auStack_17 [19];
  
  gp = 0x20004000;
  uStack_18 = FUN_ram_00065e4c(auStack_17);
  thunk_FUN_ram_000521a0(0x1009,7,&uStack_18);
  return uStack_18;
}

