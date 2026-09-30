/* Address: ram:00069350; name: FUN_ram_00069350; body bytes: 124 */

undefined4 FUN_ram_00069350(char param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  ushort uVar4;
  undefined1 auStack_20 [12];
  ushort uStack_14;
  
  gp = 0x20004000;
  cVar1 = param_1 * '\x06' + ' ';
  iVar3 = tmos_snv_read(cVar1,0x10,auStack_20);
  if ((iVar3 == 0) && (iVar3 = tmos_isbufset(auStack_20,0xff,6), iVar3 == 0)) {
    uVar4 = uStack_14 & 0xfd;
    if (param_2 != 0) {
      uVar4 = uStack_14 & 0xff | 2;
    }
    uVar2 = 1;
    if (uStack_14 != uVar4) {
      uStack_14 = uVar4;
      FUN_ram_00042e5e(cVar1,0x10,auStack_20);
      FUN_ram_00042e10(DAT_ram_200019c4);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

