/* Address: ram:00047ea8; name: FUN_ram_00047ea8; body bytes: 104 */

void FUN_ram_00047ea8(uint param_1,byte *param_2,byte *param_3)

{
  byte bVar1;
  byte bVar2;
  
  gp = 0x20004000;
  bVar2 = *param_2 & 0xfd;
  if ((param_1 & 2) != 0) {
    bVar2 = *param_2 | 2;
  }
  bVar1 = bVar2 & 0x7f;
  if ((char)param_1 < '\0') {
    bVar1 = bVar2 | 0x80;
  }
  bVar2 = bVar1 & 0xf7;
  if ((param_1 & 8) != 0) {
    bVar2 = bVar1 | 8;
  }
  bVar1 = bVar2 & 0xdf;
  if ((param_1 & 0x20) != 0) {
    bVar1 = bVar2 | 0x20;
  }
  *param_2 = bVar1;
  if (((char)param_1 < '\0') || ((param_1 & 0x2a) != 0)) {
    bVar2 = *param_3 | 0xc;
  }
  else {
    if (param_1 != 0) {
      gp = 0x20004000;
      return;
    }
    bVar2 = *param_3 & 0xf3;
  }
  *param_3 = bVar2;
  return;
}

