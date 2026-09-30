
// ==== FUN_ram_000010ce @ ram:000010ce size 64 callers []

void FUN_ram_000010ce(void)

{
  uint uVar1;
  
  FUN_ram_000018de(4,0,0,0);
  FLASH_CONTROL._2_1_ = 4;
  uVar1 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar1 & 0xfffffffb;
  uVar1 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar1 & 0xfffffff7;
  wfi();
  return;
}



// ==== FUN_ram_0000110e @ ram:0000110e size 206 callers []

void FUN_ram_0000110e(void)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  
  FUN_ram_000018de(4,0,0,0);
  FLASH_CONTROL._2_1_ = 4;
  bVar4 = OSC32K_CTRL._2_1_;
  bVar2 = OSC32M_CTRL._2_1_;
  uVar1 = RTC_CNT_32K._0_2_;
  if (0x3fff < uVar1) {
    bVar4 = bVar4 & 0xfc | 1;
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  BATTERY_CTRL._0_1_ = 0;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32K_CTRL._2_1_ = bVar4;
  OSC32M_CTRL._2_1_ = bVar2 | 3;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 | 0x20;
  SAFE_ACCESS._0_1_ = 0;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 | 4;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 & 0xfffffff7;
  wfi();
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 & 0xdf;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_000011dc @ ram:000011dc size 304 callers []

void FUN_ram_000011dc(ushort param_1)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  int local_20;
  undefined2 uStack_1c;
  int iStack_18;
  undefined2 uStack_14;
  
  local_20 = 0;
  uStack_1c = 0;
  FUN_ram_000018de(6,0x7f018,&local_20,0);
  bVar4 = OSC32K_CTRL._2_1_;
  bVar2 = OSC32M_CTRL._2_1_;
  uVar1 = RTC_CNT_32K._0_2_;
  if (0x3fff < uVar1) {
    bVar4 = bVar4 & 0xfc | 1;
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  BATTERY_CTRL._0_1_ = 0;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32K_CTRL._2_1_ = bVar4;
  OSC32M_CTRL._2_1_ = bVar2 | 3;
  SAFE_ACCESS._0_1_ = 0;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 | 4;
  uVar1 = POWER_MANAG._0_2_;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = SLEEP_CONTROL._3_1_;
  SLEEP_CONTROL._3_1_ = bVar4 | 0x40;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 | 0x20;
  POWER_MANAG._0_2_ = uVar1 & 0x600 | param_1 | 0x9004;
  do {
    uVar3 = DAT_ram_e000ed10;
    DAT_ram_e000ed10 = uVar3 & 0xfffffff7;
    wfi();
    FUN_ram_000015fc(0x46);
    iStack_18 = 0;
    uStack_14 = 0;
    FUN_ram_000018de(6,0x7f018,&iStack_18,0);
  } while (iStack_18 != local_20);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 & 0xdf;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_0000130c @ ram:0000130c size 250 callers []

void FUN_ram_0000130c(ushort param_1)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  
  FUN_ram_000018de(4,0,0,0);
  bVar4 = OSC32K_CTRL._2_1_;
  bVar2 = OSC32M_CTRL._2_1_;
  uVar1 = RTC_CNT_32K._0_2_;
  if (0x3fff < uVar1) {
    bVar4 = bVar4 & 0xfc | 1;
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  BATTERY_CTRL._0_1_ = 0;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32K_CTRL._2_1_ = bVar4;
  OSC32M_CTRL._2_1_ = bVar2 | 3;
  SAFE_ACCESS._0_1_ = 0;
  FUN_ram_00001406(0x25);
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 | 4;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = SLEEP_CONTROL._3_1_;
  SLEEP_CONTROL._3_1_ = bVar4 | 0x40;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  POWER_MANAG._0_2_ = param_1 | 0x9000;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 & 0xfffffff7;
  wfi();
  FUN_ram_000018de(4,0,0,0);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = GLOBAL_CONFIG._2_1_;
  GLOBAL_CONFIG._2_1_ = bVar4 | 1;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_00001406 @ ram:00001406 size 372 callers [ram:0000130c]

void FUN_ram_00001406(uint param_1)

{
  ushort uVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar2 & 0xdf;
  SAFE_ACCESS._0_1_ = 0;
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 0x40) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      uVar1 = CLOCK_CONFIG._0_2_;
      CLOCK_CONFIG._0_2_ = uVar1 | 0xc0;
      goto LAB_ram_000014aa;
    }
    bVar2 = CLOCK_CONFIG._2_1_;
    if ((bVar2 & 0x10) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      bVar2 = CLOCK_CONFIG._2_1_;
      CLOCK_CONFIG._2_1_ = bVar2 | 0x10;
      iVar4 = 2000;
      do {
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    CLOCK_CONFIG._0_2_ = (ushort)param_1 & 0x1f | 0x40;
    SAFE_ACCESS._0_1_ = 0;
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    if (param_1 == 0x46) {
      uVar3 = 2;
    }
    else {
      uVar3 = 0x52;
    }
  }
  else {
    bVar2 = CLOCK_CONFIG._2_1_;
    if ((bVar2 & 4) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      bVar2 = CLOCK_CONFIG._2_1_;
      CLOCK_CONFIG._2_1_ = bVar2 | 4;
      iVar4 = 0x4b0;
      do {
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    CLOCK_CONFIG._0_2_ = (ushort)param_1 & 0x1f;
    SAFE_ACCESS._0_1_ = 0;
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    uVar3 = 0x51;
  }
  FLASH_CONTROL._3_1_ = uVar3;
  SAFE_ACCESS._0_1_ = 0;
LAB_ram_000014aa:
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar2 | 0x80;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_0000157a @ ram:0000157a size 60 callers []

void FUN_ram_0000157a(void)

{
  byte bVar1;
  
  FUN_ram_000018de(4,0,0,0);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar1 = GLOBAL_CONFIG._2_1_;
  GLOBAL_CONFIG._2_1_ = bVar1 | 1;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_000015fc @ ram:000015fc size 14 callers [ram:000011dc,ram:0000160a]

void FUN_ram_000015fc(int param_1)

{
  param_1 = param_1 * 0xf;
  do {
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  return;
}



// ==== FUN_ram_0000160a @ ram:0000160a size 40 callers []

void FUN_ram_0000160a(uint param_1)

{
  uint uVar1;
  
  for (uVar1 = 0; uVar1 != param_1; uVar1 = uVar1 + 1 & 0xffff) {
    FUN_ram_000015fc(1000);
  }
  return;
}



// ==== FUN_ram_00001822 @ ram:00001822 size 18 callers [ram:0000185e,ram:000018a6,ram:000018de]

void FUN_ram_00001822(undefined1 param_1)

{
  int unaff_s0;
  
  *(undefined1 *)(unaff_s0 + -0x7fa) = 0;
  *(undefined1 *)(unaff_s0 + -0x7fa) = 5;
  *(undefined1 *)(unaff_s0 + -0x7fc) = param_1;
  return;
}



// ==== FUN_ram_00001834 @ ram:00001834 size 14 callers [ram:0000185e,ram:000018a6,ram:000018de]

void FUN_ram_00001834(void)

{
  int unaff_s0;
  
  do {
  } while (*(char *)(unaff_s0 + -0x7fa) < '\0');
  *(undefined1 *)(unaff_s0 + -0x7fa) = 0;
  return;
}



// ==== FUN_ram_00001842 @ ram:00001842 size 14 callers [ram:000018a6,ram:000018de]

undefined1 FUN_ram_00001842(void)

{
  int unaff_s0;
  
  do {
  } while (*(char *)(unaff_s0 + -0x7fa) < '\0');
  return *(undefined1 *)(unaff_s0 + -0x7fc);
}



// ==== FUN_ram_00001850 @ ram:00001850 size 14 callers [ram:0000185e,ram:000018de]

void FUN_ram_00001850(undefined1 param_1)

{
  int unaff_s0;
  
  do {
  } while (*(char *)(unaff_s0 + -0x7fa) < '\0');
  *(undefined1 *)(unaff_s0 + -0x7fc) = param_1;
  return;
}



// ==== FUN_ram_0000185e @ ram:0000185e size 72 callers [ram:000018de]

void FUN_ram_0000185e(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = 5;
  if ((param_1 & 0xbf) != 0xb) {
    FUN_ram_00001822(6);
    FUN_ram_00001834();
    iVar1 = 3;
  }
  FUN_ram_00001822(param_1);
  while (iVar1 = iVar1 + -1, iVar1 != -1) {
    FUN_ram_00001850(param_2 >> 0x10 & 0xff);
    param_2 = param_2 << 8;
  }
  return;
}



// ==== FUN_ram_000018a6 @ ram:000018a6 size 56 callers [ram:000018de]

byte FUN_ram_000018a6(void)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = 0x80000;
  FUN_ram_00001834();
  do {
    FUN_ram_00001822(5);
    FUN_ram_00001842();
    bVar2 = FUN_ram_00001842();
    FUN_ram_00001834();
    if ((bVar2 & 1) == 0) {
      return bVar2 | 1;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0;
}



// ==== FUN_ram_000018de @ ram:000018de size 874 callers [ram:000010ce,ram:0000110e,ram:000011dc,ram:0000130c,ram:0000157a]

uint FUN_ram_000018de(int param_1,uint param_2,dword *param_3,uint param_4)

{
  char cVar1;
  byte bVar2;
  dword dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  dword *pdVar8;
  uint uVar9;
  undefined4 uVar10;
  byte bVar11;
  dword dVar12;
  int iVar13;
  byte *pbVar14;
  uint uVar15;
  
  uVar4 = DAT_ram_e000e000;
  uVar5 = DAT_ram_e000e004;
  DAT_ram_e000e180 = 0xffffffff;
  DAT_ram_e000e184 = 0xffffffff;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = GLOBAL_CONFIG._0_1_;
  uVar15 = param_1 - 9U & 0xff;
  bVar11 = 0xe0;
  if (((1 < uVar15) && (param_1 != 1)) && (bVar11 = 0x20, param_1 == 2)) {
    bVar11 = 0xe0;
  }
  GLOBAL_CONFIG._0_1_ = bVar2 | bVar11;
  FLASH_CONTROL._2_1_ = 4;
  FUN_ram_00001822(0xff);
  uVar9 = FUN_ram_00001834();
  if (uVar15 < 3) {
    param_2 = param_2 + 0x70000;
    uVar9 = 0xfffffffe;
    uVar6 = uVar9;
    if ((0x77fff < param_2) || (0x78000 < param_2 + param_4)) goto LAB_ram_000019c6;
    param_2 = param_2 | 0x80000;
    if (param_1 != 10) {
      if (param_1 != 9) {
        uVar9 = FUN_ram_0000185e(0xb,param_2);
        pdVar8 = (dword *)(param_4 + (int)param_3);
        for (; param_3 != pdVar8; param_3 = (dword *)((int)param_3 + 1)) {
          uVar9 = FUN_ram_00001842();
          *(char *)param_3 = (char)uVar9;
        }
        goto LAB_ram_0000199e;
      }
      uVar15 = 0x1000;
      uVar6 = 0xff;
LAB_ram_00001a16:
      uVar7 = ~uVar6 & (param_2 & uVar6) + uVar6 + param_4;
      param_2 = ~uVar6 & param_2;
      do {
        if ((uVar15 - 1 & param_2) == 0) {
          for (; uVar15 <= uVar7; uVar7 = uVar7 - uVar15) {
            uVar10 = 0xd8;
            if ((uVar15 != 0x10000) && (uVar10 = 0x20, uVar15 != 0x1000)) {
              uVar10 = 0x81;
            }
            FUN_ram_0000185e(uVar10,param_2);
            uVar9 = FUN_ram_000018a6();
            if (uVar9 == 0) goto LAB_ram_000019c4;
            param_2 = param_2 + uVar15;
          }
        }
        uVar15 = uVar15 >> 4;
      } while (0x10 < uVar15);
      goto LAB_ram_0000199e;
    }
    do {
      if (param_4 == 0) goto LAB_ram_0000199e;
      FUN_ram_0000185e(2,param_2);
      pdVar8 = param_3;
      do {
        param_3 = (dword *)((int)pdVar8 + 1);
        param_4 = param_4 - 1;
        param_2 = param_2 + 1;
        FUN_ram_00001850((char)*pdVar8);
        if (param_4 == 0) break;
        pdVar8 = param_3;
      } while ((param_2 & 0xff) != 0);
      uVar9 = FUN_ram_000018a6();
    } while (uVar9 != 0);
LAB_ram_000019c4:
    uVar6 = 0xffffffff;
    goto LAB_ram_000019c6;
  }
  if ((param_1 - 1U & 0xff) < 3) {
    cVar1 = SAFE_ACCESS._1_1_;
    if (((cVar1 == -0x7d) && (0x7ffff < param_2)) && (param_2 + param_4 < 0x100000)) {
      param_2 = param_2 ^ 0x80000;
    }
    else {
      bVar2 = GLOBAL_CONFIG._1_1_;
      uVar15 = 0x80000;
      if ((bVar2 & 0x20) == 0) {
        uVar15 = 0x78000;
      }
      uVar9 = 0xfffffffe;
      uVar6 = 0xfffffffe;
      if ((uVar15 <= param_2) || (uVar15 < param_2 + param_4)) goto LAB_ram_000019c6;
    }
    if (param_1 == 2) {
      param_4 = param_4 >> 2;
      do {
        if (param_4 == 0) goto LAB_ram_0000199e;
        FUN_ram_0000185e(2,param_2);
        pdVar8 = param_3;
        do {
          param_3 = pdVar8 + 1;
          iVar13 = 4;
          FLASH_DATA = *pdVar8;
          do {
            do {
              cVar1 = FLASH_CONTROL._2_1_;
            } while (cVar1 < '\0');
            FLASH_CONTROL._2_1_ = 0x15;
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
          param_4 = param_4 - 1;
          param_2 = param_2 + 4;
        } while ((param_4 != 0) && (pdVar8 = param_3, (param_2 & 0xff) != 0));
        uVar9 = FUN_ram_000018a6();
      } while (uVar9 != 0);
      goto LAB_ram_000019c4;
    }
    if (param_1 == 1) {
      uVar15 = 0x10000;
      uVar6 = 0xfff;
      goto LAB_ram_00001a16;
    }
    uVar9 = FUN_ram_0000185e(0xb,param_2);
    do {
      do {
        uVar6 = param_4;
        param_4 = uVar6 - 1;
        if (uVar6 == 0) goto LAB_ram_0000199e;
        uVar9 = FUN_ram_00001842();
      } while ((param_4 & 3) != 0);
      dVar3 = FLASH_DATA;
      dVar12 = *param_3;
      param_3 = param_3 + 1;
    } while (dVar3 == dVar12);
  }
  else {
    if (param_1 == 0xd) {
      uVar9 = 0xb9;
LAB_ram_00001b60:
      uVar9 = FUN_ram_00001822(uVar9);
    }
    else {
      uVar9 = 0xab;
      if (param_1 == 0xc) goto LAB_ram_00001b60;
      if (param_1 == 6) {
        FUN_ram_0000185e(0xb,param_2 | 0x80000);
        iVar13 = 0;
        do {
          uVar9 = FUN_ram_00001842();
          if (iVar13 == 3) {
            dVar3 = FLASH_DATA;
            *param_3 = dVar3;
          }
          iVar13 = iVar13 + 1;
        } while (iVar13 != 8);
        dVar3 = FLASH_DATA;
        if ((int)(param_2 << 0x12) < 0) {
          *(short *)(param_3 + 1) = (short)dVar3;
        }
        else {
          param_3[1] = dVar3;
        }
      }
      else if (param_1 == 7) {
        FUN_ram_0000185e(0x4b,0);
        uVar15 = 0xf;
        *param_3 = 0;
        param_3[1] = 0;
        do {
          uVar9 = FUN_ram_00001842();
          pbVar14 = (byte *)((uVar15 & 7) + (int)param_3);
          uVar15 = uVar15 - 1;
          uVar9 = uVar9 ^ *pbVar14;
          *pbVar14 = (byte)uVar9;
        } while (uVar15 != 0xffffffff);
      }
      else if (param_1 == 8) {
        uVar9 = FUN_ram_000018a6(0xab);
        uVar15 = 0;
        if (((param_2 != 0) && (uVar15 = 0x3c, param_2 != 3)) && (uVar15 = 0x50, param_2 != 2)) {
          uVar15 = 0x44;
        }
        uVar9 = uVar9 & 0x7c;
        if (uVar9 != uVar15) {
          FUN_ram_00001822(6);
          FUN_ram_00001834();
          FUN_ram_00001822(1);
          FUN_ram_00001850(uVar15);
          FUN_ram_00001850(2);
          uVar9 = FUN_ram_000018a6();
          if (uVar9 == 0) goto LAB_ram_000019c4;
        }
      }
      else {
        if (param_1 == 4) {
          FUN_ram_00001822(0x66);
          FUN_ram_00001834();
          uVar9 = 0x99;
          goto LAB_ram_00001b60;
        }
        if (param_1 != 0) {
          uVar6 = 0xfffffffc;
          goto LAB_ram_000019a0;
        }
      }
    }
LAB_ram_0000199e:
    uVar6 = 0;
  }
LAB_ram_000019a0:
  FUN_ram_00001834(uVar9);
LAB_ram_000019c6:
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = GLOBAL_CONFIG._0_1_;
  GLOBAL_CONFIG._0_1_ = bVar2 & 0x10;
  DAT_ram_e000e100 = uVar4;
  DAT_ram_e000e104 = uVar5;
  return uVar6;
}



// ==== handle_reset @ ram:00001c48 size 206 callers []

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: This function may have set the stack pointer */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handle_reset(void)

{
  undefined4 *puVar1;
  undefined **ppuVar2;
  undefined4 *puVar3;
  
  gp = &PTR_ram_20002000;
  puVar1 = &DAT_ram_00001008;
  ppuVar2 = &PTR_ram_20002000;
  do {
    *ppuVar2 = (undefined *)*puVar1;
    puVar1 = puVar1 + 1;
    ppuVar2 = ppuVar2 + 1;
  } while (ppuVar2 < &gatt_af00_table);
  puVar1 = &DAT_ram_00009318;
  puVar3 = &gatt_af00_table;
  do {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  } while (puVar3 < &DAT_ram_20002f50);
  puVar1 = &DAT_ram_20002f50;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  } while (puVar1 < &DAT_ram_20006df0);
  _DAT_csreg_0bc0 = 0x1f;
  _DAT_csreg_0804 = 3;
  _mstatus = _mstatus | 0x1888;
  _mtvec = 0x20002003;
  FUN_ram_00007804(FUN_ram_0000780e);
  FUN_ram_00007846();
                    /* WARNING: Read-only address (csreg,0x0341) is written */
  mepc = main;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// ==== memset @ ram:00001d1a size 106 callers [ram:0000388a,ram:00003c48,ram:00003d8a,ram:00003dd2,ram:00003ed6,ram:00003f76,ram:00003fac,ram:000040dc,ram:00004224,ram:000042ac,ram:00004486,ram:00004eca,ram:000055c0,ram:00005864,ram:00005af0,ram:000064b8,ram:000065a0,ram:0000698c,ram:00007ed6,ram:00007f4a,ram:00007ffa]

/* memset: memset(dst, value, len), used everywhere */

void memset(uint *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint extraout_t1;
  uint uVar2;
  uint extraout_a1;
  int extraout_a2;
  uint uVar3;
  uint *puVar4;
  int extraout_a4;
  int extraout_a5;
  
  uVar1 = 0xf;
  if (0xf < param_3) {
    if (((uint)param_1 & 0xf) != 0) {
      (*(code *)(((uint)param_1 & 0xf) * 4 + 0x1d50))();
      param_1 = (uint *)(extraout_a4 - (extraout_a5 + -0x10));
      param_3 = extraout_a2 + extraout_a5 + -0x10;
      uVar1 = extraout_t1;
      param_2 = extraout_a1;
      if (param_3 <= extraout_t1) goto LAB_ram_00001d44;
    }
    uVar2 = 0;
    if (param_2 != 0) {
      uVar2 = param_2 & 0xff | (param_2 & 0xff) << 8;
      uVar2 = uVar2 | uVar2 << 0x10;
    }
    uVar3 = param_3 & 0xfffffff0;
    param_3 = param_3 & 0xf;
    puVar4 = (uint *)(uVar3 + (int)param_1);
    do {
      *param_1 = uVar2;
      param_1[1] = uVar2;
      param_1[2] = uVar2;
      param_1[3] = uVar2;
      param_1 = param_1 + 4;
    } while (param_1 < puVar4);
    if (param_3 == 0) {
      return;
    }
  }
LAB_ram_00001d44:
                    /* WARNING: Could not recover jumptable at 0x00001d50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&UNK_ram_00001d54 + (uVar1 - param_3) * 4))();
  return;
}



// ==== FUN_ram_00001dc2 @ ram:00001dc2 size 40 callers [ram:000031b8]

void FUN_ram_00001dc2(void)

{
  byte bVar1;
  
  bVar1 = TKEY_CTRL._3_1_;
  TKEY_CTRL._3_1_ = bVar1 & 0xfe;
  ADC_CTRL._3_1_ = 0x80;
  ADC_CTRL._0_1_ = 0xf;
  ADC_CTRL._1_1_ = 0x35;
  return;
}



// ==== FUN_ram_00001dea @ ram:00001dea size 46 callers []

void FUN_ram_00001dea(byte param_1)

{
  byte bVar1;
  
  bVar1 = OSC32M_CTRL._2_1_;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32M_CTRL._2_1_ = bVar1 & 0xfc | param_1 & 3;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_00001e18 @ ram:00001e18 size 398 callers [ram:0000343e]

/* WARNING: Removing unreachable block (ram,0x00001e40) */
/* WARNING: Removing unreachable block (ram,0x00001f20) */
/* WARNING: Removing unreachable block (ram,0x00001f14) */
/* WARNING: Removing unreachable block (ram,0x00001e36) */
/* WARNING: Removing unreachable block (ram,0x00001e6a) */

void FUN_ram_00001e18(uint param_1,uint param_2,int param_3,uint param_4,int param_5,uint param_6)

{
  byte bVar1;
  dword dVar2;
  dword dVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bStack_1;
  
  uVar6 = 0;
  uVar5 = param_1;
  while (0x7e4 < uVar5) {
    uVar5 = uVar5 - 1;
    iVar4 = 0x16e;
    if (((int)uVar5 % 400 != 0) && (iVar4 = 0x16d, (int)uVar5 % 100 != 0)) {
      iVar4 = ((uVar5 & 3) == 0) + 0x16d;
    }
    uVar6 = uVar6 + iVar4 & 0xffff;
  }
  for (; 1 < param_2; param_2 = param_2 - 1 & 0xffff) {
    if (param_2 == 3) {
      uVar5 = 1;
      if ((param_1 % 400 != 0) && (uVar5 = 0, param_1 % 100 != 0)) {
        uVar5 = (uint)((param_1 & 3) == 0);
      }
      iVar4 = uVar5 + 0x1c;
    }
    else {
      uVar5 = param_2 & 1;
      if (param_2 < 9) {
        uVar5 = (uint)(uVar5 == 0);
      }
      iVar4 = uVar5 + 0x1e;
    }
    uVar6 = iVar4 + uVar6 & 0xffff;
  }
  do {
    bStack_1 = OSC32K_CTRL._3_1_;
    bStack_1 = bStack_1 & 0x80;
    bVar1 = OSC32K_CTRL._3_1_;
  } while ((bVar1 & 0x80) != bStack_1);
  if (bStack_1 == 0) {
    while (bStack_1 == 0) {
      do {
        bStack_1 = OSC32K_CTRL._3_1_;
        bStack_1 = bStack_1 & 0x80;
        bVar1 = OSC32K_CTRL._3_1_;
      } while ((bVar1 & 0x80) != bStack_1);
    }
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  RTC_TRIG = param_3 + -1 + uVar6 & 0xffff;
  bVar1 = RTC_CTRL._1_1_;
  RTC_CTRL._1_1_ = bVar1 | 0x80;
  do {
    dVar2 = RTC_TRIG;
    dVar3 = RTC_CNT_DAY;
  } while (((dVar2 ^ dVar3) & 0x3fff) != 0);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  RTC_TRIG = (param_5 * 0x1e + (param_6 >> 1) + (param_4 % 0x18) * 0x708) * 0x10000 |
             (param_6 & 1) << 0xf;
  bVar1 = RTC_CTRL._1_1_;
  RTC_CTRL._1_1_ = bVar1 | 0x40;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_00001fa6 @ ram:00001fa6 size 24 callers [ram:00001fbe]

dword FUN_ram_00001fa6(void)

{
  dword dVar1;
  dword dVar2;
  
  do {
    dVar1 = RTC_CNT_32K;
    dVar2 = RTC_CNT_32K;
  } while (dVar2 != dVar1);
  return dVar1;
}



// ==== FUN_ram_00001fbe @ ram:00001fbe size 1242 callers [ram:00003156]

/* WARNING: Removing unreachable block (ram,0x000023e6) */
/* WARNING: Removing unreachable block (ram,0x000023b4) */
/* WARNING: Removing unreachable block (ram,0x000021c8) */
/* WARNING: Removing unreachable block (ram,0x000020a4) */
/* WARNING: Removing unreachable block (ram,0x0000208c) */
/* WARNING: Removing unreachable block (ram,0x00002044) */
/* WARNING: Removing unreachable block (ram,0x00002088) */
/* WARNING: Removing unreachable block (ram,0x0000209c) */
/* WARNING: Removing unreachable block (ram,0x000020b8) */
/* WARNING: Removing unreachable block (ram,0x00002398) */
/* WARNING: Removing unreachable block (ram,0x000023c0) */
/* WARNING: Removing unreachable block (ram,0x000023fe) */

void FUN_ram_00001fbe(uint param_1)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  
  iVar3 = FUN_ram_000026e8();
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar6 = OSC32K_CTRL._3_1_;
  OSC32K_CTRL._3_1_ = bVar6 | 8;
  bVar6 = OSC32K_CTRL._3_1_;
  OSC32K_CTRL._3_1_ = bVar6 & 0xf7;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar6 = OSC32K_CTRL._2_1_;
  OSC32K_CTRL._2_1_ = bVar6 & 0xfc;
  bVar6 = OSC32K_CTRL._2_1_;
  OSC32K_CTRL._2_1_ = bVar6 | 1;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  iVar8 = iVar3 / 1000;
  bVar6 = OSC_CALIB._3_1_;
  OSC_CALIB._3_1_ = bVar6 & 0xf8;
  bVar6 = OSC_CALIB._3_1_;
  OSC_CALIB._3_1_ = bVar6 | 1;
  bVar6 = 0;
  iVar7 = (iVar8 * 0x4a) / 60000;
  do {
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    bVar2 = OSC_CALIB._3_1_;
    OSC_CALIB._3_1_ = bVar2 | 0x20;
    uVar1 = OSC_CALIB._0_2_;
    OSC_CALIB._0_2_ = uVar1 | 0x4000;
    uVar1 = OSC_CALIB._0_2_;
    OSC_CALIB._0_2_ = uVar1 | 0x8000;
    while (bVar2 = OSC_CALIB._3_1_, (bVar2 & 0x20) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      bVar2 = OSC_CALIB._3_1_;
      OSC_CALIB._3_1_ = bVar2 | 0x20;
    }
    do {
      bVar2 = OSC_CALIB._3_1_;
    } while ((bVar2 & 8) == 0);
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    bVar2 = OSC_CALIB._3_1_;
    OSC_CALIB._3_1_ = bVar2 & 0xdf;
    bVar2 = OSC_CALIB._3_1_;
    OSC_CALIB._3_1_ = bVar2 | 0x20;
    uVar1 = OSC_CALIB._0_2_;
    OSC_CALIB._0_2_ = uVar1 | 0x4000;
    uVar1 = OSC_CALIB._0_2_;
    OSC_CALIB._0_2_ = uVar1 | 0x8000;
    while (bVar2 = OSC_CALIB._3_1_, (bVar2 & 0x20) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      bVar2 = OSC_CALIB._3_1_;
      OSC_CALIB._3_1_ = bVar2 | 0x20;
    }
    do {
      bVar2 = OSC_CALIB._3_1_;
    } while ((bVar2 & 8) != 0);
    iVar4 = FUN_ram_00001fa6();
    do {
      iVar5 = FUN_ram_00001fa6();
    } while (iVar5 == iVar4);
    uVar1 = OSC_CALIB._0_2_;
    OSC_CALIB._0_2_ = uVar1 | 0x4000;
    do {
      bVar2 = OSC_CALIB._3_1_;
    } while ((bVar2 & 8) == 0);
    uVar1 = OSC_CALIB._0_2_;
    bVar2 = OSC_CALIB._2_1_;
    iVar4 = ((uVar1 & 0x3fff) + (uint)bVar2 * 0x3fff) - (iVar8 * 2000) / 0x8000;
    if ((((iVar3 / -1000) * 0x25) / 0x8000 < iVar4) && (iVar4 < (iVar8 * 0x25) / 0x8000)) {
      if (bVar6 != 0) {
LAB_ram_00002218:
        SAFE_ACCESS._0_1_ = 0x57;
        SAFE_ACCESS._0_1_ = 0xa8;
        bVar6 = OSC_CALIB._3_1_;
        OSC_CALIB._3_1_ = bVar6 & 0xf8;
        bVar6 = OSC_CALIB._3_1_;
        OSC_CALIB._3_1_ = bVar6 | (byte)param_1;
        while (bVar6 = OSC_CALIB._3_1_, (bVar6 & 7) != param_1) {
          SAFE_ACCESS._0_1_ = 0x57;
          SAFE_ACCESS._0_1_ = 0xa8;
          bVar6 = OSC_CALIB._3_1_;
          OSC_CALIB._3_1_ = bVar6 | (byte)param_1;
        }
        SAFE_ACCESS._0_1_ = 0x57;
        SAFE_ACCESS._0_1_ = 0xa8;
        bVar6 = OSC_CALIB._3_1_;
        OSC_CALIB._3_1_ = bVar6 & 0xdf;
        bVar6 = OSC_CALIB._3_1_;
        OSC_CALIB._3_1_ = bVar6 | 0x20;
        uVar1 = OSC_CALIB._0_2_;
        OSC_CALIB._0_2_ = uVar1 | 0x4000;
        uVar1 = OSC_CALIB._0_2_;
        OSC_CALIB._0_2_ = uVar1 | 0x8000;
        while (bVar6 = OSC_CALIB._3_1_, (bVar6 & 0x20) == 0) {
          SAFE_ACCESS._0_1_ = 0x57;
          SAFE_ACCESS._0_1_ = 0xa8;
          bVar6 = OSC_CALIB._3_1_;
          OSC_CALIB._3_1_ = bVar6 | 0x20;
        }
        do {
          bVar6 = OSC_CALIB._3_1_;
        } while ((bVar6 & 8) == 0);
        SAFE_ACCESS._0_1_ = 0x57;
        SAFE_ACCESS._0_1_ = 0xa8;
        bVar6 = OSC_CALIB._3_1_;
        OSC_CALIB._3_1_ = bVar6 & 0xdf;
        bVar6 = OSC_CALIB._3_1_;
        OSC_CALIB._3_1_ = bVar6 | 0x20;
        uVar1 = OSC_CALIB._0_2_;
        OSC_CALIB._0_2_ = uVar1 | 0x4000;
        uVar1 = OSC_CALIB._0_2_;
        OSC_CALIB._0_2_ = uVar1 | 0x8000;
        while (bVar6 = OSC_CALIB._3_1_, (bVar6 & 0x20) == 0) {
          SAFE_ACCESS._0_1_ = 0x57;
          SAFE_ACCESS._0_1_ = 0xa8;
          bVar6 = OSC_CALIB._3_1_;
          OSC_CALIB._3_1_ = bVar6 | 0x20;
        }
        do {
          bVar6 = OSC_CALIB._3_1_;
        } while ((bVar6 & 8) != 0);
        iVar7 = FUN_ram_00001fa6();
        do {
          iVar4 = FUN_ram_00001fa6();
        } while (iVar4 == iVar7);
        uVar1 = OSC_CALIB._0_2_;
        OSC_CALIB._0_2_ = uVar1 | 0x4000;
        do {
          bVar6 = OSC_CALIB._3_1_;
        } while ((bVar6 & 8) == 0);
        SAFE_ACCESS._0_1_ = 0x57;
        SAFE_ACCESS._0_1_ = 0xa8;
        bVar6 = OSC_CALIB._3_1_;
        OSC_CALIB._3_1_ = bVar6 & 0xdf;
        uVar1 = OSC_CALIB._0_2_;
        bVar6 = OSC_CALIB._2_1_;
        iVar3 = ((uVar1 & 0x3fff) + (uint)bVar6 * 0x3fff) -
                ((((4000 << (param_1 & 0x1f)) * (iVar3 / 1000000)) / 0x100) * 1000) / 0x80;
        iVar7 = (((1 << (param_1 & 0x1f)) >> 3) * iVar8 * 0x556) / 60000;
        if (iVar7 == 0) {
          iVar7 = -1;
        }
        else {
          iVar7 = (iVar3 * 200) / iVar7;
        }
        if (iVar3 < 1) {
          iVar7 = iVar7 + -1;
        }
        else {
          iVar7 = iVar7 + 1;
        }
        SAFE_ACCESS._0_1_ = 0x57;
        SAFE_ACCESS._0_1_ = 0xa8;
        uVar1 = OSC32K_CTRL._0_2_;
        OSC32K_CTRL._0_2_ = (short)(((iVar7 / 2) * 0x20 + (uint)uVar1) * 0x10000 >> 0x10);
        return;
      }
    }
    else if (2 < bVar6) goto LAB_ram_00002218;
    bVar6 = bVar6 + 1;
    if (iVar7 == 0) {
      iVar5 = -1;
    }
    else {
      iVar5 = (iVar4 * 2) / iVar7;
    }
    if (iVar4 < 1) {
      iVar5 = iVar5 + -1;
    }
    else {
      iVar5 = iVar5 + 1;
    }
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    uVar1 = OSC32K_CTRL._0_2_;
    OSC32K_CTRL._0_2_ = (short)((iVar5 / 2 + (uint)uVar1) * 0x10000 >> 0x10);
  } while( true );
}



// ==== GPIOA_ModeCfg @ ram:00002498 size 166 callers [ram:00004810,ram:00004ddc,ram:00007794]

/* GPIOA_ModeCfg: WCH GPIOA_ModeCfg(pins, mode); modes 0 floating, 1 pull-up, 2 pull-down, 3 out 5
   mA, 4 out 20 mA */

void GPIOA_ModeCfg(uint param_1,undefined4 param_2)

{
  dword dVar1;
  
  switch(param_2) {
  case 0:
    dVar1 = PA_PD_DRV;
    PA_PD_DRV = dVar1 & ~param_1;
    dVar1 = PA_PU;
    break;
  case 1:
    dVar1 = PA_PD_DRV;
    PA_PD_DRV = dVar1 & ~param_1;
    dVar1 = PA_PU;
    PA_PU = param_1 | dVar1;
    dVar1 = PA_DIR;
    PA_DIR = ~param_1 & dVar1;
    return;
  case 2:
    dVar1 = PA_PD_DRV;
    PA_PD_DRV = dVar1 | param_1;
    dVar1 = PA_PU;
    break;
  case 3:
    dVar1 = PA_PD_DRV;
    dVar1 = ~param_1 & dVar1;
    goto LAB_ram_00002526;
  case 4:
    dVar1 = PA_PD_DRV;
    dVar1 = dVar1 | param_1;
LAB_ram_00002526:
    PA_PD_DRV = dVar1;
    dVar1 = PA_DIR;
    dVar1 = param_1 | dVar1;
    goto LAB_ram_000024d2;
  default:
    goto switchD_ram_000024ae_default;
  }
  PA_PU = dVar1 & ~param_1;
  dVar1 = PA_DIR;
  dVar1 = ~param_1 & dVar1;
LAB_ram_000024d2:
  PA_DIR = dVar1;
switchD_ram_000024ae_default:
  return;
}



// ==== GPIOB_ModeCfg @ ram:0000253e size 166 callers [ram:00004810,ram:0000566a,ram:00007794]

/* GPIOB_ModeCfg: WCH GPIOB_ModeCfg(pins, mode) */

void GPIOB_ModeCfg(uint param_1,undefined4 param_2)

{
  dword dVar1;
  
  switch(param_2) {
  case 0:
    dVar1 = PB_PD_DRV;
    PB_PD_DRV = dVar1 & ~param_1;
    dVar1 = PB_PU;
    break;
  case 1:
    dVar1 = PB_PD_DRV;
    PB_PD_DRV = dVar1 & ~param_1;
    dVar1 = PB_PU;
    PB_PU = param_1 | dVar1;
    dVar1 = PB_DIR;
    PB_DIR = ~param_1 & dVar1;
    return;
  case 2:
    dVar1 = PB_PD_DRV;
    PB_PD_DRV = dVar1 | param_1;
    dVar1 = PB_PU;
    break;
  case 3:
    dVar1 = PB_PD_DRV;
    dVar1 = ~param_1 & dVar1;
    goto LAB_ram_000025cc;
  case 4:
    dVar1 = PB_PD_DRV;
    dVar1 = dVar1 | param_1;
LAB_ram_000025cc:
    PB_PD_DRV = dVar1;
    dVar1 = PB_DIR;
    dVar1 = param_1 | dVar1;
    goto LAB_ram_00002578;
  default:
    goto switchD_ram_00002554_default;
  }
  PB_PU = dVar1 & ~param_1;
  dVar1 = PB_DIR;
  dVar1 = ~param_1 & dVar1;
LAB_ram_00002578:
  PB_DIR = dVar1;
switchD_ram_00002554_default:
  return;
}



// ==== GPIOPinRemap @ ram:000025e4 size 26 callers [ram:00004810]

/* GPIOPinRemap: R16_PIN_ALTERNATE set/clear; called with RB_PIN_TMR0 (TMR0 capture on PB23) */

void GPIOPinRemap(int param_1,ushort param_2)

{
  ushort uVar1;
  
  uVar1 = PIN_CONFIG._0_2_;
  if (param_1 == 0) {
    uVar1 = ~param_2 & uVar1;
  }
  else {
    uVar1 = param_2 | uVar1;
  }
  PIN_CONFIG._0_2_ = uVar1;
  return;
}



// ==== PWMX_CycleCfg @ ram:000025fe size 140 callers [ram:00004810]

/* PWMX_CycleCfg: PWM cycle selection */

void PWMX_CycleCfg(undefined4 param_1)

{
  byte bVar1;
  
  switch(param_1) {
  case 0:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0;
    break;
  case 1:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0 | 1;
    break;
  case 2:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0 | 4;
    break;
  case 3:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0 | 5;
    break;
  case 4:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0 | 8;
    break;
  case 5:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0 | 9;
    break;
  case 6:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0 | 0xc;
    break;
  case 7:
    bVar1 = PWM_CONTROL._2_1_;
    bVar1 = bVar1 & 0xf0 | 0xd;
    break;
  default:
    goto switchD_ram_00002618_default;
  }
  PWM_CONTROL._2_1_ = bVar1;
switchD_ram_00002618_default:
  return;
}



// ==== PWMX_ACTOUT @ ram:0000268a size 94 callers [ram:00004810,ram:000048c2]

/* PWMX_ACTOUT: PWM channel duty, polarity and enable */

void PWMX_ACTOUT(int param_1,undefined1 param_2,int param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  
  bVar1 = (byte)param_1;
  if (param_4 == 0) {
    bVar2 = PWM_CONTROL._0_1_;
    bVar2 = ~bVar1 & bVar2;
  }
  else {
    if (param_3 == 0) {
      bVar2 = PWM_CONTROL._1_1_;
      bVar2 = ~bVar1 & bVar2;
    }
    else {
      bVar2 = PWM_CONTROL._1_1_;
      bVar2 = bVar2 | bVar1;
    }
    PWM_CONTROL._1_1_ = bVar2;
    uVar3 = 0;
    do {
      if ((param_1 >> (uVar3 & 0x1f) & 1U) != 0) {
        *(undefined1 *)((int)&PWM4_7_DATA + uVar3) = param_2;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 != 8);
    bVar2 = PWM_CONTROL._0_1_;
    bVar2 = bVar1 | bVar2;
  }
  PWM_CONTROL._0_1_ = bVar2;
  return;
}



// ==== FUN_ram_000026e8 @ ram:000026e8 size 66 callers [ram:00001fbe,ram:000027e2,ram:0000286e]

int FUN_ram_000026e8(void)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = CLOCK_CONFIG._0_2_;
  if ((uVar1 & 0x40) == 0) {
    iVar2 = 0x1e85000;
  }
  else {
    if ((uVar1 & 0xc0) != 0x40) {
      return 32000;
    }
    iVar2 = 0x1c9c4000;
  }
  if ((uVar1 & 0x1f) == 0) {
    iVar2 = -1;
  }
  else {
    iVar2 = (iVar2 + -0x800) / (int)(uVar1 & 0x1f);
  }
  return iVar2;
}



// ==== FUN_ram_0000272a @ ram:0000272a size 28 callers [ram:00007466]

void FUN_ram_0000272a(uint *param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = DAT_ram_e000e000;
  iVar2 = DAT_ram_e000e004;
  *param_1 = uVar1 >> 8 | iVar2 << 0x18;
  DAT_ram_e000e180 = 0xffffffff;
  DAT_ram_e000e184 = 0xffffffff;
  return;
}



// ==== FUN_ram_00002746 @ ram:00002746 size 20 callers []

void FUN_ram_00002746(uint param_1)

{
  DAT_ram_e000e100 = param_1 << 8;
  DAT_ram_e000e104 = param_1 >> 0x18;
  return;
}



// ==== FUN_ram_00002764 @ ram:00002764 size 56 callers [ram:000072e0]

void FUN_ram_00002764(int param_1)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = GLOBAL_CONFIG._2_1_;
  bVar2 = bVar1 | 2;
  if (param_1 == 0) {
    bVar2 = bVar1 & 0xfd;
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  GLOBAL_CONFIG._2_1_ = bVar2;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== TMR0_CapInit @ ram:0000279c size 26 callers [ram:00004810]

/* TMR0_CapInit: TMR0 capture mode (edge to edge) */

void TMR0_CapInit(char param_1)

{
  TMR0_CONTROL._0_1_ = 2;
  TMR0_CONTROL._0_1_ = param_1 << 6 | 5;
  return;
}



// ==== TMR1_TimerInit @ ram:000027b6 size 22 callers [ram:00004b14]

/* TMR1_TimerInit: TMR1 period; 60000 cycles = 1 ms at 60 MHz */

void TMR1_TimerInit(dword param_1)

{
  TMR1_CNT_END = param_1;
  TMR1_CONTROL._0_1_ = 2;
  TMR1_CONTROL._0_1_ = 4;
  return;
}



// ==== TMR2_TimerInit @ ram:000027cc size 22 callers [ram:00004b14]

/* TMR2_TimerInit: TMR2 period; 6000000 cycles = 100 ms at 60 MHz */

void TMR2_TimerInit(dword param_1)

{
  TMR2_CNT_END = param_1;
  TMR2_CONTROL._0_1_ = 2;
  TMR2_CONTROL._0_1_ = 4;
  return;
}



// ==== FUN_ram_000027e2 @ ram:000027e2 size 48 callers [ram:00002812]

/* WARNING: Removing unreachable block (ram,0x000027fe) */

void FUN_ram_000027e2(uint param_1)

{
  int iVar1;
  
  iVar1 = FUN_ram_000026e8();
  if (param_1 == 0) {
    param_1 = 0xffffffff;
  }
  else {
    param_1 = ((uint)(iVar1 * 10) >> 3) / param_1;
  }
  UART0_SETUP._0_2_ = (short)((param_1 + 5) / 10);
  return;
}



// ==== uart0_init_115200 @ ram:00002812 size 50 callers [ram:00007794]

/* uart0_init_115200: UART0 115200 8N1, TX only (PB7); nothing is ever transmitted */

void uart0_init_115200(void)

{
  FUN_ram_000027e2(0x1c200);
  UART0_CTRL._2_1_ = 0x87;
  UART0_CTRL._3_1_ = 3;
  UART0_CTRL._1_1_ = 0x40;
  UART0_SETUP._2_1_ = 1;
  return;
}



// ==== uart0_drain_rx @ ram:00002844 size 42 callers [ram:20002746]

/* uart0_drain_rx: reads and discards UART0 RX FIFO */

uint uart0_drain_rx(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  while (cVar2 = UART0_FIFO._2_1_, cVar2 != '\0') {
    uVar1 = UART0_FIFO._0_1_;
    puVar3 = (undefined1 *)(param_1 + uVar4);
    uVar4 = uVar4 + 1;
    *puVar3 = uVar1;
  }
  return uVar4 & 0xffff;
}



// ==== FUN_ram_0000286e @ ram:0000286e size 48 callers [ram:0000289e]

/* WARNING: Removing unreachable block (ram,0x0000288a) */

void FUN_ram_0000286e(uint param_1)

{
  int iVar1;
  
  iVar1 = FUN_ram_000026e8();
  if (param_1 == 0) {
    param_1 = 0xffffffff;
  }
  else {
    param_1 = ((uint)(iVar1 * 10) >> 3) / param_1;
  }
  UART1_SETUP._0_2_ = (short)((param_1 + 5) / 10);
  return;
}



// ==== uart1_init_115200 @ ram:0000289e size 50 callers [ram:00004ddc]

/* uart1_init_115200: UART1 115200 8N1, link to the main MCU (PA8 RX, PA9 TX) */

void uart1_init_115200(void)

{
  FUN_ram_0000286e(0x1c200);
  UART1_CTRL._2_1_ = 0x87;
  UART1_CTRL._3_1_ = 3;
  UART1_CTRL._1_1_ = 0x40;
  UART1_SETUP._2_1_ = 1;
  return;
}



// ==== FUN_ram_000028d0 @ ram:000028d0 size 26 callers [ram:00004ddc]

void FUN_ram_000028d0(char param_1)

{
  byte bVar1;
  
  bVar1 = UART1_CTRL._2_1_;
  UART1_CTRL._2_1_ = bVar1 & 0x3f | param_1 << 6;
  return;
}



// ==== FUN_ram_000028ea @ ram:000028ea size 42 callers [ram:00004ddc]

void FUN_ram_000028ea(int param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = UART1_CTRL._1_1_;
  if (param_1 != 0) {
    UART1_CTRL._1_1_ = param_2 | bVar1;
    bVar1 = UART1_CTRL._0_1_;
    UART1_CTRL._0_1_ = bVar1 | 8;
    return;
  }
  UART1_CTRL._1_1_ = ~param_2 & bVar1;
  return;
}



// ==== uart1_send @ ram:00002914 size 40 callers []

/* uart1_send: blocking UART1 transmit (busy-waits while TX FIFO holds 8 bytes) */

void uart1_send(undefined1 *param_1,uint param_2)

{
  char cVar1;
  
  while (param_2 != 0) {
    cVar1 = UART1_FIFO._3_1_;
    if (cVar1 != '\b') {
      UART1_FIFO._0_1_ = *param_1;
      param_2 = param_2 - 1 & 0xffff;
      param_1 = param_1 + 1;
    }
  }
  return;
}



// ==== uart1_read_fifo @ ram:0000293c size 42 callers [ram:2000277e]

/* uart1_read_fifo: copies UART1 RX FIFO to a buffer, returns count */

uint uart1_read_fifo(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 *puVar3;
  uint uVar4;
  
  uVar4 = 0;
  while (cVar2 = UART1_FIFO._2_1_, cVar2 != '\0') {
    uVar1 = UART1_FIFO._0_1_;
    puVar3 = (undefined1 *)(param_1 + uVar4);
    uVar4 = uVar4 + 1;
    *puVar3 = uVar1;
  }
  return uVar4 & 0xffff;
}



// ==== usb_hw_init @ ram:00002966 size 146 callers [ram:000055c0]

/* usb_hw_init: USB device controller on, DMA buffers EP0..EP3, D+ pull-up on */

void usb_hw_init(void)

{
  ushort uVar1;
  
  USB_CONTROL._0_1_ = 0;
  USB_RX_LEN = 0;
  USB_BUF_MODE._0_1_ = 0xcc;
  USB_BUF_MODE._1_1_ = 0xcc;
  UEP0_DMA = (word)DAT_ram_20002f50;
  UEP1_DMA = (word)DAT_ram_20002f54;
  UEP2_DMA = (word)DAT_ram_20002f58;
  UEP3_DMA = (word)DAT_ram_20002f5c;
  USB_EP0_CTRL._2_1_ = 2;
  USB_EP1_CTRL._2_1_ = 0x12;
  USB_EP2_CTRL._2_1_ = 0x12;
  USB_EP3_CTRL._2_1_ = 0x12;
  USB_EP4_CTRL._2_1_ = 2;
  USB_CONTROL._3_1_ = 0;
  USB_CONTROL._0_1_ = 0x29;
  uVar1 = PIN_CONFIG._2_2_;
  PIN_CONFIG._2_2_ = uVar1 | 0xc0;
  USB_STATUS._2_1_ = 0xff;
  USB_CONTROL._1_1_ = 0x81;
  USB_CONTROL._2_1_ = 7;
  return;
}



// ==== usb_hw_off @ ram:000029f8 size 102 callers [ram:0000566a]

/* usb_hw_off: USB controller off and D+ pull-up off (device detaches) */

void usb_hw_off(void)

{
  ushort uVar1;
  byte bVar2;
  
  bVar2 = USB_BUF_MODE._0_1_;
  USB_BUF_MODE._0_1_ = bVar2 & 0x33;
  bVar2 = USB_BUF_MODE._1_1_;
  USB_BUF_MODE._1_1_ = bVar2 & 0x33;
  bVar2 = USB_CONTROL._0_1_;
  USB_CONTROL._0_1_ = bVar2 & 0xd6;
  bVar2 = USB_CONTROL._0_1_;
  USB_CONTROL._0_1_ = bVar2 | 4;
  uVar1 = PIN_CONFIG._2_2_;
  PIN_CONFIG._2_2_ = uVar1 & 0xff3f;
  bVar2 = USB_CONTROL._1_1_;
  USB_CONTROL._1_1_ = bVar2 & 0x7e;
  bVar2 = USB_CONTROL._2_1_;
  USB_CONTROL._2_1_ = bVar2 & 0xf8;
  return;
}



// ==== usb_ep1_in_arm @ ram:00002a5e size 22 callers [ram:00004eca]

/* usb_ep1_in_arm: sets EP1 T_LEN and ACK */

void usb_ep1_in_arm(undefined1 param_1)

{
  byte bVar1;
  
  USB_EP1_CTRL._0_1_ = param_1;
  bVar1 = USB_EP1_CTRL._2_1_;
  USB_EP1_CTRL._2_1_ = bVar1 & 0xfc;
  return;
}



// ==== FUN_ram_00002a74 @ ram:00002a74 size 22 callers [ram:00004f3c]

void FUN_ram_00002a74(undefined1 param_1)

{
  byte bVar1;
  
  USB_EP2_CTRL._0_1_ = param_1;
  bVar1 = USB_EP2_CTRL._2_1_;
  USB_EP2_CTRL._2_1_ = bVar1 & 0xfc;
  return;
}



// ==== FUN_ram_00002a8a @ ram:00002a8a size 22 callers [ram:00004f66]

void FUN_ram_00002a8a(undefined1 param_1)

{
  byte bVar1;
  
  USB_EP3_CTRL._0_1_ = param_1;
  bVar1 = USB_EP3_CTRL._2_1_;
  USB_EP3_CTRL._2_1_ = bVar1 & 0xfc;
  return;
}



// ==== FUN_ram_00002aa0 @ ram:00002aa0 size 22 callers [ram:00004f90]

void FUN_ram_00002aa0(undefined1 param_1)

{
  byte bVar1;
  
  USB_EP4_CTRL._0_1_ = param_1;
  bVar1 = USB_EP4_CTRL._2_1_;
  USB_EP4_CTRL._2_1_ = bVar1 & 0xfc;
  return;
}



// ==== af_read_cb @ ram:00002ab6 size 130 callers []

/* af_read_cb: AF00 service read callback: CCCD 2 bytes, AF01/AF02 20 bytes of an unwritten buffer,
   offset reads rejected 0x0B */

undefined4
af_read_cb(undefined4 param_1,char *param_2,undefined4 param_3,undefined2 *param_4,int param_5)

{
  short sVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  code *pcVar4;
  
  pcVar4 = (code *)p_tmos_memcpy;
  uVar2 = 8;
  if (((param_2[8] & 0x10U) != 0) || (uVar2 = 0xb, param_5 != 0)) {
    return uVar2;
  }
  if (*param_2 != '\x02') {
    *param_4 = 0;
    return 1;
  }
  sVar1 = **(short **)(param_2 + 4);
  uVar2 = 0x2902;
  if (sVar1 == 0x2902) {
    *param_4 = 2;
    uVar3 = 2;
  }
  else {
    uVar2 = 0xb000;
    if ((sVar1 != -0x50ff) && (uVar2 = 0xaf02, sVar1 != -0x50fe)) {
      *param_4 = 0;
      return 10;
    }
    *param_4 = 0x14;
    uVar3 = 0x14;
    pcVar4 = (code *)p_tmos_memcpy;
  }
  (*pcVar4)(param_3,*(undefined4 *)(param_2 + 0xc),uVar3,param_4,uVar2,pcVar4);
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
  return 0;
}



// ==== af_write_cb @ ram:00002b38 size 202 callers []

/* af_write_cb: AF00 service write callback: CCCD via GATTServApp_ProcessCCCWriteReq, AF01 -> app
   event 3, AF02 -> app event 4 */

int af_write_cb(undefined4 param_1,char *param_2,short *param_3,undefined2 param_4)

{
  short sVar1;
  int iVar2;
  undefined1 auStack_18 [2];
  undefined2 uStack_16;
  short *psStack_14;
  
  if ((param_2[8] & 0x20U) != 0) {
    return 8;
  }
  if (*param_2 != '\x02') {
    return 10;
  }
  sVar1 = **(short **)(param_2 + 4);
  if (sVar1 == 0x2902) {
    iVar2 = (*(code *)p_GATTServApp_ProcessCCCWriteReq)();
    if (iVar2 != 0) {
      return iVar2;
    }
    if (DAT_ram_20002f60 != (code *)0x0) {
      auStack_18[0] = 2;
      if (*param_3 == 0) {
        auStack_18[0] = 1;
      }
      (*DAT_ram_20002f60)(auStack_18);
      return 0;
    }
  }
  else {
    if (sVar1 == -0x50ff) {
      auStack_18[0] = 3;
      if (DAT_ram_20002f60 == (code *)0x0) {
        return 0;
      }
    }
    else {
      if (sVar1 != -0x50fe) {
        return 0;
      }
      if (DAT_ram_20002f60 == (code *)0x0) {
        return 0;
      }
      auStack_18[0] = 4;
    }
    uStack_16 = param_4;
    psStack_14 = param_3;
    (*DAT_ram_20002f60)(auStack_18);
  }
                    /* WARNING: Read-only address (ram,0x00040144) is written */
                    /* WARNING: Read-only address (ram,0x00040144) is written */
  return 0;
}



// ==== af_service_register @ ram:00002c6a size 114 callers [ram:000072e0]

/* af_service_register: registers AF00 table (7 attributes) and the app callback 0x72a6 */

void af_service_register(undefined4 param_1)

{
  undefined4 extraout_a4;
  
  (*(code *)p_GATTServApp_InitCharCfg)(0xffff,&DAT_ram_20003224);
  (*(code *)p_GATTServApp_InitCharCfg)(0xffff,&DAT_ram_20003014);
  (*(code *)p_linkDB_Register)(&af_linkdb_cb);
  (*(code *)p_GATTServApp_RegisterService)
            (&gatt_af00_table,7,0x10,&PTR_af_read_cb_ram_20002cb0,extraout_a4,
             p_GATTServApp_RegisterService);
  DAT_ram_20002f60 = param_1;
  return;
}



// ==== af01_notify_raw @ ram:00002cdc size 88 callers [ram:00006ff6]

/* af01_notify_raw: GATT_Notification on AF01 if its CCCD has notify set, else 0x12 */

undefined4 af01_notify_raw(undefined4 param_1,undefined2 *param_2)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar2 = (*(code *)p_GATTServApp_ReadCharCfg)(param_1,&DAT_ram_20003224);
  puVar1 = p_GATT_Notification;
  if ((uVar2 & 1) != 0) {
    *param_2 = DAT_ram_20002c6a;
    uVar3 = (*(code *)puVar1)(param_1,param_2,0);
    return uVar3;
  }
  return 0x12;
}



// ==== af02_notify_raw @ ram:00002d34 size 88 callers [ram:00006f6c]

/* af02_notify_raw: GATT_Notification on AF02 if its CCCD has notify set, else 0x12 */

undefined4 af02_notify_raw(undefined4 param_1,undefined2 *param_2)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar2 = (*(code *)p_GATTServApp_ReadCharCfg)(param_1,&DAT_ram_20003014);
  puVar1 = p_GATT_Notification;
  if ((uVar2 & 1) != 0) {
    *param_2 = DAT_ram_20002c9a;
    uVar3 = (*(code *)puVar1)(param_1,param_2,0);
    return uVar3;
  }
  return 0x12;
}



// ==== db_read_cb @ ram:00002d8c size 156 callers []

/* db_read_cb: DB00 service read callback; app hook 0x7104 is empty */

undefined4
db_read_cb(undefined4 param_1,char *param_2,undefined4 param_3,undefined2 *param_4,int param_5)

{
  undefined4 uVar1;
  undefined2 uVar2;
  code *pcVar3;
  
  pcVar3 = (code *)p_tmos_memcpy;
  uVar1 = 8;
  if (((param_2[8] & 0x10U) == 0) && (uVar1 = 0xb, param_5 == 0)) {
    if (*param_2 != '\x02') {
      *param_4 = 0;
      return 1;
    }
    if (**(short **)(param_2 + 4) == 0x2902) {
      *param_4 = 2;
      uVar2 = 2;
    }
    else {
      if (**(short **)(param_2 + 4) != -0x24ff) {
        *param_4 = 0;
        return 10;
      }
      (**(code **)(DAT_ram_20002f64 + 4))
                (0xdb01,*(undefined4 *)(param_2 + 0xc),*param_4,param_4,2,
                 *(code **)(DAT_ram_20002f64 + 4));
      uVar2 = *param_4;
      pcVar3 = (code *)p_tmos_memcpy;
    }
    (*pcVar3)(param_3,*(undefined4 *)(param_2 + 0xc),uVar2);
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
    return 0;
  }
  return uVar1;
}



// ==== db_write_cb @ ram:00002e28 size 118 callers []

/* db_write_cb: DB00 service write callback; app hook 0x6cae is empty */

undefined4 db_write_cb(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if ((param_2[8] & 0x20U) == 0) {
    uVar1 = 1;
    if (*param_2 == '\x02') {
      if (**(short **)(param_2 + 4) == 0x2902) {
                    /* WARNING: Could not recover jumptable at 0x00002e74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar1 = (*(code *)p_GATTServApp_ProcessCCCWriteReq)();
        return uVar1;
      }
      if (**(short **)(param_2 + 4) == -0x24ff) {
        (*(code *)*DAT_ram_20002f64)(0xdb01,param_3,param_4,param_4,(code *)*DAT_ram_20002f64);
        return 0;
      }
      uVar1 = 10;
    }
  }
  else {
    uVar1 = 8;
  }
  return uVar1;
}



// ==== db_service_register @ ram:00002efc size 92 callers [ram:000072e0]

/* db_service_register: registers DB00 table (4 attributes) */

void db_service_register(int param_1)

{
  undefined4 extraout_a4;
  
  (*(code *)p_GATTServApp_InitCharCfg)(0xffff,&DAT_ram_20003434);
  (*(code *)p_linkDB_Register)(&db_linkdb_cb);
  (*(code *)p_GATTServApp_RegisterService)
            (&gatt_db00_table,4,0x10,&PTR_db_read_cb_ram_20002cfc,extraout_a4,
             p_GATTServApp_RegisterService);
  if (param_1 != 0) {
    DAT_ram_20002f64 = param_1;
  }
  return;
}



// ==== devinfo_read_cb @ ram:00002f58 size 462 callers []

/* devinfo_read_cb: 180A read callback, WCH SDK placeholder values */

undefined4
devinfo_read_cb(undefined4 param_1,int param_2,undefined4 param_3,undefined2 *param_4,uint param_5,
               uint param_6)

{
  short sVar1;
  char *pcVar2;
  uint uVar3;
  code *pcVar4;
  
  pcVar4 = (code *)p_tmos_memcpy;
  sVar1 = **(short **)(param_2 + 4);
  if (sVar1 == 0x2a27) {
    if (0x10 < param_5) {
      return 7;
    }
    uVar3 = 0x11 - param_5;
    if (param_6 < 0x11 - param_5) {
      uVar3 = param_6;
    }
    *param_4 = (short)uVar3;
    pcVar2 = "Hardware Revision";
    pcVar4 = (code *)p_tmos_memcpy;
  }
  else if (sVar1 < 0x2a28) {
    if (sVar1 == 0x2a24) {
      if (0xb < param_5) {
        return 7;
      }
      uVar3 = 0xc - param_5;
      if (param_6 < 0xc - param_5) {
        uVar3 = param_6;
      }
      *param_4 = (short)uVar3;
      pcVar2 = "Model Number";
      pcVar4 = (code *)p_tmos_memcpy;
    }
    else if (sVar1 < 0x2a25) {
      if (sVar1 != 0x2a23) {
LAB_ram_00002f92:
        *param_4 = 0;
        return 10;
      }
      if (7 < param_5) {
        return 7;
      }
      uVar3 = 8 - param_5;
      if (param_6 < 8 - param_5) {
        uVar3 = param_6;
      }
      *param_4 = (short)uVar3;
      pcVar2 = (char *)0x20002f68;
    }
    else if (sVar1 == 0x2a25) {
      if (0xc < param_5) {
        return 7;
      }
      uVar3 = 0xd - param_5;
      if (param_6 < 0xd - param_5) {
        uVar3 = param_6;
      }
      *param_4 = (short)uVar3;
      pcVar2 = "Serial Number";
      pcVar4 = (code *)p_tmos_memcpy;
    }
    else {
      if (sVar1 != 0x2a26) goto LAB_ram_00002f92;
      if (0x10 < param_5) {
        return 7;
      }
      uVar3 = 0x11 - param_5;
      if (param_6 < 0x11 - param_5) {
        uVar3 = param_6;
      }
      *param_4 = (short)uVar3;
      pcVar2 = "Firmware Revision";
      pcVar4 = (code *)p_tmos_memcpy;
    }
  }
  else if (sVar1 == 0x2a29) {
    if (0x10 < param_5) {
      return 7;
    }
    uVar3 = 0x11 - param_5;
    if (param_6 < 0x11 - param_5) {
      uVar3 = param_6;
    }
    *param_4 = (short)uVar3;
    pcVar2 = "Manufacturer Name";
    pcVar4 = (code *)p_tmos_memcpy;
  }
  else if (sVar1 < 0x2a29) {
    if (0x10 < param_5) {
      return 7;
    }
    uVar3 = 0x11 - param_5;
    if (param_6 < 0x11 - param_5) {
      uVar3 = param_6;
    }
    *param_4 = (short)uVar3;
    pcVar2 = "Software Revision";
    pcVar4 = (code *)p_tmos_memcpy;
  }
  else if (sVar1 == 0x2a2a) {
    if (0xd < param_5) {
      return 7;
    }
    uVar3 = 0xe - param_5;
    if (param_6 < 0xe - param_5) {
      uVar3 = param_6;
    }
    *param_4 = (short)uVar3;
    pcVar2 = &UNK_ram_00008de8;
    pcVar4 = (code *)p_tmos_memcpy;
  }
  else {
    if (sVar1 != 0x2a50) goto LAB_ram_00002f92;
    if (6 < param_5) {
      return 7;
    }
    uVar3 = 7 - param_5;
    if (param_6 < 7 - param_5) {
      uVar3 = param_6;
    }
    *param_4 = (short)uVar3;
    pcVar2 = (char *)0x20002f20;
    pcVar4 = (code *)p_tmos_memcpy;
  }
  (*pcVar4)(param_3,pcVar2 + param_5);
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
  return 0;
}



// ==== devinfo_register @ ram:00003126 size 30 callers [ram:000072e0]

/* devinfo_register: registers the 180A table (19 attributes) */

void devinfo_register(void)

{
                    /* WARNING: Could not recover jumptable at 0x00003142. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)p_GATTServApp_RegisterService)(&gatt_180a_table,0x13,0x10,0x20002e38);
  return;
}



// ==== FUN_ram_00003144 @ ram:00003144 size 18 callers [ram:000072e0]

undefined4 FUN_ram_00003144(int param_1)

{
  if (param_1 != 0) {
    DAT_ram_20002f70 = param_1;
    return 0;
  }
  return 0x11;
}



// ==== FUN_ram_00003156 @ ram:00003156 size 6 callers [ram:0000322a,ram:0000343e]

void FUN_ram_00003156(void)

{
  FUN_ram_00001fbe(4);
  return;
}



// ==== ble_flash_read_cb @ ram:0000315c size 28 callers []

/* ble_flash_read_cb: bleConfig readFlashCB -> EEPROM read */

undefined4 ble_flash_read_cb(undefined4 param_1,int param_2,undefined4 param_3)

{
  FLASH_EEPROM_CMD(0xb,param_1,param_3,param_2 << 2);
  return 0;
}



// ==== ble_flash_write_cb @ ram:00003178 size 64 callers []

/* ble_flash_write_cb: bleConfig writeFlashCB -> EEPROM erase + write */

undefined4 ble_flash_write_cb(undefined4 param_1,int param_2,undefined4 param_3)

{
  FLASH_EEPROM_CMD(9,param_1,0,param_2 << 2);
  FLASH_EEPROM_CMD(10,param_1,param_3,param_2 << 2);
  return 0;
}



// ==== ble_temp_sample_cb @ ram:000031b8 size 114 callers []

/* ble_temp_sample_cb: bleConfig tsCB, ADC temperature sample */

undefined2 ble_temp_sample_cb(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  undefined1 uVar5;
  undefined2 uVar6;
  
  uVar1 = TKEY_CTRL._3_1_;
  uVar5 = ADC_CTRL._3_1_;
  uVar2 = ADC_CTRL._0_1_;
  uVar3 = ADC_CTRL._1_1_;
  FUN_ram_00001dc2();
  bVar4 = ADC_CTRL._2_1_;
  ADC_CTRL._2_1_ = bVar4 | 1;
  do {
    bVar4 = ADC_CTRL._2_1_;
  } while ((bVar4 & 1) != 0);
  uVar6 = ADC_DATA._0_2_;
  ADC_CTRL._3_1_ = uVar5;
  ADC_CTRL._0_1_ = uVar2;
  ADC_CTRL._1_1_ = uVar3;
  TKEY_CTRL._3_1_ = uVar1;
  return uVar6;
}



// ==== hal_task_event @ ram:0000322a size 140 callers []

/* hal_task_event: TMOS HAL task: LSI calibration every 0x2EE00 ticks */

uint hal_task_event(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_a3;
  undefined4 extraout_a4;
  
  if ((short)param_2 < 0) {
    iVar1 = (*(code *)p_tmos_msg_receive)();
    if (iVar1 != 0) {
      (*(code *)p_tmos_msg_deallocate)();
    }
    uVar2 = 0x8000;
  }
  else {
    if ((param_2 & 1) != 0) {
      return param_2 ^ 1;
    }
    if ((int)(param_2 << 0x12) < 0) {
      (*(code *)p_BLE_RegInit)(param_2 ^ 1);
      FUN_ram_00003156();
      (*(code *)p_tmos_start_task)
                (DAT_ram_20002f74,0x2000,0x2ee00,extraout_a3,extraout_a4,p_tmos_start_task);
      uVar2 = 0x2000;
    }
    else {
      if (-1 < (int)(param_2 << 0x11)) {
        return 0;
      }
      (*(code *)p_tmos_start_task)(DAT_ram_20002f74,0x4000,0x640,param_4,param_5,p_tmos_start_task);
      uVar2 = 0x4000;
    }
  }
                    /* WARNING: Read-only address (ram,0x00040058) is written */
                    /* WARNING: Read-only address (ram,0x00040068) is written */
                    /* WARNING: Read-only address (ram,0x0004006c) is written */
                    /* WARNING: Read-only address (ram,0x000401ec) is written */
  return uVar2 ^ param_2;
}



// ==== ble_lib_init @ ram:000032b6 size 282 callers [ram:00007794]

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* ble_lib_init: checks VER_LIB == CH58x_BLE_LIB_V1.8, fills bleConfig_t, BLE_LibInit */

void ble_lib_init(void)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined **ppuVar3;
  undefined1 local_54 [8];
  undefined *puStack_4c;
  ushort uStack_48;
  undefined4 uStack_44;
  undefined1 uStack_3d;
  undefined2 uStack_3c;
  undefined1 uStack_3a;
  undefined4 uStack_38;
  undefined1 auStack_32 [6];
  undefined1 *puStack_2c;
  undefined1 *puStack_28;
  code *pcStack_24;
  code *pcStack_20;
  code *pcStack_18;
  code *pcStack_14;
  
  iVar1 = (*(code *)p_tmos_memcmp)(p_VER_LIB,"CH58x_BLE_LIB_V1.8",0x12,in_a3,in_a4,p_tmos_memcmp);
  if (iVar1 == 0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  _DAT_ram_e000f010 = 0xfffffffe;
  _DAT_ram_e000f014 = 0xffffffff;
  DAT_ram_e000e100 = 0x1000;
  _DAT_ram_e000f000 = 0x2f;
  DAT_ram_e000e180 = 0x1000;
  (*(code *)p_tmos_memset)(&puStack_4c,0,0x3c,&DAT_ram_e000f000,0x1000,p_tmos_memset);
  puStack_4c = &ble_lib_heap;
  uStack_48 = 0x1c00;
  uStack_3c = 0xfb;
  uStack_3d = 5;
  uStack_3a = 1;
  uStack_44 = 0x7e00;
  pcStack_18 = ble_flash_read_cb;
  pcStack_14 = ble_flash_write_cb;
  puStack_2c = &LAB_ram_0000275a;
  pcStack_24 = ble_temp_sample_cb;
  pcStack_20 = FUN_ram_00003156;
  uStack_38 = 0xd022e3d;
  puStack_28 = &LAB_ram_000034a6;
  FLASH_EEPROM_CMD(6,0x7f018,local_54,0);
  iVar1 = 0;
  ppuVar3 = &puStack_4c;
  do {
    puVar2 = local_54 + iVar1;
    iVar1 = iVar1 + 1;
    *(undefined1 *)((int)ppuVar3 + 0x1a) = *puVar2;
    ppuVar3 = (undefined **)((int)ppuVar3 + 1);
  } while (iVar1 != 6);
  if ((puStack_4c != (undefined *)0x0) && (0xfff < uStack_48)) {
    iVar1 = (*(code *)p_BLE_LibInit)(&puStack_4c);
    if (iVar1 != 0) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== hal_init @ ram:000033d0 size 70 callers [ram:00007794]

/* hal_init: registers HAL task, RTC and TMOS timer init */

void hal_init(void)

{
  DAT_ram_20002f74 = (*(code *)p_TMOS_ProcessEventRegister)(hal_task_event);
  FUN_ram_0000343e();
  FUN_ram_0000354a();
  (*(code *)p_tmos_start_task)(DAT_ram_20002f74,0x2000,0x2ee00);
  return;
}



// ==== FUN_ram_00003416 @ ram:00003416 size 40 callers []

void FUN_ram_00003416(dword param_1)

{
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  RTC_TRIG = param_1;
  SAFE_ACCESS._0_1_ = 0;
  DAT_ram_20002f78 = 0;
  return;
}



// ==== FUN_ram_0000343e @ ram:0000343e size 104 callers [ram:000033d0]

void FUN_ram_0000343e(void)

{
  byte bVar1;
  
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar1 = OSC32K_CTRL._3_1_;
  OSC32K_CTRL._3_1_ = bVar1 & 0xfa;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar1 = OSC32K_CTRL._3_1_;
  OSC32K_CTRL._3_1_ = bVar1 | 2;
  SAFE_ACCESS._0_1_ = 0;
  FUN_ram_00003156();
  FUN_ram_00001e18(0x7e4,1,1,0,0,0);
  (*(code *)p_TMOS_TimerInit)(0);
  return;
}



// ==== FUN_ram_0000354a @ ram:0000354a size 78 callers [ram:000033d0]

void FUN_ram_0000354a(void)

{
  byte bVar1;
  
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar1 = SLEEP_CONTROL._2_1_;
  SLEEP_CONTROL._2_1_ = bVar1 | 8;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar1 = RTC_CTRL._1_1_;
  RTC_CTRL._1_1_ = bVar1 | 0x20;
  SAFE_ACCESS._0_1_ = 0;
  DAT_ram_e000e100 = 0x10000000;
  return;
}



// ==== FUN_ram_00003598 @ ram:00003598 size 2 callers [ram:000047c8]

void FUN_ram_00003598(void)

{
  return;
}



// ==== frame_decoder_reset @ ram:0000359a size 14 callers [ram:00003876]

/* frame_decoder_reset: clears decoder state/count fields of a slot */

void frame_decoder_reset(int param_1)

{
  *(undefined1 *)(param_1 + 0x214) = 0;
  *(undefined1 *)(param_1 + 0x208) = 0;
  *(undefined4 *)(param_1 + 0x20c) = 0;
  return;
}



// ==== frame_encode @ ram:000035a8 size 186 callers [ram:0000388a,ram:00003c48,ram:00003d8a,ram:00003dd2,ram:00004628]

/* frame_encode: AA, (hi<<4|lo), len, data, sum; AA doubled; returns encoded length */

int frame_encode(undefined4 param_1,char *param_2,undefined1 *param_3)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  char *pcVar5;
  byte bVar6;
  char cVar7;
  
  cVar7 = *param_2;
  bVar1 = param_2[1];
  bVar6 = cVar7 << 4 | bVar1 & 0xf;
  *param_3 = 0xaa;
  param_3[1] = cVar7 << 4 | bVar1 & 0xf;
  if (bVar6 == 0xaa) {
    pcVar3 = param_3 + 3;
    param_3[2] = 0xaa;
  }
  else {
    pcVar3 = param_3 + 2;
  }
  cVar7 = param_2[2];
  *pcVar3 = cVar7;
  if (cVar7 == -0x56) {
    pcVar5 = pcVar3 + 2;
    pcVar3[1] = -0x56;
  }
  else {
    pcVar5 = pcVar3 + 1;
  }
  cVar7 = bVar6 + param_2[2];
  uVar4 = 0;
  while( true ) {
    pcVar3 = pcVar5 + 1;
    if (*(ushort *)(param_2 + 2) <= uVar4) break;
    cVar2 = param_2[uVar4 + 4];
    cVar7 = cVar7 + cVar2;
    *pcVar5 = cVar2;
    if (cVar2 == -0x56) {
      pcVar3 = pcVar5 + 2;
      pcVar5[1] = -0x56;
    }
    uVar4 = uVar4 + 1 & 0xff;
    pcVar5 = pcVar3;
  }
  *pcVar5 = cVar7;
  if (cVar7 == -0x56) {
    pcVar3 = pcVar5 + 2;
    pcVar5[1] = -0x56;
  }
  return (int)pcVar3 - (int)param_3;
}



// ==== frame_decode_byte @ ram:00003662 size 194 callers [ram:0000384e]

/* frame_decode_byte: per-slot stuffed-frame decoder (USB OUT uses slot 1) */

undefined1 * frame_decode_byte(undefined1 *param_1,uint param_2)

{
  undefined1 *puVar1;
  byte bVar2;
  byte bVar3;
  undefined4 uVar4;
  uint uVar5;
  
  bVar2 = (byte)param_2;
  if (param_2 == 0xaa) {
    bVar3 = param_1[0x214] + 1;
    param_1[0x214] = bVar3;
    if ((bVar3 & 1) != 0) {
      return (undefined1 *)0x0;
    }
LAB_ram_000036a6:
    switch(*(undefined4 *)(param_1 + 0x20c)) {
    case 0:
      goto switchD_ram_000036c0_caseD_0;
    case 1:
      goto switchD_ram_000036c0_caseD_1;
    default:
switchD_ram_000036c0_caseD_2:
      *(undefined4 *)(param_1 + 0x20c) = 0;
      return (undefined1 *)0x0;
    case 4:
      if (param_2 == 0) goto switchD_ram_000036c0_caseD_2;
      *(short *)(param_1 + 2) = (short)param_2;
      param_1[0x210] = 0;
      param_1[0x211] = bVar2 + param_1[0x211];
      uVar4 = 6;
      break;
    case 6:
      bVar3 = param_1[0x210];
      param_1[bVar3 + 4] = bVar2;
      uVar5 = bVar3 + 1;
      param_1[0x211] = bVar2 + param_1[0x211];
      param_1[0x210] = (char)uVar5;
      if ((uVar5 & 0xff) < (uint)*(ushort *)(param_1 + 2)) {
        return (undefined1 *)0x0;
      }
      uVar4 = 7;
      break;
    case 7:
      puVar1 = (undefined1 *)0x0;
      if ((byte)param_1[0x211] == param_2) {
        param_1[0x208] = 1;
        puVar1 = param_1;
      }
      *(undefined4 *)(param_1 + 0x20c) = 0;
      return puVar1;
    }
  }
  else {
    if ((param_1[0x214] & 1) == 0) goto LAB_ram_000036a6;
    param_1[0x214] = 0;
switchD_ram_000036c0_caseD_1:
    param_1[1] = bVar2 & 0xf;
    *param_1 = (char)(param_2 >> 4);
    param_1[0x211] = bVar2;
    uVar4 = 4;
  }
  *(undefined4 *)(param_1 + 0x20c) = uVar4;
switchD_ram_000036c0_caseD_0:
  return (undefined1 *)0x0;
}



// ==== tmr1_1ms_tick @ ram:00003724 size 116 callers [ram:200026fc]

/* WARNING: Removing unreachable block (ram,0x00003770) */
/* WARNING: Removing unreachable block (ram,0x00003746) */
/* WARNING: Removing unreachable block (ram,0x0000375a) */
/* WARNING: Removing unreachable block (ram,0x00003786) */
/* tmr1_1ms_tick: 1 ms counter, sets 1/10/100/500/1000 ms flags */

void tmr1_1ms_tick(void)

{
  DAT_ram_20002f84 = DAT_ram_20002f84 + 1;
  DAT_ram_20002f7f = 1;
  if (DAT_ram_20002f84 % 10 == 0) {
    DAT_ram_20002f7e = 1;
  }
  if (DAT_ram_20002f84 % 100 == 0) {
    DAT_ram_20002f7d = 1;
  }
  if (DAT_ram_20002f84 % 500 == 0) {
    DAT_ram_20002f80 = 1;
  }
  if (DAT_ram_20002f84 % 1000 == 0) {
    DAT_ram_20002f7c = 1;
  }
  return;
}



// ==== FUN_ram_00003798 @ ram:00003798 size 24 callers [ram:00004bb8]

bool FUN_ram_00003798(void)

{
  bool bVar1;
  
  bVar1 = DAT_ram_20002f7f != '\0';
  if (bVar1) {
    DAT_ram_20002f7f = '\0';
  }
  return bVar1;
}



// ==== FUN_ram_000037b0 @ ram:000037b0 size 24 callers [ram:00004bb8]

bool FUN_ram_000037b0(void)

{
  bool bVar1;
  
  bVar1 = DAT_ram_20002f7e != '\0';
  if (bVar1) {
    DAT_ram_20002f7e = '\0';
  }
  return bVar1;
}



// ==== FUN_ram_000037c8 @ ram:000037c8 size 24 callers [ram:00004bb8]

bool FUN_ram_000037c8(void)

{
  bool bVar1;
  
  bVar1 = DAT_ram_20002f7d != '\0';
  if (bVar1) {
    DAT_ram_20002f7d = '\0';
  }
  return bVar1;
}



// ==== FUN_ram_000037e0 @ ram:000037e0 size 24 callers [ram:00004bb8]

bool FUN_ram_000037e0(void)

{
  bool bVar1;
  
  bVar1 = DAT_ram_20002f80 != '\0';
  if (bVar1) {
    DAT_ram_20002f80 = '\0';
  }
  return bVar1;
}



// ==== FUN_ram_000037f8 @ ram:000037f8 size 24 callers [ram:00004bb8]

bool FUN_ram_000037f8(void)

{
  bool bVar1;
  
  bVar1 = DAT_ram_20002f7c != '\0';
  if (bVar1) {
    DAT_ram_20002f7c = '\0';
  }
  return bVar1;
}



// ==== acc_to_mcu_queue @ ram:00003810 size 62 callers [ram:000042a4,ram:000042ac]

/* acc_to_mcu_queue: copies an accessory frame to slot 2 (address 0x52) and marks it pending */

void acc_to_mcu_queue(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{
  (*(code *)p_tmos_memcpy)(&DAT_ram_20003e84,param_1,param_2,param_4,param_5,p_tmos_memcpy);
  DAT_ram_20003e80 = &vstvec;
  DAT_ram_20003e82 = (short)param_2;
  DAT_ram_20004088 = 1;
  return;
}



// ==== decoder_feed_slot @ ram:0000384e size 20 callers [ram:00004e86]

/* decoder_feed_slot: feeds one byte to the decoder of slot n */

void decoder_feed_slot(int param_1)

{
  frame_decode_byte(&bridge_slots + param_1 * 0x10c);
  return;
}



// ==== slot_rx_frame_ptr @ ram:00003862 size 20 callers [ram:00004cee]

/* slot_rx_frame_ptr: returns slot n + 0x104 (copy of a frame received from the MCU) */

int slot_rx_frame_ptr(int param_1)

{
  return param_1 * 0x218 + 0x20003b54;
}



// ==== decoder_reset_slot @ ram:00003876 size 20 callers [ram:000055c0,ram:0000566a]

/* decoder_reset_slot: resets the decoder of slot n */

void decoder_reset_slot(int param_1)

{
  frame_decoder_reset(&bridge_slots + param_1 * 0x10c);
  return;
}



// ==== mcu_ctl_cmd @ ram:0000388a size 958 callers [ram:00004628]

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* mcu_ctl_cmd: channel 3 handler: 00,10,50,52,E0,EF,F0,FC from the main MCU */

void mcu_ctl_cmd(code *param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 uVar5;
  undefined1 auStack_140 [14];
  undefined1 auStack_132 [10];
  undefined1 auStack_128 [14];
  undefined1 auStack_11a [10];
  undefined1 auStack_110 [256];
  
  bVar1 = DAT_ram_200041a0;
  memset(auStack_110,0,0x100);
  if (bVar1 == 0x52) {
    if (DAT_ram_200041a1 == 'S') {
      remote_enabled = '\x01';
      if (usb_enabled == '\0') {
        usb_enable();
      }
      auStack_128[0] = 1;
    }
    else {
      remote_enabled = '\0';
      usb_disable();
      auStack_128[0] = 0;
    }
    (*(code *)p_GAPRole_SetParameter)(0x305,1,auStack_128);
    host_iface_mode = '\0';
    uVar5 = 0x53;
LAB_ram_000038d0:
    _DAT_ram_2000409c = CONCAT22(_DAT_ram_2000409e,uVar5);
  }
  else {
    if (bVar1 < 0x53) {
      if (bVar1 == 0x10) {
        uVar4 = get_uptime_ms();
        _DAT_ram_2000409c =
             CONCAT13((char)((uint)uVar4 >> 0x10),
                      CONCAT12((char)((uint)uVar4 >> 8),CONCAT11((char)uVar4,0x11)));
        DAT_ram_200040a0 = CONCAT31(DAT_ram_200040a0._1_3_,(char)((uint)uVar4 >> 0x18));
        DAT_ram_2000409a = 5;
        goto LAB_ram_00003a34;
      }
      if (bVar1 != 0x50) {
        if (bVar1 != 0) {
          return;
        }
        uVar5 = 1;
        goto LAB_ram_000038d0;
      }
      host_iface_mode = DAT_ram_200041a1;
      if (DAT_ram_200041a1 == '\x01') {
        usb_disable();
      }
      else if ((DAT_ram_200041a1 == '\0' && usb_enabled == '\0') && (remote_enabled != '\0')) {
        usb_enable();
      }
      if (host_iface_mode == '\x02') {
        auStack_128[0] = 0;
LAB_ram_00003a9c:
        (*(code *)p_GAPRole_SetParameter)(0x305,1,auStack_128);
      }
      else if (host_iface_mode == '\0') {
        auStack_128[0] = 1;
        goto LAB_ram_00003a9c;
      }
      uVar5 = 0x51;
      goto LAB_ram_000038d0;
    }
    if (bVar1 == 0xef) {
      if (DAT_ram_200041a1 == '*') {
        DAT_ram_20002fb4 = 1;
        return;
      }
      if (DAT_ram_200041a1 != ',') {
        return;
      }
      DAT_ram_20002fb4 = 0;
      return;
    }
    if (bVar1 < 0xf0) {
      if (bVar1 != 0xe0) {
        return;
      }
      _DAT_ram_2000409c = 0x33504de1;
      DAT_ram_200040a0 = 0x423530;
      DAT_ram_200040a4 = 0x66000100;
      DAT_ram_200040b0 = 0x33504d0f;
      DAT_ram_200040b4 = 0x423530;
      DAT_ram_200040b8 = 0;
      DAT_ram_200040ba = 0;
      DAT_ram_200040a8 = 0x100;
      DAT_ram_200040ac = 0x100;
      DAT_ram_2000409a = 0x1f;
      goto LAB_ram_00003a34;
    }
    if (bVar1 == 0xf0) {
      if (DAT_ram_200041a1 != -0x54) {
        return;
      }
      _DAT_ram_2000409c = CONCAT22(_DAT_ram_2000409e,0xf1);
      DAT_ram_2000409a = 2;
      if (DAT_ram_20002fb8 == 1) goto LAB_ram_00003a34;
      DAT_ram_20002fb8 = 1;
      DAT_ram_20002fb6 = 100;
    }
    else {
      if (bVar1 != 0xfc) {
        return;
      }
      if (DAT_ram_200041a1 != '*') {
        return;
      }
      _DAT_ram_2000409c = CONCAT22(_DAT_ram_2000409e,&UNK_csreg_03fd);
      if ((uint)DAT_ram_200041a2 + (uint)DAT_ram_200041a3 + (uint)DAT_ram_200041a4 +
          (uint)DAT_ram_200041a5 != 0) {
        (*(code *)p_tmos_memset)(auStack_140,0xff,0x16);
        (*(code *)p_tmos_memset)(auStack_128,0xff,0x16);
        FLASH_EEPROM_CMD(0xb,0x6e00,auStack_128,0x16);
        iVar3 = (*(code *)p_tmos_memcmp)(auStack_132,auStack_11a,4);
        if (iVar3 == 0) {
          iVar3 = (*(code *)p_tmos_memcmp)(auStack_11a,&DAT_ram_200041a2,8);
          if (iVar3 != 0) goto LAB_ram_000039ec;
          (*(code *)p_tmos_memcpy)(auStack_11a,&DAT_ram_200041a2,8);
          FLASH_EEPROM_CMD(9,0x6e00,0,0x100);
        }
        else {
          (*(code *)p_tmos_memcpy)(auStack_11a,&DAT_ram_200041a2,8);
          FLASH_EEPROM_CMD(9,0x6e00,0,0x100);
        }
        FLASH_EEPROM_CMD(10,0x6e00,auStack_128,0x16);
      }
LAB_ram_000039ec:
      adv_mfr_set_from_fc(&DAT_ram_200041aa);
    }
  }
  DAT_ram_2000409a = 2;
LAB_ram_00003a34:
  DAT_ram_20004098 = DAT_ram_2000419c >> 8 | DAT_ram_2000419c << 8;
  uVar2 = frame_encode(&DAT_ram_20004098,&DAT_ram_20004098,auStack_110);
  (*param_1)(auStack_110,uVar2);
                    /* WARNING: Read-only address (ram,0x0004003c) is written */
                    /* WARNING: Read-only address (ram,0x00040048) is written */
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
                    /* WARNING: Read-only address (ram,0x00040174) is written */
  return;
}



// ==== usb_partial_frame_ack @ ram:00003c48 size 196 callers [ram:00004628]

/* usb_partial_frame_ack: local IN reply for an incomplete USB frame: 20 -> "20 04", F4 -> "F5 00 d2
   d3 d4 d5 01" */

void usb_partial_frame_ack(code *param_1)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 auStack_110 [260];
  
  cVar1 = DAT_ram_20003c6c;
  memset(auStack_110,0,0x100);
  if (cVar1 == -0xc) {
    DAT_ram_20003d70 = (undefined *)0xf5;
    DAT_ram_20003d72 = DAT_ram_20003c6e;
    DAT_ram_20003d74 = DAT_ram_20003c70;
    DAT_ram_20003d76 = 1;
    DAT_ram_20003d6e = 7;
  }
  else {
    if (cVar1 != ' ') {
      return;
    }
    DAT_ram_20003d70 = &UNK_csreg_0420;
    DAT_ram_20003d6e = 2;
  }
  DAT_ram_20003d6c = DAT_ram_20003c68 >> 8 | DAT_ram_20003c68 << 8;
  uVar2 = frame_encode(&DAT_ram_20003c68,&DAT_ram_20003d6c,auStack_110);
  (*param_1)(auStack_110,uVar2);
  return;
}



// ==== usb_in_queue_push @ ram:00003d0c size 126 callers [ram:00003d8a]

/* usb_in_queue_push: pushes an encoded frame to the 4-slot USB IN ring (accepts while count < 5) */

void usb_in_queue_push(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  if (usb_in_count < 5) {
    memcpy(&usb_in_ring + (uint)DAT_ram_20003a4d * 0x100,param_1,param_2);
    uVar1 = DAT_ram_20003a4d + 1;
    (&DAT_ram_20003a44)[DAT_ram_20003a4d] = (char)param_2;
    if ((uVar1 & 0xff) < 4) {
      DAT_ram_20003a4d = (byte)uVar1;
    }
    else {
      DAT_ram_20003a4d = 0;
    }
    usb_in_count = usb_in_count + 1;
    return;
  }
  return;
}



// ==== mcu_to_usb_enqueue @ ram:00003d8a size 72 callers [ram:00004628]

/* mcu_to_usb_enqueue: re-encodes a frame from the MCU (dst 1) and queues it for USB IN */

void mcu_to_usb_enqueue(int param_1)

{
  undefined1 uVar1;
  undefined1 auStack_110 [264];
  
  memset(auStack_110,0,0x100);
  uVar1 = frame_encode(&bridge_slots + param_1 * 0x10c,param_1 * 0x218 + 0x20003b54,auStack_110);
  usb_in_queue_push(auStack_110,uVar1);
  return;
}



// ==== slot_forward_to_mcu @ ram:00003dd2 size 72 callers [ram:00004628]

/* slot_forward_to_mcu: re-encodes slot n frame and sends it on UART1 */

void slot_forward_to_mcu(int param_1)

{
  undefined1 uVar1;
  undefined1 auStack_110 [264];
  
  memset(auStack_110,0,0x100);
  uVar1 = frame_encode(&bridge_slots + param_1 * 0x10c,&bridge_slots + param_1 * 0x10c,auStack_110);
  uart1_send(auStack_110,uVar1);
  return;
}



// ==== usb_in_pump @ ram:00003e1a size 188 callers [ram:00004b9c]

/* usb_in_pump: sends the head of the USB IN ring in 62-byte pieces */

void usb_in_pump(void)

{
  byte bVar1;
  
  if ((usb_in_idle != '\0') && (usb_in_count != '\0')) {
    if ((byte)(&DAT_ram_20003a44)[DAT_ram_20003a4b] < 0x3f) {
      usb_ep1_in_send(&usb_in_ring + CONCAT11(DAT_ram_20003a4b,DAT_ram_20003a4c));
      DAT_ram_20003a4c = '\0';
      bVar1 = DAT_ram_20003a4b + 1;
      usb_in_count = usb_in_count + -1;
      DAT_ram_20003a4b = DAT_ram_20003a4b + 1;
      if (3 < bVar1) {
        DAT_ram_20003a4b = 0;
      }
    }
    else {
      usb_ep1_in_send(&usb_in_ring + CONCAT11(DAT_ram_20003a4b,DAT_ram_20003a4c),0x3e);
      (&DAT_ram_20003a44)[DAT_ram_20003a4b] = (&DAT_ram_20003a44)[DAT_ram_20003a4b] + -0x3e;
      DAT_ram_20003a4c = DAT_ram_20003a4c + '>';
    }
    return;
  }
  return;
}



// ==== acc_af02_notify_handle @ ram:00003ed6 size 74 callers [ram:00005af0]

/* acc_af02_notify_handle: handles a stored accessory AF02 notification; "BE FF" forgets the
   accessory */

void acc_af02_notify_handle(char *param_1)

{
  if (*param_1 != '\0') {
    if ((param_1[1] == -0x42) && (param_1[2] == -1)) {
      memset(&acc_peer_addr,0,6);
    }
    memset(param_1,0,*param_1);
    return;
  }
  return;
}



// ==== acc_cmd_b8 @ ram:00003f20 size 26 callers [ram:000045d4]

/* acc_cmd_b8: B8: byte 1 == B0 schedules write "F0 B0" to the accessory AF02 */

undefined4 acc_cmd_b8(int param_1)

{
  if (*(char *)(param_1 + 1) == -0x50) {
    DAT_ram_20004c09 = 1;
  }
  return 0;
}



// ==== acc_cmd_bc_set_addr @ ram:00003f3a size 60 callers [ram:000045d4]

/* acc_cmd_bc_set_addr: BC: sets the accessory BD address (6 bytes) */

undefined4 acc_cmd_bc_set_addr(int param_1)

{
  acc_peer_addr._0_1_ = *(undefined1 *)(param_1 + 1);
  acc_peer_addr._1_1_ = *(undefined1 *)(param_1 + 2);
  acc_peer_addr._2_1_ = *(undefined1 *)(param_1 + 3);
  acc_peer_addr._3_1_ = *(undefined1 *)(param_1 + 4);
  DAT_ram_20002f34._0_1_ = *(undefined1 *)(param_1 + 5);
  DAT_ram_20002f34._1_1_ = *(undefined1 *)(param_1 + 6);
  return 0;
}



// ==== acc_cmd_be_disconnect @ ram:00003f76 size 54 callers [ram:000045d4]

/* acc_cmd_be_disconnect: BE: terminates the accessory link and invalidates the address */

undefined4 acc_cmd_be_disconnect(void)

{
  undefined1 *puVar1;
  
  (*(code *)p_GAPRole_TerminateLink)(DAT_ram_20002f36);
  puVar1 = (undefined1 *)memset(&acc_peer_addr,0,6);
  *puVar1 = 1;
  return 0;
}



// ==== mcu_to_ble_router @ ram:00003fac size 200 callers [ram:00004628]

/* mcu_to_ble_router: MCU reply routing: last byte 0x31 -> AF01 with 0x31 in front, else AF02 minus
   last byte; saves host ID after 19 00 */

void mcu_to_ble_router(int param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char local_120;
  undefined1 auStack_11f [267];
  
  param_1 = param_1 * 0x218;
  pcVar2 = &DAT_ram_20003b58 + param_1;
  uVar3 = *(ushort *)(&DAT_ram_20003b56 + param_1) & 0xff;
  cVar1 = pcVar2[uVar3 - 1];
  if (cVar1 == '1') {
    memset(&local_120,0,0x100);
    (*(code *)p_tmos_memcpy)(auStack_11f,pcVar2,uVar3 - 1);
    local_120 = cVar1;
    af01_notify(&local_120,uVar3);
  }
  else {
    af02_notify(pcVar2,uVar3 - 1 & 0xffff);
  }
  if (*pcVar2 == '\x19') {
    if (notify_failed == '\0' && (&DAT_ram_20003b59)[param_1] == '\0') {
      host_id_save(&pending_host_id);
      ble_bind_state = 2;
    }
  }
  return;
}



// ==== ble_to_mcu_queue @ ram:00004074 size 104 callers [ram:000040dc,ram:00004224,ram:000042ac]

/* ble_to_mcu_queue: copies a GATT write to slot 0 (address 0x62) and appends route tag 0x31 or 0x00
    */

void ble_to_mcu_queue(undefined4 param_1,int param_2,int param_3,undefined4 param_4,
                     undefined4 param_5)

{
  if (param_2 != 0) {
    (*(code *)p_tmos_memcpy)(&DAT_ram_20003a54,param_1,param_2,param_4,param_5,p_tmos_memcpy);
    if (param_3 == 0) {
      (&DAT_ram_20003a54)[param_2] = 0x31;
    }
    else {
      (&DAT_ram_20003a54)[param_2] = 0;
    }
    DAT_ram_20003a52 = (short)param_2 + 1;
    bridge_slots = &UNK_csreg_0206;
    DAT_ram_20003c58 = 1;
    return;
  }
  return;
}



// ==== af02_write_handler @ ram:000040dc size 328 callers []

/* af02_write_handler: AF02: blocked when mode 2; 00 local status; 18 bind; else forward with tag
   0x00 */

void af02_write_handler(char *param_1,int param_2,code *param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 uStack_128;
  undefined1 uStack_127;
  undefined1 uStack_126;
  undefined1 uStack_125;
  undefined1 uStack_124;
  undefined1 uStack_123;
  undefined2 uStack_120;
  undefined1 uStack_11e;
  undefined1 uStack_11d;
  undefined1 uStack_11c;
  undefined1 uStack_11b;
  undefined1 uStack_11a;
  undefined1 uStack_119;
  undefined1 uStack_118;
  undefined1 uStack_117;
  undefined1 uStack_116;
  undefined1 uStack_115;
  undefined1 uStack_114;
  
  cVar1 = *param_1;
  memset(&uStack_120,0,0x100);
  if (host_iface_mode == '\x02') {
    return;
  }
  if (cVar1 == '\0') {
    (*(code *)p_GAPRole_GetParameter)(0x304,&uStack_128);
    uVar3 = 0xd;
    uStack_120 = CONCAT11((char)gaprole_state,1);
    uStack_11e = (undefined1)ble_bind_state;
    uStack_11d = (undefined1)ble_conn_timer;
    uStack_11c = (undefined1)((uint)ble_conn_timer >> 8);
    uStack_11a = (undefined1)((uint)ble_conn_timer >> 0x18);
    uStack_11b = (undefined1)((uint)ble_conn_timer >> 0x10);
    uStack_119 = uStack_128;
    uStack_118 = uStack_127;
    uStack_117 = uStack_126;
    uStack_116 = uStack_125;
    uStack_115 = uStack_124;
    uStack_114 = uStack_123;
LAB_ram_000041d0:
    (*param_3)(&uStack_120,uVar3);
  }
  else {
    if (cVar1 == '\x18') {
      if (param_1[param_2 + -1] != '\0') {
        iVar2 = host_id_lookup(param_1 + 1);
        if (iVar2 == 0) {
          uStack_120 = 0xff19;
          ble_bind_state = 0;
        }
        else {
          uStack_120 = 0x19;
          ble_bind_state = 2;
        }
        uVar3 = 2;
        goto LAB_ram_000041d0;
      }
      (*(code *)p_tmos_memcpy)(&pending_host_id,param_1 + 1,0x10);
    }
    ble_to_mcu_queue(param_1,param_2,1);
  }
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
                    /* WARNING: Read-only address (ram,0x00040178) is written */
  return;
}



// ==== af01_write_handler @ ram:00004224 size 128 callers []

/* af01_write_handler: AF01 (first byte already dropped): blocked when mode 2; 10/C0 local adv tail;
   else forward with tag 0x31 */

void af01_write_handler(char *param_1,undefined4 param_2,code *param_3)

{
  undefined2 local_110;
  undefined1 uStack_10e;
  
  memset(&local_110,0,0x100);
  if (host_iface_mode != '\x02') {
    if ((*param_1 == '\x10') || (*param_1 == -0x40)) {
      adv_mfr_tail_store(param_1 + 1,0xe);
      local_110 = 0xc131;
      uStack_10e = 0;
      (*param_3)(&local_110,3);
    }
    else {
      ble_to_mcu_queue(param_1,param_2,0);
    }
  }
  return;
}



// ==== acc_to_mcu_send @ ram:000042a4 size 8 callers [ram:000042ac,ram:00004486,ram:00005af0]

/* acc_to_mcu_send: calls 0x3810 when length is non-zero */

void acc_to_mcu_send(undefined4 param_1,int param_2)

{
  if (param_2 != 0) {
    acc_to_mcu_queue();
    return;
  }
  return;
}



// ==== link_state_reporter @ ram:000042ac size 474 callers [ram:00004b9c]

/* link_state_reporter: sends BD 00/BD 01 on channel 6 and accessory BD on channel 5 when states
   change */

void link_state_reporter(void)

{
  undefined1 uVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  undefined1 *puVar5;
  uint uVar6;
  undefined2 uStack_54;
  undefined1 auStack_52 [34];
  
  if ((DAT_ram_20002f98 != ble_bind_state) && (DAT_ram_20003c58 == '\0')) {
    if (ble_bind_state == 0) {
      uStack_54 = (undefined *)0xbd;
      ble_to_mcu_queue(&uStack_54,2,0);
    }
    if (ble_bind_state == 2) {
      uStack_54 = &UNK_csreg_01bd;
      ble_to_mcu_queue(&uStack_54,2,0);
    }
    DAT_ram_20002f98 = ble_bind_state;
  }
  if ((DAT_ram_20002f9c != DAT_ram_20002fdb) && (DAT_ram_20004088 == '\0')) {
    if (DAT_ram_20002f9d != DAT_ram_20002fc8) {
      if (DAT_ram_20002fdb == '\0') {
        uStack_54 = (undefined *)0xbd;
        acc_to_mcu_queue(&uStack_54,2);
      }
      if ((DAT_ram_20002fdb == '\x02') && (DAT_ram_20002fc8 == '\x01')) {
        memset(auStack_52,0,0x21);
        uVar1 = 1;
        if (DAT_ram_20002fcf == '\0') {
          uVar1 = 2;
        }
        puVar3 = &DAT_ram_20004b40;
        uStack_54 = (undefined *)CONCAT11(uVar1,0xbd);
        puVar5 = &DAT_ram_20004be5;
        uVar2 = 0;
        do {
          uVar6 = uVar2 & 0xff;
          iVar4 = (*(code *)p_tmos_memcmp)(&acc_peer_addr,puVar5,6);
          if (iVar4 != 0) {
            debug_hexdump(&DAT_ram_20004b4a + uVar2 * 0x1f,puVar3[0xc3],99);
            if (puVar3[0xc3] != '\0') {
              (*(code *)p_tmos_memcpy)(auStack_52,&DAT_ram_20004b4a + uVar2 * 0x1f);
              goto LAB_ram_00004410;
            }
          }
          uVar2 = uVar2 + 1;
          puVar5 = puVar5 + 6;
          puVar3 = puVar3 + 1;
        } while (uVar2 != 5);
        uVar6 = 5;
LAB_ram_00004410:
        acc_to_mcu_send(&uStack_54,(&DAT_ram_20004c03)[uVar6] + '\x02',0);
        memset(&DAT_ram_20004b40,0,0xcc);
      }
      DAT_ram_20002f9c = DAT_ram_20002fdb;
      DAT_ram_20002f9d = DAT_ram_20002fc8;
    }
  }
  return;
}



// ==== acc_list_build_bb @ ram:00004486 size 334 callers [ram:000045d4]

/* acc_list_build_bb: builds "BB n {addr6 len name}" accessory list for the MCU */

uint acc_list_build_bb(undefined1 *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  *param_1 = 0xbb;
  param_1[1] = DAT_ram_20004c08;
  uVar1 = 2;
  for (uVar4 = 0; uVar4 < DAT_ram_20004c08; uVar4 = uVar4 + 1 & 0xff) {
    iVar2 = uVar4 * 6;
    uVar5 = uVar1 + 7;
    param_1[uVar1] = (&DAT_ram_20004be5)[iVar2];
    param_1[uVar1 + 1 & 0xff] = (&DAT_ram_20004be6)[iVar2];
    param_1[uVar1 + 2 & 0xff] = (&DAT_ram_20004be7)[iVar2];
    param_1[uVar1 + 3 & 0xff] = (&DAT_ram_20004be8)[iVar2];
    param_1[uVar1 + 4 & 0xff] = (&DAT_ram_20004be9)[iVar2];
    param_1[uVar1 + 5 & 0xff] = (&DAT_ram_20004bea)[iVar2];
    param_1[uVar1 + 6 & 0xff] = (&DAT_ram_20004c03)[uVar4];
    for (uVar3 = 0; uVar1 = uVar3 + (uVar5 & 0xff) & 0xff, uVar3 < (byte)(&DAT_ram_20004c03)[uVar4];
        uVar3 = uVar3 + 1 & 0xff) {
      param_1[uVar1] = (&DAT_ram_20004b4a)[uVar4 * 0x1f + uVar3];
    }
  }
  acc_to_mcu_send(param_1,uVar1,0);
  if ((byte)(DAT_ram_20002f94 + 1U) < 0xf) {
    if (ble_bind_state == 0) {
      DAT_ram_20002f94 = DAT_ram_20002f94 + '\x01';
      return uVar1;
    }
  }
  else if (ble_bind_state == 0) {
    DAT_ram_20002f94 = DAT_ram_20002f94 + '\x01';
    memset(&DAT_ram_20004b40,0,0xcc);
  }
  DAT_ram_20002f94 = 0;
  return uVar1;
}



// ==== acc_cmd_dispatch @ ram:000045d4 size 84 callers [ram:00004628]

/* acc_cmd_dispatch: channel 5 commands from the MCU: B8, BA, BC, BE */

void acc_cmd_dispatch(int param_1)

{
  byte bVar1;
  
  param_1 = param_1 * 0x218;
  bVar1 = (&DAT_ram_20003b58)[param_1];
  if (bVar1 == 0xba) {
    acc_list_build_bb(&DAT_ram_20003b58 + param_1,(&DAT_ram_20003b56)[param_1]);
    return;
  }
  if (bVar1 < 0xbb) {
    if (bVar1 != 0xb8) {
      return;
    }
    acc_cmd_b8();
    return;
  }
  if (bVar1 == 0xbc) {
    acc_cmd_bc_set_addr();
    return;
  }
  if (bVar1 != 0xbe) {
    return;
  }
  acc_cmd_be_disconnect();
  return;
}



// ==== bridge_loop @ ram:00004628 size 414 callers [ram:00004b9c]

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* bridge_loop: main bridge scheduler (MCU->BLE/USB/acc/ctl, USB->MCU, BLE->MCU, 55 status) */

void bridge_loop(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined2 uStack_14;
  
  if (DAT_ram_20002f8c != '\0') {
    mcu_frame_seen = '\x01';
    DAT_ram_20002f8c = '\0';
    mcu_to_ble_router(0);
  }
  if (DAT_ram_20002f8d != '\0') {
    mcu_frame_seen = '\x01';
    DAT_ram_20002f8d = '\0';
    mcu_to_usb_enqueue(1);
  }
  if (DAT_ram_20002f8e != '\0') {
    mcu_frame_seen = '\x01';
    DAT_ram_20002f8e = '\0';
    acc_cmd_dispatch(2);
  }
  if (DAT_ram_20002f8f == '\0') {
    if (DAT_ram_20002f90 == 0) {
      if (DAT_ram_20003c58 == '\0') {
        if (DAT_ram_200042a0 == '\0' && DAT_ram_20004088 == '\0') {
          if (mcu_frame_seen == '\0') {
            return;
          }
          DAT_ram_200041a1 = (usb_in_count < 4) + -1;
          DAT_ram_200041a2 = -(notify_failed != '\0');
          _DAT_ram_2000419c = 0x30203;
          DAT_ram_200041a0 = 0x55;
          uStack_1c = 0;
          uStack_18 = 0;
          uStack_14 = 0;
          uVar1 = frame_encode(&DAT_ram_20004098,&DAT_ram_2000419c,&uStack_1c);
          uart1_send(&uStack_1c,uVar1);
          mcu_frame_seen = 0;
          return;
        }
        if (DAT_ram_20004088 == '\0') {
          DAT_ram_200042a0 = '\0';
          uVar2 = 3;
        }
        else {
          DAT_ram_20004088 = '\0';
          uVar2 = 2;
        }
      }
      else {
        DAT_ram_20003c58 = '\0';
        uVar2 = 0;
      }
      slot_forward_to_mcu(uVar2);
    }
    else {
      if (DAT_ram_20003e70 == '\0') {
        if (usb_in_idle == '\0') {
          return;
        }
        usb_partial_frame_ack();
      }
      else {
        DAT_ram_20003e70 = '\0';
        slot_forward_to_mcu(1);
      }
      DAT_ram_20002f90 = 0;
    }
  }
  else {
    mcu_frame_seen = '\x01';
    DAT_ram_20002f8f = '\0';
    mcu_ctl_cmd(uart1_send);
  }
  return;
}



// ==== FUN_ram_000047c6 @ ram:000047c6 size 2 callers [ram:00004b14]

void FUN_ram_000047c6(void)

{
  return;
}



// ==== FUN_ram_000047c8 @ ram:000047c8 size 54 callers [ram:0000780e]

void FUN_ram_000047c8(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  do {
    iVar2 = (int)&bridge_slots + iVar1;
    iVar1 = iVar1 + 0x218;
    FUN_ram_00003598(iVar2);
  } while (iVar1 != 0x860);
  return;
}



// ==== name_variant_flag @ ram:000047fe size 18 callers [ram:00006cb0]

/* name_variant_flag: returns RAM 0x200043B7 == 0xA5 (never true in this image) */

bool name_variant_flag(void)

{
  return name_variant_magic == -0x5b;
}



// ==== rgb_led_init @ ram:00004810 size 178 callers [ram:00004b14]

/* rgb_led_init: PWM4 (PA12), PWM7 (PB4), PWM10 (PB14) outputs; TMR0 capture on PB23 */

void rgb_led_init(void)

{
  dword dVar1;
  byte bVar2;
  
  dVar1 = PA_OUT;
  PA_OUT = dVar1 | 0x1000;
  dVar1 = PB_OUT;
  PB_OUT = dVar1 | 0x4010;
  GPIOA_ModeCfg(0x1000,4);
  GPIOB_ModeCfg(0x4010,4);
  PWM_CONTROL._3_1_ = 0xf0;
  PWMX_CycleCfg(1);
  PWMX_ACTOUT(1,0,1,0);
  PWMX_ACTOUT(8,0,1,0);
  PWMX_ACTOUT(0x40,0,1,0);
  GPIOPinRemap(1,1);
  GPIOB_ModeCfg(0x800000,0);
  TMR0_CapInit(1);
  TMR0_CNT_END = 6000;
  bVar2 = TMR0_CONTROL._2_1_;
  TMR0_CONTROL._2_1_ = bVar2 | 2;
  DAT_ram_e000e410 = 0;
  DAT_ram_e000e100 = 0x10000;
  return;
}



// ==== pwm_set_channel @ ram:000048c2 size 84 callers [ram:00004916]

/* pwm_set_channel: sets one LED PWM channel duty */

void pwm_set_channel(int param_1,uint param_2)

{
  if (param_2 == 0) {
    if (param_1 == 1) {
      PWM4_7_DATA._0_1_ = 0;
      return;
    }
    if (param_1 == 8) {
      PWM4_7_DATA._3_1_ = 0;
      return;
    }
    if (param_1 == 0x40) {
      PWM8_11_DATA._2_1_ = 0;
    }
  }
  else if (((param_1 == 1) || (param_1 == 8)) || (param_1 == 0x40)) {
    PWMX_ACTOUT(param_1,param_2 & 0xff,1,1);
    return;
  }
  return;
}



// ==== rgb_led_set_grb @ ram:00004916 size 78 callers [ram:00004964]

/* rgb_led_set_grb: sets G/R/B PWM from a 24-bit GRB value */

void rgb_led_set_grb(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1 >> 8 & 0xff;
  uVar2 = param_1 >> 0x10 & 0xff;
  printf("GRB:(%d,%d,%d)",uVar2,uVar1,param_1 & 0xff);
  pwm_set_channel(0x40,uVar2);
  pwm_set_channel(1,uVar1);
  pwm_set_channel(8,param_1 & 0xff);
  return;
}



// ==== ws2812_rx_decode @ ram:00004964 size 340 callers [ram:00004bb8]

/* ws2812_rx_decode: decodes a captured 24-bit GRB pulse train (TMR0 capture) */

void ws2812_rx_decode(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  if ((0x5f < DAT_ram_20002fa4) && (DAT_ram_20002fa0 != 0)) {
    uVar4 = 0;
    uVar5 = 0;
    uVar3 = 0;
    do {
      uVar2 = (&DAT_ram_200043c0)[uVar4] & 0xffffff;
      if (uVar2 < 100) {
        uVar1 = (uint)(&DAT_ram_200043c0)[uVar4] >> 0x19 & 1;
        if ((uVar1 != 0) && (uVar5 < 0x18)) {
          uVar3 = uVar3 << 1;
          if (0x28 < uVar2) {
            uVar3 = uVar3 | 1;
          }
          uVar5 = uVar5 + 1;
        }
        if (DAT_ram_20002f2c == uVar1) {
          DAT_ram_20002fa8 = DAT_ram_20002fa8 + 1;
          putchar(0x2d);
        }
        DAT_ram_20002f2c = uVar1;
        printf("%d,%d,%d,%d\n",uVar1,uVar2,uVar5,uVar3);
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < DAT_ram_20002fa4);
    printf("------------%d,%d\n",DAT_ram_20002fac,DAT_ram_20002fa8);
    DAT_ram_20002fa8 = 0;
    DAT_ram_20002f2c = 2;
    DAT_ram_20002fa4 = 0;
    rgb_led_set_grb(uVar3);
    return;
  }
  return;
}



// ==== update_prep_countdown @ ram:00004ab8 size 92 callers [ram:00004bb2]

/* update_prep_countdown: after F0 AC: USB off, write IAP flag, soft reset */

void update_prep_countdown(uint param_1)

{
  if (DAT_ram_20002fb8 == 0) {
    return;
  }
  if (param_1 < DAT_ram_20002fb6) {
    param_1 = DAT_ram_20002fb6 - param_1;
    DAT_ram_20002fb6 = (ushort)(param_1 * 0x10000 >> 0x10);
    if ((param_1 & 0xffff) != 0) {
      return;
    }
  }
  else {
    DAT_ram_20002fb6 = 0;
  }
  if (DAT_ram_20002fb8 != 1) {
    DAT_ram_20002fb8 = 0;
    return;
  }
  usb_disable();
  enter_iap();
  DAT_ram_20002fb8 = 0;
  return;
}



// ==== periph_init @ ram:00004b14 size 136 callers [ram:000072e0]

/* periph_init: UART1, LED, USB off, TMR1 1 ms, TMR2 100 ms */

void periph_init(void)

{
  byte bVar1;
  
  FUN_ram_000047c6();
  uart1_init();
  rgb_led_init();
  usb_disable();
  bVar1 = TMR1_CONTROL._0_1_;
  TMR1_CONTROL._0_1_ = bVar1 | 4;
  TMR1_TimerInit(60000);
  bVar1 = TMR1_CONTROL._2_1_;
  TMR1_CONTROL._2_1_ = bVar1 | 1;
  DAT_ram_e000e100 = 0x1000000;
  bVar1 = TMR2_CONTROL._0_1_;
  TMR2_CONTROL._0_1_ = bVar1 | 4;
  TMR2_TimerInit(6000000);
  bVar1 = TMR2_CONTROL._2_1_;
  TMR2_CONTROL._2_1_ = bVar1 | 1;
  DAT_ram_e000e100 = 0x2000000;
  DAT_ram_20002fb5 = 1;
  return;
}



// ==== bridge_tick @ ram:00004b9c size 22 callers [ram:00004bb8]

/* bridge_tick: bridge_loop, link_state_reporter, usb_in_pump */

void bridge_tick(void)

{
  bridge_loop(1);
  link_state_reporter();
  usb_in_pump(1);
  return;
}



// ==== FUN_ram_00004bb2 @ ram:00004bb2 size 6 callers [ram:00004bb8]

void FUN_ram_00004bb2(void)

{
  update_prep_countdown(100);
  return;
}



// ==== periodic_dispatch @ ram:00004bb8 size 40 callers [ram:00006cb0]

/* periodic_dispatch: 1 ms, 10 ms, 100 ms flag dispatch (called from TMOS event 0x800) */

void periodic_dispatch(void)

{
  int iVar1;
  
  iVar1 = FUN_ram_00003798();
  if (iVar1 != 0) {
    bridge_tick();
  }
  iVar1 = FUN_ram_000037b0();
  if (iVar1 != 0) {
    ws2812_rx_decode();
  }
  iVar1 = FUN_ram_000037c8();
  if (iVar1 != 0) {
    FUN_ram_00004bb2();
  }
  FUN_ram_000037e0();
  FUN_ram_000037f8();
  return;
}



// ==== get_uptime_ms @ ram:00004be0 size 12 callers [ram:0000388a]

/* get_uptime_ms: returns RAM 0x20002FBC (ms, 100 ms resolution) */

undefined4 get_uptime_ms(void)

{
  return uptime_ms;
}



// ==== uart1_frame_decode_byte @ ram:00004bec size 258 callers [ram:00004cee]

/* uart1_frame_decode_byte: decoder for frames from the main MCU */

void uart1_frame_decode_byte(uint param_1)

{
  byte bVar1;
  uint uVar2;
  
  bVar1 = (byte)param_1;
  if (param_1 == 0xaa) {
    DAT_ram_20004561 = DAT_ram_20004561 + 1;
    if ((DAT_ram_20004561 & 1) != 0) {
      return;
    }
  }
  else if ((DAT_ram_20004561 & 1) != 0) {
    DAT_ram_20004561 = 0;
    goto switchD_ram_00004c6a_caseD_1;
  }
  switch(DAT_ram_20004668) {
  case 0:
    goto switchD_ram_00004c6a_caseD_0;
  case 1:
switchD_ram_00004c6a_caseD_1:
    DAT_ram_2000466c = bVar1;
    DAT_ram_20004565 = bVar1 & 0xf;
    uart1_rx_frame = (char)(param_1 >> 4);
    DAT_ram_20004668 = 4;
    return;
  case 4:
    if (param_1 != 0) {
      DAT_ram_20004562 = 0;
      DAT_ram_20004566 = (short)param_1;
      DAT_ram_20004668 = 6;
      DAT_ram_2000466c = bVar1 + DAT_ram_2000466c;
      return;
    }
    break;
  case 6:
    uVar2 = DAT_ram_20004562 + 1;
    (&DAT_ram_20004568)[DAT_ram_20004562] = bVar1;
    DAT_ram_20004562 = (byte)uVar2;
    if ((uVar2 & 0xff) < (uint)DAT_ram_20004566) {
      DAT_ram_2000466c = bVar1 + DAT_ram_2000466c;
      return;
    }
    DAT_ram_20004668 = 7;
    DAT_ram_2000466c = bVar1 + DAT_ram_2000466c;
    return;
  case 7:
    if (DAT_ram_2000466c == param_1) {
      DAT_ram_20004560 = 1;
    }
  }
  DAT_ram_20004668 = 0;
switchD_ram_00004c6a_caseD_0:
  return;
}



// ==== uart1_rx_route @ ram:00004cee size 234 callers [ram:2000277e]

/* uart1_rx_route: routes decoded MCU frames by low nibble: 6 BLE, 1 USB, 5 accessory, other CH58x
    */

void uart1_rx_route(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar3 = (uint)DAT_ram_20004770;
  for (uVar2 = 0; (uVar2 & 0xff) < uVar3; uVar2 = uVar2 + 1) {
    uart1_frame_decode_byte((&DAT_ram_20004670)[uVar2]);
  }
  if (DAT_ram_20004560 != '\0') {
    DAT_ram_20004560 = '\0';
    cVar1 = DAT_ram_20004565;
    if (DAT_ram_20004565 == '\x06') {
      uVar4 = slot_rx_frame_ptr(0);
      memcpy(uVar4,&uart1_rx_frame,0x104);
      DAT_ram_20002f8c = 1;
    }
    else if (DAT_ram_20004565 == '\x01') {
      uVar4 = slot_rx_frame_ptr(1);
      memcpy(uVar4,&uart1_rx_frame,0x104);
      DAT_ram_20002f8d = cVar1;
    }
    else if (DAT_ram_20004565 == '\x05') {
      uVar4 = slot_rx_frame_ptr(2);
      memcpy(uVar4,&uart1_rx_frame,0x104);
      DAT_ram_20002f8e = 1;
    }
    else {
      uVar4 = slot_rx_frame_ptr(3);
      memcpy(uVar4,&uart1_rx_frame,0x104);
      DAT_ram_20002f8f = 1;
    }
  }
  return;
}



// ==== uart1_send @ ram:00004dd8 size 4 callers [ram:00003dd2,ram:00004628]

void uart1_send(undefined1 *param_1,uint param_2)

{
  char cVar1;
  
  while (param_2 != 0) {
    cVar1 = UART1_FIFO._3_1_;
    if (cVar1 != '\b') {
      UART1_FIFO._0_1_ = *param_1;
      param_2 = param_2 - 1 & 0xffff;
      param_1 = param_1 + 1;
    }
  }
  return;
}



// ==== uart1_init @ ram:00004ddc size 60 callers []

/* uart1_init: PA8 RX pull-up, PA9 TX, UART1 115200, RX interrupts */

void uart1_init(void)

{
  GPIOA_ModeCfg(0x100,1);
  GPIOA_ModeCfg(0x200,3);
  uart1_init_115200();
  FUN_ram_000028d0(3);
  FUN_ram_000028ea(1,3);
  DAT_ram_e000e100 = 0x8000000;
  return;
}



// ==== uart1_init @ ram:00004e18 size 2 callers [ram:00004b14]

void uart1_init(void)

{
  GPIOA_ModeCfg(0x100,1);
  GPIOA_ModeCfg(0x200,3);
  uart1_init_115200();
  FUN_ram_000028d0(3);
  FUN_ram_000028ea(1,3);
  DAT_ram_e000e100 = 0x8000000;
  return;
}



// ==== debug_hexdump @ ram:00004e1a size 108 callers [ram:000042ac,ram:00005af0,ram:000065a0]

/* debug_hexdump: printf hex dump (output discarded) */

void debug_hexdump(undefined1 *param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  
  printf("Data-%x:");
  puVar1 = param_1 + param_2;
  if (param_3 == 99) {
    for (; param_1 != puVar1; param_1 = param_1 + 1) {
      printf(&DAT_ram_00008f18,*param_1);
    }
  }
  else {
    for (; param_1 != puVar1; param_1 = param_1 + 1) {
      printf(&DAT_ram_00008f1c,*param_1);
    }
  }
  putchar(10);
  return;
}



// ==== usb_ep1_out_handler @ ram:00004e86 size 68 callers [ram:00004fba]

/* usb_ep1_out_handler: feeds report bytes 2..2+n-1 (n = byte 1) to the slot 1 decoder */

void usb_ep1_out_handler(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (uint)*(byte *)(DAT_ram_20002f54 + 1) + DAT_ram_20002f54;
  for (iVar1 = DAT_ram_20002f54; iVar1 != iVar2; iVar1 = iVar1 + 1) {
    decoder_feed_slot(1,*(undefined1 *)(iVar1 + 2));
  }
  DAT_ram_20002f90 = usb_ep1_in_send;
  return;
}



// ==== usb_ep1_in_send @ ram:00004eca size 114 callers [ram:00003e1a]

/* usb_ep1_in_send: builds IN report [02][n][n bytes][zero pad] and arms EP1 */

void usb_ep1_in_send(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = DAT_ram_20002f54;
  memset(DAT_ram_20002f54 + 0x42,0,0x3e);
  for (uVar3 = 0; iVar2 = DAT_ram_20002f54, uVar3 < param_2; uVar3 = uVar3 + 1 & 0xff) {
    *(undefined1 *)(iVar1 + uVar3 + 0x42) = *(undefined1 *)(param_1 + uVar3);
  }
  *(char *)(DAT_ram_20002f54 + 0x41) = (char)param_2;
  *(undefined1 *)(iVar2 + 0x40) = 2;
  usb_ep1_in_arm(0x40);
  usb_in_idle = 0;
  return;
}



// ==== usb_ep2_echo @ ram:00004f3c size 42 callers [ram:00004fba]

/* usb_ep2_echo: WCH sample leftover: EP2 OUT echoed inverted */

void usb_ep2_echo(uint param_1)

{
  uint uVar1;
  
  for (uVar1 = 0; (uVar1 & 0xff) < param_1; uVar1 = uVar1 + 1) {
    ((byte *)(DAT_ram_20002f58 + uVar1))[0x40] = ~*(byte *)(DAT_ram_20002f58 + uVar1);
  }
  FUN_ram_00002a74();
  return;
}



// ==== usb_ep3_echo @ ram:00004f66 size 42 callers [ram:00004fba]

/* usb_ep3_echo: WCH sample leftover: EP3 OUT echoed inverted */

void usb_ep3_echo(uint param_1)

{
  uint uVar1;
  
  for (uVar1 = 0; (uVar1 & 0xff) < param_1; uVar1 = uVar1 + 1) {
    ((byte *)(DAT_ram_20002f5c + uVar1))[0x40] = ~*(byte *)(DAT_ram_20002f5c + uVar1);
  }
  FUN_ram_00002a8a();
  return;
}



// ==== usb_ep4_echo @ ram:00004f90 size 42 callers [ram:00004fba]

/* usb_ep4_echo: WCH sample leftover: EP4 OUT echoed inverted */

void usb_ep4_echo(uint param_1)

{
  uint uVar1;
  
  for (uVar1 = 0; (uVar1 & 0xff) < param_1; uVar1 = uVar1 + 1) {
    *(byte *)(DAT_ram_20002f50 + uVar1 + 0x80) = ~*(byte *)(DAT_ram_20002f50 + uVar1 + 0x40);
  }
  FUN_ram_00002aa0();
  return;
}



// ==== usb_irq_handler @ ram:00004fba size 1344 callers [ram:200027fe]

/* usb_irq_handler: USB device interrupt: EP0 standard requests, EP1 in/out */

void usb_irq_handler(void)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  byte bVar6;
  undefined1 uVar7;
  byte bVar8;
  ushort uVar9;
  
  bVar2 = USB_STATUS._2_1_;
  if ((bVar2 & 2) == 0) {
    if ((bVar2 & 1) == 0) {
      if ((bVar2 & 4) == 0) {
        USB_STATUS._2_1_ = bVar2;
        goto LAB_ram_000052ec;
      }
      bVar6 = USB_STATUS._1_1_;
      if ((bVar6 & 4) != 0) {
        usb_in_count = 0;
        DAT_ram_20003a4b = 0;
        DAT_ram_20003a4d = 0;
        DAT_ram_20003a4c = 0;
        usb_in_idle = 1;
      }
      uVar7 = 4;
    }
    else {
      USB_CONTROL._3_1_ = 0;
      USB_EP0_CTRL._2_1_ = 2;
      USB_EP1_CTRL._2_1_ = 0x12;
      USB_EP2_CTRL._2_1_ = 0x12;
      USB_EP3_CTRL._2_1_ = 0x12;
      uVar7 = 1;
    }
    goto LAB_ram_000052e8;
  }
  bVar6 = USB_STATUS._3_1_;
  if ((bVar6 & 0x30) != 0x30) {
    bVar6 = USB_STATUS._3_1_;
    bVar8 = bVar6 & 0x3f;
    if (bVar8 == 4) {
      bVar6 = USB_STATUS._3_1_;
      if ((bVar6 & 0x40) != 0) {
        bVar6 = USB_EP4_CTRL._2_1_;
        USB_EP4_CTRL._2_1_ = bVar6 ^ 0x80;
        bVar6 = USB_RX_LEN;
        usb_ep4_echo(bVar6);
      }
    }
    else if (bVar8 < 5) {
      if (bVar8 == 1) {
        bVar6 = USB_STATUS._3_1_;
        if ((bVar6 & 0x40) != 0) {
          bVar6 = USB_RX_LEN;
          usb_ep1_out_handler();
        }
      }
      else if ((bVar6 & 0x3f) == 0) {
        bVar6 = USB_RX_LEN;
      }
      else if (bVar8 == 2) {
        bVar6 = USB_STATUS._3_1_;
        if ((bVar6 & 0x40) != 0) {
          bVar6 = USB_RX_LEN;
          usb_ep2_echo(bVar6);
        }
      }
      else if ((bVar8 == 3) && (bVar6 = USB_STATUS._3_1_, (bVar6 & 0x40) != 0)) {
        bVar6 = USB_RX_LEN;
        usb_ep3_echo(bVar6);
      }
    }
    else if (bVar8 == 0x22) {
      bVar6 = USB_EP2_CTRL._2_1_;
      USB_EP2_CTRL._2_1_ = bVar6 & 0xfc | 2;
    }
    else if (bVar8 < 0x23) {
      if (bVar8 == 0x20) {
        if (DAT_ram_20002fc1 == 5) {
          bVar6 = USB_CONTROL._3_1_;
          USB_CONTROL._3_1_ = bVar6 & 0x80 | (byte)DAT_ram_20002fc2;
LAB_ram_00005184:
          bVar6 = 2;
        }
        else {
          if (DAT_ram_20002fc1 != 6) {
            USB_EP0_CTRL._0_1_ = 0;
            goto LAB_ram_00005184;
          }
          uVar4 = (uint)DAT_ram_20002fc2;
          if (0x40 < uVar4) {
            uVar4 = 0x40;
          }
          memcpy(DAT_ram_20002f50,DAT_ram_20002fc4,uVar4);
          DAT_ram_20002fc2 = DAT_ram_20002fc2 - (short)uVar4;
          DAT_ram_20002fc4 = DAT_ram_20002fc4 + uVar4;
          USB_EP0_CTRL._0_1_ = (char)uVar4;
          bVar6 = USB_EP0_CTRL._2_1_;
          bVar6 = bVar6 ^ 0x40;
        }
        USB_EP0_CTRL._2_1_ = bVar6;
      }
      else if (bVar8 == 0x21) {
        bVar6 = USB_EP1_CTRL._2_1_;
        USB_EP1_CTRL._2_1_ = bVar6 & 0xfc | 2;
        usb_in_idle = 1;
      }
    }
    else if (bVar8 == 0x23) {
      bVar6 = USB_EP3_CTRL._2_1_;
      USB_EP3_CTRL._2_1_ = bVar6 & 0xfc | 2;
    }
    else if (bVar8 == 0x24) {
      bVar6 = USB_EP4_CTRL._2_1_;
      USB_EP4_CTRL._2_1_ = bVar6 ^ 0x40;
      bVar6 = USB_EP4_CTRL._2_1_;
      USB_EP4_CTRL._2_1_ = bVar6 & 0xfc | 2;
    }
    USB_STATUS._2_1_ = 2;
  }
  cVar3 = USB_STATUS._3_1_;
  if (-1 < cVar3) goto LAB_ram_000052ec;
  USB_EP0_CTRL._2_1_ = 0xc2;
  DAT_ram_20002fc2 = *(ushort *)(DAT_ram_20002f50 + 6);
  DAT_ram_20002fc1 = DAT_ram_20002f50[1];
  bVar6 = *DAT_ram_20002f50;
  if ((bVar6 & 0x60) != 0) {
switchD_ram_00005082_caseD_2:
    uVar7 = 0xcf;
    goto LAB_ram_000052de;
  }
  switch(DAT_ram_20002fc1) {
  case 0:
    *DAT_ram_20002f50 = 0;
    DAT_ram_20002f50[1] = 0;
    uVar9 = 2;
    if (2 < DAT_ram_20002fc2) goto LAB_ram_00005388;
    break;
  case 1:
    if ((bVar6 & 0x1f) != 2) goto switchD_ram_00005082_caseD_2;
    bVar8 = DAT_ram_20002f50[4];
    if (bVar8 == 2) {
      bVar8 = USB_EP2_CTRL._2_1_;
      bVar8 = bVar8 & 0x73;
LAB_ram_00005448:
      USB_EP2_CTRL._2_1_ = bVar8;
    }
    else {
      if (bVar8 < 3) {
        if (bVar8 != 1) goto switchD_ram_00005082_caseD_2;
        bVar8 = USB_EP1_CTRL._2_1_;
        bVar8 = bVar8 & 0x73;
      }
      else {
        if (bVar8 != 0x81) {
          if (bVar8 == 0x82) {
            bVar8 = USB_EP2_CTRL._2_1_;
            bVar8 = bVar8 & 0xbc | 2;
            goto LAB_ram_00005448;
          }
          goto switchD_ram_00005082_caseD_2;
        }
        bVar8 = USB_EP1_CTRL._2_1_;
        bVar8 = bVar8 & 0xbc | 2;
      }
      USB_EP1_CTRL._2_1_ = bVar8;
    }
    break;
  default:
    goto switchD_ram_00005082_caseD_2;
  case 5:
    uVar9 = (ushort)DAT_ram_20002f50[2];
    goto LAB_ram_00005388;
  case 6:
    uVar9 = *(ushort *)(DAT_ram_20002f50 + 2);
    uVar1 = uVar9 >> 8;
    if (uVar1 == 2) {
      DAT_ram_20002fc4 = &usb_config_desc;
      iVar5 = 0;
      uVar9 = 0x29;
    }
    else if (uVar1 < 3) {
      if (uVar1 == 1) {
        DAT_ram_20002fc4 = &usb_device_desc;
        iVar5 = 0;
        uVar9 = 0x12;
      }
      else {
LAB_ram_00005234:
        iVar5 = 0xff;
        uVar9 = 0;
      }
    }
    else if (uVar1 == 3) {
      if ((uVar9 & 0xff) == 1) {
        DAT_ram_20002fc4 = &usb_string1_manufacturer;
        iVar5 = 0;
        uVar9 = 0xe;
      }
      else if ((uVar9 & 0xff) == 0) {
        DAT_ram_20002fc4 = &usb_string0_langid;
        iVar5 = 0;
        uVar9 = 4;
      }
      else {
        if ((uVar9 & 0xff) != 2) goto LAB_ram_00005234;
        DAT_ram_20002fc4 = &usb_string2_product;
        iVar5 = 0;
        uVar9 = (ushort)usb_string2_product;
      }
    }
    else {
      if (uVar1 != 0x22) goto LAB_ram_00005234;
      if (DAT_ram_20002f50[4] == 0) {
        DAT_ram_20002fc4 = &usb_hid_report_desc;
        iVar5 = 0;
        uVar9 = 0x23;
      }
      else {
        iVar5 = 0;
        uVar9 = 0xff;
      }
    }
    if (uVar9 < DAT_ram_20002fc2) {
      DAT_ram_20002fc2 = uVar9;
    }
    uVar4 = (uint)DAT_ram_20002fc2;
    if (0x40 < uVar4) {
      uVar4 = 0x40;
    }
    memcpy(DAT_ram_20002f50,DAT_ram_20002fc4,uVar4);
    DAT_ram_20002fc4 = DAT_ram_20002fc4 + uVar4;
    if (iVar5 == 0xff) goto switchD_ram_00005082_caseD_2;
    break;
  case 8:
    *DAT_ram_20002f50 = DAT_ram_20002fc0;
    goto LAB_ram_0000539e;
  case 9:
    DAT_ram_20002fc0 = DAT_ram_20002f50[2];
    break;
  case 10:
    *DAT_ram_20002f50 = 0;
LAB_ram_0000539e:
    if (1 < DAT_ram_20002fc2) {
      uVar9 = 1;
LAB_ram_00005388:
      DAT_ram_20002fc2 = uVar9;
    }
  }
  uVar7 = 0;
  if ((char)bVar6 < '\0') {
    uVar9 = DAT_ram_20002fc2;
    if (0x40 < DAT_ram_20002fc2) {
      uVar9 = 0x40;
    }
    DAT_ram_20002fc2 = DAT_ram_20002fc2 - uVar9;
    uVar7 = (undefined1)uVar9;
  }
  USB_EP0_CTRL._0_1_ = uVar7;
  uVar7 = 0xc0;
LAB_ram_000052de:
  USB_EP0_CTRL._2_1_ = uVar7;
  uVar7 = 2;
LAB_ram_000052e8:
  USB_STATUS._2_1_ = uVar7;
LAB_ram_000052ec:
  if ((bVar2 & 0x20) != 0) {
    usb_in_idle = 1;
  }
  return;
}



// ==== usb_product_string_from_flash @ ram:000054fa size 198 callers [ram:000055c0]

/* usb_product_string_from_flash: builds USB string 2 from the DataFlash 0x6E0E name override */

void usb_product_string_from_flash(void)

{
  int iVar1;
  char cVar2;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined1 *puVar3;
  char cVar4;
  uint uVar5;
  undefined1 auStack_20 [24];
  
  (*(code *)p_tmos_memset)(auStack_20,0xff,0xe,in_a3,in_a4,p_tmos_memset);
  FLASH_EEPROM_CMD(0xb,0x6e00,&DAT_ram_200042b0,0x16);
  iVar1 = (*(code *)p_tmos_memcmp)(auStack_20,&DAT_ram_200042be,8);
  if (iVar1 == 0) {
    puVar3 = &DAT_ram_200042b0;
    cVar4 = '\0';
    do {
      cVar2 = cVar4 + '\x01';
      if ((puVar3[0xe] & 0xdf) == 0) break;
      puVar3 = puVar3 + 1;
      cVar4 = cVar2;
    } while (cVar2 != '\b');
    usb_string2_product = (cVar4 + '\x01') * '\x02';
    DAT_ram_20002e45 = 3;
    for (uVar5 = 2; uVar5 < usb_string2_product; uVar5 = uVar5 + 2 & 0xff) {
      (&usb_string2_product)[uVar5] = *(undefined1 *)((uVar5 >> 1) + 0x200042bd);
      (&DAT_ram_20002e45)[uVar5] = 0;
    }
  }
  return;
}



// ==== usb_enable @ ram:000055c0 size 170 callers [ram:0000388a]

/* usb_enable: starts the USB device */

void usb_enable(void)

{
  int iVar1;
  
  usb_product_string_from_flash();
  decoder_reset_slot(1);
  iVar1 = (int)DAT_ram_20002f54;
  usb_in_idle = 1;
  usb_enabled = 1;
  usb_in_count = 0;
  DAT_ram_20003a4b = 0;
  DAT_ram_20003a4d = 0;
  DAT_ram_20003a4c = 0;
  memset((int)DAT_ram_20002f54 + 0x40,0,0x40);
  memset(iVar1,0,0x40);
  DAT_ram_20002f50 = &DAT_ram_20004774;
  DAT_ram_20002f54 = &DAT_ram_20004834;
  DAT_ram_20002f58 = &DAT_ram_200048b4;
  DAT_ram_20002f5c = &DAT_ram_20004934;
  usb_hw_init();
  DAT_ram_e000e100 = 0x400000;
  return;
}



// ==== usb_disable @ ram:0000566a size 86 callers [ram:0000388a,ram:00004ab8,ram:00004b14]

/* usb_disable: stops the USB device and detaches */

void usb_disable(void)

{
  DAT_ram_e000e180 = 0x400000;
  usb_hw_off();
  GPIOB_ModeCfg(0x800,2);
  GPIOB_ModeCfg(0x400,2);
  decoder_reset_slot(1);
  usb_in_count = 0;
  DAT_ram_20003a4b = 0;
  DAT_ram_20003a4d = 0;
  DAT_ram_20003a4c = 0;
  usb_enabled = 0;
  return;
}



// ==== FUN_ram_000056c0 @ ram:000056c0 size 2 callers []

void FUN_ram_000056c0(void)

{
  return;
}



// ==== FUN_ram_000056c2 @ ram:000056c2 size 12 callers []

void FUN_ram_000056c2(void)

{
  DAT_ram_20002fd8 = 1;
  return;
}



// ==== central_passcode_cb @ ram:000056ce size 48 callers []

/* WARNING: Removing unreachable block (ram,0x000056e8) */
/* central_passcode_cb: GAPBondMgr_PasscodeRsp with a random 6-digit code */

void central_passcode_cb(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = (*(code *)p_tmos_rand)();
  (*(code *)p_GAPBondMgr_PasscodeRsp)(param_2,0,uVar1 % 1000000);
  return;
}



// ==== central_pair_state_cb @ ram:000056fe size 18 callers []

/* central_pair_state_cb: pairing state 2 (bonded), status 0 -> accessory bonded flag */

void central_pair_state_cb(undefined4 param_1,int param_2,int param_3)

{
  if ((param_2 == 2) && (param_3 == 0)) {
    DAT_ram_20002fd1 = 2;
  }
  return;
}



// ==== acc_addr_load @ ram:00005710 size 52 callers [ram:00005744]

/* acc_addr_load: loads the accessory address from DataFlash 0x6A01 */

void acc_addr_load(void)

{
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  uStack_18 = 0;
  uStack_14 = 0;
  FLASH_EEPROM_CMD(0xb,0x6a00,&uStack_18,8);
  memcpy(&acc_peer_addr,(int)&uStack_18 + 1,6);
  return;
}



// ==== central_app_init @ ram:00005744 size 288 callers [ram:00007794]

/* central_app_init: central role parameters, bond manager, TMOS task */

void central_app_init(void)

{
  undefined4 extraout_a3;
  undefined1 uStack_19;
  undefined1 uStack_18;
  undefined1 uStack_17;
  undefined1 uStack_16;
  byte bStack_15;
  undefined4 auStack_14 [2];
  
  DAT_ram_20002fdc = (*(code *)p_TMOS_ProcessEventRegister)(central_task_event);
  (*(code *)p_GAP_SetParamValue)(2,0x12c0);
  (*(code *)p_GAP_SetParamValue)(7,8);
  (*(code *)p_GAP_SetParamValue)(8,0x28);
  (*(code *)p_GAP_SetParamValue)(0xd,&LAB_ram_00001770);
  uStack_19 = 2;
  auStack_14[0] = 0;
  uStack_18 = 0;
  uStack_17 = 0;
  uStack_16 = 1;
  (*(code *)p_GAPBondMgr_SetParameter)(0x40f,4,auStack_14);
  (*(code *)p_GAPBondMgr_SetParameter)(0x408,1,&uStack_19);
  (*(code *)p_GAPBondMgr_SetParameter)(0x409,1,&uStack_18);
  (*(code *)p_GAPBondMgr_SetParameter)(0x40a,1,&uStack_17);
  (*(code *)p_GAPBondMgr_SetParameter)(0x40d,1,&uStack_16);
  bStack_15 = 0;
  (*(code *)p_GAPBondMgr_GetParameter)(0x415,&bStack_15);
  if (2 < bStack_15) {
    (*(code *)p_GAPBondMgr_SetParameter)(0x410,0,0,extraout_a3,bStack_15,p_GAPBondMgr_SetParameter);
  }
  (*(code *)p_GATT_InitClient)();
  (*(code *)p_GATT_RegisterForInd)(DAT_ram_20002fdc);
  (*(code *)p_GGS_AddService)(0xffffffff);
  (*(code *)p_GATTServApp_AddService)(0xffffffff);
  acc_addr_load();
  (*(code *)p_tmos_set_event)(DAT_ram_20002fdc,1);
  return;
}



// ==== hid_report_map_parse @ ram:00005864 size 652 callers [ram:00005af0]

/* hid_report_map_parse: finds button and wheel byte offsets in an accessory report map */

undefined4 hid_report_map_parse(int param_1,int param_2)

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
  
  memset(abStack_5c,0,0x1a);
  DAT_ram_20002fcc._1_1_ = 0;
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
          DAT_ram_20002fcc._0_1_ = (undefined1)uStack_4c;
          DAT_ram_20002fce = (undefined1)sStack_44;
          printf("Button:%x,Wheel:%x,Num:%x\n",DAT_ram_20002fcc._1_1_);
          return 0;
        }
        memset(abStack_5c,0,0x1a);
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
          DAT_ram_20002fcc._1_1_ = (undefined1)uStack_4c;
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
        printf("-GLOBAL_REPORT_SIZE:%x-\n");
        uStack_54 = (ushort)bVar2;
        goto switchD_ram_00005908_caseD_5;
      case 8:
        pcVar6 = "-GLOBAL_REPORT_ID:%x-\n";
        abStack_5c[0] = bVar2;
        break;
      case 9:
        printf("-GLOBAL_REPORT_CNT:%x-\n");
        uStack_52 = (ushort)bVar2;
        goto switchD_ram_00005908_caseD_5;
      }
      printf(pcVar6);
switchD_ram_00005908_caseD_5:
      pbVar8 = pbVar8 + 1;
    } while (uVar10 != 0);
    iVar9 = ((uVar4 & 3) - 1 & 0xff) + iVar9 + 2;
  } while( true );
}



// ==== central_task_event @ ram:00005af0 size 2504 callers []

/* central_task_event: central TMOS task: discovery, CCCD enable, HID notifications */

uint central_task_event(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                       undefined4 param_5)

{
  byte bVar1;
  short sVar2;
  char *pcVar3;
  char cVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  uint extraout_a3;
  uint uVar8;
  undefined2 *puVar9;
  undefined4 uVar10;
  undefined4 extraout_a4;
  undefined1 uVar11;
  ushort uVar12;
  short sVar13;
  char *pcVar14;
  uint uVar15;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined2 uStack_138;
  
  sVar13 = DAT_ram_20002fd8;
  if (-1 < (short)param_2) {
    if ((param_2 & 1) != 0) {
      (*(code *)p_GAPRole_CentralStartDevice)
                (DAT_ram_20002fdc,&PTR_central_passcode_cb_ram_20002e54,
                 &PTR_FUN_ram_000056c0_ram_20002e60,param_4,param_5,p_GAPRole_CentralStartDevice);
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x20,800);
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x400,0x10);
      return param_2 ^ 1;
    }
    if ((param_2 & 0x200) != 0) {
      (*(code *)p_GAPRole_TerminateLink)(0xffff);
      return param_2 ^ 0x200;
    }
    if ((param_2 & 8) != 0) {
      uVar15 = (uint)DAT_ram_20002fd1;
      uVar10 = 2;
      if (uVar15 == 2) {
        if (DAT_ram_20002f36 == -2) goto LAB_ram_0000605c;
        DAT_ram_20004c4c = 0;
        DAT_ram_20002fd3 = '\x01';
        iVar5 = (*(code *)p_GATT_DiscAllPrimaryServices)(DAT_ram_20002f36,DAT_ram_20002fdc);
        if (iVar5 == 0) {
          uStack_140 = 0;
          uStack_13c = (undefined1 *)0x0;
          FLASH_EEPROM_CMD(0xb,0x6a00,&uStack_140,8);
          iVar5 = (*(code *)p_tmos_memcmp)(&acc_peer_addr,(int)&uStack_140 + 1,6);
          if (iVar5 == 0) {
            FLASH_EEPROM_CMD(9,0x6a00,0,8);
            FLASH_EEPROM_CMD(10,0x6a01,&acc_peer_addr,8);
          }
          DAT_ram_20002fc8 = 1;
          goto LAB_ram_0000605c;
        }
        uVar15 = extraout_a3;
        uVar10 = extraout_a4;
        if (iVar5 != 0x16) goto LAB_ram_0000605c;
      }
      else if (DAT_ram_20002f36 == -2) goto LAB_ram_0000605c;
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,8,800,uVar15,uVar10,p_tmos_start_task);
LAB_ram_0000605c:
      return param_2 ^ 8;
    }
    if ((param_2 & 0x10) != 0) {
      (*(code *)p_GAPRole_UpdateLink)(DAT_ram_20002f36,8,0x28,2,500,p_GAPRole_UpdateLink);
      return param_2 ^ 0x10;
    }
    if ((param_2 & 0x400) != 0) {
      acc_af02_notify_handle(&DAT_ram_200049b4);
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x400,0x10);
      return param_2 ^ 0x400;
    }
    if ((param_2 & 0x20) == 0) {
      if ((param_2 & 0x40) != 0) {
        if (DAT_ram_20002fd8 == 0) {
          uStack_138 = 0;
          uStack_140 = CONCAT22(2,(&DAT_ram_20004c0c)[DAT_ram_20002fd2]);
          uStack_13c = (undefined1 *)
                       (*(code *)p_GATT_bm_alloc)(DAT_ram_20002f36,0x12,2,0,0,p_GATT_bm_alloc);
          if (uStack_13c != (undefined1 *)0x0) {
            *uStack_13c = 1;
            uVar11 = DAT_ram_20002fdc;
            uStack_13c[1] = 0;
            iVar5 = (*(code *)p_GATT_WriteCharValue)(DAT_ram_20002f36,&uStack_140,uVar11);
            if (iVar5 == 0) {
              DAT_ram_20002fd8 = (short)uStack_140;
              DAT_ram_20002fd2 = 0;
            }
            else {
              (*(code *)p_GATT_bm_free)(&uStack_140,0x12);
            }
          }
        }
        return param_2 ^ 0x40;
      }
      if ((param_2 & 0x80) != 0) {
        uStack_140 = CONCAT22(uStack_140._2_2_,(&DAT_ram_20004c0c)[DAT_ram_20002fd2]);
        iVar5 = (*(code *)p_GATT_ReadCharValue)
                          (DAT_ram_20002f36,&uStack_140,DAT_ram_20002fdc,param_4,
                           (uint)DAT_ram_20002fd2 * 2,p_GATT_ReadCharValue);
        if (iVar5 == 0) {
          DAT_ram_20002fd8 = (short)uStack_140;
          DAT_ram_20002fd2 = 0;
        }
        return param_2 ^ 0x80;
      }
      if ((param_2 & 0x100) == 0) {
        return 0;
      }
      (*(code *)p_GAPRole_ReadRssiCmd)(DAT_ram_20002f36);
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x100,0x960);
      return param_2 ^ 0x100;
    }
    if (DAT_ram_20002fd8 == 0) {
      if ((DAT_ram_20004c14 == 0) && (DAT_ram_20002fd6 == '\0')) {
        sVar13 = DAT_ram_20004c48._2_2_;
        if (DAT_ram_20004c48._2_2_ != 0) {
          DAT_ram_20002fd4 = '\x01';
          sVar2 = 0;
          goto LAB_ram_00006124;
        }
      }
      else {
        puVar9 = &DAT_ram_20004c0c;
        iVar5 = 5;
        do {
          if ((puVar9[5] != 0) &&
             (*(char *)((int)&DAT_ram_20004c30 + iVar5) == '\0' && DAT_ram_20002fd2 == 0)) {
            DAT_ram_20002fd2 = (byte)iVar5;
            *(char *)((int)&DAT_ram_20004c30 + iVar5) = '\x01';
            (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x40,800,0,puVar9,p_tmos_start_task);
            break;
          }
          iVar5 = iVar5 + 1;
          puVar9 = puVar9 + 1;
        } while (iVar5 != 0x10);
        sVar2 = (short)DAT_ram_20004c44;
        if ((DAT_ram_20004c2c == 0) || (DAT_ram_20004c40 != '\0' || DAT_ram_20002fd2 != 0)) {
          if ((DAT_ram_20004c0c == 0) || ((char)DAT_ram_20004c30 != '\0' || DAT_ram_20002fd2 != 0))
          {
            if (DAT_ram_20004c09 == '\0') goto LAB_ram_000060f4;
            DAT_ram_20004c09 = '\0';
            if ((short)DAT_ram_20004c44 != 0) {
              DAT_ram_20002fd5 = '\x01';
              uVar15 = (uint)DAT_ram_20002fde;
              (&DAT_ram_20004a48)[uVar15] = 0xf0;
              DAT_ram_20002fde = DAT_ram_20002fde + 2;
              (&DAT_ram_20004a48)[uVar15 + 1 & 0xffff] = 0xb0;
              goto LAB_ram_00006124;
            }
            goto LAB_ram_000060f6;
          }
          DAT_ram_20004c30._0_1_ = '\x01';
        }
        else {
          DAT_ram_20002fd2 = 0x10;
          DAT_ram_20004c40 = '\x01';
        }
        (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x40,800);
      }
      sVar2 = 0;
    }
    else {
LAB_ram_000060f4:
      sVar2 = 0;
LAB_ram_000060f6:
      sVar13 = 0;
    }
LAB_ram_00006124:
    if (DAT_ram_20002fd8 == 0) {
      if (DAT_ram_20002fd5 == '\0') {
        if ((DAT_ram_20002fd4 == '\x01') && (sVar13 != 0)) {
          uStack_140 = CONCAT22(uStack_140._2_2_,sVar13);
          printf("ReadcentralCharHdl:%x\n",sVar13);
          iVar5 = (*(code *)p_GATT_ReadCharValue)(DAT_ram_20002f36,&uStack_140,DAT_ram_20002fdc);
          if (iVar5 == 0) {
            DAT_ram_20002fd4 = '\0';
            DAT_ram_20002fd8 = sVar13;
          }
        }
      }
      else {
        uStack_138 = 0;
        uStack_140 = CONCAT22(DAT_ram_20002fde,sVar2);
        uStack_13c = (undefined1 *)
                     (*(code *)p_GATT_bm_alloc)
                               (DAT_ram_20002f36,0x12,DAT_ram_20002fde,0,0,p_GATT_bm_alloc);
        if (uStack_13c != (undefined1 *)0x0) {
          memcpy(uStack_13c,&DAT_ram_20004a48,DAT_ram_20002fde);
          iVar5 = (*(code *)p_GATT_WriteCharValue)(DAT_ram_20002f36,&uStack_140,DAT_ram_20002fdc);
          if (iVar5 == 0) {
            DAT_ram_20002fde = 0;
            DAT_ram_20002fd5 = '\0';
            DAT_ram_20002fd8 = sVar2;
          }
          else {
            (*(code *)p_GATT_bm_free)(&uStack_140,0x12);
          }
        }
      }
    }
    (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x20,800);
    return param_2 ^ 0x20;
  }
  pcVar3 = (char *)(*(code *)p_tmos_msg_receive)(DAT_ram_20002fdc);
  if (pcVar3 == (char *)0x0) goto LAB_ram_00005b7c;
  if (*pcVar3 == -0x50) {
    cVar4 = pcVar3[4];
    if (DAT_ram_20002fdb == '\x02') {
      if (cVar4 == '\x03') {
LAB_ram_00005bf0:
        DAT_ram_20002fd8 = 0;
        if (cVar4 == '\v') {
LAB_ram_00005bfe:
          for (uVar12 = 0; uVar12 < *(ushort *)(pcVar3 + 8); uVar12 = uVar12 + 1 & 0xff) {
          }
          if ((DAT_ram_20004c48._2_2_ == DAT_ram_20002fd8) &&
             (DAT_ram_20002fd6 = '\x01', DAT_ram_20004c14 == 0)) {
            hid_report_map_parse(*(undefined4 *)(pcVar3 + 0xc));
          }
          goto LAB_ram_00005bda;
        }
        if (cVar4 == '\x01') goto LAB_ram_00005bcc;
LAB_ram_00005c3c:
        if (cVar4 == '\x13') goto LAB_ram_00005bda;
        if (cVar4 != '\x1b') goto LAB_ram_00005d64;
        memset(&uStack_140,0,0x100);
        bVar1 = pcVar3[10];
        uVar8 = (uint)bVar1;
        debug_hexdump(*(undefined4 *)(pcVar3 + 0xc),uVar8,0);
        uVar15 = *(ushort *)(pcVar3 + 8) + 1;
        if (DAT_ram_20004c0c == uVar15) {
          DAT_ram_200049b4 = bVar1;
          (*(code *)p_tmos_memcpy)
                    (&DAT_ram_200049b5,*(undefined4 *)(pcVar3 + 0xc),uVar8,(uint)DAT_ram_20004c0c,
                     uVar15,p_tmos_memcpy);
        }
        else if ((DAT_ram_20004c16 <= uVar15) &&
                ((uint)*(ushort *)(pcVar3 + 8) < (uint)DAT_ram_20004c2a)) {
          if (uVar8 < 5) {
            if (uVar8 == 4) {
              uStack_140._0_2_ = CONCAT11(**(undefined1 **)(pcVar3 + 0xc),0xbe);
              uVar11 = (*(undefined1 **)(pcVar3 + 0xc))[3];
              goto LAB_ram_00005d0a;
            }
          }
          else {
            puVar6 = *(undefined1 **)(pcVar3 + 0xc);
            if ((DAT_ram_20002fcc._1_1_ < 2) || ((byte)DAT_ram_20002fcc < 5)) {
              uVar11 = *puVar6;
            }
            else {
              uVar11 = puVar6[DAT_ram_20002fcc._1_1_];
            }
            uStack_140._0_2_ = CONCAT11(uVar11,0xbe);
            if ((DAT_ram_20002fce < 2) || ((byte)DAT_ram_20002fcc < 5)) {
              uVar11 = puVar6[uVar8 - 2];
            }
            else {
              uVar11 = puVar6[DAT_ram_20002fce - 1];
            }
LAB_ram_00005d0a:
            uStack_13c = (undefined1 *)CONCAT13(uVar11,(undefined3)uStack_13c);
          }
          if ((DAT_ram_20002fd0 != uStack_140._1_1_) || (uStack_13c._3_1_ != '\0')) {
            DAT_ram_20002fd0 = uStack_140._1_1_;
            acc_to_mcu_send(&uStack_140,9,0);
          }
        }
      }
      else {
        if (cVar4 != '\x01') {
          if (cVar4 != '\v') goto LAB_ram_00005c3c;
          goto LAB_ram_00005bfe;
        }
        if (pcVar3[8] == '\x02') goto LAB_ram_00005bf0;
LAB_ram_00005bcc:
        if ((pcVar3[8] - 10U & 0xf7) != 0) {
LAB_ram_00005d64:
          if (DAT_ram_20002fd3 != '\0') {
            if (DAT_ram_20002fd3 == '\x01') {
              if (cVar4 == '\x11') {
                if (pcVar3[1] == '\x1a') {
LAB_ram_00005d86:
                  DAT_ram_20002fd3 = '\x02';
                  (*(code *)p_GATT_DiscAllChars)
                            (DAT_ram_20002f36,1,0xffff,DAT_ram_20002fdc,&DAT_ram_20002d88,
                             p_GATT_DiscAllChars);
                }
              }
              else if (cVar4 == '\x01') goto LAB_ram_00005d86;
            }
            else if (((DAT_ram_20002fd3 == '\x02') && (cVar4 == '\t')) &&
                    (*(short *)(pcVar3 + 8) != 0)) {
              FUN_ram_00007ab4("TypeRspAnalysis");
              DAT_ram_20002fd8 = 1;
              for (uVar15 = 0; uVar15 < *(ushort *)(pcVar3 + 8); uVar15 = uVar15 + 1 & 0xff) {
                uVar12 = *(ushort *)(pcVar3 + 10);
                iVar7 = uVar12 * uVar15;
                iVar5 = *(int *)(pcVar3 + 0xc) + iVar7;
                bVar1 = *(byte *)(iVar5 + 2);
                sVar13 = *(short *)(iVar5 + 3);
                pcVar14 = (char *)(*(int *)(pcVar3 + 0xc) + iVar7 + 5);
                for (uVar8 = 0; (uVar8 & 0xff) < (uVar12 - 5 & 0xff); uVar8 = uVar8 + 1) {
                  printf("%02x ",pcVar14[uVar8]);
                }
                putchar(10);
                if ((((bVar1 & 2) != 0) && (*pcVar14 == 'K')) && (pcVar14[1] == '*')) {
                  DAT_ram_20004c48._2_2_ = sVar13;
                }
                if ((((bVar1 & 0xc) != 0) && (DAT_ram_20004c4c = sVar13, *pcVar14 == '\x02')) &&
                   (pcVar14[1] == -0x51)) {
                  DAT_ram_20004c44._0_2_ = sVar13;
                }
                if ((bVar1 & 0x10) != 0) {
                  DAT_ram_20004c2c = sVar13 + 1;
                }
                if ((bVar1 & 0x20) != 0) {
                  DAT_ram_20004c2c = sVar13 + 1;
                }
                if ((*pcVar14 == 'N') && (pcVar14[1] == '*')) {
                  DAT_ram_20004c48._0_2_ = sVar13;
                }
                if (*pcVar14 == 'M') {
                  if ((pcVar14[1] == '*') && ((bVar1 & 0x10) != 0)) {
                    puVar9 = &DAT_ram_20004c0c;
                    iVar5 = 5;
                    do {
                      if (puVar9[5] == 0) {
                        DAT_ram_20004c2a = sVar13 + 1;
                        (&DAT_ram_20004c0c)[iVar5] = DAT_ram_20004c2a;
                        break;
                      }
                      iVar5 = iVar5 + 1;
                      puVar9 = puVar9 + 1;
                    } while (iVar5 != 0x10);
                  }
                }
                else if (((*pcVar14 == '\x02') && (pcVar14[1] == -0x51)) && ((bVar1 & 0x10) != 0)) {
                  DAT_ram_20004c0c = sVar13 + 1;
                }
              }
              goto LAB_ram_00005bda;
            }
          }
          goto LAB_ram_00005be2;
        }
LAB_ram_00005bda:
        DAT_ram_20002fd8 = 0;
      }
LAB_ram_00005be2:
      cVar4 = pcVar3[4];
    }
    (*(code *)p_GATT_bm_free)(pcVar3 + 8,cVar4);
  }
  (*(code *)p_tmos_msg_deallocate)(pcVar3);
LAB_ram_00005b7c:
                    /* WARNING: Read-only address (ram,0x0004003c) is written */
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
                    /* WARNING: Read-only address (ram,0x00040058) is written */
                    /* WARNING: Read-only address (ram,0x00040068) is written */
                    /* WARNING: Read-only address (ram,0x0004006c) is written */
                    /* WARNING: Read-only address (ram,0x000400dc) is written */
                    /* WARNING: Read-only address (ram,0x000400e8) is written */
                    /* WARNING: Read-only address (ram,0x000400f4) is written */
                    /* WARNING: Read-only address (ram,0x0004010c) is written */
                    /* WARNING: Read-only address (ram,0x00040128) is written */
                    /* WARNING: Read-only address (ram,0x0004012c) is written */
                    /* WARNING: Read-only address (ram,0x0004017c) is written */
                    /* WARNING: Read-only address (ram,0x00040180) is written */
                    /* WARNING: Read-only address (ram,0x00040184) is written */
                    /* WARNING: Read-only address (ram,0x000401b0) is written */
  return param_2 ^ 0x8000;
}



// ==== central_link_reset @ ram:000064b8 size 232 callers [ram:0000698c]

/* central_link_reset: clears accessory link state */

void central_link_reset(int param_1)

{
  DAT_ram_20002fdb = 0;
  DAT_ram_20002f36 = 0xfffe;
  DAT_ram_20002fd3 = 0;
  DAT_ram_20002fd1 = 0;
  DAT_ram_20002fda = 0;
  DAT_ram_20002fc8 = 0;
  DAT_ram_20004c44 = 0;
  DAT_ram_20004c48 = 0;
  DAT_ram_20004c4c = 0;
  memset(&DAT_ram_20004c0c,0,0x22);
  memset(&DAT_ram_20004c50,0,0x4e0);
  DAT_ram_20004c30 = 0;
  DAT_ram_20004c34 = 0;
  DAT_ram_20004c38 = 0;
  DAT_ram_20004c3c = 0;
  DAT_ram_20004c40 = 0;
  DAT_ram_20002fcc = 0;
  DAT_ram_20002fce = 0;
  DAT_ram_20002fd2 = 0;
  DAT_ram_20002fd6 = 0;
  DAT_ram_20002fd8 = 0;
  DAT_ram_20002fcf = 0;
  if (param_1 == 0) {
    acc_peer_addr = 0;
    DAT_ram_20002f34 = 0;
  }
  return;
}



// ==== adv_report_parse @ ram:000065a0 size 698 callers [ram:0000698c]

/* adv_report_parse: parses one advertising report of a scanned device */

void adv_report_parse(undefined4 param_1,undefined1 *param_2,uint param_3,int param_4)

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
            printf("16-bit UUID: 0x%04X\n",sVar7);
          }
          *(short *)(&DAT_ram_20004c5a + iVar5) = sVar7;
        }
      }
      else {
        (&DAT_ram_20004c7e)[iVar5] = (char)(uVar2 - 1);
        memcpy(iVar5 + 0x20004c5f,psVar9,uVar8);
        debug_hexdump(psVar9,uVar8,99);
      }
    }
    else if (bVar1 == 0x19) {
      sVar7 = 0;
      for (psVar6 = psVar9; (int)psVar6 - (int)psVar9 < (int)uVar8; psVar6 = psVar6 + 1) {
        sVar7 = *psVar6;
        printf("16-bit ad_type: %x\n",sVar7);
      }
      (&DAT_ram_20004c5c)[param_4 * 0x27] = sVar7;
    }
    else if (bVar1 == 0xff) {
      if ((2 < uVar8) && ((undefined *)(&DAT_ram_20004c5c)[param_4 * 0x27] == &pmpaddr18)) {
        printf("Manufacturer Data Len:%d\n",uVar8);
        iVar4 = 0;
        do {
          printf("%02X ",*(char *)((int)psVar9 + iVar4));
          iVar4 = iVar4 + 1;
        } while (iVar4 < (int)uVar8);
      }
      memcpy(&DAT_ram_20004c7f + iVar5,psVar9,uVar8);
      if (((((char)*psVar9 == -0x46) && (*(char *)((int)psVar9 + 1) == -0x55)) &&
          ((char)psVar9[1] == -0x42)) && (*(char *)((int)psVar9 + 3) == -0x15)) {
        uStack_48 = 0;
        uStack_44 = 0;
        FLASH_EEPROM_CMD(0xb,0x6a00,&uStack_48,8);
        if ((uint)*(byte *)(psVar9 + 2) + (uint)*(byte *)((int)psVar9 + 5) +
            (uint)*(byte *)(psVar9 + 3) + (uint)*(byte *)((int)psVar9 + 7) == 0) {
          iVar4 = (*(code *)p_tmos_memcmp)
                            (&DAT_ram_20004c52 + iVar5,(int)&uStack_48 + 1,6,
                             (uint)*(byte *)((int)psVar9 + 7),p_tmos_memcmp);
          if ((iVar4 != 0) &&
             (iVar4 = (*(code *)p_tmos_memcmp)(&acc_peer_addr,(int)&uStack_48 + 1,6), iVar4 != 0)) {
            acc_peer_addr = 0;
            DAT_ram_20002f34 = 0;
            FLASH_EEPROM_CMD(9,0x6a00,0,8);
          }
        }
        else {
          uStack_50 = 0;
          uStack_4c = 0;
          FLASH_EEPROM_CMD(6,0x7f018,&uStack_50,0);
          iVar4 = (*(code *)p_tmos_memcmp)(&DAT_ram_20004c52 + iVar5,(int)&uStack_48 + 1,6);
          if ((iVar4 == 0) ||
             (iVar4 = (*(code *)p_tmos_memcmp)((char *)((int)psVar9 + 5),&uStack_50,6), iVar4 == 0))
          {
            memset(&DAT_ram_20004c50 + iVar5,0,0x4e);
          }
        }
      }
    }
    uVar3 = uVar3 + uVar2 + 1 & 0xff;
  } while( true );
}



