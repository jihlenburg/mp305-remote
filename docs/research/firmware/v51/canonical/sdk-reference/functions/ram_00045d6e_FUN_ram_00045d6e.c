/* Address: ram:00045d6e; name: FUN_ram_00045d6e; body bytes: 636 */

undefined4 FUN_ram_00045d6e(char *param_1)

{
  uint uVar1;
  byte *pbVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  byte bVar6;
  ushort uVar7;
  char *pcVar8;
  char *pcVar9;
  uint uVar10;
  undefined1 auStack_32 [14];
  
  gp = 0x20004000;
  pcVar8 = param_1 + 2;
  uVar1 = FUN_ram_00044326(param_1[1],pcVar8);
  param_1[1] = (char)uVar1;
  if ((*(char *)(DAT_ram_20001a04 + 1) == '\x03') || (*(char *)(DAT_ram_20001a04 + 1) == '\0')) {
LAB_ram_00045dac:
    uVar10 = 0;
    if (DAT_ram_20001a08 != (char *)0x0) {
      for (; (uVar10 & 0xffff) < (uint)DAT_ram_20001a02; uVar10 = uVar10 + 1) {
        pcVar4 = DAT_ram_20001a08 + uVar10 * 0x10;
        if (((*pcVar4 == *param_1) && ((byte)pcVar4[1] == uVar1)) &&
           (iVar5 = tmos_memcmp(pcVar4 + 2,pcVar8,6), iVar5 != 0)) {
          pcVar4 = DAT_ram_20001a08 + uVar10 * 0x10;
          if ((*param_1 == '\x04') || (*param_1 == '\v')) {
            pcVar9 = *(char **)(pcVar4 + 0xc);
          }
          else {
            pcVar9 = *(char **)(pcVar4 + 8);
          }
          if ((*pcVar9 == param_1[0x17]) &&
             (iVar5 = tmos_memcmp(pcVar9 + 1,*(undefined4 *)(param_1 + 0x18)), iVar5 == 1)) {
            iVar5 = GAP_GetParamValue(0x15);
            if (iVar5 != 0) goto LAB_ram_00045e10;
          }
          else {
            FUN_ram_20000104(pcVar9);
            pcVar9 = (char *)FUN_ram_20000040((byte)param_1[0x17] + 1,0x471e);
            if (pcVar9 != (char *)0x0) {
              if ((*param_1 == '\x04') || (*param_1 == '\v')) {
                *(char **)(pcVar4 + 0xc) = pcVar9;
              }
              else {
                *(char **)(pcVar4 + 8) = pcVar9;
              }
              *pcVar9 = param_1[0x17];
              tmos_memcpy(pcVar9 + 1,*(undefined4 *)(param_1 + 0x18),param_1[0x17]);
            }
          }
          if (pcVar4 != (char *)0x0) goto LAB_ram_00045f16;
          break;
        }
      }
      pcVar4 = DAT_ram_20001a08;
      for (uVar7 = 0; uVar7 < DAT_ram_20001a02; uVar7 = uVar7 + 1) {
        if (*pcVar4 == -1) {
          *pcVar4 = *param_1;
          pcVar4[1] = param_1[1];
          tmos_memcpy(pcVar4 + 2,pcVar8,6);
          pcVar8 = (char *)FUN_ram_20000040((byte)param_1[0x17] + 1,0x471f);
          if (pcVar8 != (char *)0x0) {
            if (*param_1 == '\x04') {
              *(char **)(pcVar4 + 0xc) = pcVar8;
            }
            else {
              *(char **)(pcVar4 + 8) = pcVar8;
            }
            *pcVar8 = param_1[0x17];
            tmos_memcpy(pcVar8 + 1,*(undefined4 *)(param_1 + 0x18),param_1[0x17]);
          }
          break;
        }
        pcVar4 = pcVar4 + 0x10;
      }
    }
LAB_ram_00045f16:
    uVar3 = 1;
  }
  else {
    pbVar2 = (byte *)FUN_ram_00044162(1,auStack_32,param_1[0x17],*(undefined4 *)(param_1 + 0x18));
    if (pbVar2 == (byte *)0x0) {
      if (((*param_1 == '\x04') || (*param_1 == '\v')) && (DAT_ram_20001a08 != (char *)0x0)) {
        pcVar4 = (char *)0x0;
        for (uVar10 = 0; (uVar10 & 0xffff) < (uint)DAT_ram_20001a02; uVar10 = uVar10 + 1) {
          pcVar9 = DAT_ram_20001a08 + uVar10 * 0x10;
          if (((*pcVar9 == *param_1) && ((byte)pcVar9[1] == uVar1)) &&
             (iVar5 = tmos_memcmp(pcVar9 + 2,pcVar8,6), iVar5 != 0)) {
            pcVar4 = DAT_ram_20001a08 + uVar10 * 0x10;
          }
        }
        if (pcVar4 != (char *)0x0) goto LAB_ram_00045dac;
      }
    }
    else {
      if (*(char *)(DAT_ram_20001a04 + 1) == '\x01') {
        bVar6 = *pbVar2 & 3;
      }
      else {
        bVar6 = *pbVar2 & 1;
        if (*(char *)(DAT_ram_20001a04 + 1) != '\x02') goto LAB_ram_00045dac;
      }
      if (bVar6 != 0) goto LAB_ram_00045dac;
    }
LAB_ram_00045e10:
    uVar3 = 0;
  }
  return uVar3;
}

