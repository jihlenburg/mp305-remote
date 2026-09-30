/* Address: ram:000065a0; name: FUN_ram_000065a0; body bytes: 698 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_ram_000065a0(undefined4 param_1,undefined1 *param_2,uint param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  short sVar7;
  uint uVar8;
  short *psVar9;
  undefined4 uStack_50;
  undefined2 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  
  gp = &DAT_ram_20002000;
  iVar5 = param_4 * 0x4e;
  uVar3 = 0;
  do {
    if (param_3 <= uVar3) {
      return;
    }
    uVar2 = (uint)(byte)param_2[uVar3];
    if (uVar2 == 0) {
      return;
    }
    if ((int)param_3 < (int)(uVar3 + uVar2)) {
      return;
    }
    bVar1 = (param_2 + uVar3)[1];
    psVar9 = (short *)(param_2 + uVar3 + 2);
    uVar8 = uVar2 - 1 & 0xff;
    if (bVar1 < 10) {
      if (bVar1 < 8) {
        if (bVar1 == 1) {
          (&DAT_ram_20004c58)[iVar5] = *param_2;
        }
        else if ((bVar1 != 0) && (bVar1 < 4)) {
          sVar7 = 0;
          psVar6 = psVar9;
          while ((int)psVar6 - (int)psVar9 < (int)uVar8) {
            sVar7 = *psVar6;
            psVar6 = psVar6 + 1;
            if (sVar7 == 0x1812) break;
            FUN_ram_00007968("16-bit UUID: 0x%04X\n",sVar7);
          }
          *(short *)(&DAT_ram_20004c5a + iVar5) = sVar7;
        }
      }
      else {
        (&DAT_ram_20004c7e)[iVar5] = (char)(uVar2 - 1);
        FUN_ram_000078b2(iVar5 + 0x20004c5f,psVar9,uVar8);
        FUN_ram_00004e1a(psVar9,uVar8,99);
      }
    }
    else if (bVar1 == 0x19) {
      sVar7 = 0;
      for (psVar6 = psVar9; (int)psVar6 - (int)psVar9 < (int)uVar8; psVar6 = psVar6 + 1) {
        sVar7 = *psVar6;
        FUN_ram_00007968("16-bit ad_type: %x\n",sVar7);
      }
      (&DAT_ram_20004c5c)[param_4 * 0x27] = sVar7;
    }
    else if (bVar1 == 0xff) {
      if ((2 < uVar8) && ((undefined *)(&DAT_ram_20004c5c)[param_4 * 0x27] == &pmpaddr18)) {
        FUN_ram_00007968("Manufacturer Data Len:%d\n",uVar8);
        iVar4 = 0;
        do {
          FUN_ram_00007968("%02X ",*(char *)((int)psVar9 + iVar4));
          iVar4 = iVar4 + 1;
        } while (iVar4 < (int)uVar8);
      }
      FUN_ram_000078b2(&DAT_ram_20004c7f + iVar5,psVar9,uVar8);
      if (((((char)*psVar9 == -0x46) && (*(char *)((int)psVar9 + 1) == -0x55)) &&
          ((char)psVar9[1] == -0x42)) && (*(char *)((int)psVar9 + 3) == -0x15)) {
        uStack_48 = 0;
        uStack_44 = 0;
        FUN_ram_200028d6(0xb,&LAB_ram_000069fe_2,&uStack_48,8);
        if ((uint)*(byte *)(psVar9 + 2) + (uint)*(byte *)((int)psVar9 + 5) +
            (uint)*(byte *)(psVar9 + 3) + (uint)*(byte *)((int)psVar9 + 7) == 0) {
          iVar4 = (*_DAT_ram_0004003c)
                            (&DAT_ram_20004c52 + iVar5,(int)&uStack_48 + 1,6,
                             (uint)*(byte *)((int)psVar9 + 7),_DAT_ram_0004003c);
          if ((iVar4 != 0) &&
             (iVar4 = (*_DAT_ram_0004003c)(&DAT_ram_20002f30,(int)&uStack_48 + 1,6), iVar4 != 0)) {
            DAT_ram_20002f30 = 0;
            DAT_ram_20002f34 = 0;
            FUN_ram_200028d6(9,&LAB_ram_000069fe_2,0,8);
          }
        }
        else {
          uStack_50 = 0;
          uStack_4c = 0;
          FUN_ram_200028d6(6,0x7f018,&uStack_50,0);
          iVar4 = (*_DAT_ram_0004003c)(&DAT_ram_20004c52 + iVar5,(int)&uStack_48 + 1,6);
          if ((iVar4 == 0) ||
             (iVar4 = (*_DAT_ram_0004003c)((char *)((int)psVar9 + 5),&uStack_50,6), iVar4 == 0)) {
            FUN_ram_00001d1a(&DAT_ram_20004c50 + iVar5,0,0x4e);
          }
        }
      }
    }
    uVar3 = uVar3 + uVar2 + 1 & 0xff;
  } while( true );
}

