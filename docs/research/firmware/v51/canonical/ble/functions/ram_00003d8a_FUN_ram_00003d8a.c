/* Address: ram:00003d8a; name: FUN_ram_00003d8a; body bytes: 72 */

void FUN_ram_00003d8a(int param_1)

{
  undefined1 uVar1;
  undefined1 auStack_110 [264];
  
  gp = &DAT_ram_20002000;
  FUN_ram_00001d1a(auStack_110,0,0x100);
  uVar1 = encode_transport_frame
                    (&DAT_ram_20003a50 + param_1 * 0x10c,param_1 * 0x218 + 0x20003b54,auStack_110);
  FUN_ram_00003d0c(auStack_110,uVar1);
  return;
}