// ==== acc_list_add @ ram:0000685a size 276 callers [ram:0000698c]

/* acc_list_add: adds a scanned HID mouse appearance device to the 5-entry list */

void acc_list_add(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 *puVar6;
  
  iVar3 = param_1 * 0x4e;
  if ((undefined *)(&DAT_ram_20004c5c)[param_1 * 0x27] == &pmpaddr18) {
    cVar1 = (&DAT_ram_20004c7e)[iVar3];
    puVar6 = &DAT_ram_20004be5;
    iVar2 = 0;
    do {
      iVar4 = (*(code *)p_tmos_memcmp)(&DAT_ram_20004c52 + iVar3,puVar6,6);
      if (iVar4 != 0) {
        if ((&DAT_ram_20004c03)[iVar2] != '\0') {
          return;
        }
        if (cVar1 == '\0') {
          return;
        }
        (&DAT_ram_20004c03)[iVar2] = cVar1;
        memcpy(&DAT_ram_20004b4a + iVar2 * 0x1f,iVar3 + 0x20004c5f,cVar1);
        return;
      }
      iVar2 = iVar2 + 1;
      puVar6 = puVar6 + 6;
    } while (iVar2 != 5);
    (&DAT_ram_20004b4a)[(uint)DAT_ram_20004c08 * 0x1f] = 0;
    memcpy(&DAT_ram_20004b4a + (uint)DAT_ram_20004c08 * 0x1f,iVar3 + 0x20004c5f,cVar1);
    uVar5 = (uint)DAT_ram_20004c08;
    (&DAT_ram_20004c03)[uVar5] = cVar1;
    memcpy(&DAT_ram_20004be5 + uVar5 * 6,&DAT_ram_20004c52 + iVar3,6);
    if (4 < DAT_ram_20004c08) {
      DAT_ram_20004c08 = 0;
      FUN_ram_0000696e();
      return;
    }
    DAT_ram_20004c08 = DAT_ram_20004c08 + 1;
  }
                    /* WARNING: Read-only address (ram,0x0004003c) is written */
  return;
}



