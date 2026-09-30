/* Address: 0001c8b8; name: cmd_d6; body bytes: 412 */

undefined4 cmd_d6(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  bool bVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  char cVar11;
  
  uVar8 = 0;
  *param_3 = *param_1 + '\x01';
  bVar1 = param_1[1];
  uVar9 = 2;
  cVar11 = '\0';
  bVar6 = false;
  if ((bVar1 < 0xb) && (bVar1 != 0)) {
    do {
      if ((&DAT_1fffa3fe)[uVar8] == bVar1) {
        if (uVar8 < 10) goto LAB_0001c912;
        break;
      }
      uVar8 = uVar8 + 1 & 0xff;
    } while (uVar8 < 10);
    uVar8 = 0;
    do {
      if ((&DAT_1fffa3fe)[uVar8] == '\0') {
        (&DAT_1fffa3fe)[uVar8] = bVar1;
        DAT_1fffa409 = DAT_1fffa409 + '\x01';
        break;
      }
      uVar8 = uVar8 + 1 & 0xff;
    } while (uVar8 < 10);
LAB_0001c912:
    uVar10 = 0;
    do {
      (&DAT_1fffa354)[uVar10 + uVar8 * 0x10] = param_1[uVar9];
      uVar10 = uVar10 + 1 & 0xff;
      uVar9 = uVar9 + 1 & 0xff;
    } while (uVar10 < 0x10);
    (&DAT_1fffa3f4)[uVar8] = param_1[uVar9];
    uVar9 = uVar9 + 1 & 0xff;
    uVar5 = (undefined1)uVar8;
    cVar2 = param_1[uVar9];
    cVar3 = param_1[uVar9 + 1 & 0xff];
    DAT_1fffa8c7 = cVar3;
    DAT_1fffa8cb = uVar5;
    if ((cVar3 == '\x01') && (DAT_1fffa409 != '\0')) {
      DAT_1fffa409 = DAT_1fffa409 + -1;
      uVar9 = 0;
      do {
        bVar4 = (&DAT_1fffa3fe)[uVar9];
        if (bVar4 == bVar1) {
          (&DAT_1fffa3f4)[uVar9] = 0;
          (&DAT_1fffa3fe)[uVar9] = 0;
          if (DAT_1fffa408 == uVar9) {
            bVar6 = true;
          }
        }
        else if (bVar1 < bVar4) {
          (&DAT_1fffa3fe)[uVar9] = bVar4 - 1;
        }
        uVar9 = uVar9 + 1 & 0xff;
      } while (uVar9 < 10);
      if (DAT_1fffa409 == '\0') {
        DAT_1fffaaf0 = 0;
        DAT_1fffaaed = 0;
        DAT_1fffaaef = 1;
      }
      if (bVar6) {
        uVar9 = 0;
        do {
          if ((&DAT_1fffa3fe)[uVar9] == '\x01') {
            DAT_1fffaaf0 = (undefined1)uVar9;
            DAT_1fffaaed = 0;
            DAT_1fffaaef = 1;
          }
          uVar9 = uVar9 + 1 & 0xff;
        } while (uVar9 < 10);
      }
    }
    if (cVar2 != '\0') {
      if (cVar3 == '\x02') {
        DAT_1fffa8c6 = 1;
        goto LAB_0001ca36;
      }
      DAT_1fffa8c6 = 2;
    }
    if (((cVar3 == '\0') && (uVar8 == DAT_1fffa408)) && ((&DAT_1fffa3f4)[uVar8] == '\0')) {
      DAT_1fffaaed = 0;
      DAT_1fffaaef = 1;
      DAT_1fffaaf0 = uVar5;
    }
  }
  else {
    cVar11 = -1;
  }
LAB_0001ca36:
  param_3[1] = cVar11;
  uVar7 = 2;
  if (param_4 == 6) {
    param_3[2] = param_1[param_2 + -1];
    uVar7 = 3;
  }
  return uVar7;
}

