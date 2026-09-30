/* Address: ram:000538d8; name: FUN_ram_000538d8; body bytes: 662 */

/* WARNING: Removing unreachable block (ram,0x00053a10) */

undefined4 FUN_ram_000538d8(int param_1)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  byte *pbVar4;
  byte bVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  gp = 0x20004000;
  pbVar4 = *(byte **)(param_1 + 0x50);
  bVar5 = pbVar4[1];
  *(byte *)(param_1 + 0x12) = bVar5 & 0x3f;
  if (((bVar5 & 0x3f) == 0xc) &&
     (bVar5 = *pbVar4, *(byte *)(param_1 + 0x13) = bVar5 & 0xf, (bVar5 & 0xf) == 3)) {
    iVar3 = tmos_memcmp(param_1 + 0x36,pbVar4 + 8,6);
    uVar6 = 4;
    if (iVar3 != 0) {
      *(byte *)(param_1 + 0x45) = (byte)((int)(uint)**(byte **)(param_1 + 0x50) >> 6) & 1;
      tmos_memcpy(param_1 + 0x46,*(byte **)(param_1 + 0x50) + 2,6);
      iVar3 = FUN_ram_000536fe(param_1);
      uVar6 = 8;
      if (iVar3 != 0) {
        puVar2 = *(undefined1 **)(param_1 + 0x4c);
        *(undefined1 *)(param_1 + 0x10) = 7;
        *puVar2 = 7;
        puVar2[2] = 1;
        puVar2[3] = 1;
        tmos_memcpy(puVar2 + 4,param_1 + 0x36,6);
        cVar1 = puVar2[2];
        uVar8 = 0;
        puVar2[2] = cVar1 + 6U;
        puVar2[3] = puVar2[3] | 8;
        *(char *)((uint)(byte)(cVar1 + 6U) + *(int *)(param_1 + 0x4c) + 3) =
             (char)*(undefined2 *)(param_1 + 0x6a);
        *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar2[2] + 4) =
             (byte)((ushort)*(undefined2 *)(param_1 + 0x6a) >> 8) & 0xf |
             *(char *)(param_1 + 0x61) << 4;
        bVar5 = puVar2[2] + 2;
        puVar2[2] = bVar5;
        iVar3 = DAT_ram_20001eb0;
        if (*(ushort *)(param_1 + 0x1e) != 0) {
          iVar9 = -2;
          if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
            iVar9 = -3;
          }
          uVar8 = iVar9 - (uint)bVar5 & 0xff;
          if (uVar8 < *(ushort *)(param_1 + 0x1e)) {
            uVar8 = uVar8 - 3 & 0xff;
            if (*(char *)(param_1 + 99) == '\x02') {
              iVar9 = 0x4290;
            }
            else {
              iVar9 = 0x428;
              if (*(char *)(param_1 + 99) != '\x01') {
                iVar9 = 0x848;
              }
            }
            uVar7 = (iVar9 + 0x1b7U) / 0x1e;
            DAT_ram_20001dd4 = DAT_ram_20001dd4 | 0x10;
            *(undefined4 *)(DAT_ram_20001eb0 + 8) = 0x1000;
            *(uint *)(iVar3 + 0x60) = uVar7 * 0x3c;
            puVar2[3] = puVar2[3] | 0x10;
            *(undefined1 *)((uint)bVar5 + *(int *)(param_1 + 0x4c) + 3) =
                 *(undefined1 *)(param_1 + 0x62);
            *(char *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar2[2] + 4) = (char)uVar7;
            *(byte *)(*(int *)(param_1 + 0x4c) + (uint)(byte)puVar2[2] + 5) =
                 (byte)(uVar7 >> 8) | *(char *)(param_1 + 99) << 5;
            puVar2[2] = puVar2[2] + '\x03';
            *(uint *)(param_1 + 0x78) = *(int *)(param_1 + 0x2c) + uVar8;
            *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x1e) - (short)uVar8;
          }
        }
        if ((*(byte *)(param_1 + 0x60) & 0x40) != 0) {
          iVar3 = *(int *)(param_1 + 0x4c);
          puVar2[3] = puVar2[3] | 0x40;
          *(undefined1 *)(iVar3 + (uint)(byte)puVar2[2] + 3) = *(undefined1 *)(param_1 + 0x15);
          puVar2[2] = puVar2[2] + '\x01';
        }
        if ((*(ushort *)(param_1 + 0x1e) == 0) || (uVar8 < *(ushort *)(param_1 + 0x1e))) {
          tmos_memcpy(*(int *)(param_1 + 0x4c) + (byte)puVar2[2] + 3,*(undefined4 *)(param_1 + 0x2c)
                      ,uVar8);
        }
        else {
          tmos_memcpy();
          uVar8 = (uint)*(byte *)(param_1 + 0x1e);
        }
        bVar5 = puVar2[2];
        *(byte *)(param_1 + 0x11) = (char)uVar8 + (bVar5 & 0x3f) + 1;
        puVar2[2] = bVar5;
        if (((*(byte *)(param_1 + 0x35) & 1) != 0) || (*(char *)(param_1 + 0x34) == '\x02')) {
          **(byte **)(param_1 + 0x4c) = **(byte **)(param_1 + 0x4c) | 0x40;
        }
        *(undefined1 *)(*(int *)(param_1 + 0x4c) + 1) = *(undefined1 *)(param_1 + 0x11);
        *(undefined1 *)(param_1 + 0xb) = 0x99;
        FUN_ram_00061f0a(*(undefined1 *)(param_1 + 99));
        FUN_ram_200011be(3,*(undefined1 *)(param_1 + 99),*(undefined1 *)(param_1 + 0x11));
        FUN_ram_00062262();
        uVar6 = 0;
      }
    }
    return uVar6;
  }
  return 0x80;
}