// ==== FUN_ram_0000696e @ ram:0000696e size 20 callers [ram:00006982]

void FUN_ram_0000696e(void)

{
  return;
}



// ==== FUN_ram_00006982 @ ram:00006982 size 10 callers []

void FUN_ram_00006982(void)

{
  DAT_ram_20004c08 = 0;
  FUN_ram_0000696e();
  return;
}



// ==== central_event_cb @ ram:0000698c size 746 callers []

/* central_event_cb: central role GAP event callback (discovery, link established/terminated) */

void central_event_cb(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  uint extraout_a4;
  undefined4 uVar10;
  undefined2 auStack_34 [8];
  
  switch(*(undefined1 *)(param_1 + 2)) {
  case 1:
    for (uVar9 = 0; uVar9 < DAT_ram_20002fda; uVar9 = uVar9 + 1 & 0xff) {
      iVar5 = uVar9 * 0x4e;
      if ((undefined *)(&DAT_ram_20004c5c)[uVar9 * 0x27] == &pmpaddr18) {
        cVar4 = (&DAT_ram_20004c7e)[iVar5];
        iVar6 = (*(code *)p_tmos_memcmp)(&acc_peer_addr,&DAT_ram_20004c52 + iVar5,6);
        if (((iVar6 != 0) && (cVar4 != '\0')) && (remote_enabled != '\0')) {
          if ((((&DAT_ram_20004c7f)[iVar5] == -0x46) && ((&DAT_ram_20004c80)[iVar5] == -0x55)) &&
             (((&DAT_ram_20004c81)[iVar5] == -0x42 && ((&DAT_ram_20004c82)[iVar5] == -0x15)))) {
            DAT_ram_20002fcf = 1;
          }
          break;
        }
      }
    }
    if (DAT_ram_20002fda != uVar9) {
      (*(code *)p_GAPRole_CentralEstablishLink)
                (1,0,(&DAT_ram_20004c51)[uVar9 * 0x4e],&DAT_ram_20004c52 + uVar9 * 0x4e,
                 p_GAPRole_CentralEstablishLink);
      uVar7 = 16000;
      uVar10 = 0x200;
LAB_ram_00006ba8:
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,uVar10,uVar7);
      return;
    }
    memset(&DAT_ram_20004c50,0,0x4e0);
    DAT_ram_20002fda = 0;
  case 0:
    break;
  case 2:
  case 3:
  case 4:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
    goto switchD_ram_000069bc_caseD_2;
  case 5:
    (*(code *)p_tmos_stop_task)(DAT_ram_20002fdc,0x200);
    if (*(char *)(param_1 + 1) == '\0') {
      DAT_ram_20002f36 = *(undefined2 *)(param_1 + 10);
      DAT_ram_20002fdb = 2;
      DAT_ram_20002fd8 = 1;
      auStack_34[0] = 0xf7;
      (*(code *)p_GATT_ExchangeMTU)(DAT_ram_20002f36,auStack_34,DAT_ram_20002fdc);
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,8,0x640);
      (*(code *)p_tmos_start_task)(DAT_ram_20002fdc,0x10,0xc80);
      uVar7 = 0x960;
      uVar10 = 0x100;
      goto LAB_ram_00006ba8;
    }
    central_link_reset(0);
    (*(code *)p_tmos_stop_task)(DAT_ram_20002fdc,0x100);
    break;
  case 6:
    central_link_reset(1);
    (*(code *)p_tmos_stop_task)(DAT_ram_20002fdc,0x100);
    break;
  case 0xd:
    uVar9 = (uint)DAT_ram_20002fda;
    if (0xf < uVar9) {
      return;
    }
    uVar1 = *(undefined1 *)(param_1 + 3);
    uVar2 = *(undefined1 *)(param_1 + 4);
    uVar3 = *(undefined1 *)(param_1 + 0xc);
    uVar10 = *(undefined4 *)(param_1 + 0x10);
    uVar8 = 0;
    while( true ) {
      if (DAT_ram_20002fda <= uVar8) {
        (*(code *)p_tmos_memcpy)
                  (&DAT_ram_20004c52 + (uint)DAT_ram_20002fda * 0x4e,param_1 + 5,6,uVar8,uVar9,
                   p_tmos_memcpy);
        (&DAT_ram_20004c51)[(uint)DAT_ram_20002fda * 0x4e] = uVar2;
        adv_report_parse(uVar1,uVar10,uVar3);
        acc_list_add(DAT_ram_20002fda);
        DAT_ram_20002fda = DAT_ram_20002fda + 1;
        return;
      }
      iVar5 = (*(code *)p_tmos_memcmp)
                        (param_1 + 5,&DAT_ram_20004c52 + uVar8 * 0x4e,6,uVar8,uVar9,p_tmos_memcmp);
      if (iVar5 != 0) break;
      uVar8 = uVar8 + 1 & 0xff;
      uVar9 = extraout_a4;
    }
    adv_report_parse(uVar1,uVar10,uVar3);
    return;
  default:
    return;
  }
  (*(code *)p_GAPRole_CentralStartDiscovery)(3,1,0);
