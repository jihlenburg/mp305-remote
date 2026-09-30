/* Address: 0004b484; name: FUN_0004b484; body bytes: 452 */

void FUN_0004b484(undefined4 param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  char *pcVar8;
  uint uVar9;
  undefined1 auStack_a0 [32];
  undefined1 local_80;
  undefined1 local_65;
  byte local_57;
  undefined1 local_48;
  undefined1 local_34;
  undefined1 auStack_30 [16];
  
  iVar3 = FUN_00046688();
  iVar4 = FUN_00046698(param_1);
  if (iVar3 != 0x17) {
    if (iVar3 == 0x1a) {
      uVar5 = FUN_00046718(param_1);
      FUN_00042ec4(auStack_a0);
      FUN_0004d0bc(iVar4,0,auStack_a0);
      iVar3 = FUN_0004c638(iVar4,0);
      if (iVar3 != 0) {
        local_57 = local_57 | 0x20;
      }
      uVar6 = FUN_0004cbd2(iVar4,0);
      uVar7 = FUN_0004cba0(iVar4,0);
      FUN_0003d992(auStack_30,iVar4 + 0x14);
      FUN_0003db32(auStack_30,uVar6,uVar7);
    }
    else {
      if (iVar3 != 0x1d) {
        return;
      }
      uVar5 = FUN_00046718(param_1);
      FUN_000318e0(iVar4,uVar5);
      iVar3 = FUN_0004c638(iVar4,0);
      if (iVar3 == 0) {
        return;
      }
      FUN_00042ec4(auStack_a0);
      local_48 = 0;
      local_80 = 0;
      local_65 = 0;
      local_34 = 0;
      FUN_0004d0bc(iVar4,0,auStack_a0);
      uVar6 = FUN_0004cbd2(iVar4,0);
      uVar7 = FUN_0004cba0(iVar4,0);
      FUN_0003d992(auStack_30,iVar4 + 0x14);
      FUN_0003db32(auStack_30,uVar6,uVar7);
    }
    FUN_00042a98(uVar5,auStack_a0,auStack_30);
    return;
  }
  pcVar8 = (char *)FUN_0004673a(param_1);
  if (*pcVar8 == '\x02') {
    return;
  }
  iVar3 = FUN_0004c924(iVar4,0,0x2d);
  if (iVar3 != 0) {
    *pcVar8 = '\x02';
    return;
  }
  uVar5 = FUN_0004c94e(iVar4,0);
  uVar6 = FUN_0004cbd2(iVar4,0);
  uVar7 = FUN_0004cba0(iVar4,0);
  FUN_0003d992(auStack_a0,iVar4 + 0x14);
  FUN_0003db32(auStack_a0,uVar6,uVar7);
  iVar3 = FUN_0003db8c(*(undefined4 *)(pcVar8 + 4),auStack_a0,uVar5);
  if ((((iVar3 != 0) && (uVar9 = FUN_0004c620(iVar4,0), 0xfc < uVar9)) &&
      (bVar1 = FUN_0004c924(iVar4,0,0x5f), 0xfc < bVar1)) &&
     ((cVar2 = FUN_0004c924(iVar4,0,0x20), cVar2 == '\0' ||
      (bVar1 = FUN_0004c924(iVar4,0,0x25), 0xfc < bVar1)))) {
    iVar3 = FUN_0004c924(iVar4,0,0x26);
    if (iVar3 != 0) {
      for (uVar9 = 0; uVar9 < *(byte *)(iVar3 + 10); uVar9 = uVar9 + 1) {
        if (*(byte *)(uVar9 * 5 + iVar3 + 3) < 0xfd) goto LAB_0004b5dc;
      }
    }
    *pcVar8 = '\0';
    return;
  }
LAB_0004b5dc:
  *pcVar8 = '\x01';
  return;
}

