/* Address: 0001c73c; name: cmd_da; body bytes: 354 */

undefined4 cmd_da(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  undefined4 uVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;
  uint uVar10;
  
  *param_3 = *param_1 + '\x01';
  uVar9 = 0;
  bVar1 = param_1[1];
  uVar4 = 2;
  cVar3 = '\0';
  if ((bVar1 < 10) && (bVar1 != 0)) {
    do {
      if ((&DAT_1fffa3fe)[uVar9] == bVar1) {
        DAT_1fffa8cb = (byte)uVar9;
        if (uVar9 < 10) goto LAB_0001c77e;
        break;
      }
      uVar9 = uVar9 + 1 & 0xff;
    } while (uVar9 < 10);
    cVar3 = -1;
LAB_0001c77e:
    bVar1 = (&DAT_1fffa3f4)[DAT_1fffa8cb];
    if ((uint)DAT_1fffa8cc < (uint)bVar1) {
      if (cVar3 == '\0') {
        bVar8 = 0;
        do {
          uVar9 = uVar4 + 1 & 0xff;
          uVar5 = uVar9 + 1 & 0xff;
          uVar6 = uVar5 + 1 & 0xff;
          uVar7 = uVar6 + 1 & 0xff;
          uVar10 = CONCAT13(param_1[uVar6],
                            CONCAT12(param_1[uVar5],CONCAT11(param_1[uVar9],param_1[uVar4])));
          uVar4 = uVar7 + 1 & 0xff;
          uVar9 = uVar4 + 1 & 0xff;
          uVar5 = uVar9 + 1 & 0xff;
          uVar6 = uVar5 + 1 & 0xff;
          uVar7 = CONCAT13(param_1[uVar5],
                           CONCAT12(param_1[uVar9],CONCAT11(param_1[uVar4],param_1[uVar7])));
          uVar4 = uVar6 + 1 & 0xff;
          uVar9 = uVar4 + 1 & 0xff;
          uVar5 = uVar9 + 1 & 0xff;
          uVar9 = CONCAT13(param_1[uVar5],
                           CONCAT12(param_1[uVar9],CONCAT11(param_1[uVar4],param_1[uVar6])));
          uVar4 = uVar5 + 1 & 0xff;
          if (0x7724 < uVar10) goto LAB_0001c87a;
          if (uVar7 < 0x13ed) {
            if (0x18696 < uVar9) goto LAB_0001c87a;
          }
          else if (uVar9 != 0) goto LAB_0001c87a;
          uVar5 = (uint)DAT_1fffa8cc;
          *(uint *)(&DAT_1fff8f7c + uVar5 * 0xc) = uVar10;
          *(uint *)(&DAT_1fff8f80 + uVar5 * 0xc) = uVar7;
          *(uint *)(&DAT_1fff8f84 + uVar5 * 0xc) = uVar9;
          DAT_1fffa8cc = (byte)(uVar5 + 1);
          if ((uint)bVar1 <= (uVar5 + 1 & 0xff)) {
            DAT_1fffa8c8 = 1;
            return 0;
          }
          bVar8 = bVar8 + 1;
        } while (bVar8 < 10);
        goto LAB_0001c888;
      }
    }
    else if (cVar3 == '\0') goto LAB_0001c888;
  }
  else {
LAB_0001c87a:
    cVar3 = -1;
  }
  DAT_1fffab17 = 2;
LAB_0001c888:
  param_3[1] = cVar3;
  uVar2 = 2;
  if (param_4 == 6) {
    param_3[2] = param_1[param_2 + -1];
    uVar2 = 3;
  }
  return uVar2;
}