switchD_ram_000069bc_caseD_2:
                    /* WARNING: Read-only address (ram,0x0004003c) is written */
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
                    /* WARNING: Read-only address (ram,0x00040058) is written */
                    /* WARNING: Read-only address (ram,0x0004005c) is written */
                    /* WARNING: Read-only address (ram,0x000400d8) is written */
                    /* WARNING: Read-only address (ram,0x000401b4) is written */
                    /* WARNING: Read-only address (ram,0x000401bc) is written */
  return;
}



// ==== FUN_ram_00006c76 @ ram:00006c76 size 2 callers []

void FUN_ram_00006c76(void)

{
  return;
}



// ==== periph_param_update_cb @ ram:00006c78 size 54 callers []

/* periph_param_update_cb: records host link interval/latency/timeout */

void periph_param_update_cb(uint param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  if (ble_conn_handle == param_1) {
    DAT_ram_20002fb1 = (undefined1)param_4;
    DAT_ram_20002fb2 = (undefined1)param_2;
    DAT_ram_20002ffe = param_2;
    DAT_ram_20003000 = param_3;
    DAT_ram_20003002 = param_4;
  }
  return;
}



// ==== FUN_ram_00006cae @ ram:00006cae size 2 callers []

void FUN_ram_00006cae(void)

