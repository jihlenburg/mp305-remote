/* Address: 0002bfc4; name: FUN_0002bfc4; body bytes: 622 */

void FUN_0002bfc4(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint local_a0;
  uint local_9c;
  undefined4 *puStack_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined1 auStack_5c [12];
  undefined2 local_50;
  int local_48;
  int local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  int iStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  iVar2 = FUN_00046688();
  iVar3 = FUN_00046698(param_1);
  if (iVar2 == 0x17) {
    pcVar5 = (char *)FUN_0004673a(param_1);
    if (*pcVar5 != '\x02') {
      uVar4 = *(uint *)(iVar3 + 0x58);
      if ((((~uVar4 & 3) != 0) && ((uVar4 & 3) != 2)) &&
         ((iVar2 = FUN_0004035a((uVar4 & 0x7f) >> 2), iVar2 == 0 &&
          ((cVar1 = FUN_0004c924(iVar3,0,0x44), cVar1 == -1 && (*(int *)(iVar3 + 0x44) == 0)))))) {
        if ((*(int *)(iVar3 + 0x48) == 0x100) && (*(int *)(iVar3 + 0x4c) == 0x100)) {
          piVar8 = (int *)(iVar3 + 0x14);
          uVar6 = *(undefined4 *)(pcVar5 + 4);
        }
        else {
          FUN_00047af8(iVar3,&local_84);
          uVar6 = FUN_0004bbec(iVar3);
          uVar9 = FUN_0004ccf8(iVar3);
          local_a0 = (uint)*(ushort *)(iVar3 + 0x48);
          puStack_98 = &local_84;
          local_9c = (uint)*(ushort *)(iVar3 + 0x4c);
          FUN_0004747e(&local_94,uVar9,uVar6,0);
          local_94 = *(int *)(iVar3 + 0x14) + local_94;
          local_90 = *(int *)(iVar3 + 0x18) + local_90;
          local_8c = *(int *)(iVar3 + 0x14) + local_8c;
          local_88 = *(int *)(iVar3 + 0x18) + local_88;
          piVar8 = &local_94;
          uVar6 = *(undefined4 *)(pcVar5 + 4);
        }
        iVar2 = FUN_0003db8c(uVar6,piVar8,0);
        if ((iVar2 != 0) && (*(int *)(iVar3 + 0x30) == 0)) {
          return;
        }
      }
      *pcVar5 = '\x01';
    }
  }
  else if ((((iVar2 == 0x1a) && (*(int *)(iVar3 + 0x40) != 0)) && (*(int *)(iVar3 + 0x3c) != 0)) &&
          ((*(int *)(iVar3 + 0x48) != 0 && (*(int *)(iVar3 + 0x4c) != 0)))) {
    iVar2 = FUN_00046718(param_1);
    uVar4 = *(uint *)(iVar3 + 0x58) & 3;
    if ((uVar4 == 1) || ((*(uint *)(iVar3 + 0x58) & 3) == 0)) {
      FUN_00041b74(&local_9c);
      FUN_0004ce8c(iVar3,0,&local_9c);
      uVar11 = *(undefined4 *)(iVar2 + 0x20);
      uVar6 = *(undefined4 *)(iVar2 + 0x24);
      uVar9 = *(undefined4 *)(iVar2 + 0x18);
      uVar10 = *(undefined4 *)(iVar2 + 0x1c);
      FUN_00047af8(iVar3,auStack_5c);
      local_6c = *(undefined4 *)(iVar3 + 0x48);
      local_68 = *(undefined4 *)(iVar3 + 0x4c);
      local_70 = *(undefined4 *)(iVar3 + 0x44);
      local_50 = local_50 & 0xefff;
      local_50 = CONCAT11((byte)(local_50 >> 8) & 0xf0 |
                          (byte)((ushort)((ushort)(*(byte *)(iVar3 + 0x58) >> 7) << 0xc) >> 8) |
                          (byte)((ushort)*(undefined2 *)(iVar3 + 0x58) >> 0xc),(undefined1)local_50)
      ;
      local_34 = *(undefined4 *)(iVar3 + 0x30);
      local_80 = *(undefined4 *)(iVar3 + 0x2c);
      local_a0 = (*(int *)(iVar3 + 0x40) + *(int *)(iVar3 + 0x18)) - 1;
      FUN_0003ddf0();
      local_38 = FUN_0004c924(iVar3,0,0xc);
      uVar4 = (*(ushort *)(iVar3 + 0x58) & 0xfff) >> 8;
      if (uVar4 < 10) {
        local_a0 = *(uint *)(iVar3 + 0x38);
        FUN_0003d7de(iVar3 + 0x14,&local_48,uVar4,*(undefined4 *)(iVar3 + 0x34));
        local_30 = local_48;
        iStack_2c = local_44;
        uStack_28 = uStack_40;
        uStack_24 = uStack_3c;
      }
      else if (uVar4 == 0xc) {
        FUN_0003db4c(iVar2 + 0x18,iVar2 + 0x18,iVar3 + 0x14);
        FUN_0003ddd6(&local_48,*(undefined4 *)(iVar3 + 0x34),*(undefined4 *)(iVar3 + 0x38));
        iVar7 = *(int *)(iVar3 + 0x40);
        iVar3 = *(int *)(iVar3 + 0x3c);
        FUN_0003ddd6(&local_48,iVar3 * ((((*(int *)(iVar2 + 0x18) - local_48) - iVar3) + 1) / iVar3)
                     ,iVar7 * ((((*(int *)(iVar2 + 0x1c) - local_44) - iVar7) + 1) / iVar7));
        local_30 = *(int *)(iVar2 + 0x18);
        iStack_2c = *(int *)(iVar2 + 0x1c);
        uStack_28 = *(undefined4 *)(iVar2 + 0x20);
        uStack_24 = *(undefined4 *)(iVar2 + 0x24);
        local_50 = local_50 | 0x2000;
      }
      else {
        local_30 = local_48;
        iStack_2c = local_44;
        uStack_28 = uStack_40;
        uStack_24 = uStack_3c;
      }
      FUN_00041acc(iVar2,&local_9c,&local_30);
      *(undefined4 *)(iVar2 + 0x18) = uVar9;
      *(undefined4 *)(iVar2 + 0x1c) = uVar10;
      *(undefined4 *)(iVar2 + 0x20) = uVar11;
      *(undefined4 *)(iVar2 + 0x24) = uVar6;
    }
    else if (uVar4 == 2) {
      FUN_00041db4(&local_a0);
      FUN_0004cf40(iVar3,0,&local_a0);
      local_84 = *(undefined4 *)(iVar3 + 0x2c);
      FUN_00041d52(iVar2,&local_a0,iVar3 + 0x14);
    }
  }
  return;
}

