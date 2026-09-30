/* Address: ram:00069728; name: GAPBondMgr_GetParameter; body bytes: 346 */

undefined4 GAPBondMgr_GetParameter(uint param_1,byte *param_2)

{
  byte bVar1;
  undefined2 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
  
  gp = 0x20004000;
  switch(param_1 - 0x400 & 0xffff) {
  case 0:
    bVar1 = DAT_ram_200019ca;
    break;
  case 1:
    bVar1 = DAT_ram_20001a98;
    goto LAB_ram_00069766;
  case 2:
    bVar1 = DAT_ram_20001a99;
    break;
  case 3:
    bVar1 = DAT_ram_20001a9b;
    break;
  case 4:
    puVar3 = &DAT_ram_20001b24;
    goto LAB_ram_00069788;
  case 5:
    bVar1 = DAT_ram_20001a98;
    goto LAB_ram_000697a6;
  case 6:
    bVar1 = DAT_ram_20001a9a;
    break;
  case 7:
    uVar4 = DAT_ram_20001a9c;
    goto LAB_ram_000697bc;
  case 8:
    bVar1 = DAT_ram_200019c7;
    break;
  case 9:
    bVar1 = DAT_ram_20001a90;
LAB_ram_00069766:
    bVar1 = (byte)((int)(uint)bVar1 >> 2);
    goto LAB_ram_000697a6;
  case 10:
    bVar1 = DAT_ram_20001a91;
    break;
  case 0xb:
    bVar1 = DAT_ram_20001a93;
    break;
  case 0xc:
    puVar3 = &DAT_ram_20001b14;
LAB_ram_00069788:
    tmos_memcpy(param_2,puVar3,0x10);
    gp = 0x20004000;
    return 0;
  case 0xd:
    bVar1 = DAT_ram_20001a90;
    goto LAB_ram_000697a6;
  case 0xe:
    bVar1 = DAT_ram_20001a92;
    break;
  case 0xf:
    uVar4 = DAT_ram_20001a94;
LAB_ram_000697bc:
    *(undefined4 *)param_2 = uVar4;
    gp = 0x20004000;
    return 0;
  default:
    if (param_1 < 0x40) {
      uVar2 = GAP_GetParamValue();
      *(undefined2 *)param_2 = uVar2;
      gp = 0x20004000;
      return 0;
    }
    gp = 0x20004000;
    return 2;
  case 0x11:
    bVar1 = DAT_ram_20001a8f;
    break;
  case 0x12:
    bVar1 = DAT_ram_200019c5;
    break;
  case 0x13:
    bVar1 = DAT_ram_200019c9;
    break;
  case 0x14:
    bVar1 = DAT_ram_20001a85;
    break;
  case 0x15:
    bVar1 = FUN_ram_00068a86();
    *param_2 = bVar1;
    gp = 0x20004000;
    return 0;
  case 0x1e:
    bVar1 = DAT_ram_200019c8;
    break;
  case 0x1f:
    bVar1 = DAT_ram_20001a84;
    break;
  case 0x21:
    bVar1 = DAT_ram_20001a98;
    goto LAB_ram_00069860;
  case 0x22:
    bVar1 = DAT_ram_20001a90;
LAB_ram_00069860:
    bVar1 = (byte)((int)(uint)bVar1 >> 3);
LAB_ram_000697a6:
    bVar1 = bVar1 & 1;
  }
  *param_2 = bVar1;
  return 0;
}