{
  return;
}



// ==== periph_task_event @ ram:00006cb0 size 700 callers []

/* periph_task_event: peripheral TMOS task: start, 1 s name/timeout housekeeping, watchdog, param
   update */

uint periph_task_event(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                      undefined4 param_5)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  undefined1 auStack_20 [16];
  
  if ((short)param_2 < 0) {
    iVar2 = (*(code *)p_tmos_msg_receive)(DAT_ram_20002f44);
    if (iVar2 != 0) {
      (*(code *)p_tmos_msg_deallocate)();
    }
    return param_2 ^ 0x8000;
  }
  if ((param_2 & 1) != 0) {
    (*(code *)p_GAPRole_PeripheralStartDevice)
              (DAT_ram_20002f44,&DAT_ram_20005140,&PTR_periph_state_cb_ram_20002e6c,param_4,param_5,
               p_GAPRole_PeripheralStartDevice);
    (*(code *)p_tmos_start_task)(DAT_ram_20002f44,0x800,2);
    (*(code *)p_tmos_start_task)(DAT_ram_20002f44,0x100,0x10);
    (*(code *)p_tmos_start_task)(DAT_ram_20002f44,2,0x640);
    return param_2 ^ 1;
  }
  if ((param_2 & 2) == 0) {
    if ((param_2 & 0x800) != 0) {
      periodic_dispatch();
      (*(code *)p_tmos_start_task)(DAT_ram_20002f44,0x800,2);
      return (param_2 ^ 0x800) & 0xffff;
    }
    if ((param_2 & 0x100) != 0) {
      SAFE_ACCESS._3_1_ = 0;
      (*(code *)p_tmos_start_task)(DAT_ram_20002f44,0x100,0x10,param_4,param_5,p_tmos_start_task);
      return param_2 ^ 0x100;
    }
    if ((param_2 & 0x400) != 0) {
      if (DAT_ram_20002fb5 == '\0') {
        (*(code *)p_tmos_start_task)(DAT_ram_20002f44,0x400,0x140,param_4,param_5,p_tmos_start_task)
        ;
      }
      return param_2 ^ 0x400;
    }
    if ((param_2 & 8) == 0) {
      return 0;
    }
    (*(code *)p_GAPRole_PeripheralConnParamUpdateReq)
              (ble_conn_handle,6,0x28,0,500,DAT_ram_20002f44,p_GAPRole_PeripheralConnParamUpdateReq)
    ;
    return param_2 ^ 8;
  }
  iVar2 = name_variant_flag();
  if ((iVar2 == 0) || (cVar3 = '3', DAT_ram_20002e9c == '3')) {
    iVar2 = name_variant_flag();
    bVar1 = false;
    if ((iVar2 == 0) && (cVar3 = '0', DAT_ram_20002e9c != '0')) goto LAB_ram_00006d70;
  }
  else {
LAB_ram_00006d70:
    DAT_ram_20002e9c = cVar3;
    bVar1 = true;
  }
  cVar3 = ' ';
  if ((remote_enabled != '\0') && (host_iface_mode != '\x02')) {
    cVar3 = 'S';
  }
  if (DAT_ram_20002ea6 != cVar3) {
    bVar1 = true;
    DAT_ram_20002ea6 = cVar3;
  }
  (*(code *)p_tmos_memset)(auStack_20,0xff,0xe);
  FLASH_EEPROM_CMD(0xb,0x6e00,&DAT_ram_200042b0,0x16);
  iVar2 = (*(code *)p_tmos_memcmp)(auStack_20,&DAT_ram_200042be,8);
  if (iVar2 == 0) {
    (*(code *)p_tmos_memcpy)(s_MP305B_ram_20002e9e,&DAT_ram_200042be,8);
  }
  else if (!bVar1) goto LAB_ram_00006e3e;
  (*(code *)p_GAPRole_SetParameter)(0x307,0x1f,&scan_rsp_data);
