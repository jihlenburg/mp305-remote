/* Address: ram:0006b342; name: GAPRole_GetParameter; body bytes: 314 */

undefined4 GAPRole_GetParameter(uint param_1,byte *param_2)

{
  undefined2 uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  byte bVar4;
  
  gp = 0x20004000;
  switch(param_1 - 0x300 & 0xffff) {
  case 0:
    bVar4 = DAT_ram_20001f48;
    break;
  case 1:
    uVar3 = 0x10;
    puVar2 = &DAT_ram_20001f28;
    goto LAB_ram_0006b380;
  case 2:
    uVar3 = 0x10;
    puVar2 = &DAT_ram_20001f38;
    goto LAB_ram_0006b380;
  case 3:
    *(undefined4 *)param_2 = DAT_ram_20001acc;
    gp = 0x20004000;
    return 0;
  case 4:
    uVar3 = 6;
    puVar2 = &DAT_ram_20001f4c;
    goto LAB_ram_0006b380;
  case 5:
    bVar4 = DAT_ram_20001f14;
    break;
  case 6:
    FUN_ram_00047820(param_2);
    gp = 0x20004000;
    return 0;
  case 7:
    FUN_ram_00047848(param_2);
    gp = 0x20004000;
    return 0;
  case 8:
    bVar4 = DAT_ram_20001f16;
    break;
  case 9:
    bVar4 = DAT_ram_20001f24;
    break;
  case 10:
    uVar3 = 6;
    puVar2 = &DAT_ram_20001ac4;
LAB_ram_0006b380:
    tmos_memcpy(param_2,puVar2,uVar3);
    gp = 0x20004000;
    return 0;
  case 0xb:
    bVar4 = DAT_ram_20001f15;
    break;
  case 0xc:
    bVar4 = DAT_ram_20001f49;
    break;
  case 0xd:
    bVar4 = (byte)DAT_ram_20001f20;
    break;
  case 0xe:
    bVar4 = DAT_ram_20001ac0;
    break;
  default:
    if (param_1 < 0x40) {
      uVar1 = GAP_GetParamValue();
      *(undefined2 *)param_2 = uVar1;
      gp = 0x20004000;
      return 0;
    }
    gp = 0x20004000;
    return 2;
  case 0x11:
    uVar1 = DAT_ram_20001f1c;
    goto LAB_ram_0006b424;
  case 0x12:
    uVar1 = DAT_ram_20001f26;
LAB_ram_0006b424:
    *(undefined2 *)param_2 = uVar1;
    gp = 0x20004000;
    return 0;
  case 0x13:
    bVar4 = DAT_ram_20001f19;
    break;
  case 0x14:
    bVar4 = DAT_ram_20001f1a;
    break;
  case 0x15:
    FUN_ram_00047880(param_2);
    gp = 0x20004000;
    return 0;
  case 0x16:
    bVar4 = DAT_ram_20001f18 & 0x7f;
    break;
  case 0x17:
    bVar4 = DAT_ram_20001f53;
  }
  *param_2 = bVar4;
  return 0;
}

