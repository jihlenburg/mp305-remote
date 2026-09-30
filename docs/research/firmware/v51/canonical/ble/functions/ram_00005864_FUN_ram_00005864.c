/* Address: ram:00005864; name: FUN_ram_00005864; body bytes: 652 */

undefined4 FUN_ram_00005864(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  uint uVar10;
  byte abStack_5c [8];
  ushort uStack_54;
  ushort uStack_52;
  undefined2 uStack_50;
  undefined2 uStack_4e;
  ushort uStack_4c;
  char cStack_4a;
  undefined1 uStack_48;
  undefined1 uStack_47;
  char cStack_46;
  short sStack_44;
  
  gp = &DAT_ram_20002000;
  FUN_ram_00001d1a(abStack_5c,0,0x1a);
  DAT_ram_20002fcd = 0;
  bVar3 = false;
  FUN_ram_00007ab4("----------------Analysis------------------");
  iVar9 = 0;
  do {
    while( true ) {
      if (param_2 <= iVar9) {
        return 0;
      }
      iVar7 = iVar9 + 1;
      pbVar8 = (byte *)(param_1 + iVar9);
      bVar1 = *pbVar8;
      uVar4 = (uint)bVar1;
      if ((bVar1 & 3) != 0) break;
      iVar9 = iVar7;
      if (uVar4 == 0xc0) {
        FUN_ram_00007ab4("------END_COLLECTION--------");
        if (bVar3) {
          DAT_ram_20002fcc = (undefined1)uStack_4c;
          DAT_ram_20002fce = (undefined1)sStack_44;
          FUN_ram_00007968("Button:%x,Wheel:%x,Num:%x\n",DAT_ram_20002fcd);
          return 0;
        }
        FUN_ram_00001d1a(abStack_5c,0,0x1a);
        bVar3 = false;
      }
    }
    bVar1 = bVar1 >> 4;
    uVar5 = (int)uVar4 >> 2 & 3;
    uVar10 = uVar4 & 3;
    do {
      bVar2 = pbVar8[1];
      uVar10 = uVar10 - 1 & 0xff;
      if (uVar5 != 1) {
        if (uVar5 == 2) {
          if (bVar1 == 0) {
            if (bVar2 == 2) {
              bVar3 = true;
            }
            else if (bVar2 == 0x30) {
              uStack_48 = 1;
              cStack_4a = cStack_4a + '\x01';
            }
            else if (bVar2 == 0x31) {
              uStack_47 = 1;
              cStack_4a = cStack_4a + '\x01';
            }
            else if (bVar2 == 0x38) {
              cStack_46 = '\x01';
              cStack_4a = cStack_4a + '\x01';
            }
          }
        }
        else if (uVar5 == 0) {
          if (bVar1 == 9) {
            FUN_ram_00007ab4("Output: ");
            uStack_4e = 1;
          }
          else if (bVar1 < 10) {
            if (bVar1 == 8) {
              FUN_ram_00007ab4("Input: ");
              uStack_50 = 1;
              uStack_4c = (ushort)((((int)((uint)uStack_52 * (uint)uStack_54) >> 3) +
                                   (uint)uStack_4c) * 0x10000 >> 0x10);
              if (cStack_46 != '\0') {
                sStack_44 = uStack_4c - 1;
                cStack_46 = '\0';
              }
              cStack_4a = '\0';
            }
          }
          else {
            if (bVar1 == 10) {
              pcVar6 = "Collection: ";
            }
            else {
              pcVar6 = "End Collection";
              if (bVar1 != 0xc) goto switchD_ram_00005908_caseD_5;
            }
LAB_ram_00005a56:
            FUN_ram_00007ab4(pcVar6);
          }
        }
        goto switchD_ram_00005908_caseD_5;
      }
      if (9 < bVar1) goto switchD_ram_00005908_caseD_5;
      switch(bVar1) {
      case 0:
        pcVar6 = "------USAGE_PAGE:Generic Desktop--------";
        if (bVar2 == 1) goto LAB_ram_00005a56;
        if (bVar2 == 9) {
          DAT_ram_20002fcd = (undefined1)uStack_4c;
        }
        goto switchD_ram_00005908_caseD_5;
      case 1:
        pcVar6 = "-GLOBAL_LOG_MIN:%x-\n";
        break;
      case 2:
        pcVar6 = "-GLOBAL_LOG_MAX:%x-\n";
        break;
      case 3:
        pcVar6 = "-GLOBAL_PHY_MIN:%x-\n";
        break;
      case 4:
        pcVar6 = "-GLOBAL_PHY_MAX:%x-\n";
        break;
      default:
        goto switchD_ram_00005908_caseD_5;
      case 7:
        FUN_ram_00007968("-GLOBAL_REPORT_SIZE:%x-\n");
        uStack_54 = (ushort)bVar2;
        goto switchD_ram_00005908_caseD_5;
      case 8:
        pcVar6 = "-GLOBAL_REPORT_ID:%x-\n";
        abStack_5c[0] = bVar2;
        break;
      case 9:
        FUN_ram_00007968("-GLOBAL_REPORT_CNT:%x-\n");
        uStack_52 = (ushort)bVar2;
        goto switchD_ram_00005908_caseD_5;
      }
      FUN_ram_00007968(pcVar6);
switchD_ram_00005908_caseD_5:
      pbVar8 = pbVar8 + 1;
    } while (uVar10 != 0);
    iVar9 = ((uVar4 & 3) - 1 & 0xff) + iVar9 + 2;
  } while( true );
}

