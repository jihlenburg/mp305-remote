/* Address: ram:0005841a; name: FUN_ram_0005841a; body bytes: 338 */

undefined4 FUN_ram_0005841a(void)

{
  char *pcVar1;
  ushort uVar2;
  int iVar3;
  undefined1 uVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  int iVar7;
  uint uVar8;
  
  iVar3 = DAT_ram_20001de8;
  gp = 0x20004000;
  pcVar1 = (char *)(DAT_ram_20001de8 + 0x65);
  *(undefined1 *)(DAT_ram_20001de8 + 100) = 0;
  if (*pcVar1 == '\0') {
LAB_ram_0005843a:
    *(undefined1 *)(iVar3 + 100) = 1;
    puVar6 = &DAT_ram_20001e38;
  }
  else {
    if (*pcVar1 != '\x01') {
      iVar7 = *(int *)(iVar3 + 0x84);
      if (iVar7 == 0) {
        if (*(char *)(iVar3 + 0x6c) != '\0') {
          iVar7 = FUN_ram_20000c00(iVar3 + 0x6c);
          *(int *)(iVar3 + 0x84) = iVar7;
          if ((iVar7 != 0) && (*(char *)(iVar7 + 10) != '\0')) {
            *(undefined1 *)(iVar3 + 100) = 2;
            goto LAB_ram_000584c8;
          }
LAB_ram_000584d4:
          if (*(char *)(iVar3 + 100) == '\x02') goto LAB_ram_000584de;
        }
      }
      else if (*(char *)(iVar7 + 10) != '\0') {
        *(undefined1 *)(iVar3 + 100) = 2;
LAB_ram_000584c8:
        tmos_memcpy(iVar3 + 0x66,iVar7 + 0xc,6);
        goto LAB_ram_000584d4;
      }
      if (*(char *)(iVar3 + 0x65) == '\x02') goto LAB_ram_0005843a;
    }
    if (DAT_ram_20001d62 == '\0') {
      gp = 0x20004000;
      return 0x12;
    }
    *(undefined1 *)(iVar3 + 100) = 1;
    puVar6 = &DAT_ram_20001e3e;
  }
  tmos_memcpy(iVar3 + 0x66,puVar6,6);
LAB_ram_000584de:
  uVar5 = FUN_ram_00042934(0,0xffffff);
  *(undefined4 *)(iVar3 + 0x5c) = uVar5;
  uVar5 = BLE_AccessAddressGenerate();
  *(undefined4 *)(iVar3 + 0x58) = uVar5;
  uVar4 = FUN_ram_000428ec(5,0x10);
  *(undefined1 *)(iVar3 + 7) = 1;
  *(undefined1 *)(iVar3 + 4) = 3;
  *(undefined1 *)(iVar3 + 0xc) = uVar4;
  if (*(char *)(iVar3 + 0x38) == '\x03') {
    uVar8 = (uint)*(ushort *)(iVar3 + 0x34) + (uint)*(ushort *)(iVar3 + 0x46);
  }
  else {
    if (*(char *)(iVar3 + 0x38) == '\x02') {
      uVar2 = *(ushort *)(iVar3 + 0x46);
    }
    else {
      uVar2 = *(ushort *)(iVar3 + 0x34);
    }
    uVar8 = (uint)uVar2;
  }
  tmos_start_reload_task(DAT_ram_20001b67,0x10,uVar8);
  tmos_set_event(DAT_ram_20001b67,0x10);
  DAT_ram_20001d60 = 0;
  return 0;
}

