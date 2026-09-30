/* Address: ram:0004f118; name: FUN_ram_0004f118; body bytes: 194 */

undefined1 FUN_ram_0004f118(undefined4 param_1,undefined4 param_2,uint param_3)

{
  ushort *puVar1;
  undefined1 uVar2;
  int iVar3;
  undefined1 uVar4;
  undefined1 auStack_30 [24];
  
  gp = 0x20004000;
  iVar3 = FUN_ram_0004df14(param_3);
  if (iVar3 == 0) {
    gp = 0x20004000;
    return 0x12;
  }
  puVar1 = *(ushort **)(iVar3 + 0x34);
  if (puVar1 == (ushort *)0x0) {
    gp = 0x20004000;
    return 0x12;
  }
  if (*puVar1 != param_3) {
    gp = 0x20004000;
    return 0x12;
  }
  if ((*(byte *)((int)puVar1 + 5) & 8) != 0) {
    if (DAT_ram_20001f04 == 0) {
      gp = 0x20004000;
      return 0xfe;
    }
    if (*(int *)(DAT_ram_20001f04 + 8) == 0) {
      gp = 0x20004000;
      return 0xfe;
    }
    tmos_memcpy(puVar1 + 0xc,param_1,0x10);
    uVar2 = (**(code **)(DAT_ram_20001f04 + 8))
                      (*(int *)(puVar1 + 0x40) + 0x40,*(int *)(puVar1 + 0x40) + 0x40,puVar1 + 0xc,0,
                       auStack_30,*(code **)(DAT_ram_20001f04 + 8));
    iVar3 = tmos_memcmp(auStack_30,param_2,0x10);
    if (iVar3 != 0) goto LAB_ram_0004f1a2;
  }
  uVar2 = 2;
LAB_ram_0004f1a2:
  if (*(char *)((int)puVar1 + 3) == '[') {
    FUN_ram_000502a6(puVar1);
    if ((char)puVar1[1] == '\0') {
      uVar4 = 0x5e;
    }
    else {
      uVar4 = 0x5c;
    }
    *(undefined1 *)((int)puVar1 + 3) = uVar4;
  }
  return uVar2;
}

