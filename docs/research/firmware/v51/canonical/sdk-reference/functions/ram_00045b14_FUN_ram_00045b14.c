/* Address: ram:00045b14; name: FUN_ram_00045b14; body bytes: 602 */

bool FUN_ram_00045b14(byte *param_1)

{
  char cVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  undefined1 auStack_32 [10];
  
  gp = 0x20004000;
  if (*param_1 == 1) {
    bVar6 = 0;
    pbVar2 = (byte *)0x0;
  }
  else {
    pbVar2 = (byte *)FUN_ram_00044162(1,auStack_32,param_1[8],param_1 + 9);
    bVar6 = 0;
    if (pbVar2 != (byte *)0x0) {
      bVar6 = *pbVar2;
    }
  }
  if ((((*param_1 != 4) && (cVar1 = *(char *)(DAT_ram_20001a04 + 1), cVar1 != '\x03')) &&
      (bVar6 != 0)) && (cVar1 != '\0')) {
    if (pbVar2 == (byte *)0x0) {
      gp = 0x20004000;
      return false;
    }
    if (cVar1 == '\x01') {
      bVar6 = bVar6 & 3;
    }
    else {
      if (cVar1 != '\x02') {
        gp = 0x20004000;
        return false;
      }
      bVar6 = bVar6 & 1;
    }
    if (bVar6 == 0) {
      gp = 0x20004000;
      return false;
    }
  }
  pbVar2 = param_1 + 2;
  uVar3 = FUN_ram_00044326(param_1[1],pbVar2);
  param_1[1] = (byte)uVar3;
  uVar7 = 0;
  if (DAT_ram_20001a08 == (byte *)0x0) {
    gp = 0x20004000;
    return true;
  }
  do {
    if (DAT_ram_20001a02 <= uVar7) {
LAB_ram_00045c0a:
      if ((*param_1 != 4) && (DAT_ram_20001a08 != (byte *)0x0)) {
        pbVar4 = DAT_ram_20001a08;
        for (bVar6 = 0; DAT_ram_20001a02 != bVar6; bVar6 = bVar6 + 1) {
          if (*pbVar4 == 0xff) {
            *pbVar4 = *param_1;
            pbVar4[1] = param_1[1];
            tmos_memcpy(pbVar4 + 2,pbVar2,6);
            pbVar2 = (byte *)FUN_ram_20000040(param_1[8] + 1,0x471f);
            if (pbVar2 != (byte *)0x0) {
              if (*param_1 == 4) {
                *(byte **)(pbVar4 + 0xc) = pbVar2;
              }
              else {
                *(byte **)(pbVar4 + 8) = pbVar2;
              }
              *pbVar2 = param_1[8];
              tmos_memcpy(pbVar2 + 1,param_1 + 9,param_1[8]);
            }
            if (param_1[8] != 0) {
              gp = 0x20004000;
              return true;
            }
            iVar5 = *param_1 - 1;
LAB_ram_00045d68:
            gp = 0x20004000;
            return iVar5 == 0;
          }
          pbVar4 = pbVar4 + 0x10;
        }
      }
      return false;
    }
    pbVar4 = DAT_ram_20001a08 + uVar7 * 0x10;
    if (((*pbVar4 != 0xff) && (pbVar4[1] == uVar3)) &&
       (iVar5 = tmos_memcmp(pbVar4 + 2,pbVar2,6), iVar5 != 0)) {
      pbVar4 = DAT_ram_20001a08 + uVar7 * 0x10;
      if (pbVar4 != (byte *)0x0) {
        if (*param_1 == 4) {
          pbVar2 = *(byte **)(pbVar4 + 0xc);
        }
        else {
          pbVar2 = *(byte **)(pbVar4 + 8);
        }
        if (pbVar2 != (byte *)0x0) {
          if ((*pbVar2 == param_1[8]) && (iVar5 = tmos_memcmp(pbVar2 + 1,param_1 + 9), iVar5 == 1))
          {
            iVar5 = GAP_GetParamValue(0x15);
            goto LAB_ram_00045d68;
          }
          if (*param_1 == 4) {
            if (*(int *)(pbVar4 + 0xc) != 0) {
              FUN_ram_20000104();
              pbVar4[0xc] = 0;
              pbVar4[0xd] = 0;
              pbVar4[0xe] = 0;
              pbVar4[0xf] = 0;
            }
          }
          else if (*(int *)(pbVar4 + 8) != 0) {
            FUN_ram_20000104();
            pbVar4[8] = 0;
            pbVar4[9] = 0;
            pbVar4[10] = 0;
            pbVar4[0xb] = 0;
          }
        }
        pbVar2 = (byte *)FUN_ram_20000040(param_1[8] + 1,0x471e);
        if (pbVar2 != (byte *)0x0) {
          if (*param_1 == 4) {
            *(byte **)(pbVar4 + 0xc) = pbVar2;
          }
          else {
            *(byte **)(pbVar4 + 8) = pbVar2;
          }
          *pbVar2 = param_1[8];
          tmos_memcpy(pbVar2 + 1,param_1 + 9,param_1[8]);
        }
        gp = 0x20004000;
        return param_1[8] != 0;
      }
      goto LAB_ram_00045c0a;
    }
    uVar7 = uVar7 + 1 & 0xff;
  } while( true );
}

