/* Address: 00015bec; name: cmd_d0; body bytes: 174 */

uint cmd_d0(char *param_1,int param_2,char *param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  *param_3 = *param_1 + '\x01';
  uVar2 = (uint)(byte)(param_1[1] - 1);
  param_3[1] = param_1[1];
  uVar1 = 2;
  if ((byte)(&DAT_1fffa340)[uVar2] < 0x65) {
    uVar4 = 7;
  }
  else {
    uVar4 = 9;
  }
  uVar3 = 0;
  do {
    param_3[uVar1] = (&DAT_1fffa138)[uVar3 + uVar2 * 0x10];
    uVar3 = uVar3 + 1 & 0xff;
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar3 < 0x10);
  param_3[uVar1] = (&DAT_1fffa340)[uVar2];
  uVar1 = uVar1 + 1 & 0xff;
  param_3[uVar1] = (char)uVar4;
  for (uVar3 = 0; uVar1 = uVar1 + 1 & 0xff, uVar3 < uVar4; uVar3 = uVar3 + 1 & 0xff) {
    iVar5 = uVar2 * 0x24 + uVar3 * 4;
    param_3[uVar1] = (&DAT_1fffa1d8)[iVar5];
    uVar1 = uVar1 + 1 & 0xff;
    param_3[uVar1] = (&DAT_1fffa1d9)[iVar5];
    uVar1 = uVar1 + 1 & 0xff;
    param_3[uVar1] = (&DAT_1fffa1da)[iVar5];
    uVar1 = uVar1 + 1 & 0xff;
    param_3[uVar1] = (&DAT_1fffa1db)[iVar5];
  }
  if (param_4 == 6) {
    param_3[uVar1] = param_1[param_2 + -1];
    uVar1 = uVar1 + 1 & 0xff;
  }
  return uVar1;
}