LAB_ram_00006e3e:
  if ((gaprole_state == 4) &&
     (((ble_conn_timer = ble_conn_timer + 0x640, ble_bind_state == 0 || (ble_bind_state == 1)) &&
      (47999 < ble_conn_timer)))) {
    (*(code *)p_GAPRole_TerminateLink)(ble_conn_handle);
  }
  (*(code *)p_tmos_start_task)(DAT_ram_20002f44,2,0x640);
                    /* WARNING: Read-only address (ram,0x0004003c) is written */
                    /* WARNING: Read-only address (ram,0x00040048) is written */
                    /* WARNING: Read-only address (ram,0x0004004c) is written */
                    /* WARNING: Read-only address (ram,0x00040058) is written */
                    /* WARNING: Read-only address (ram,0x00040068) is written */
                    /* WARNING: Read-only address (ram,0x0004006c) is written */
                    /* WARNING: Read-only address (ram,0x00040174) is written */
                    /* WARNING: Read-only address (ram,0x0004017c) is written */
                    /* WARNING: Read-only address (ram,0x000401a4) is written */
                    /* WARNING: Read-only address (ram,0x000401a8) is written */
  return param_2 ^ 2;
}



// ==== af02_notify @ ram:00006f6c size 138 callers [ram:00003fac]

/* af02_notify: GATT_bm_alloc + notify on AF02; sets notify-failed flag 0x20002F88 */

void af02_notify(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uStack_18;
  int iStack_14;
  
  uStack_18 = 0;
  iStack_14 = 0;
  iStack_14 = (*(code *)p_GATT_bm_alloc)(ble_conn_handle,0x1b,param_2,0,0,p_GATT_bm_alloc);
  if (iStack_14 == 0) {
    notify_failed = 1;
  }
  else {
    (*(code *)p_tmos_memcpy)(iStack_14,param_1,param_2);
    uStack_18 = CONCAT22((short)param_2,(undefined2)uStack_18);
    iVar1 = af02_notify_raw(ble_conn_handle,&uStack_18,DAT_ram_20002f44);
    if (iVar1 == 0) {
      notify_failed = 0;
    }
    else {
      notify_failed = 1;
      (*(code *)p_GATT_bm_free)(&uStack_18,0x1b);
    }
  }
  return;
}



// ==== af01_notify @ ram:00006ff6 size 138 callers [ram:00003fac]

/* af01_notify: GATT_bm_alloc + notify on AF01; sets notify-failed flag 0x20002F88 */

void af01_notify(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uStack_18;
  int iStack_14;
  
  uStack_18 = 0;
  iStack_14 = 0;
  iStack_14 = (*(code *)p_GATT_bm_alloc)(ble_conn_handle,0x1b,param_2,0,0,p_GATT_bm_alloc);
  if (iStack_14 == 0) {
    notify_failed = 1;
  }
  else {
    (*(code *)p_tmos_memcpy)(iStack_14,param_1,param_2);
    uStack_18 = CONCAT22((short)param_2,(undefined2)uStack_18);
    iVar1 = af01_notify_raw(ble_conn_handle,&uStack_18,DAT_ram_20002f44);
    if (iVar1 == 0) {
      notify_failed = 0;
    }
    else {
      notify_failed = 1;
      (*(code *)p_GATT_bm_free)(&uStack_18,0x1b);
    }
  }
  return;
}



// ==== periph_link_terminated @ ram:00007080 size 102 callers [ram:00007106]

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* periph_link_terminated: clears host link, re-enables advertising unless blocked */

void periph_link_terminated(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 auStack_11 [13];
  
  if (*(short *)(param_1 + 4) == ble_conn_handle) {
    _ble_conn_handle = 0xfffe;
    _DAT_ram_20003000 = 0;
    auStack_11[0] = 1;
    if ((host_iface_mode == '\x02') || (remote_enabled == '\0')) {
      auStack_11[0] = 0;
    }
    (*(code *)p_GAPRole_SetParameter)
              (0x305,1,auStack_11,param_4,host_iface_mode,p_GAPRole_SetParameter);
    return;
  }
  return;
}



// ==== FUN_ram_000070e6 @ ram:000070e6 size 30 callers []

void FUN_ram_000070e6(int param_1)

{
  undefined1 auStack_14 [16];
  
  if ((param_1 == 0) || (param_1 == 2)) {
    (*(code *)p_tmos_memcpy)(auStack_14);
  }
  return;
}



// ==== FUN_ram_00007104 @ ram:00007104 size 2 callers []

void FUN_ram_00007104(void)

{
  return;
}



// ==== periph_state_cb @ ram:00007106 size 416 callers []

/* WARNING: Removing unreachable block (ram,0x00007208) */
/* WARNING: Removing unreachable block (ram,0x000071ee) */
/* WARNING: Removing unreachable block (ram,0x000071de) */
/* WARNING: Removing unreachable block (ram,0x000071f2) */
/* WARNING: Removing unreachable block (ram,0x00007214) */
/* periph_state_cb: gapRolesCBs.pfnStateChange; BD-address name suffix, link established/terminated
    */

void periph_state_cb(uint param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = param_1 & 0xf;
  if (uVar1 == 2) {
    if (*(char *)(param_2 + 2) == '\x06') {
      periph_link_terminated(param_2);
      DAT_ram_20002fb0 = *(undefined1 *)(param_2 + 6);
    }
    ble_bind_state = 0;
  }
  else if (uVar1 < 3) {
    if (uVar1 == 1) {
      (*(code *)p_GAPRole_GetParameter)(0x304,&DAT_ram_20002fe8);
      uVar1 = (uint)(DAT_ram_20002feb ^ DAT_ram_20002fea) << 0x10 |
              (uint)(DAT_ram_20002fe9 ^ DAT_ram_20002fe8) << 0x18 |
              (DAT_ram_20002fec & 0xff) << 8 | (uint)(DAT_ram_20002fec >> 8);
      DAT_ram_20002eb4 = (char)(uVar1 % 0x5e) + '!';
      DAT_ram_20002eb5 = (char)((uVar1 / 0x5e) % 0x5e) + '!';
      DAT_ram_20002eb6 = (char)((uVar1 / 0x2284) % 0x5e) + '!';
      (*(code *)p_GAPRole_SetParameter)
                (0x307,0x1f,&scan_rsp_data,0x5e,&DAT_ram_2000321c,p_GAPRole_SetParameter);
    }
  }
  else {
    if (uVar1 == 3) {
      if (*(char *)(param_2 + 2) != '\x06') {
        gaprole_state = param_1;
        return;
      }
      periph_link_terminated(param_2);
    }
    else {
      if (uVar1 != 4) {
        gaprole_state = param_1;
        return;
      }
      if (*(char *)(param_2 + 2) == '\x05') {
        ble_conn_timer = 0;
        if (ble_conn_handle == -2) {
          DAT_ram_20002ffe = *(undefined2 *)(param_2 + 0xe);
          DAT_ram_20003000 = *(undefined2 *)(param_2 + 0x10);
          DAT_ram_20003002 = *(undefined2 *)(param_2 + 0x12);
          ble_conn_handle = *(short *)(param_2 + 10);
          (*(code *)p_tmos_start_task)
                    (DAT_ram_20002f44,8,0x1900,param_4,&DAT_ram_20003284,p_tmos_start_task);
        }
        else {
          (*(code *)p_GAPRole_TerminateLink)();
        }
      }
      if (*(char *)(param_2 + 2) != '\x06') {
        gaprole_state = param_1;
        return;
      }
    }
    DAT_ram_20002fb0 = *(undefined1 *)(param_2 + 6);
  }
                    /* WARNING: Read-only address (ram,0x00040058) is written */
                    /* WARNING: Read-only address (ram,0x00040174) is written */
                    /* WARNING: Read-only address (ram,0x00040178) is written */
                    /* WARNING: Read-only address (ram,0x0004017c) is written */
  gaprole_state = param_1;
  return;
}



// ==== periph_app_init @ ram:000072e0 size 390 callers [ram:00007794]

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* periph_app_init: advertising/scan response, 500 ms interval, bond manager, services */

void periph_app_init(void)

{
  undefined1 uStack_19;
  undefined1 uStack_18;
  undefined1 uStack_17;
  ushort uStack_16;
  undefined4 auStack_14 [2];
  
  DAT_ram_20002f44 = (*(code *)p_TMOS_ProcessEventRegister)(periph_task_event);
  uStack_17 = 0;
  uStack_16 = 6;
  auStack_14[0] = CONCAT22(auStack_14[0]._2_2_,0x28);
  (*(code *)p_GAPRole_SetParameter)(0x305,1,&uStack_17);
  (*(code *)p_GAPRole_SetParameter)(0x307,0x1f,&scan_rsp_data);
  (*(code *)p_GAPRole_SetParameter)(0x306,0x1f,&adv_data);
  (*(code *)p_GAPRole_SetParameter)(0x311,2,&uStack_16);
  (*(code *)p_GAPRole_SetParameter)(0x312,2,auStack_14);
  (*(code *)p_GAP_SetParamValue)(3,800);
  (*(code *)p_GAP_SetParamValue)(4,800);
  (*(code *)p_GAP_SetParamValue)(0x1e,1);
  auStack_14[0] = 0;
  uStack_19 = 1;
  uStack_18 = 1;
  uStack_17 = 1;
  uStack_16 = uStack_16 & 0xff00;
  (*(code *)p_GAPBondMgr_SetParameter)(0x407,4,auStack_14);
  (*(code *)p_GAPBondMgr_SetParameter)(0x400,1,&uStack_19);
  (*(code *)p_GAPBondMgr_SetParameter)(0x401,1,&uStack_18);
  (*(code *)p_GAPBondMgr_SetParameter)(0x402,1,&uStack_16);
  (*(code *)p_GAPBondMgr_SetParameter)(0x405,1,&uStack_17);
  (*(code *)p_GGS_AddService)(0xffffffff);
  (*(code *)p_GATTServApp_AddService)(0xffffffff);
  devinfo_register();
  af_service_register(&af_app_cb);
  db_service_register(&PTR_FUN_ram_00006cae_ram_20002f38);
  _ble_conn_handle = 0xfffe;
  _DAT_ram_20003000 = 0;
  FUN_ram_00003144(&PTR_FUN_ram_000070e6_ram_20002f40);
  (*(code *)p_GAPRole_BroadcasterSetCB)(&DAT_ram_20002fe0);
  (*(code *)p_tmos_set_event)(DAT_ram_20002f44,1);
  periph_init();
  FUN_ram_00002764(1);
  return;
}



// ==== FUN_ram_00007466 @ ram:00007466 size 6 callers [ram:000074bc]

void FUN_ram_00007466(void)

{
  FUN_ram_0000272a(0);
  return;
}



// ==== iap_flag_write @ ram:0000746c size 80 callers [ram:000074bc]

/* iap_flag_write: DataFlash 0x7000 byte 0 = value (3 before update reset) */

void iap_flag_write(undefined1 param_1)

{
  FLASH_EEPROM_CMD(0xb,0x7000,&DAT_ram_20005150,4);
  FLASH_EEPROM_CMD(9,0x7000,0,0x100);
  DAT_ram_20005150 = param_1;
  FLASH_EEPROM_CMD(10,0x7000,&DAT_ram_20005150,4);
  return;
}



// ==== enter_iap @ ram:000074bc size 22 callers [ram:00004ab8]

/* enter_iap: disable interrupts, write IAP flag 3, soft reset */

void enter_iap(void)

{
  FUN_ram_00007466();
  iap_flag_write(3);
  sys_soft_reset();
  return;
}



// ==== adv_mfr_tail_load @ ram:000074d2 size 96 callers [ram:00007532]

/* adv_mfr_tail_load: loads the 14-byte manufacturer data tail from DataFlash 0x6E00 */

void adv_mfr_tail_load(void)

{
  int iVar1;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined1 auStack_20 [24];
  
  (*(code *)p_tmos_memset)(auStack_20,0xff,0xe,in_a3,in_a4,p_tmos_memset);
  FLASH_EEPROM_CMD(0xb,0x6e00,&DAT_ram_200042b0,0x16);
  iVar1 = (*(code *)p_tmos_memcmp)(auStack_20,&DAT_ram_200042b0,0xe);
  if (iVar1 == 0) {
    (*(code *)p_tmos_memcpy)(&DAT_ram_20002e89,&DAT_ram_200042b0,0xe);
  }
  return;
}



// ==== adv_mfr_set_from_fc @ ram:00007532 size 54 callers [ram:0000388a]

/* adv_mfr_set_from_fc: FC: 4 bytes into manufacturer data bytes 2..5, reload tail, update advert */

void adv_mfr_set_from_fc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
                        ,undefined4 param_5)

{
  (*(code *)p_tmos_memcpy)(&DAT_ram_20002e85,param_1,4,param_4,param_5,p_tmos_memcpy);
  adv_mfr_tail_load();
  (*(code *)p_GAPRole_SetParameter)(0x306,0x1f,&adv_data);
  return;
}



// ==== adv_mfr_tail_store @ ram:00007568 size 176 callers [ram:00004224]

/* adv_mfr_tail_store: AF01 10/C0: 14 bytes into manufacturer data bytes 6..19 and DataFlash 0x6E00
   (erases the name override) */

void adv_mfr_tail_store(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                       undefined4 param_5)

{
  uint uVar1;
  
  (*(code *)p_tmos_memcpy)(&DAT_ram_20002e89,param_1,param_2,param_4,param_5,p_tmos_memcpy);
  (*(code *)p_GAPRole_SetParameter)(0x306,0x1f,&adv_data);
  FLASH_EEPROM_CMD(0xb,0x6e00,&DAT_ram_200042b0,param_2);
  for (uVar1 = 0; (uVar1 & 0xff) < param_2; uVar1 = uVar1 + 1) {
    (&DAT_ram_200042b0)[uVar1] = *(undefined1 *)(param_1 + uVar1);
  }
  FLASH_EEPROM_CMD(9,0x6e00,0,0x100);
  FLASH_EEPROM_CMD(10,0x6e00,&DAT_ram_200042b0,param_2);
  return;
}



// ==== host_ids_load @ ram:00007618 size 126 callers [ram:00007696,ram:0000773c]

/* host_ids_load: reads the 5 x 16-byte host table at DataFlash 0x6F00, counts used slots */

void host_ids_load(void)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 in_a3;
  undefined4 in_a4;
  undefined1 auStack_30 [28];
  
  (*(code *)p_tmos_memset)(auStack_30,0xff,0x10,in_a3,in_a4,p_tmos_memset);
  FLASH_EEPROM_CMD(0xb,0x6f00,&DAT_ram_200042b0,0x50);
  puVar2 = &DAT_ram_200042b0;
  cVar1 = '\0';
  do {
    iVar3 = (*(code *)p_tmos_memcmp)(auStack_30,puVar2,0x10);
    if (iVar3 == 0) {
      cVar1 = cVar1 + '\x01';
    }
    puVar2 = puVar2 + 0x10;
  } while (puVar2 != (undefined1 *)0x20004300);
  DAT_ram_20002fee = cVar1;
  return;
}



// ==== host_id_save @ ram:00007696 size 166 callers [ram:00003fac]

/* host_id_save: appends a host ID (shifts when 5 used), rewrites DataFlash 0x6F00 */

void host_id_save(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  
  host_ids_load();
  uVar2 = (uint)DAT_ram_20002fee;
  if (4 < uVar2) {
    for (uVar1 = 0; uVar2 = DAT_ram_20002fee - 1, (int)uVar1 < (int)uVar2; uVar1 = uVar1 + 1 & 0xff)
    {
      (*(code *)p_tmos_memcpy)
                (&DAT_ram_200042b0 + uVar1 * 0x10,&DAT_ram_200042c0 + uVar1 * 0x10,0x10);
    }
  }
  (*(code *)p_tmos_memcpy)(&DAT_ram_200042b0 + uVar2 * 0x10,param_1,0x10);
  FLASH_EEPROM_CMD(9,0x6f00,0,0x100);
  FLASH_EEPROM_CMD(10,0x6f00,&DAT_ram_200042b0,0x50);
  return;
}



// ==== host_id_lookup @ ram:0000773c size 88 callers [ram:000040dc]

/* host_id_lookup: 1 if the 16 bytes match a stored host ID */

undefined4 host_id_lookup(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 extraout_a3;
  undefined4 uVar3;
  undefined4 extraout_a3_00;
  undefined4 extraout_a4;
  undefined4 uVar4;
  undefined4 extraout_a4_00;
  
  uVar1 = 0;
  host_ids_load();
  uVar3 = extraout_a3;
  uVar4 = extraout_a4;
  while( true ) {
    if (DAT_ram_20002fee <= uVar1) {
                    /* WARNING: Read-only address (ram,0x0004003c) is written */
      return 0;
    }
    iVar2 = (*(code *)p_tmos_memcmp)
                      (param_1,&DAT_ram_200042b0 + uVar1 * 0x10,0x10,uVar3,uVar4,p_tmos_memcmp);
    if (iVar2 != 0) break;
    uVar1 = uVar1 + 1 & 0xff;
    uVar3 = extraout_a3_00;
    uVar4 = extraout_a4_00;
  }
  return 1;
}



// ==== main @ ram:00007794 size 108 callers []

/* main: clock 60 MHz, GPIO, UART0, BLE lib, roles, app init, TMOS loop */

void main(void)

{
  dword dVar1;
  
  FUN_ram_200023fe(0x48);
  GPIOA_ModeCfg(0xffffefff,2);
  GPIOB_ModeCfg(0xffffbfef,2);
  dVar1 = PB_OUT;
  PB_OUT = dVar1 | 0x80;
  GPIOB_ModeCfg(0x80,3);
  uart0_init_115200();
  ble_lib_init();
  hal_init();
  (*(code *)p_GAPRole_PeripheralInit)();
  (*(code *)p_GAPRole_CentralInit)();
  periph_app_init();
  central_app_init();
  FUN_ram_2000280a();
  return;
}



// ==== FUN_ram_00007800 @ ram:00007800 size 2 callers [ram:00007846]

void FUN_ram_00007800(void)

{
  return;
}



// ==== FUN_ram_00007804 @ ram:00007804 size 10 callers [ram:00001c48,ram:00007d1e]

void FUN_ram_00007804(undefined4 param_1)

{
  FUN_ram_00007c92(0,param_1,0,0);
  return;
}



// ==== FUN_ram_0000780e @ ram:0000780e size 58 callers []

void FUN_ram_0000780e(void)

{
  int iVar1;
  
  iVar1 = 0;
  while (iVar1 != 0) {
    iVar1 = iVar1 + -1;
    (*(code *)(&DAT_ram_00009318)[iVar1])();
  }
  return;
}



// ==== FUN_ram_00007846 @ ram:00007846 size 108 callers [ram:00001c48]

void FUN_ram_00007846(void)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 != 0; iVar1 = iVar1 + 1) {
    (*(code *)(&PTR_FUN_ram_00007d1e_ram_00009310)[iVar1])();
  }
  FUN_ram_00007800();
  for (iVar1 = 0; iVar1 != 2; iVar1 = iVar1 + 1) {
    (*(code *)(&PTR_FUN_ram_00007d1e_ram_00009310)[iVar1])();
  }
  return;
}



// ==== memcpy @ ram:000078b2 size 182 callers [ram:00003d0c,ram:00004cee,ram:00004fba,ram:00005710,ram:00005af0,ram:000065a0,ram:0000685a,ram:2000277e]

/* memcpy: memcpy */

void memcpy(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  
  puVar4 = (undefined4 *)((int)param_1 + param_3);
  if (((((uint)param_2 ^ (uint)param_1) & 3) == 0) && (3 < param_3)) {
    for (; ((uint)param_1 & 3) != 0; param_1 = (undefined4 *)((int)param_1 + 1)) {
      uVar1 = *(undefined1 *)param_2;
      param_2 = (undefined4 *)((int)param_2 + 1);
      *(undefined1 *)param_1 = uVar1;
    }
    for (; param_1 < (undefined4 *)((uint)puVar4 & 0xfffffffc) + -8; param_1 = param_1 + 9) {
      uVar2 = param_2[1];
      uVar11 = param_2[2];
      uVar10 = param_2[3];
      uVar9 = param_2[4];
      uVar8 = param_2[5];
      uVar3 = param_2[6];
      uVar7 = param_2[7];
      *param_1 = *param_2;
      uVar6 = param_2[8];
      param_1[1] = uVar2;
      param_1[2] = uVar11;
      param_1[3] = uVar10;
      param_1[4] = uVar9;
      param_1[5] = uVar8;
      param_1[6] = uVar3;
      param_1[7] = uVar7;
      param_1[8] = uVar6;
      param_2 = param_2 + 9;
    }
    for (; param_1 < (undefined4 *)((uint)puVar4 & 0xfffffffc); param_1 = param_1 + 1) {
      uVar2 = *param_2;
      param_2 = param_2 + 1;
      *param_1 = uVar2;
    }
  }
  if (puVar4 <= param_1) {
    return;
  }
  do {
    uVar1 = *(undefined1 *)param_2;
    puVar5 = (undefined4 *)((int)param_1 + 1);
    param_2 = (undefined4 *)((int)param_2 + 1);
    *(undefined1 *)param_1 = uVar1;
    param_1 = puVar5;
  } while (puVar5 < puVar4);
  return;
}



// ==== printf @ ram:00007968 size 68 callers [ram:00004916,ram:00004964,ram:00004e1a,ram:00005864,ram:00005af0,ram:000065a0]

/* printf: newlib printf; _write is a stub, so nothing is output */

void printf(undefined4 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_ram_20002eb8_ram_20002f48;
  if ((PTR_DAT_ram_20002eb8_ram_20002f48 != (undefined *)0x0) &&
     (*(int *)(PTR_DAT_ram_20002eb8_ram_20002f48 + 0x18) == 0)) {
    FUN_ram_00007f90(PTR_DAT_ram_20002eb8_ram_20002f48);
  }
  FUN_ram_00008402(puVar1,*(undefined4 *)(puVar1 + 8),param_1);
  return;
}



// ==== putchar @ ram:000079ac size 46 callers [ram:00004964,ram:00004e1a,ram:00005af0]

/* putchar: newlib putchar; output discarded */

void putchar(undefined4 param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_ram_20002eb8_ram_20002f48;
  if ((PTR_DAT_ram_20002eb8_ram_20002f48 != (undefined *)0x0) &&
     (*(int *)(PTR_DAT_ram_20002eb8_ram_20002f48 + 0x18) == 0)) {
    FUN_ram_00007f90(PTR_DAT_ram_20002eb8_ram_20002f48,param_1);
  }
  FUN_ram_00008a52(puVar1,param_1,*(undefined4 *)(puVar1 + 8));
  return;
}



// ==== FUN_ram_00007ab4 @ ram:00007ab4 size 232 callers [ram:00005864,ram:00005af0]

undefined4 FUN_ram_00007ab4(char *param_1)

