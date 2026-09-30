/* Address: ram:000488b8; name: FUN_ram_000488b8; body bytes: 48 */

void FUN_ram_000488b8(short *param_1)

{
  char cVar1;
  char cVar2;
  
  gp = 0x20004000;
  if (*param_1 == 0xb0) {
    cVar2 = (char)param_1[2];
    if (cVar2 == '\x12') {
      cVar1 = *(char *)((int)param_1 + 0x11);
      cVar2 = '\x01';
    }
    else {
      cVar1 = '\x1b';
    }
    if (cVar2 == cVar1) {
      FUN_ram_0004c756(param_1[1],1);
      return;
    }
  }
  return;
}

