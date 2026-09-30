/* Address: ram:0004b062; name: FUN_ram_0004b062; body bytes: 746 */

int FUN_ram_0004b062(undefined4 param_1,char *param_2,undefined4 param_3,undefined1 *param_4,
                    ushort *param_5,uint param_6,int param_7,undefined4 param_8)

{
  byte bVar1;
  short sVar2;
  undefined2 uVar3;
  undefined4 *puVar4;
  int iVar5;
  code *pcVar6;
  byte *pbVar7;
  undefined1 *puVar8;
  ushort uVar9;
  undefined2 *puVar10;
  char *pcVar11;
  undefined2 uStack_34;
  undefined2 auStack_32 [5];
  
  gp = 0x20004000;
  if ((param_2[8] & 0x10U) == 0) {
LAB_ram_0004b090:
    if (*param_2 != '\x02') goto LAB_ram_0004b09a;
    sVar2 = **(short **)(param_2 + 4);
    if (sVar2 == 0x2900) {
LAB_ram_0004b32c:
      if (param_6 != 0) {
        gp = 0x20004000;
        return 0xb;
      }
      puVar8 = *(undefined1 **)(param_2 + 0xc);
      *param_5 = 2;
      *param_4 = *puVar8;
      param_4[1] = *(undefined1 *)(*(int *)(param_2 + 0xc) + 1);
    }
    else if (sVar2 < 0x2901) {
      if (sVar2 == 0x2802) {
        if (param_6 != 0) {
          gp = 0x20004000;
          return 0xb;
        }
        puVar10 = *(undefined2 **)(param_2 + 0xc);
        uVar3 = *puVar10;
        *param_5 = 4;
        *param_4 = *(undefined1 *)puVar10;
        param_4[1] = *(undefined1 *)(*(int *)(param_2 + 0xc) + 1);
        puVar8 = (undefined1 *)GATT_FindHandle(uVar3,&uStack_34);
        if (puVar8 != (undefined1 *)0x0) {
          pcVar11 = *(char **)(puVar8 + 0xc);
          iVar5 = FUN_ram_0004afa0(puVar8,0xffff,uStack_34,auStack_32);
          if ((iVar5 == 0) &&
             (iVar5 = ATT_CompareUUID(&DAT_ram_0006c660,2,*(undefined4 *)(puVar8 + 4),*puVar8),
             iVar5 == 0)) {
            auStack_32[0] = 0xffff;
          }
          uVar3 = auStack_32[0];
          if (*pcVar11 == '\x02') {
            tmos_memcpy(param_4 + 4,*(undefined4 *)(pcVar11 + 4),2);
            *param_5 = *param_5 + 2;
            uVar3 = auStack_32[0];
          }
        }
        auStack_32[0] = uVar3;
        param_4[2] = (char)auStack_32[0];
        param_4[3] = (char)((ushort)auStack_32[0] >> 8);
      }
      else if (sVar2 < 0x2803) {
        if (sVar2 < 0x2800) {
LAB_ram_0004b09a:
          puVar4 = (undefined4 *)FUN_ram_0004a156(param_3);
          if ((puVar4 != (undefined4 *)0x0) && ((code *)*puVar4 != (code *)0x0)) {
            iVar5 = (*(code *)*puVar4)(param_1,param_2,param_4,param_5,param_6,param_7,param_8);
            gp = 0x20004000;
            return iVar5;
          }
          goto LAB_ram_0004b0c6;
        }
        if (param_6 != 0) {
          gp = 0x20004000;
          return 0xb;
        }
        bVar1 = **(byte **)(param_2 + 0xc);
        uVar9 = (ushort)bVar1;
        iVar5 = *(int *)(*(byte **)(param_2 + 0xc) + 4);
        *param_5 = (ushort)bVar1;
LAB_ram_0004b2be:
        tmos_memcpy(param_4,iVar5,uVar9);
      }
      else {
        if (sVar2 != 0x2803) goto LAB_ram_0004b09a;
        if (param_6 != 0) {
          gp = 0x20004000;
          return 0xb;
        }
        *param_5 = 1;
        *param_4 = **(undefined1 **)(param_2 + 0xc);
        pbVar7 = (byte *)GATT_FindHandle(*(short *)(param_2 + 10) + 1,0);
        if (pbVar7 != (byte *)0x0) {
          *param_5 = *param_5 + 2 + (ushort)*pbVar7;
          param_4[1] = (char)*(undefined2 *)(pbVar7 + 10);
          param_4[2] = (char)((ushort)*(undefined2 *)(pbVar7 + 10) >> 8);
          uVar9 = (ushort)*pbVar7;
          iVar5 = *(int *)(pbVar7 + 4);
          param_4 = param_4 + 3;
          goto LAB_ram_0004b2be;
        }
        *param_5 = *param_5 + 4;
        tmos_memset(param_4 + 1,0,4);
      }
    }
    else if (sVar2 == 0x2902) {
      if (param_6 != 0) {
        gp = 0x20004000;
        return 0xb;
      }
      uVar3 = GATTServApp_ReadCharCfg(param_1,*(undefined4 *)(param_2 + 0xc));
      *param_5 = 2;
      *param_4 = (char)uVar3;
      param_4[1] = (char)((ushort)uVar3 >> 8);
    }
    else {
      if (sVar2 < 0x2902) {
        uVar9 = tmos_strlen(*(undefined4 *)(param_2 + 0xc));
        if (uVar9 < param_6) {
          gp = 0x20004000;
          return 7;
        }
        if (param_6 == uVar9) {
          *param_5 = 0;
        }
        else if ((int)(param_7 + param_6) < (int)(uint)uVar9) {
          *param_5 = (ushort)param_7;
        }
        else {
          *param_5 = uVar9 - (short)param_6;
        }
        uVar9 = *param_5;
        iVar5 = *(int *)(param_2 + 0xc) + param_6;
        goto LAB_ram_0004b2be;
      }
      if (sVar2 == 0x2903) goto LAB_ram_0004b32c;
      if (sVar2 != 0x2904) goto LAB_ram_0004b09a;
      if (param_6 != 0) {
        gp = 0x20004000;
        return 0xb;
      }
      puVar8 = *(undefined1 **)(param_2 + 0xc);
      *param_5 = 7;
      *param_4 = *puVar8;
      param_4[1] = puVar8[1];
      param_4[2] = (char)*(undefined2 *)(puVar8 + 2);
      param_4[3] = (char)((ushort)*(undefined2 *)(puVar8 + 2) >> 8);
      param_4[4] = puVar8[4];
      param_4[5] = (char)*(undefined2 *)(puVar8 + 6);
      param_4[6] = (char)((ushort)*(undefined2 *)(puVar8 + 6) >> 8);
    }
    iVar5 = 0;
  }
  else {
    pcVar6 = (code *)FUN_ram_0004a174(param_3);
    if (pcVar6 != (code *)0x0) {
      iVar5 = (*pcVar6)(param_1,param_2,10);
      if (iVar5 != 0) {
        gp = 0x20004000;
        return iVar5;
      }
      goto LAB_ram_0004b090;
    }
LAB_ram_0004b0c6:
    iVar5 = 0xe;
  }
  return iVar5;
}