{
  char cVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int iVar4;
  char *pcVar5;
  undefined1 *puVar6;
  
  puVar2 = PTR_DAT_ram_20002eb8_ram_20002f48;
  if ((PTR_DAT_ram_20002eb8_ram_20002f48 != (undefined *)0x0) &&
     (*(int *)(PTR_DAT_ram_20002eb8_ram_20002f48 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  puVar3 = *(undefined4 **)(puVar2 + 8);
  if (*(int *)(puVar2 + 0x18) == 0) {
    FUN_ram_00007f90(puVar2);
  }
  if (puVar3 == &DAT_ram_00009234) {
    puVar3 = *(undefined4 **)(puVar2 + 4);
  }
  else if (puVar3 == &DAT_ram_00009254) {
    puVar3 = *(undefined4 **)(puVar2 + 8);
  }
  else if (puVar3 == (undefined4 *)&DAT_ram_00009214) {
    puVar3 = *(undefined4 **)(puVar2 + 0xc);
  }
  if ((((*(ushort *)(puVar3 + 3) & 8) != 0) && (puVar3[4] != 0)) ||
     (iVar4 = FUN_ram_00007b82(puVar2,puVar3), iVar4 == 0)) {
    do {
      while( true ) {
        cVar1 = *param_1;
        iVar4 = puVar3[2] + -1;
        if (cVar1 == '\0') {
          puVar3[2] = iVar4;
          if (iVar4 < 0) {
            iVar4 = FUN_ram_00007ac2(puVar2,10,puVar3);
            if (iVar4 == -1) {
              return 0xffffffff;
            }
          }
          else {
            puVar6 = (undefined1 *)*puVar3;
            *puVar3 = puVar6 + 1;
            *puVar6 = 10;
          }
          return 10;
        }
        puVar3[2] = iVar4;
        param_1 = param_1 + 1;
        if ((iVar4 < 0) && ((iVar4 < (int)puVar3[6] || (cVar1 == '\n')))) break;
        pcVar5 = (char *)*puVar3;
        *puVar3 = pcVar5 + 1;
        *pcVar5 = cVar1;
      }
      iVar4 = FUN_ram_00007ac2(puVar2,cVar1,puVar3);
    } while (iVar4 != -1);
  }
  return 0xffffffff;
}



// ==== FUN_ram_00007ac2 @ ram:00007ac2 size 192 callers [ram:00007ab4,ram:00008396,ram:00008a52]

uint FUN_ram_00007ac2(int param_1,byte param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_3 == &DAT_ram_00009234) {
    param_3 = *(int **)(param_1 + 4);
  }
  else if (param_3 == &DAT_ram_00009254) {
    param_3 = *(int **)(param_1 + 8);
  }
  else if (param_3 == (int *)&DAT_ram_00009214) {
    param_3 = *(int **)(param_1 + 0xc);
  }
  param_3[2] = param_3[6];
  if ((((*(ushort *)(param_3 + 3) & 8) != 0) && (param_3[4] != 0)) ||
     (iVar1 = FUN_ram_00007b82(param_1,param_3), iVar1 == 0)) {
    uVar4 = (uint)param_2;
    iVar1 = *param_3 - param_3[4];
    if (param_3[5] <= iVar1) {
      iVar2 = FUN_ram_00007e72(param_1,param_3);
      iVar1 = 0;
      if (iVar2 != 0) {
        return 0xffffffff;
      }
    }
    param_3[2] = param_3[2] + -1;
    pbVar3 = (byte *)*param_3;
    *param_3 = (int)(pbVar3 + 1);
    *pbVar3 = param_2;
    if (param_3[5] != iVar1 + 1) {
      if ((*(ushort *)(param_3 + 3) & 1) == 0) {
        return uVar4;
      }
      if (uVar4 != 10) {
        return uVar4;
      }
    }
    iVar1 = FUN_ram_00007e72(param_1,param_3);
    if (iVar1 == 0) {
      return uVar4;
    }
  }
  return 0xffffffff;
}



// ==== FUN_ram_00007b82 @ ram:00007b82 size 272 callers [ram:00007ab4,ram:00007ac2,ram:00008402]

undefined4 FUN_ram_00007b82(undefined4 *param_1,undefined4 *param_2)

{
  ushort uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  puVar2 = PTR_DAT_ram_20002eb8_ram_20002f48;
  if ((PTR_DAT_ram_20002eb8_ram_20002f48 != (undefined *)0x0) &&
     (*(int *)(PTR_DAT_ram_20002eb8_ram_20002f48 + 0x18) == 0)) {
    FUN_ram_00007f90(PTR_DAT_ram_20002eb8_ram_20002f48);
  }
  if (param_2 == &DAT_ram_00009234) {
    param_2 = *(undefined4 **)(puVar2 + 4);
  }
  else if (param_2 == &DAT_ram_00009254) {
    param_2 = *(undefined4 **)(puVar2 + 8);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009214) {
    param_2 = *(undefined4 **)(puVar2 + 0xc);
  }
  uVar1 = *(ushort *)(param_2 + 3);
  if ((uVar1 & 8) == 0) {
    if ((uVar1 & 0x10) == 0) {
      *param_1 = 9;
      *(ushort *)(param_2 + 3) = uVar1 | 0x40;
      return 0xffffffff;
    }
    if ((uVar1 & 4) != 0) {
      if ((undefined4 *)param_2[0xd] != (undefined4 *)0x0) {
        if ((undefined4 *)param_2[0xd] != param_2 + 0x11) {
          FUN_ram_000081fe(param_1);
        }
        param_2[0xd] = 0;
      }
      param_2[1] = 0;
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) & 0xffdb;
      *param_2 = param_2[4];
    }
    *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 8;
  }
  if ((param_2[4] == 0) && ((*(ushort *)(param_2 + 3) & 0x280) != 0x200)) {
    FUN_ram_00008160(param_1,param_2);
  }
  if ((*(ushort *)(param_2 + 3) & 1) == 0) {
    uVar3 = 0;
    if ((*(ushort *)(param_2 + 3) & 2) == 0) {
      uVar3 = param_2[5];
    }
    param_2[2] = uVar3;
  }
  else {
    param_2[2] = 0;
    param_2[6] = -param_2[5];
  }
  if (param_2[4] == 0) {
    if ((*(ushort *)(param_2 + 3) & 0x80) != 0) {
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x40;
      return 0xffffffff;
    }
    return 0;
  }
  return 0;
}



// ==== FUN_ram_00007c92 @ ram:00007c92 size 140 callers [ram:00007804]

/* WARNING: Removing unreachable block (ram,0x00007cbc) */

undefined4 FUN_ram_00007c92(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined *puVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  
  if (DAT_ram_20003004 == (undefined *)0x0) {
    DAT_ram_20003004 = &DAT_ram_20006d60;
  }
  puVar1 = DAT_ram_20003004;
  uVar4 = *(uint *)(DAT_ram_20003004 + 4);
  uVar2 = 0xffffffff;
  if ((int)uVar4 < 0x20) {
    if (param_1 != 0) {
      iVar5 = *(int *)(DAT_ram_20003004 + 0x88);
      if (iVar5 == 0) {
        return 0xffffffff;
      }
      puVar6 = (undefined4 *)(uVar4 * 4 + iVar5);
      *puVar6 = param_3;
      uVar3 = 1 << (uVar4 & 0x1f);
      *(uint *)(iVar5 + 0x100) = *(uint *)(iVar5 + 0x100) | uVar3;
      puVar6[0x20] = param_4;
      if (param_1 == 2) {
        *(uint *)(iVar5 + 0x104) = uVar3 | *(uint *)(iVar5 + 0x104);
      }
    }
    *(uint *)(puVar1 + 4) = uVar4 + 1;
    *(undefined4 *)(puVar1 + uVar4 * 4 + 8) = param_2;
    uVar2 = 0;
  }
  return uVar2;
}



// ==== FUN_ram_00007d1e @ ram:00007d1e size 24 callers [ram:00007846]

/* WARNING: Removing unreachable block (ram,0x00007d28) */

void FUN_ram_00007d1e(void)

{
  return;
}



// ==== FUN_ram_00007d36 @ ram:00007d36 size 316 callers [ram:00007e72]

undefined4 FUN_ram_00007d36(uint *param_1,int *param_2)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  code *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  uVar1 = *(ushort *)(param_2 + 3);
  if ((uVar1 & 8) == 0) {
    if ((param_2[1] < 1) && (param_2[0x10] < 1)) {
      return 0;
    }
    pcVar4 = (code *)param_2[0xb];
    if (pcVar4 == (code *)0x0) {
      return 0;
    }
    uVar7 = *param_1;
    *param_1 = 0;
    if ((int)((uint)uVar1 << 0x13) < 0) {
      iVar3 = param_2[0x15];
    }
    else {
      iVar3 = (*pcVar4)(param_1,param_2[8],0,1);
      if ((iVar3 == -1) && (uVar6 = *param_1, uVar6 != 0)) {
        if ((uVar6 == 0x1d) || (uVar6 == 0x16)) {
          *param_1 = uVar7;
          return 0;
        }
LAB_ram_00007e5c:
        *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x40;
        return 0xffffffff;
      }
    }
    if (((*(ushort *)(param_2 + 3) & 4) != 0) && (iVar3 = iVar3 - param_2[1], param_2[0xd] != 0)) {
      iVar3 = iVar3 - param_2[0x10];
    }
    iVar3 = (*(code *)param_2[0xb])(param_1,param_2[8],iVar3,0);
    if ((iVar3 == -1) && ((0x1d < *param_1 || ((0x20400001U >> (*param_1 & 0x1f) & 1) == 0)))) {
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x40;
      return 0xffffffff;
    }
    param_2[1] = 0;
    *param_2 = param_2[4];
    if (((int)((uint)*(ushort *)(param_2 + 3) << 0x13) < 0) && ((iVar3 != -1 || (*param_1 == 0)))) {
      param_2[0x15] = iVar3;
    }
    piVar2 = (int *)param_2[0xd];
    *param_1 = uVar7;
    if (piVar2 != (int *)0x0) {
      if (piVar2 != param_2 + 0x11) {
        FUN_ram_000081fe(param_1);
      }
      param_2[0xd] = 0;
    }
  }
  else {
    iVar3 = param_2[4];
    if (iVar3 != 0) {
      iVar8 = *param_2;
      *param_2 = iVar3;
      iVar8 = iVar8 - iVar3;
      iVar5 = 0;
      if ((uVar1 & 3) == 0) {
        iVar5 = param_2[5];
      }
      param_2[2] = iVar5;
      for (; 0 < iVar8; iVar8 = iVar8 - iVar5) {
        iVar5 = (*(code *)param_2[10])(param_1,param_2[8],iVar3,iVar8);
        if (iVar5 < 1) goto LAB_ram_00007e5c;
        iVar3 = iVar3 + iVar5;
      }
    }
  }
  return 0;
}



// ==== FUN_ram_00007e72 @ ram:00007e72 size 100 callers [ram:00007ac2]

undefined4 FUN_ram_00007e72(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2[4] == 0) {
    return 0;
  }
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_2 == &DAT_ram_00009234) {
    param_2 = *(undefined4 **)(param_1 + 4);
  }
  else if (param_2 == &DAT_ram_00009254) {
    param_2 = *(undefined4 **)(param_1 + 8);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009214) {
    param_2 = *(undefined4 **)(param_1 + 0xc);
  }
  if (*(short *)(param_2 + 3) != 0) {
    uVar1 = FUN_ram_00007d36(param_1);
    return uVar1;
  }
  return 0;
}



// ==== FUN_ram_00007ed6 @ ram:00007ed6 size 106 callers [ram:00007f90]

void FUN_ram_00007ed6(undefined4 *param_1,undefined2 param_2,undefined2 param_3)

{
  *(undefined2 *)(param_1 + 3) = param_2;
  *(undefined2 *)((int)param_1 + 0xe) = param_3;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[0x19] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  memset(param_1 + 0x17,0,8);
  param_1[9] = FUN_ram_00008b08;
  param_1[10] = &DAT_ram_00008b38;
  param_1[0xb] = FUN_ram_00008b86;
  param_1[8] = param_1;
  param_1[0xc] = &LAB_ram_00008bbc;
  return;
}



// ==== FUN_ram_00007f40 @ ram:00007f40 size 10 callers []

void FUN_ram_00007f40(undefined4 param_1)

{
  FUN_ram_0000809a(param_1,FUN_ram_00007e72);
  return;
}



// ==== FUN_ram_00007f4a @ ram:00007f4a size 70 callers [ram:00007ffa]

undefined4 * FUN_ram_00007f4a(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = (param_2 + -1) * 0x68;
  puVar2 = (undefined4 *)FUN_ram_000082ae(param_1,iVar1 + 0x74);
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = 0;
    puVar2[1] = param_2;
    puVar2[2] = puVar2 + 3;
    memset(puVar2 + 3,0,iVar1 + 0x68);
  }
  return puVar2;
}



// ==== FUN_ram_00007f90 @ ram:00007f90 size 106 callers [ram:00007968,ram:000079ac,ram:00007ab4,ram:00007ac2,ram:00007b82,ram:00007e72,ram:00007ffa,ram:00008402,ram:00008a52]

void FUN_ram_00007f90(undefined *param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    *(code **)(param_1 + 0x28) = FUN_ram_00007f40;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined4 *)(param_1 + 0x4c) = 0;
    *(undefined4 *)(param_1 + 0x50) = 0;
    if (param_1 == &DAT_ram_20002eb8) {
      DAT_ram_20002ed0 = 1;
    }
    uVar1 = FUN_ram_00007ffa();
    *(undefined4 *)(param_1 + 4) = uVar1;
    uVar1 = FUN_ram_00007ffa(param_1);
    *(undefined4 *)(param_1 + 8) = uVar1;
    uVar1 = FUN_ram_00007ffa(param_1);
    *(undefined4 *)(param_1 + 0xc) = uVar1;
    FUN_ram_00007ed6(*(undefined4 *)(param_1 + 4),4,0);
    FUN_ram_00007ed6(*(undefined4 *)(param_1 + 8),9,1);
    FUN_ram_00007ed6(*(undefined4 *)(param_1 + 0xc),0x12,2);
    *(undefined4 *)(param_1 + 0x18) = 1;
    return;
  }
  return;
}



// ==== FUN_ram_00007ffa @ ram:00007ffa size 160 callers [ram:00007f90]

undefined4 * FUN_ram_00007ffa(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  
  if (DAT_ram_20002ed0 == 0) {
    FUN_ram_00007f90(&DAT_ram_20002eb8);
  }
  piVar2 = &DAT_ram_20002f00;
  do {
    puVar1 = (undefined4 *)piVar2[2];
    iVar3 = piVar2[1];
    while (iVar3 = iVar3 + -1, -1 < iVar3) {
      if (*(short *)(puVar1 + 3) == 0) {
        puVar1[0x19] = 0;
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        puVar1[3] = 0xffff0001;
        puVar1[4] = 0;
        puVar1[5] = 0;
        puVar1[6] = 0;
        memset(puVar1 + 0x17,0,8);
        puVar1[0xd] = 0;
        puVar1[0xe] = 0;
        puVar1[0x12] = 0;
        puVar1[0x13] = 0;
        return puVar1;
      }
      puVar1 = puVar1 + 0x1a;
    }
    if (*piVar2 == 0) {
      iVar3 = FUN_ram_00007f4a(param_1,4);
      *piVar2 = iVar3;
      if (iVar3 == 0) {
        *param_1 = 0xc;
        return (undefined4 *)0x0;
      }
    }
    piVar2 = (int *)*piVar2;
  } while( true );
}



// ==== FUN_ram_0000809a @ ram:0000809a size 108 callers [ram:00007f40]

uint FUN_ram_0000809a(int param_1,code *param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = 0;
  for (piVar1 = (int *)(param_1 + 0x48); piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
    iVar2 = piVar1[2];
    iVar5 = piVar1[1];
    while (iVar5 = iVar5 + -1, -1 < iVar5) {
      if ((1 < *(ushort *)(iVar2 + 0xc)) && (*(short *)(iVar2 + 0xe) != -1)) {
        uVar3 = (*param_2)(param_1,iVar2);
        uVar4 = uVar4 | uVar3;
      }
      iVar2 = iVar2 + 0x68;
    }
  }
  return uVar4;
}



// ==== FUN_ram_00008106 @ ram:00008106 size 90 callers [ram:00008160]

undefined4 FUN_ram_00008106(undefined4 param_1,int param_2,undefined4 *param_3,uint *param_4)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_68 [4];
  uint uStack_64;
  
  if (*(short *)(param_2 + 0xe) < 0) {
LAB_ram_0000811a:
    uVar1 = *(ushort *)(param_2 + 0xc);
    *param_4 = 0;
    if ((uVar1 & 0x80) != 0) {
      uVar3 = 0x40;
      goto LAB_ram_00008152;
    }
  }
  else {
    iVar2 = FUN_ram_00008c26(param_1,(int)*(short *)(param_2 + 0xe),auStack_68);
    if (iVar2 < 0) goto LAB_ram_0000811a;
    *param_4 = (uint)((uStack_64 & 0xf000) == 0x2000);
  }
  uVar3 = 0x400;
LAB_ram_00008152:
  *param_3 = uVar3;
  return 0;
}



// ==== FUN_ram_00008160 @ ram:00008160 size 158 callers [ram:00007b82]

void FUN_ram_00008160(int param_1,int *param_2)

{
  ushort uVar1;
  int iVar2;
  int iStack_18;
  int iStack_14;
  
  if ((*(ushort *)(param_2 + 3) & 2) == 0) {
    uVar1 = FUN_ram_00008106(param_1,param_2,&iStack_18,&iStack_14);
    iVar2 = FUN_ram_000082ae(param_1,iStack_18);
    if (iVar2 != 0) {
      *(code **)(param_1 + 0x28) = FUN_ram_00007f40;
      *param_2 = iVar2;
      param_2[4] = iVar2;
      *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) | 0x80;
      param_2[5] = iStack_18;
      if ((iStack_14 != 0) &&
         (iVar2 = FUN_ram_00008c58(param_1,(int)*(short *)((int)param_2 + 0xe)), iVar2 != 0)) {
        *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) & 0xfffc | 1;
      }
      *(ushort *)(param_2 + 3) = uVar1 | *(ushort *)(param_2 + 3);
      return;
    }
    if ((*(ushort *)(param_2 + 3) & 0x200) != 0) {
      return;
    }
    *(ushort *)(param_2 + 3) = *(ushort *)(param_2 + 3) & 0xfffc | 2;
  }
  *param_2 = (int)param_2 + 0x47;
  param_2[4] = (int)param_2 + 0x47;
  param_2[5] = 1;
  return;
}



// ==== FUN_ram_000081fe @ ram:000081fe size 176 callers [ram:00007b82,ram:00007d36]

void FUN_ram_000081fe(undefined4 *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  if (param_2 == 0) {
    return;
  }
  piVar1 = (int *)(param_2 - 4);
  if (*(int *)(param_2 + -4) < 0) {
    piVar1 = (int *)((int)piVar1 + *(int *)(param_2 + -4));
  }
  FUN_ram_00008cd6();
  if (DAT_ram_20003008 == (int *)0x0) {
    piVar1[1] = 0;
    DAT_ram_20003008 = piVar1;
  }
  else {
    piVar4 = DAT_ram_20003008;
    if (piVar1 < DAT_ram_20003008) {
      if (DAT_ram_20003008 == (int *)((int)piVar1 + *piVar1)) {
        iVar3 = *DAT_ram_20003008;
        DAT_ram_20003008 = (int *)DAT_ram_20003008[1];
        *piVar1 = iVar3 + *piVar1;
      }
      piVar1[1] = (int)DAT_ram_20003008;
      DAT_ram_20003008 = piVar1;
    }
    else {
      do {
        piVar6 = piVar4;
        piVar4 = (int *)piVar6[1];
        if (piVar4 == (int *)0x0) break;
      } while (piVar4 <= piVar1);
      piVar2 = (int *)((int)piVar6 + *piVar6);
      if (piVar2 == piVar1) {
        iVar3 = *piVar6 + *piVar1;
        *piVar6 = iVar3;
        if (piVar4 == (int *)((int)piVar6 + iVar3)) {
          iVar5 = piVar4[1];
          *piVar6 = iVar3 + *piVar4;
          piVar6[1] = iVar5;
        }
      }
      else if (piVar1 < piVar2) {
        *param_1 = 0xc;
      }
      else {
        if (piVar4 == (int *)((int)piVar1 + *piVar1)) {
          iVar3 = *piVar4;
          piVar4 = (int *)piVar4[1];
          *piVar1 = iVar3 + *piVar1;
        }
        piVar1[1] = (int)piVar4;
        piVar6[1] = (int)piVar1;
      }
    }
  }
  FUN_ram_00008cd8(param_1);
  return;
}



// ==== FUN_ram_000082ae @ ram:000082ae size 232 callers [ram:00007f4a,ram:00008160]

uint FUN_ram_000082ae(undefined4 *param_1,uint param_2)

{
  uint *puVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  
  uVar2 = (param_2 + 3 & 0xfffffffc) + 8;
  if (uVar2 < 0xc) {
    uVar2 = 0xc;
  }
  else if ((int)uVar2 < 0) goto LAB_ram_0000831e;
  if (param_2 <= uVar2) {
    FUN_ram_00008cd6();
    puVar3 = DAT_ram_20003008;
    puVar5 = DAT_ram_20003008;
    do {
      puVar1 = puVar3;
      if (puVar1 == (uint *)0x0) {
        if (DAT_ram_2000300c == 0) {
          DAT_ram_2000300c = FUN_ram_00008ad8(param_1,0);
        }
        puVar3 = (uint *)FUN_ram_00008ad8(param_1,uVar2);
        if ((puVar3 == (uint *)0xffffffff) ||
           ((puVar1 = (uint *)((int)puVar3 + 3U & 0xfffffffc), puVar3 != puVar1 &&
            (iVar4 = FUN_ram_00008ad8(param_1,(int)puVar1 - (int)puVar3), iVar4 == -1)))) {
          *param_1 = 0xc;
          FUN_ram_00008cd8(param_1);
          return 0;
        }
LAB_ram_00008344:
        *puVar1 = uVar2;
        puVar3 = DAT_ram_20003008;
LAB_ram_00008356:
        DAT_ram_20003008 = puVar3;
        FUN_ram_00008cd8(param_1);
        uVar2 = (int)puVar1 + 0xbU & 0xfffffff8;
        iVar4 = uVar2 - (int)(puVar1 + 1);
        if (iVar4 != 0) {
          *(uint *)((int)puVar1 + iVar4) = (int)(puVar1 + 1) - uVar2;
          return uVar2;
        }
        return uVar2;
      }
      uVar6 = *puVar1 - uVar2;
      if (-1 < (int)uVar6) {
        if (uVar6 < 0xc) {
          puVar3 = (uint *)puVar1[1];
          if (puVar5 != puVar1) {
            puVar5[1] = puVar1[1];
            puVar3 = DAT_ram_20003008;
          }
          goto LAB_ram_00008356;
        }
        *puVar1 = uVar6;
        puVar1 = (uint *)((int)puVar1 + uVar6);
        goto LAB_ram_00008344;
      }
      puVar3 = (uint *)puVar1[1];
      puVar5 = puVar1;
    } while( true );
  }
LAB_ram_0000831e:
  *param_1 = 0xc;
  return 0;
}



// ==== FUN_ram_00008396 @ ram:00008396 size 42 callers [ram:000083c0]

int FUN_ram_00008396(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined1 *puVar2;
  
  iVar1 = param_3[2] + -1;
  param_3[2] = iVar1;
  if ((iVar1 < 0) && ((iVar1 < (int)param_3[6] || (param_2 == 10)))) {
    iVar1 = FUN_ram_00007ac2();
    return iVar1;
  }
  puVar2 = (undefined1 *)*param_3;
  *param_3 = puVar2 + 1;
  *puVar2 = (char)param_2;
  return param_2;
}



// ==== FUN_ram_000083c0 @ ram:000083c0 size 66 callers [ram:00008402]

undefined4 FUN_ram_000083c0(undefined4 param_1,undefined4 param_2,undefined1 *param_3,int param_4)

{
  undefined1 *puVar1;
  int iVar2;
  
  puVar1 = param_3 + param_4;
  do {
    if (param_3 == puVar1) {
      return 0;
    }
    iVar2 = FUN_ram_00008396(param_1,*param_3,param_2);
    param_3 = param_3 + 1;
  } while (iVar2 != -1);
  return 0xffffffff;
}



// ==== FUN_ram_00008402 @ ram:00008402 size 668 callers [ram:00007968]

/* WARNING: Removing unreachable block (ram,0x0000865a) */

int FUN_ram_00008402(int param_1,undefined4 *param_2,byte *param_3,int *param_4)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  byte *pbVar4;
  int unaff_s4;
  int iVar5;
  int *piStack_94;
  uint uStack_90;
  int iStack_8c;
  undefined4 uStack_88;
  int iStack_84;
  int iStack_7c;
  byte bStack_78;
  undefined1 uStack_77;
  undefined1 uStack_76;
  undefined1 uStack_4d;
  undefined4 uStack_38;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_2 == &DAT_ram_00009234) {
    param_2 = *(undefined4 **)(param_1 + 4);
  }
  else if (param_2 == &DAT_ram_00009254) {
    param_2 = *(undefined4 **)(param_1 + 8);
  }
  else if (param_2 == (undefined4 *)&DAT_ram_00009214) {
    param_2 = *(undefined4 **)(param_1 + 0xc);
  }
  if ((((*(ushort *)(param_2 + 3) & 8) == 0) || (param_2[4] == 0)) &&
     (iVar5 = FUN_ram_00007b82(param_1,param_2), iVar5 != 0)) {
    return -1;
  }
  uStack_77 = 0x20;
  iStack_7c = 0;
  uStack_76 = 0x30;
  piStack_94 = param_4;
  pbVar4 = param_3;
  do {
    for (; (*param_3 != 0 && (*param_3 != 0x25)); param_3 = param_3 + 1) {
    }
    iVar5 = (int)param_3 - (int)pbVar4;
    if (iVar5 != 0) {
      iVar1 = FUN_ram_000083c0(param_1,param_2,pbVar4,iVar5);
      if (iVar1 == -1) {
LAB_ram_0000867a:
        if ((*(ushort *)(param_2 + 3) & 0x40) != 0) {
          return -1;
        }
        return iStack_7c;
      }
      iStack_7c = iStack_7c + iVar5;
    }
    if (*param_3 == 0) goto LAB_ram_0000867a;
    uStack_90 = 0;
    iStack_84 = 0;
    iStack_8c = -1;
    uStack_88 = 0;
    uStack_4d = 0;
    uStack_38 = 0;
    pbVar4 = param_3 + 1;
    while( true ) {
      iVar5 = FUN_ram_00008cbc(&DAT_ram_00009274,*pbVar4,5);
      param_3 = pbVar4 + 1;
      if (iVar5 == 0) break;
      uStack_90 = uStack_90 | 1 << (iVar5 - 0x9274U & 0x1f);
      pbVar4 = param_3;
    }
    if ((uStack_90 & 0x10) != 0) {
      uStack_4d = 0x20;
    }
    if ((uStack_90 & 8) != 0) {
      uStack_4d = 0x2b;
    }
    if (*pbVar4 == 0x2a) {
      piVar3 = piStack_94 + 1;
      iStack_84 = *piStack_94;
      piStack_94 = piVar3;
      if (iStack_84 < 0) {
        iStack_84 = -iStack_84;
        uStack_90 = uStack_90 | 2;
      }
    }
    else {
      bVar2 = false;
      param_3 = pbVar4;
      iVar5 = iStack_84;
      while( true ) {
        if (9 < *param_3 - 0x30) break;
        bVar2 = true;
        iVar5 = iVar5 * 10 + (*param_3 - 0x30);
        param_3 = param_3 + 1;
      }
      if (bVar2) {
        iStack_84 = iVar5;
      }
    }
    if (*param_3 == 0x2e) {
      if (param_3[1] == 0x2a) {
        param_3 = param_3 + 2;
        piVar3 = piStack_94 + 1;
        iVar5 = *piStack_94;
        piStack_94 = piVar3;
        if (iVar5 < 0) {
          iVar5 = -1;
        }
      }
      else {
        iStack_8c = 0;
        bVar2 = false;
        iVar5 = 0;
        while( true ) {
          param_3 = param_3 + 1;
          if (9 < *param_3 - 0x30) break;
          bVar2 = true;
          iVar5 = iVar5 * 10 + (*param_3 - 0x30);
        }
        if (!bVar2) goto LAB_ram_000085e0;
      }
      iStack_8c = iVar5;
    }
LAB_ram_000085e0:
    iVar5 = FUN_ram_00008cbc(&DAT_ram_0000927c,*param_3,3);
    if (iVar5 != 0) {
      param_3 = param_3 + 1;
      uStack_90 = uStack_90 | 0x40 << (iVar5 - 0x927cU & 0x1f);
    }
    bStack_78 = *param_3;
    param_3 = param_3 + 1;
    iVar5 = FUN_ram_00008cbc("efgEFG",bStack_78,6);
    if (iVar5 == 0) {
      unaff_s4 = FUN_ram_000087aa(param_1,&uStack_90,param_2,FUN_ram_000083c0,&piStack_94);
      if (unaff_s4 == -1) goto LAB_ram_0000867a;
    }
    else if ((uStack_90 & 0x100) == 0) {
      piStack_94 = (int *)(((int)piStack_94 + 7U & 0xfffffff8) + 8);
    }
    else {
      piStack_94 = piStack_94 + 1;
    }
    iStack_7c = iStack_7c + unaff_s4;
    pbVar4 = param_3;
  } while( true );
}



// ==== FUN_ram_0000869e @ ram:0000869e size 268 callers [ram:000087aa]

undefined4
FUN_ram_0000869e(undefined4 param_1,uint *param_2,uint *param_3,undefined4 param_4,code *param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  
  uVar5 = param_2[4];
  if ((int)param_2[4] < (int)param_2[2]) {
    uVar5 = param_2[2];
  }
  *param_3 = uVar5;
  if (*(char *)((int)param_2 + 0x43) != '\0') {
    *param_3 = uVar5 + 1;
  }
  if ((*param_2 & 0x20) != 0) {
    *param_3 = *param_3 + 2;
  }
  if ((*param_2 & 6) == 0) {
    iVar1 = 0;
    while( true ) {
      if ((int)(param_2[3] - *param_3) <= iVar1) break;
      iVar6 = (*param_5)(param_1,param_4,(int)param_2 + 0x19,1);
      if (iVar6 == -1) goto LAB_ram_0000875e;
      iVar1 = iVar1 + 1;
    }
  }
  uVar4 = (uint)(*(char *)((int)param_2 + 0x43) != '\0');
  uVar5 = uVar4;
  if ((*param_2 & 0x20) != 0) {
    *(undefined1 *)((int)param_2 + uVar4 + 0x43) = 0x30;
    uVar5 = uVar4 + 2;
    *(undefined1 *)((int)param_2 + uVar4 + 0x44) = *(undefined1 *)((int)param_2 + 0x45);
  }
  iVar1 = (*param_5)(param_1,param_4,(int)param_2 + 0x43,uVar5);
  if (iVar1 == -1) {
LAB_ram_0000875e:
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = 0;
    if (((*param_2 & 6) == 4) && (iVar1 = param_2[3] - *param_3, iVar1 < 0)) {
      iVar1 = 0;
    }
    if ((int)param_2[4] < (int)param_2[2]) {
      iVar1 = iVar1 + (param_2[2] - param_2[4]);
    }
    for (iVar6 = 0; iVar1 != iVar6; iVar6 = iVar6 + 1) {
      iVar3 = (*param_5)(param_1,param_4,(int)param_2 + 0x1a,1);
      if (iVar3 == -1) goto LAB_ram_0000875e;
    }
    uVar2 = 0;
  }
  return uVar2;
}



// ==== FUN_ram_000087aa @ ram:000087aa size 680 callers [ram:00008402]

uint FUN_ram_000087aa(undefined4 param_1,uint *param_2,undefined4 param_3,code *param_4,int *param_5
                     )

{
  bool bVar1;
  byte bVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined4 *puVar12;
  char *pcVar13;
  uint uStack_24;
  
  bVar2 = (byte)param_2[6];
  pcVar7 = (char *)((int)param_2 + 0x43);
  pcVar13 = pcVar7;
  if (bVar2 == 0x69) {
LAB_ram_0000880a:
    uVar9 = *param_2;
    puVar3 = (uint *)*param_5;
    if ((uVar9 & 0x80) == 0) {
      uVar10 = *puVar3;
      *param_5 = (int)(puVar3 + 1);
      if ((uVar9 & 0x40) != 0) {
        uVar10 = (uint)(short)uVar10;
      }
    }
    else {
      uVar10 = *puVar3;
      *param_5 = (int)(puVar3 + 1);
    }
    if ((int)uVar10 < 0) {
      uVar10 = -uVar10;
      *(undefined1 *)((int)param_2 + 0x43) = 0x2d;
    }
    pcVar8 = "0123456789ABCDEF";
    uVar9 = 10;
LAB_ram_000088f0:
    uVar6 = param_2[1];
    param_2[2] = uVar6;
    if (-1 < (int)uVar6) {
      *param_2 = *param_2 & 0xfffffffb;
    }
    if ((uVar10 != 0) || (uVar6 != 0)) {
      do {
        uVar6 = uVar10;
        if (uVar9 != 0) {
          uVar6 = uVar10 % uVar9;
        }
        pcVar13 = pcVar13 + -1;
        *pcVar13 = pcVar8[uVar6];
        if (uVar9 == 0) {
          uVar6 = 0xffffffff;
        }
        else {
          uVar6 = uVar10 / uVar9;
        }
        bVar1 = uVar9 <= uVar10;
        uVar10 = uVar6;
      } while (bVar1);
    }
    if (((uVar9 == 8) && ((*param_2 & 1) != 0)) && ((int)param_2[1] <= (int)param_2[4])) {
      pcVar13[-1] = '0';
      pcVar13 = pcVar13 + -1;
    }
    param_2[4] = (int)pcVar7 - (int)pcVar13;
    goto LAB_ram_00008942;
  }
  if (bVar2 < 0x6a) {
    if (bVar2 == 0x58) {
      *(undefined1 *)((int)param_2 + 0x45) = 0x58;
      pcVar8 = "0123456789ABCDEF";
LAB_ram_00008976:
      uVar9 = *param_2;
      uVar10 = *(uint *)*param_5;
      puVar3 = (uint *)*param_5 + 1;
      if ((uVar9 & 0x80) == 0) {
        *param_5 = (int)puVar3;
        if ((uVar9 & 0x40) != 0) {
          uVar10 = uVar10 & 0xffff;
        }
      }
      else {
        *param_5 = (int)puVar3;
      }
      if ((uVar9 & 1) != 0) {
        *param_2 = uVar9 | 0x20;
      }
      uVar9 = 0x10;
      if (uVar10 == 0) {
        *param_2 = *param_2 & 0xffffffdf;
        uVar9 = 0x10;
      }
LAB_ram_000088ec:
      *(undefined1 *)((int)param_2 + 0x43) = 0;
      goto LAB_ram_000088f0;
    }
    if (bVar2 < 0x59) {
      if (bVar2 == 0) {
LAB_ram_00008a04:
        param_2[4] = 0;
        goto LAB_ram_00008942;
      }
      if (bVar2 == 0x43) goto LAB_ram_000088a8;
LAB_ram_000087f0:
      *(byte *)((int)param_2 + 0x42) = bVar2;
    }
    else {
      if (bVar2 != 99) {
        if (bVar2 == 100) goto LAB_ram_0000880a;
        goto LAB_ram_000087f0;
      }
LAB_ram_000088a8:
      uVar11 = *(undefined4 *)*param_5;
      *param_5 = (int)((undefined4 *)*param_5 + 1);
      *(char *)((int)param_2 + 0x42) = (char)uVar11;
    }
    pcVar13 = (char *)((int)param_2 + 0x42);
    uVar10 = 1;
  }
  else {
    if (bVar2 == 0x70) {
      *param_2 = *param_2 | 0x20;
LAB_ram_000089aa:
      *(undefined1 *)((int)param_2 + 0x45) = 0x78;
      pcVar8 = "0123456789abcdef";
      goto LAB_ram_00008976;
    }
    if (bVar2 < 0x71) {
      if (bVar2 == 0x6e) {
        uVar9 = *param_2;
        puVar12 = (undefined4 *)*param_5;
        uVar10 = param_2[5];
        if ((uVar9 & 0x80) == 0) {
          *param_5 = (int)(puVar12 + 1);
          puVar3 = (uint *)*puVar12;
          if ((uVar9 & 0x40) != 0) {
            *(short *)puVar3 = (short)uVar10;
            goto LAB_ram_00008a04;
          }
        }
        else {
          *param_5 = (int)(puVar12 + 1);
          puVar3 = (uint *)*puVar12;
        }
        *puVar3 = uVar10;
        goto LAB_ram_00008a04;
      }
      if (bVar2 != 0x6f) goto LAB_ram_000087f0;
LAB_ram_00008854:
      uVar10 = *param_2;
      puVar3 = (uint *)*param_5;
      if ((uVar10 & 0x80) == 0) {
        *param_5 = (int)(puVar3 + 1);
        if ((uVar10 & 0x40) == 0) goto LAB_ram_00008866;
        uVar10 = (uint)(ushort)*puVar3;
      }
      else {
        *param_5 = (int)(puVar3 + 1);
LAB_ram_00008866:
        uVar10 = *puVar3;
      }
      if (bVar2 == 0x6f) {
        pcVar8 = "0123456789ABCDEF";
        uVar9 = 8;
      }
      else {
        pcVar8 = "0123456789ABCDEF";
        uVar9 = 10;
      }
      goto LAB_ram_000088ec;
    }
    if (bVar2 == 0x75) goto LAB_ram_00008854;
    if (bVar2 == 0x78) goto LAB_ram_000089aa;
    if (bVar2 != 0x73) goto LAB_ram_000087f0;
    puVar12 = (undefined4 *)*param_5;
    uVar10 = param_2[1];
    *param_5 = (int)(puVar12 + 1);
    pcVar13 = (char *)*puVar12;
    iVar4 = FUN_ram_00008cbc(pcVar13,0,uVar10);
    if (iVar4 != 0) {
      param_2[1] = iVar4 - (int)pcVar13;
    }
    uVar10 = param_2[1];
  }
  param_2[4] = uVar10;
  *(undefined1 *)((int)param_2 + 0x43) = 0;
LAB_ram_00008942:
  iVar4 = FUN_ram_0000869e(param_1,param_2,&uStack_24,param_3,param_4);
  if ((iVar4 == -1) || (iVar4 = (*param_4)(param_1,param_3,pcVar13,param_2[4]), iVar4 == -1)) {
LAB_ram_00008954:
    uVar10 = 0xffffffff;
  }
  else {
    if ((*param_2 & 2) != 0) {
      for (iVar4 = 0; iVar4 < (int)(param_2[3] - uStack_24); iVar4 = iVar4 + 1) {
        iVar5 = (*param_4)(param_1,param_3,(int)param_2 + 0x19,1);
        if (iVar5 == -1) goto LAB_ram_00008954;
      }
    }
    uVar10 = param_2[3];
    if ((int)param_2[3] < (int)uStack_24) {
      uVar10 = uStack_24;
    }
  }
  return uVar10;
}



