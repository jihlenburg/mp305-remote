/* Address: ram:0004bb50; name: FUN_ram_0004bb50; body bytes: 270 */

undefined4 FUN_ram_0004bb50(ushort *param_1)

{
  ushort uVar1;
  bool bVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  
  gp = 0x20004000;
  if (*param_1 != 0) {
    puVar3 = *(undefined1 **)(param_1 + 2);
    iVar4 = ATT_CompareUUID(&DAT_ram_0006c65c,2,*(undefined4 *)(puVar3 + 4),*puVar3);
    if ((iVar4 == 0) &&
       (iVar4 = ATT_CompareUUID(&DAT_ram_0006c660,2,*(undefined4 *)(puVar3 + 4),*puVar3), iVar4 == 0
       )) {
      uVar9 = 2;
    }
    else if ((byte)((char)param_1[1] - 7U) < 10) {
      uVar9 = 1;
      if ((DAT_ram_200019c0 != 0) && (uVar9 = 1, (uint)*param_1 + (uint)DAT_ram_200019c0 < 0x10001))
      {
        puVar5 = (undefined4 *)FUN_ram_20000040(0xc,0x4702);
        uVar9 = 0x13;
        if (puVar5 != (undefined4 *)0x0) {
          tmos_memset(puVar5,0,0xc);
          uVar1 = *param_1;
          uVar6 = (uint)DAT_ram_200019c0;
          bVar2 = false;
          for (uVar7 = 0; uVar7 < uVar1; uVar7 = uVar7 + 1) {
            *(short *)(*(int *)(param_1 + 2) + uVar7 * 0x10 + 10) =
                 (short)((uVar6 + uVar7) * 0x10000 >> 0x10);
            bVar2 = true;
          }
          if (bVar2) {
            DAT_ram_200019c0 = (ushort)((uVar1 + uVar6) * 0x10000 >> 0x10);
          }
          *puVar5 = 0;
          tmos_memcpy(puVar5 + 1,param_1,8);
          puVar10 = DAT_ram_20001a48;
          if (DAT_ram_20001a48 == (undefined4 *)0x0) {
            uVar9 = 0;
            DAT_ram_20001a48 = puVar5;
          }
          else {
            do {
              puVar8 = puVar10;
              puVar10 = (undefined4 *)*puVar8;
            } while (puVar10 != (undefined4 *)0x0);
            *puVar8 = puVar5;
            uVar9 = 0;
          }
        }
      }
    }
    else {
      uVar9 = 0x18;
    }
    return uVar9;
  }
  return 2;
}

