/* Address: ram:00068ea8; name: FUN_ram_00068ea8; body bytes: 116 */

void FUN_ram_00068ea8(undefined4 param_1,char param_2,uint param_3,int param_4,undefined4 param_5)

{
  char cVar1;
  int iVar2;
  undefined1 auStack_2c [26];
  char cStack_12;
  
  gp = 0x20004000;
  if (param_4 == 8) {
    cVar1 = param_2 * '\x06' + '\"';
  }
  else {
    cVar1 = param_2 * '\x06' + '!';
  }
  tmos_memset(auStack_2c,0,0x1c);
  iVar2 = tmos_snv_read(cVar1,0x1c,auStack_2c);
  if (iVar2 == 0) {
    if ((byte)(cStack_12 - 7U) < 10) {
      FUN_ram_00044baa(param_1,param_3 & 1,auStack_2c,param_5);
    }
  }
  return;
}

