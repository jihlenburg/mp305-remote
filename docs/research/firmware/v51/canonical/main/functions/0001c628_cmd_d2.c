/* Address: 0001c628; name: cmd_d2; body bytes: 258 */

undefined4 cmd_d2(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  
  *param_3 = *param_1 + '\x01';
  DAT_1fffa8c5 = param_1[1] - 1;
  uVar6 = (uint)DAT_1fffa8c5;
  cVar9 = '\0';
  uVar5 = 2;
  if (uVar6 < 10) {
    uVar7 = 0;
    do {
      (&DAT_1fffa138)[uVar7 + uVar6 * 0x10] = param_1[uVar5];
      uVar7 = uVar7 + 1 & 0xff;
      uVar5 = uVar5 + 1 & 0xff;
    } while (uVar7 < 0x10);
    uVar7 = uVar5 + 1 & 0xff;
    (&DAT_1fffa340)[uVar6] = param_1[uVar5];
    bVar1 = param_1[uVar7];
    uVar5 = uVar7 + 1 & 0xff;
    cVar2 = param_1[uVar5];
    uVar7 = uVar5 + 1 & 0xff;
    uVar5 = 0;
    do {
      if (uVar5 < bVar1) {
        iVar3 = uVar5 * 4 + uVar6 * 0x24;
        uVar8 = uVar7 + 1 & 0xff;
        (&DAT_1fffa138)[iVar3 + 0xa0] = param_1[uVar7];
        uVar7 = uVar8 + 1 & 0xff;
        (&DAT_1fffa138)[iVar3 + 0xa1] = param_1[uVar8];
        uVar8 = uVar7 + 1 & 0xff;
        (&DAT_1fffa138)[iVar3 + 0xa2] = param_1[uVar7];
        (&DAT_1fffa138)[iVar3 + 0xa3] = param_1[uVar8];
        uVar7 = uVar8 + 1 & 0xff;
      }
      else {
        iVar3 = uVar5 * 4 + uVar6 * 0x24;
        *(ushort *)(&DAT_1fffa138 + iVar3 + 0xa0) =
             *(ushort *)(&DAT_1fffa138 + iVar3 + 0xa0) & 0xfff8;
      }
      uVar5 = uVar5 + 1 & 0xff;
    } while (uVar5 < 9);
    if (uVar6 == DAT_1fffa34a) {
      DAT_1fffaaf3 = 1;
    }
    if (cVar2 != '\0') {
      DAT_1fffa8c4 = 1;
    }
  }
  else {
    cVar9 = -1;
    DAT_1fffab17 = 2;
  }
  param_3[1] = cVar9;
  uVar4 = 2;
  if (param_4 == 6) {
    param_3[2] = param_1[param_2 + -1];
    uVar4 = 3;
  }
  return uVar4;
}

