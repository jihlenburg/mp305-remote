/* Address: 00015e48; name: cmd_d4; body bytes: 124 */

uint cmd_d4(char *param_1,int param_2,char *param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  
  *param_3 = *param_1 + '\x01';
  param_3[1] = DAT_1fffa409;
  uVar1 = 2;
  bVar4 = 1;
  do {
    if (DAT_1fffa409 < bVar4) {
      if (param_4 == 6) {
        param_3[uVar1] = param_1[param_2 + -1];
        uVar1 = uVar1 + 1 & 0xff;
      }
      return uVar1;
    }
    uVar2 = 0;
    while ((&DAT_1fffa3fe)[uVar2] != bVar4) {
      uVar2 = uVar2 + 1 & 0xff;
      if (9 < uVar2) goto LAB_00015ea2;
    }
    uVar3 = 0;
    do {
      param_3[uVar1] = (&DAT_1fffa354)[uVar3 + uVar2 * 0x10];
      uVar3 = uVar3 + 1 & 0xff;
      uVar1 = uVar1 + 1 & 0xff;
    } while (uVar3 < 0x10);
    param_3[uVar1] = (&DAT_1fffa3f4)[uVar2];
    uVar1 = uVar1 + 1 & 0xff;
LAB_00015ea2:
    bVar4 = bVar4 + 1;
  } while( true );
}

