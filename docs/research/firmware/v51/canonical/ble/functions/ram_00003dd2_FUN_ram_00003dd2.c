/* Address: ram:00003dd2; name: FUN_ram_00003dd2; body bytes: 72 */

void FUN_ram_00003dd2(int param_1)

{
  undefined1 uVar1;
  undefined1 auStack_110 [264];
  
  gp = &DAT_ram_20002000;
  FUN_ram_00001d1a(auStack_110,0,0x100);
  uVar1 = encode_transport_frame
                    (&DAT_ram_20003a50 + param_1 * 0x10c,&DAT_ram_20003a50 + param_1 * 0x10c,
                     auStack_110);
  thunk_FUN_ram_00002914(auStack_110,uVar1);
  return;
}

