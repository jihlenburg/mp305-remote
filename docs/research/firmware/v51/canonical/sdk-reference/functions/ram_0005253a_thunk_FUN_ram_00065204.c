/* Address: ram:0005253a; name: thunk_FUN_ram_00065204; body bytes: 4 */

undefined1 thunk_FUN_ram_00065204(void)

{
  undefined1 uStack_14;
  undefined1 auStack_13 [15];
  
  gp = 0x20004000;
  uStack_14 = FUN_ram_00065e92(auStack_13);
  thunk_FUN_ram_000521a0(0x2002,4,&uStack_14);
  return uStack_14;
}