// ==== FUN_ram_00008a52 @ ram:00008a52 size 134 callers [ram:000079ac]

uint FUN_ram_00008a52(int param_1,byte param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x18) == 0)) {
    FUN_ram_00007f90();
  }
  if (param_3 == &DAT_ram_00009234) {
    param_3 = *(undefined4 **)(param_1 + 4);
  }
  else if (param_3 == &DAT_ram_00009254) {
    param_3 = *(undefined4 **)(param_1 + 8);
  }
  else if (param_3 == (undefined4 *)&DAT_ram_00009214) {
    param_3 = *(undefined4 **)(param_1 + 0xc);
  }
  iVar2 = param_3[2] + -1;
  param_3[2] = iVar2;
  if (iVar2 < 0) {
    if ((int)param_3[6] <= iVar2) {
      if (param_2 != 10) goto LAB_ram_00008ac0;
    }
    uVar1 = FUN_ram_00007ac2(param_1);
    return uVar1;
  }
LAB_ram_00008ac0:
  pbVar3 = (byte *)*param_3;
  *param_3 = pbVar3 + 1;
  *pbVar3 = param_2;
  return (uint)param_2;
}



// ==== FUN_ram_00008ad8 @ ram:00008ad8 size 48 callers [ram:000082ae]

void FUN_ram_00008ad8(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d5e(param_2);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}



// ==== FUN_ram_00008b08 @ ram:00008b08 size 48 callers []

void FUN_ram_00008b08(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_ram_00008cda(param_1,(int)*(short *)(param_2 + 0xe));
  if (iVar1 < 0) {
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 0xefff;
  }
  else {
    *(int *)(param_2 + 0x54) = *(int *)(param_2 + 0x54) + iVar1;
  }
  return;
}



// ==== FUN_ram_00008b86 @ ram:00008b86 size 54 callers []

void FUN_ram_00008b86(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_ram_00008c88(param_1,(int)*(short *)(param_2 + 0xe));
  if (iVar1 == -1) {
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 0xefff;
  }
  else {
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) | 0x1000;
    *(int *)(param_2 + 0x54) = iVar1;
  }
  return;
}



// ==== FUN_ram_00008bc2 @ ram:00008bc2 size 52 callers []

void FUN_ram_00008bc2(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  DAT_ram_20006dec = 0;
  iVar1 = _write_stub(param_2,param_3,param_4);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}



// ==== FUN_ram_00008bf6 @ ram:00008bf6 size 48 callers []

void FUN_ram_00008bf6(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d0e(param_2);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}



// ==== FUN_ram_00008c26 @ ram:00008c26 size 50 callers [ram:00008106]

void FUN_ram_00008c26(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d1e(param_2,param_3);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}



// ==== FUN_ram_00008c58 @ ram:00008c58 size 48 callers [ram:00008160]

void FUN_ram_00008c58(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d2e(param_2);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}



// ==== FUN_ram_00008c88 @ ram:00008c88 size 52 callers [ram:00008b86]

void FUN_ram_00008c88(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d3e(param_2,param_3,param_4);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}



// ==== FUN_ram_00008cbc @ ram:00008cbc size 26 callers [ram:00008402,ram:000087aa]

char * FUN_ram_00008cbc(char *param_1,char param_2,int param_3)

{
  char *pcVar1;
  
  pcVar1 = param_1 + param_3;
  while( true ) {
    if (param_1 == pcVar1) {
      return (char *)0x0;
    }
    if (*param_1 == param_2) break;
    param_1 = param_1 + 1;
  }
  return param_1;
}



// ==== FUN_ram_00008cd6 @ ram:00008cd6 size 2 callers [ram:000081fe,ram:000082ae]

void FUN_ram_00008cd6(void)

{
  return;
}



// ==== FUN_ram_00008cd8 @ ram:00008cd8 size 2 callers [ram:000081fe,ram:000082ae]

void FUN_ram_00008cd8(void)

{
  return;
}



// ==== FUN_ram_00008cda @ ram:00008cda size 52 callers [ram:00008b08]

void FUN_ram_00008cda(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  DAT_ram_20006dec = 0;
  iVar1 = FUN_ram_00008d4e(param_2,param_3,param_4);
  if ((iVar1 == -1) && (DAT_ram_20006dec != 0)) {
    *param_1 = DAT_ram_20006dec;
  }
  return;
}



// ==== FUN_ram_00008d0e @ ram:00008d0e size 16 callers [ram:00008bf6]

undefined4 FUN_ram_00008d0e(void)

{
  DAT_ram_20006dec = 0x58;
  return 0xffffffff;
}



// ==== FUN_ram_00008d1e @ ram:00008d1e size 16 callers [ram:00008c26]

undefined4 FUN_ram_00008d1e(void)

{
  DAT_ram_20006dec = 0x58;
  return 0xffffffff;
}



// ==== FUN_ram_00008d2e @ ram:00008d2e size 16 callers [ram:00008c58]

undefined4 FUN_ram_00008d2e(void)

{
  DAT_ram_20006dec = 0x58;
  return 0;
}



// ==== FUN_ram_00008d3e @ ram:00008d3e size 16 callers [ram:00008c88]

undefined4 FUN_ram_00008d3e(void)

{
  DAT_ram_20006dec = 0x58;
  return 0xffffffff;
}



// ==== FUN_ram_00008d4e @ ram:00008d4e size 16 callers [ram:00008cda]

undefined4 FUN_ram_00008d4e(void)

{
  DAT_ram_20006dec = 0x58;
  return 0xffffffff;
}



// ==== FUN_ram_00008d5e @ ram:00008d5e size 48 callers [ram:00008ad8]

undefined * FUN_ram_00008d5e(int param_1)

{
  undefined *puVar1;
  
  puVar1 = DAT_ram_20003010;
  if (DAT_ram_20003010 != (undefined *)0x0) {
    DAT_ram_20003010 = DAT_ram_20003010 + param_1;
    return puVar1;
  }
  DAT_ram_20003010 = &DAT_ram_20006df0 + param_1;
  return &DAT_ram_20006df0;
}



// ==== _write_stub @ ram:00008d8e size 16 callers [ram:00008bc2]

/* _write_stub: newlib _write stub: errno 88 (ENOSYS), returns -1 */

undefined4 _write_stub(void)

{
  DAT_ram_20006dec = 0x58;
  return 0xffffffff;
}



// ==== NMI_Handler @ ram:20002090 size 2 callers []

void NMI_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== SysTick_Handler @ ram:2000209a size 2 callers []

void SysTick_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== SW_Handler @ ram:2000209c size 2 callers []

void SW_Handler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== GPIOA_IRQHandler @ ram:200020a0 size 2 callers []

void GPIOA_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== GPIOB_IRQHandler @ ram:200020a2 size 2 callers []

void GPIOB_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== SPI0_IRQHandler @ ram:200020a4 size 2 callers []

void SPI0_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== BB_IRQHandler @ ram:200020a6 size 2 callers []

void BB_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== LLE_IRQHandler @ ram:200020a8 size 2 callers []

void LLE_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== USB2_IRQHandler @ ram:200020ac size 2 callers []

void USB2_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== ADC_IRQHandler @ ram:200020b8 size 2 callers []

void ADC_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== I2C_IRQHandler @ ram:200020ba size 2 callers []

void I2C_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== PWMX_IRQHandler @ ram:200020bc size 2 callers []

void PWMX_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== TMR3_IRQHandler @ ram:200020be size 2 callers []

void TMR3_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== UART2_IRQHandler @ ram:200020c0 size 2 callers []

void UART2_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== WDOG_BAT_IRQHandler @ ram:200020c4 size 2 callers []

void WDOG_BAT_IRQHandler(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== FUN_ram_200020c6 @ ram:200020c6 size 64 callers []

void FUN_ram_200020c6(void)

{
  uint uVar1;
  
  FLASH_EEPROM_CMD(4,0,0,0);
  FLASH_CONTROL._2_1_ = 4;
  uVar1 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar1 & 0xfffffffb;
  uVar1 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar1 & 0xfffffff7;
  wfi();
  return;
}



// ==== FUN_ram_20002106 @ ram:20002106 size 206 callers []

void FUN_ram_20002106(void)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  
  FLASH_EEPROM_CMD(4,0,0,0);
  FLASH_CONTROL._2_1_ = 4;
  bVar4 = OSC32K_CTRL._2_1_;
  bVar2 = OSC32M_CTRL._2_1_;
  uVar1 = RTC_CNT_32K._0_2_;
  if (0x3fff < uVar1) {
    bVar4 = bVar4 & 0xfc | 1;
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  BATTERY_CTRL._0_1_ = 0;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32K_CTRL._2_1_ = bVar4;
  OSC32M_CTRL._2_1_ = bVar2 | 3;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 | 0x20;
  SAFE_ACCESS._0_1_ = 0;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 | 4;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 & 0xfffffff7;
  wfi();
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 & 0xdf;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_200021d4 @ ram:200021d4 size 304 callers []

void FUN_ram_200021d4(ushort param_1)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  int local_20;
  undefined2 uStack_1c;
  int iStack_18;
  undefined2 uStack_14;
  
  local_20 = 0;
  uStack_1c = 0;
  FLASH_EEPROM_CMD(6,0x7f018,&local_20,0);
  bVar4 = OSC32K_CTRL._2_1_;
  bVar2 = OSC32M_CTRL._2_1_;
  uVar1 = RTC_CNT_32K._0_2_;
  if (0x3fff < uVar1) {
    bVar4 = bVar4 & 0xfc | 1;
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  BATTERY_CTRL._0_1_ = 0;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32K_CTRL._2_1_ = bVar4;
  OSC32M_CTRL._2_1_ = bVar2 | 3;
  SAFE_ACCESS._0_1_ = 0;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 | 4;
  uVar1 = POWER_MANAG._0_2_;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = SLEEP_CONTROL._3_1_;
  SLEEP_CONTROL._3_1_ = bVar4 | 0x40;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 | 0x20;
  POWER_MANAG._0_2_ = uVar1 & 0x600 | param_1 | 0x9004;
  do {
    uVar3 = DAT_ram_e000ed10;
    DAT_ram_e000ed10 = uVar3 & 0xfffffff7;
    wfi();
    FUN_ram_200025f4(0x46);
    iStack_18 = 0;
    uStack_14 = 0;
    FLASH_EEPROM_CMD(6,0x7f018,&iStack_18,0);
  } while (iStack_18 != local_20);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar4 & 0xdf;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_20002304 @ ram:20002304 size 250 callers []

void FUN_ram_20002304(ushort param_1)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  
  FLASH_EEPROM_CMD(4,0,0,0);
  bVar4 = OSC32K_CTRL._2_1_;
  bVar2 = OSC32M_CTRL._2_1_;
  uVar1 = RTC_CNT_32K._0_2_;
  if (0x3fff < uVar1) {
    bVar4 = bVar4 & 0xfc | 1;
  }
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  BATTERY_CTRL._0_1_ = 0;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32K_CTRL._2_1_ = bVar4;
  OSC32M_CTRL._2_1_ = bVar2 | 3;
  SAFE_ACCESS._0_1_ = 0;
  FUN_ram_200023fe(0x25);
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 | 4;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = SLEEP_CONTROL._3_1_;
  SLEEP_CONTROL._3_1_ = bVar4 | 0x40;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  POWER_MANAG._0_2_ = param_1 | 0x9000;
  uVar3 = DAT_ram_e000ed10;
  DAT_ram_e000ed10 = uVar3 & 0xfffffff7;
  wfi();
  FLASH_EEPROM_CMD(4,0,0,0);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar4 = GLOBAL_CONFIG._2_1_;
  GLOBAL_CONFIG._2_1_ = bVar4 | 1;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== FUN_ram_200023fe @ ram:200023fe size 372 callers [ram:00007794,ram:20002304]

void FUN_ram_200023fe(uint param_1)

{
  ushort uVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar2 & 0xdf;
  SAFE_ACCESS._0_1_ = 0;
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 0x40) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      uVar1 = CLOCK_CONFIG._0_2_;
      CLOCK_CONFIG._0_2_ = uVar1 | 0xc0;
      goto LAB_ram_200024a2;
    }
    bVar2 = CLOCK_CONFIG._2_1_;
    if ((bVar2 & 0x10) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      bVar2 = CLOCK_CONFIG._2_1_;
      CLOCK_CONFIG._2_1_ = bVar2 | 0x10;
      iVar4 = 2000;
      do {
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    CLOCK_CONFIG._0_2_ = (ushort)param_1 & 0x1f | 0x40;
    SAFE_ACCESS._0_1_ = 0;
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    if (param_1 == 0x46) {
      uVar3 = 2;
    }
    else {
      uVar3 = 0x52;
    }
  }
  else {
    bVar2 = CLOCK_CONFIG._2_1_;
    if ((bVar2 & 4) == 0) {
      SAFE_ACCESS._0_1_ = 0x57;
      SAFE_ACCESS._0_1_ = 0xa8;
      bVar2 = CLOCK_CONFIG._2_1_;
      CLOCK_CONFIG._2_1_ = bVar2 | 4;
      iVar4 = 0x4b0;
      do {
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    CLOCK_CONFIG._0_2_ = (ushort)param_1 & 0x1f;
    SAFE_ACCESS._0_1_ = 0;
    SAFE_ACCESS._0_1_ = 0x57;
    SAFE_ACCESS._0_1_ = 0xa8;
    uVar3 = 0x51;
  }
  FLASH_CONTROL._3_1_ = uVar3;
  SAFE_ACCESS._0_1_ = 0;
LAB_ram_200024a2:
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = MISC_CTRL._3_1_;
  MISC_CTRL._3_1_ = bVar2 | 0x80;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== sys_soft_reset @ ram:20002572 size 60 callers [ram:000074bc]

/* sys_soft_reset: flash command 4 then RB_SOFTWARE_RESET */

void sys_soft_reset(void)

{
  byte bVar1;
  
  FLASH_EEPROM_CMD(4,0,0,0);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar1 = GLOBAL_CONFIG._2_1_;
  GLOBAL_CONFIG._2_1_ = bVar1 | 1;
  SAFE_ACCESS._0_1_ = 0;
  return;
}



// ==== HardFault_Handler @ ram:200025ae size 70 callers []

void HardFault_Handler(void)

{
  byte bVar1;
  
  FLASH_EEPROM_CMD(4,0,0,0);
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  OSC32K_CTRL._0_2_ = 0xffff;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar1 = GLOBAL_CONFIG._2_1_;
  GLOBAL_CONFIG._2_1_ = bVar1 | 1;
  SAFE_ACCESS._0_1_ = 0;
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== FUN_ram_200025f4 @ ram:200025f4 size 14 callers [ram:200021d4,ram:20002602]

void FUN_ram_200025f4(int param_1)

{
  param_1 = param_1 * 0xf;
  do {
    param_1 = param_1 + -1;
  } while (param_1 != 0);
  return;
}



// ==== FUN_ram_20002602 @ ram:20002602 size 40 callers []

void FUN_ram_20002602(uint param_1)

{
  uint uVar1;
  
  for (uVar1 = 0; uVar1 != param_1; uVar1 = uVar1 + 1 & 0xffff) {
    FUN_ram_200025f4(1000);
  }
  return;
}



// ==== RTC_IRQHandler @ ram:2000262a size 26 callers []

void RTC_IRQHandler(void)

{
  RTC_CTRL._0_1_ = 0x30;
  DAT_ram_20002f78 = 1;
  return;
}



// ==== TMR0_IRQHandler @ ram:20002644 size 184 callers []

void TMR0_IRQHandler(void)

{
  byte bVar1;
  dword dVar2;
  dword *pdVar3;
  char cVar4;
  
  bVar1 = TMR0_STATUS._2_1_;
  if ((bVar1 & 1) != 0) {
    DAT_ram_20002fa0 = 1;
    TMR0_STATUS._2_1_ = 1;
    bVar1 = TMR0_CONTROL._2_1_;
    TMR0_CONTROL._2_1_ = bVar1 & 0xfe;
  }
  bVar1 = TMR0_STATUS._2_1_;
  if ((bVar1 & 2) != 0) {
    cVar4 = TMR0_STATUS._3_1_;
    while (cVar4 = cVar4 + -1, cVar4 != -1) {
      if ((0x67 < DAT_ram_20002fa4) || (DAT_ram_20002fa0 != 0)) {
        DAT_ram_20002fa4 = 0;
        DAT_ram_20002fa0 = 0;
      }
      dVar2 = TMR0_FIFO;
      pdVar3 = &DAT_ram_200043c0 + DAT_ram_20002fa4;
      DAT_ram_20002fa4 = DAT_ram_20002fa4 + 1;
      *pdVar3 = dVar2;
    }
    TMR0_STATUS._2_1_ = 2;
    bVar1 = TMR0_CONTROL._2_1_;
    TMR0_CONTROL._2_1_ = bVar1 | 1;
  }
  return;
}



// ==== TMR1_IRQHandler @ ram:200026fc size 30 callers []

void TMR1_IRQHandler(void)

{
  byte bVar1;
  
  bVar1 = TMR1_STATUS._2_1_;
  if ((bVar1 & 1) != 0) {
    TMR1_STATUS._2_1_ = 1;
    tmr1_1ms_tick();
  }
  return;
}



// ==== TMR2_IRQHandler @ ram:2000271a size 44 callers []

void TMR2_IRQHandler(void)

{
  byte bVar1;
  
  bVar1 = TMR2_STATUS._2_1_;
  if ((bVar1 & 1) != 0) {
    TMR2_STATUS._2_1_ = 1;
    uptime_ms = uptime_ms + 100;
  }
  return;
}



// ==== UART0_IRQHandler @ ram:20002746 size 44 callers []

void UART0_IRQHandler(void)

{
  byte bVar1;
  undefined1 auStack_10 [16];
  
  bVar1 = UART0_STAT._0_1_;
  if (((bVar1 & 0xf) != 4) && ((bVar1 & 0xf) != 0xc)) {
    return;
  }
  uart0_drain_rx(auStack_10);
  return;
}



// ==== UART3_IRQHandler @ ram:20002772 size 12 callers []

void UART3_IRQHandler(void)

{
  undefined1 uVar1;
  
  uVar1 = UART3_STAT._0_1_;
  return;
}



// ==== UART1_IRQHandler @ ram:2000277e size 128 callers []

void UART1_IRQHandler(void)

{
  byte bVar1;
  undefined1 auStack_20 [24];
  
  bVar1 = UART1_STAT._0_1_;
  if (((bVar1 & 0xf) != 4) && ((bVar1 & 0xf) != 0xc)) {
    return;
  }
  bVar1 = uart1_read_fifo(auStack_20);
  if ((uint)DAT_ram_20004770 + (uint)bVar1 < 0x100) {
    memcpy(&DAT_ram_20004670 + DAT_ram_20004770,auStack_20,(uint)bVar1);
    DAT_ram_20004770 = bVar1 + DAT_ram_20004770;
    uart1_rx_route();
    DAT_ram_20004770 = 0;
  }
  return;
}



// ==== USB_IRQHandler @ ram:200027fe size 12 callers []

void USB_IRQHandler(void)

{
  usb_irq_handler();
  return;
}



// ==== FUN_ram_2000280a @ ram:2000280a size 16 callers [ram:00007794]

void FUN_ram_2000280a(void)

{
  do {
    (*DAT_ram_20000000)();
  } while( true );
}



// ==== FUN_ram_2000281a @ ram:2000281a size 18 callers [ram:20002856,ram:2000289e,ram:200028d6]

void FUN_ram_2000281a(undefined1 param_1)

{
  int unaff_s0;
  
  *(undefined1 *)(unaff_s0 + -0x7fa) = 0;
  *(undefined1 *)(unaff_s0 + -0x7fa) = 5;
  *(undefined1 *)(unaff_s0 + -0x7fc) = param_1;
  return;
}



// ==== FUN_ram_2000282c @ ram:2000282c size 14 callers [ram:20002856,ram:2000289e,ram:200028d6]

void FUN_ram_2000282c(void)

{
  int unaff_s0;
  
  do {
  } while (*(char *)(unaff_s0 + -0x7fa) < '\0');
  *(undefined1 *)(unaff_s0 + -0x7fa) = 0;
  return;
}



// ==== FUN_ram_2000283a @ ram:2000283a size 14 callers [ram:2000289e,ram:200028d6]

undefined1 FUN_ram_2000283a(void)

{
  int unaff_s0;
  
  do {
  } while (*(char *)(unaff_s0 + -0x7fa) < '\0');
  return *(undefined1 *)(unaff_s0 + -0x7fc);
}



// ==== FUN_ram_20002848 @ ram:20002848 size 14 callers [ram:20002856,ram:200028d6]

void FUN_ram_20002848(undefined1 param_1)

{
  int unaff_s0;
  
  do {
  } while (*(char *)(unaff_s0 + -0x7fa) < '\0');
  *(undefined1 *)(unaff_s0 + -0x7fc) = param_1;
  return;
}



// ==== FUN_ram_20002856 @ ram:20002856 size 72 callers [ram:200028d6]

void FUN_ram_20002856(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = 5;
  if ((param_1 & 0xbf) != 0xb) {
    FUN_ram_2000281a(6);
    FUN_ram_2000282c();
    iVar1 = 3;
  }
  FUN_ram_2000281a(param_1);
  while (iVar1 = iVar1 + -1, iVar1 != -1) {
    FUN_ram_20002848(param_2 >> 0x10 & 0xff);
    param_2 = param_2 << 8;
  }
  return;
}



// ==== FUN_ram_2000289e @ ram:2000289e size 56 callers [ram:200028d6]

byte FUN_ram_2000289e(void)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = 0x80000;
  FUN_ram_2000282c();
  do {
    FUN_ram_2000281a(5);
    FUN_ram_2000283a();
    bVar2 = FUN_ram_2000283a();
    FUN_ram_2000282c();
    if ((bVar2 & 1) == 0) {
      return bVar2 | 1;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0;
}



// ==== FLASH_EEPROM_CMD @ ram:200028d6 size 874 callers [ram:0000315c,ram:00003178,ram:000032b6,ram:0000388a,ram:000054fa,ram:00005710,ram:00005af0,ram:000065a0,ram:00006cb0,ram:0000746c,ram:000074d2,ram:00007568,ram:00007618,ram:00007696,ram:200020c6,ram:20002106,ram:200021d4,ram:20002304,ram:20002572,ram:200025ae]

/* FLASH_EEPROM_CMD: WCH ISP ROM API in RAM: 1/2/3 code flash, 4 reset, 6 ROM info, 9/10/11
   DataFlash erase/write/read (offset + 0x70000) */

uint FLASH_EEPROM_CMD(int param_1,uint param_2,dword *param_3,uint param_4)

{
  char cVar1;
  byte bVar2;
  dword dVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  dword *pdVar8;
  uint uVar9;
  undefined4 uVar10;
  byte bVar11;
  dword dVar12;
  int iVar13;
  byte *pbVar14;
  uint uVar15;
  
  uVar4 = DAT_ram_e000e000;
  uVar5 = DAT_ram_e000e004;
  DAT_ram_e000e180 = 0xffffffff;
  DAT_ram_e000e184 = 0xffffffff;
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = GLOBAL_CONFIG._0_1_;
  uVar15 = param_1 - 9U & 0xff;
  bVar11 = 0xe0;
  if (((1 < uVar15) && (param_1 != 1)) && (bVar11 = 0x20, param_1 == 2)) {
    bVar11 = 0xe0;
  }
  GLOBAL_CONFIG._0_1_ = bVar2 | bVar11;
  FLASH_CONTROL._2_1_ = 4;
  FUN_ram_2000281a(0xff);
  uVar9 = FUN_ram_2000282c();
  if (uVar15 < 3) {
    param_2 = param_2 + 0x70000;
    uVar9 = 0xfffffffe;
    uVar6 = uVar9;
    if ((0x77fff < param_2) || (0x78000 < param_2 + param_4)) goto LAB_ram_200029be;
    param_2 = param_2 | 0x80000;
    if (param_1 != 10) {
      if (param_1 != 9) {
        uVar9 = FUN_ram_20002856(0xb,param_2);
        pdVar8 = (dword *)(param_4 + (int)param_3);
        for (; param_3 != pdVar8; param_3 = (dword *)((int)param_3 + 1)) {
          uVar9 = FUN_ram_2000283a();
          *(char *)param_3 = (char)uVar9;
        }
        goto LAB_ram_20002996;
      }
      uVar15 = 0x1000;
      uVar6 = 0xff;
LAB_ram_20002a0e:
      uVar7 = ~uVar6 & (param_2 & uVar6) + uVar6 + param_4;
      param_2 = ~uVar6 & param_2;
      do {
        if ((uVar15 - 1 & param_2) == 0) {
          for (; uVar15 <= uVar7; uVar7 = uVar7 - uVar15) {
            uVar10 = 0xd8;
            if ((uVar15 != 0x10000) && (uVar10 = 0x20, uVar15 != 0x1000)) {
              uVar10 = 0x81;
            }
            FUN_ram_20002856(uVar10,param_2);
            uVar9 = FUN_ram_2000289e();
            if (uVar9 == 0) goto LAB_ram_200029bc;
            param_2 = param_2 + uVar15;
          }
        }
        uVar15 = uVar15 >> 4;
      } while (0x10 < uVar15);
      goto LAB_ram_20002996;
    }
    do {
      if (param_4 == 0) goto LAB_ram_20002996;
      FUN_ram_20002856(2,param_2);
      pdVar8 = param_3;
      do {
        param_3 = (dword *)((int)pdVar8 + 1);
        param_4 = param_4 - 1;
        param_2 = param_2 + 1;
        FUN_ram_20002848((char)*pdVar8);
        if (param_4 == 0) break;
        pdVar8 = param_3;
      } while ((param_2 & 0xff) != 0);
      uVar9 = FUN_ram_2000289e();
    } while (uVar9 != 0);
LAB_ram_200029bc:
    uVar6 = 0xffffffff;
    goto LAB_ram_200029be;
  }
  if ((param_1 - 1U & 0xff) < 3) {
    cVar1 = SAFE_ACCESS._1_1_;
    if (((cVar1 == -0x7d) && (0x7ffff < param_2)) && (param_2 + param_4 < 0x100000)) {
      param_2 = param_2 ^ 0x80000;
    }
    else {
      bVar2 = GLOBAL_CONFIG._1_1_;
      uVar15 = 0x80000;
      if ((bVar2 & 0x20) == 0) {
        uVar15 = 0x78000;
      }
      uVar9 = 0xfffffffe;
      uVar6 = 0xfffffffe;
      if ((uVar15 <= param_2) || (uVar15 < param_2 + param_4)) goto LAB_ram_200029be;
    }
    if (param_1 == 2) {
      param_4 = param_4 >> 2;
      do {
        if (param_4 == 0) goto LAB_ram_20002996;
        FUN_ram_20002856(2,param_2);
        pdVar8 = param_3;
        do {
          param_3 = pdVar8 + 1;
          iVar13 = 4;
          FLASH_DATA = *pdVar8;
          do {
            do {
              cVar1 = FLASH_CONTROL._2_1_;
            } while (cVar1 < '\0');
            FLASH_CONTROL._2_1_ = 0x15;
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
          param_4 = param_4 - 1;
          param_2 = param_2 + 4;
        } while ((param_4 != 0) && (pdVar8 = param_3, (param_2 & 0xff) != 0));
        uVar9 = FUN_ram_2000289e();
      } while (uVar9 != 0);
      goto LAB_ram_200029bc;
    }
    if (param_1 == 1) {
      uVar15 = 0x10000;
      uVar6 = 0xfff;
      goto LAB_ram_20002a0e;
    }
    uVar9 = FUN_ram_20002856(0xb,param_2);
    do {
      do {
        uVar6 = param_4;
        param_4 = uVar6 - 1;
        if (uVar6 == 0) goto LAB_ram_20002996;
        uVar9 = FUN_ram_2000283a();
      } while ((param_4 & 3) != 0);
      dVar3 = FLASH_DATA;
      dVar12 = *param_3;
      param_3 = param_3 + 1;
    } while (dVar3 == dVar12);
  }
  else {
    if (param_1 == 0xd) {
      uVar9 = 0xb9;
LAB_ram_20002b58:
      uVar9 = FUN_ram_2000281a(uVar9);
    }
    else {
      uVar9 = 0xab;
      if (param_1 == 0xc) goto LAB_ram_20002b58;
      if (param_1 == 6) {
        FUN_ram_20002856(0xb,param_2 | 0x80000);
        iVar13 = 0;
        do {
          uVar9 = FUN_ram_2000283a();
          if (iVar13 == 3) {
            dVar3 = FLASH_DATA;
            *param_3 = dVar3;
          }
          iVar13 = iVar13 + 1;
        } while (iVar13 != 8);
        dVar3 = FLASH_DATA;
        if ((int)(param_2 << 0x12) < 0) {
          *(short *)(param_3 + 1) = (short)dVar3;
        }
        else {
          param_3[1] = dVar3;
        }
      }
      else if (param_1 == 7) {
        FUN_ram_20002856(0x4b,0);
        uVar15 = 0xf;
        *param_3 = 0;
        param_3[1] = 0;
        do {
          uVar9 = FUN_ram_2000283a();
          pbVar14 = (byte *)((uVar15 & 7) + (int)param_3);
          uVar15 = uVar15 - 1;
          uVar9 = uVar9 ^ *pbVar14;
          *pbVar14 = (byte)uVar9;
        } while (uVar15 != 0xffffffff);
      }
      else if (param_1 == 8) {
        uVar9 = FUN_ram_2000289e(0xab);
        uVar15 = 0;
        if (((param_2 != 0) && (uVar15 = 0x3c, param_2 != 3)) && (uVar15 = 0x50, param_2 != 2)) {
          uVar15 = 0x44;
        }
        uVar9 = uVar9 & 0x7c;
        if (uVar9 != uVar15) {
          FUN_ram_2000281a(6);
          FUN_ram_2000282c();
          FUN_ram_2000281a(1);
          FUN_ram_20002848(uVar15);
          FUN_ram_20002848(2);
          uVar9 = FUN_ram_2000289e();
          if (uVar9 == 0) goto LAB_ram_200029bc;
        }
      }
      else {
        if (param_1 == 4) {
          FUN_ram_2000281a(0x66);
          FUN_ram_2000282c();
          uVar9 = 0x99;
          goto LAB_ram_20002b58;
        }
        if (param_1 != 0) {
          uVar6 = 0xfffffffc;
          goto LAB_ram_20002998;
        }
      }
    }
LAB_ram_20002996:
    uVar6 = 0;
  }
LAB_ram_20002998:
  FUN_ram_2000282c(uVar9);
LAB_ram_200029be:
  SAFE_ACCESS._0_1_ = 0x57;
  SAFE_ACCESS._0_1_ = 0xa8;
  bVar2 = GLOBAL_CONFIG._0_1_;
  GLOBAL_CONFIG._0_1_ = bVar2 & 0x10;
  DAT_ram_e000e100 = uVar4;
  DAT_ram_e000e104 = uVar5;
  return uVar6;
}


