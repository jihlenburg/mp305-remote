/* Address: ram:00001fbe; name: FUN_ram_00001fbe; body bytes: 1242 */

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
/* WARNING: Removing unreachable block (ram,0x00002460) */
/* WARNING: Removing unreachable block (ram,0x000021e0) */
/* WARNING: Removing unreachable block (ram,0x000021fa) */
/* WARNING: Removing unreachable block (ram,0x0000247a) */

void FUN_ram_00001fbe(uint param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  
  gp = &DAT_ram_20002000;
  iVar2 = FUN_ram_000026e8();
  DAT_ram_4000102f = DAT_ram_4000102f & 0xf7;
  DAT_ram_4000102e = DAT_ram_4000102e & 0xfc | 1;
  iVar7 = iVar2 / 1000;
  DAT_ram_40001053 = DAT_ram_40001053 & 0xf8 | 1;
  bVar5 = 0;
  iVar6 = (iVar7 * 0x4a) / 60000;
  do {
    do {
      bVar1 = DAT_ram_40001053;
    } while ((DAT_ram_40001053 & 8) == 0);
    DAT_ram_40001050 = DAT_ram_40001050 | 0xc000;
    DAT_ram_40001053 = DAT_ram_40001053 & 0xdf | 0x20;
    DAT_ram_40001040 = 0xa8;
    do {
    } while ((bVar1 & 8) != 0);
    iVar3 = FUN_ram_00001fa6();
    do {
      iVar4 = FUN_ram_00001fa6();
    } while (iVar4 == iVar3);
    do {
    } while ((DAT_ram_40001053 & 8) == 0);
    iVar3 = (((DAT_ram_40001050 | 0x4000) & 0x3fff) + (uint)DAT_ram_40001052 * 0x3fff) -
            (iVar7 * 2000) / 0x8000;
    if ((((iVar2 / -1000) * 0x25) / 0x8000 < iVar3) && (iVar3 < (iVar7 * 0x25) / 0x8000)) {
      if (bVar5 != 0) {
LAB_ram_00002218:
        DAT_ram_40001053 = DAT_ram_40001053 & 0xf8;
        do {
          DAT_ram_40001053 = DAT_ram_40001053 | (byte)param_1;
          bVar5 = DAT_ram_40001053;
        } while ((DAT_ram_40001053 & 7) != param_1);
        do {
        } while ((DAT_ram_40001053 & 8) == 0);
        DAT_ram_40001050 = DAT_ram_40001050 | 0xc000;
        DAT_ram_40001053 = DAT_ram_40001053 & 0xdf | 0x20;
        DAT_ram_40001040 = 0xa8;
        do {
        } while ((bVar5 & 8) != 0);
        iVar6 = FUN_ram_00001fa6();
        do {
          iVar3 = FUN_ram_00001fa6();
        } while (iVar3 == iVar6);
        DAT_ram_40001050 = DAT_ram_40001050 | 0x4000;
        do {
        } while ((DAT_ram_40001053 & 8) == 0);
        DAT_ram_40001053 = DAT_ram_40001053 & 0xdf;
        iVar2 = ((DAT_ram_40001050 & 0x3fff) + (uint)DAT_ram_40001052 * 0x3fff) -
                ((((4000 << (param_1 & 0x1f)) * (iVar2 / 1000000)) / 0x100) * 1000) / 0x80;
        iVar6 = (((1 << (param_1 & 0x1f)) >> 3) * iVar7 * 0x556) / 60000;
        if (iVar6 == 0) {
          iVar6 = -1;
        }
        else {
          iVar6 = (iVar2 * 200) / iVar6;
        }
        if (iVar2 < 1) {
          iVar6 = iVar6 + -1;
        }
        else {
          iVar6 = iVar6 + 1;
        }
        DAT_ram_40001040 = 0xa8;
        DAT_ram_4000102c = (short)(((iVar6 / 2) * 0x20 + (uint)DAT_ram_4000102c) * 0x10000 >> 0x10);
        return;
      }
    }
    else if (2 < bVar5) goto LAB_ram_00002218;
    bVar5 = bVar5 + 1;
    if (iVar6 == 0) {
      iVar4 = -1;
    }
    else {
      iVar4 = (iVar3 * 2) / iVar6;
    }
    if (iVar3 < 1) {
      iVar4 = iVar4 + -1;
    }
    else {
      iVar4 = iVar4 + 1;
    }
    DAT_ram_4000102c = (ushort)((iVar4 / 2 + (uint)DAT_ram_4000102c) * 0x10000 >> 0x10);
    DAT_ram_40001050 = DAT_ram_40001050 | 0x4000;
  } while( true );
}

