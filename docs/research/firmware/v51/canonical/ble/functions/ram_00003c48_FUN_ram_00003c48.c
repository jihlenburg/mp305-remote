/* Address: ram:00003c48; name: FUN_ram_00003c48; body bytes: 196 */

void FUN_ram_00003c48(code *param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 auStack_110 [260];
  
  cVar1 = DAT_ram_20003c6c;
  gp = &DAT_ram_20002000;
  FUN_ram_00001d1a(auStack_110,0,0x100);
  if (cVar1 == -0xc) {
    DAT_ram_20003d70 = 0xf5;
    DAT_ram_20003d72 = DAT_ram_20003c6e;
    DAT_ram_20003d74 = DAT_ram_20003c70;
    DAT_ram_20003d76 = 1;
    DAT_ram_20003d6e = 7;
  }
  else {
    if (cVar1 != ' ') {
      gp = &DAT_ram_20002000;
      return;
    }
    DAT_ram_20003d70 = 0x420;
    DAT_ram_20003d6e = 2;
  }
  DAT_ram_20003d6c = DAT_ram_20003c68 >> 8 | DAT_ram_20003c68 << 8;
  uVar2 = encode_transport_frame(&DAT_ram_20003c68,&DAT_ram_20003d6c,auStack_110);
  (*param_1)(auStack_110,uVar2);
  return;
}

