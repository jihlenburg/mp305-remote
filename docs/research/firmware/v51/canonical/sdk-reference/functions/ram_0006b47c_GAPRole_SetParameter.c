/* Address: ram:0006b47c; name: GAPRole_SetParameter; body bytes: 770 */

undefined4 GAPRole_SetParameter(uint param_1,uint param_2,byte *param_3)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  undefined2 uVar5;
  byte bVar6;
  byte bVar7;
  short sVar8;
  byte bVar9;
  undefined *puVar10;
  undefined4 uVar11;
  
  gp = 0x20004000;
  bVar6 = DAT_ram_20001f15;
  bVar7 = DAT_ram_20001f16;
  sVar3 = DAT_ram_20001f1c;
  bVar2 = DAT_ram_20001f24;
  sVar8 = DAT_ram_20001f26;
  bVar9 = DAT_ram_20001f49;
  switch(param_1 - 0x301 & 0xffff) {
  case 0:
    if (param_2 != 0x10) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar11 = 0x10;
    puVar10 = &DAT_ram_20001f28;
    goto LAB_ram_0006b4b8;
  case 1:
    if (param_2 != 0x10) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar11 = 0x10;
    puVar10 = &DAT_ram_20001f38;
    goto LAB_ram_0006b4b8;
  case 2:
    if (param_2 != 4) {
      gp = 0x20004000;
      return 0x18;
    }
    DAT_ram_20001acc = *(undefined4 *)param_3;
    break;
  case 3:
  case 0xc:
  case 0xe:
  case 0xf:
    if (0x3f < param_1) {
      gp = 0x20004000;
      return 2;
    }
    if (param_2 != 2) {
      gp = 0x20004000;
      return 2;
    }
    uVar5 = *(undefined2 *)param_3;
    goto LAB_ram_0006b756;
  case 4:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar2 = *param_3;
    if (DAT_ram_20001f14 != 0) {
      if (bVar2 != 0) {
        gp = 0x20004000;
        DAT_ram_20001f14 = bVar2;
        return 0;
      }
      if (((DAT_ram_20001f20 & 0xf) != 2) && ((DAT_ram_20001f20 & 0xf) != 5)) {
        gp = 0x20004000;
        DAT_ram_20001f14 = bVar2;
        return 0;
      }
      DAT_ram_20001f14 = bVar2;
      FUN_ram_000471e2(DAT_ram_200019cc);
      gp = 0x20004000;
      return 0;
    }
    if (bVar2 == 0) {
      gp = 0x20004000;
      DAT_ram_20001f14 = bVar2;
      return 0;
    }
    if ((DAT_ram_20001f20 != 1) && (1 < (DAT_ram_20001f20 & 0xf) - 3)) {
      gp = 0x20004000;
      DAT_ram_20001f14 = bVar2;
      return 0;
    }
    uVar11 = 1;
    DAT_ram_20001f14 = bVar2;
    goto LAB_ram_0006b54c;
  case 5:
    if (0x1cc < param_2) {
      gp = 0x20004000;
      return 0x18;
    }
    if (param_3 == (byte *)0x0) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar11 = FUN_ram_00047530();
    return uVar11;
  case 6:
    if (0x1cc < param_2) {
      gp = 0x20004000;
      return 0x18;
    }
    if (param_3 == (byte *)0x0) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar11 = FUN_ram_00047640();
    return uVar11;
  case 7:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar7 = *param_3;
    if (10 < *param_3) {
      gp = 0x20004000;
      return 0x18;
    }
    break;
  case 8:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar2 = *param_3;
    bVar1 = bVar2;
    goto joined_r0x0006b5f8;
  case 9:
    if (param_2 != 6) {
      gp = 0x20004000;
      return 0x18;
    }
    uVar11 = 6;
    puVar10 = &DAT_ram_20001ac4;
LAB_ram_0006b4b8:
    tmos_memcpy(puVar10,param_3,uVar11);
    bVar6 = DAT_ram_20001f15;
    bVar7 = DAT_ram_20001f16;
    sVar3 = DAT_ram_20001f1c;
    bVar2 = DAT_ram_20001f24;
    sVar8 = DAT_ram_20001f26;
    bVar9 = DAT_ram_20001f49;
    break;
  case 10:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar6 = *param_3;
    if (7 < *param_3) {
      gp = 0x20004000;
      return 0x18;
    }
    break;
  case 0xb:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar9 = *param_3;
    bVar1 = *param_3;
joined_r0x0006b5f8:
    if (3 < bVar1) {
      gp = 0x20004000;
      return 0x18;
    }
    break;
  case 0xd:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    DAT_ram_20001ac0 = *param_3;
    break;
  case 0x10:
    if (param_2 != 2) {
      gp = 0x20004000;
      return 0x18;
    }
    sVar3 = *(short *)param_3;
    sVar4 = sVar3;
    goto joined_r0x0006b65e;
  case 0x11:
    if (param_2 != 2) {
      gp = 0x20004000;
      return 0x18;
    }
    sVar8 = *(short *)param_3;
    sVar4 = *(short *)param_3;
joined_r0x0006b65e:
    if (0xc7a < (ushort)(sVar4 - 6U)) {
      gp = 0x20004000;
      return 0x18;
    }
    break;
  case 0x12:
    DAT_ram_20001f19 = *param_3;
    goto LAB_ram_0006b680;
  case 0x13:
    DAT_ram_20001f1a = *param_3;
LAB_ram_0006b680:
    thunk_FUN_ram_000657a4(0,DAT_ram_20001f19,DAT_ram_20001f1a);
    bVar6 = DAT_ram_20001f15;
    bVar7 = DAT_ram_20001f16;
    sVar3 = DAT_ram_20001f1c;
    bVar2 = DAT_ram_20001f24;
    sVar8 = DAT_ram_20001f26;
    bVar9 = DAT_ram_20001f49;
    break;
  case 0x14:
    if ((param_2 < 0x1cd) && (param_3 != (byte *)0x0)) {
      uVar11 = FUN_ram_00047750();
      return uVar11;
    }
    gp = 0x20004000;
    return 0x18;
  case 0x15:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar2 = *param_3;
    if ((DAT_ram_20001f18 & 1) != 0) {
      if ((bVar2 & 1) != 0) {
        gp = 0x20004000;
        DAT_ram_20001f18 = bVar2;
        return 0;
      }
      DAT_ram_20001f18 = bVar2;
      FUN_ram_000473a6();
      gp = 0x20004000;
      return 0;
    }
    if ((bVar2 & 1) == 0) {
      gp = 0x20004000;
      DAT_ram_20001f18 = bVar2;
      return 0;
    }
    uVar11 = 2;
    DAT_ram_20001f18 = bVar2;
    if ((DAT_ram_20001f20 & 0xe) == 0) {
      gp = 0x20004000;
      DAT_ram_20001f18 = bVar2 | 0x80;
      return 0;
    }
    goto LAB_ram_0006b54c;
  case 0x16:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    bVar2 = *param_3;
    if (DAT_ram_20001f53 != 0) {
      if (bVar2 != 0) {
        gp = 0x20004000;
        DAT_ram_20001f53 = bVar2;
        return 0;
      }
      DAT_ram_20001f53 = bVar2;
      FUN_ram_000473d4(1,param_3);
      gp = 0x20004000;
      return 0;
    }
    if (bVar2 == 0) {
      gp = 0x20004000;
      DAT_ram_20001f53 = bVar2;
      return 0;
    }
    if ((DAT_ram_20001f20 & 0xf0) == 0) {
      gp = 0x20004000;
      DAT_ram_20001f53 = bVar2 | 0x80;
      return 0;
    }
    uVar11 = 4;
    DAT_ram_20001f53 = bVar2;
LAB_ram_0006b54c:
    tmos_set_event(DAT_ram_200019cc,uVar11);
    bVar6 = DAT_ram_20001f15;
    bVar7 = DAT_ram_20001f16;
    sVar3 = DAT_ram_20001f1c;
    bVar2 = DAT_ram_20001f24;
    sVar8 = DAT_ram_20001f26;
    bVar9 = DAT_ram_20001f49;
    break;
  default:
    if ((0x3f < param_1) || (param_2 != 2)) {
      return 2;
    }
    uVar5 = *(undefined2 *)param_3;
LAB_ram_0006b756:
    uVar11 = GAP_SetParamValue(param_1,uVar5);
    return uVar11;
  }
  DAT_ram_20001f49 = bVar9;
  DAT_ram_20001f26 = sVar8;
  DAT_ram_20001f24 = bVar2;
  DAT_ram_20001f1c = sVar3;
  DAT_ram_20001f16 = bVar7;
  DAT_ram_20001f15 = bVar6;
  return 0;
}

