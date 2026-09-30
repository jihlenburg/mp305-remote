/* Address: ram:000693cc; name: FUN_ram_000693cc; body bytes: 242 */

undefined4 FUN_ram_000693cc(char param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  ushort *puVar3;
  undefined1 auStack_38 [16];
  ushort local_28;
  undefined1 auStack_26 [22];
  
  gp = 0x20004000;
  iVar1 = tmos_snv_read(param_1 * '\x06' + ' ',0x10,auStack_38);
  if ((iVar1 == 0) && (iVar1 = tmos_isbufset(auStack_38,0xff,6), iVar1 == 0)) {
    iVar1 = tmos_snv_read(param_1 + 'p',0x18,&local_28);
    if (iVar1 == 0) {
      FUN_ram_00068a38(&local_28);
      if (param_2 != 0) {
        puVar3 = &local_28;
        do {
          if (*puVar3 == param_2) goto LAB_ram_000694aa;
          puVar3 = puVar3 + 2;
        } while (puVar3 != (ushort *)&stack0xfffffff0);
        puVar3 = &local_28;
        if (param_3 == 0) {
          gp = 0x20004000;
          return 0;
        }
LAB_ram_00069496:
        if (*puVar3 != 0) goto code_r0x0006949e;
        *puVar3 = (ushort)param_2;
LAB_ram_000694aa:
        if ((byte)puVar3[1] != param_3) {
          *(char *)(puVar3 + 1) = (char)param_3;
          if (param_3 == 0) {
            *puVar3 = 0;
          }
          goto LAB_ram_00069454;
        }
        goto LAB_ram_00069428;
      }
      iVar1 = tmos_isbufset(&local_28,0,0x18);
      if (iVar1 == 0) {
        tmos_memset(&local_28,0,0x18);
LAB_ram_00069454:
        DAT_ram_20001aa0 = 1;
        FUN_ram_00068a38(&local_28);
        FUN_ram_00042e5e(param_1 + 'p',0x18,&local_28);
        FUN_ram_00042e10(DAT_ram_200019c4);
      }
    }
LAB_ram_00069428:
    uVar2 = 1;
  }
  else {
LAB_ram_000693f4:
    uVar2 = 0;
  }
  return uVar2;
code_r0x0006949e:
  puVar3 = puVar3 + 2;
  if ((ushort *)&stack0xfffffff0 == puVar3) goto LAB_ram_000693f4;
  goto LAB_ram_00069496;
}

