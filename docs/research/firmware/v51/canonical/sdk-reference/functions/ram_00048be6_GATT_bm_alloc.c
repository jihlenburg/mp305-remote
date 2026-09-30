/* Address: ram:00048be6; name: GATT_bm_alloc; body bytes: 232 */

void GATT_bm_alloc(undefined4 param_1,uint param_2,uint param_3,undefined2 *param_4,
                  undefined4 param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  gp = 0x20004000;
  if (param_2 < 0x18) {
    if (0x15 < param_2) {
      iVar2 = 5;
      goto LAB_ram_00048c70;
    }
    if (param_2 != 9) {
      if (param_2 < 10) {
        if (param_2 != 5) {
          if (param_2 != 6) goto LAB_ram_00048c12;
          iVar2 = 7;
          goto LAB_ram_00048c70;
        }
      }
      else if (param_2 != 0x11) {
        uVar3 = 0x12;
        goto LAB_ram_00048c66;
      }
    }
    iVar1 = 2;
LAB_ram_00048c14:
    iVar2 = iVar1;
    if (param_3 != 0xffff) {
      if (param_2 != 0xd2) goto LAB_ram_00048c2c;
LAB_ram_00048cac:
      param_3 = param_3 + 0xc & 0xffff;
      iVar2 = iVar1;
      goto LAB_ram_00048c2c;
    }
  }
  else {
    if (param_2 != 0x1d) {
      if (param_2 < 0x1e) {
        uVar3 = 0x1b;
LAB_ram_00048c66:
        iVar2 = 3;
        if (param_2 == uVar3) goto LAB_ram_00048c70;
LAB_ram_00048c12:
        iVar1 = 1;
        goto LAB_ram_00048c14;
      }
      if (param_2 != 0x52) {
        if (param_2 != 0xd2) goto LAB_ram_00048c12;
        iVar2 = 3;
        iVar1 = 3;
        if (param_3 != 0xffff) goto LAB_ram_00048cac;
        goto LAB_ram_00048c1c;
      }
    }
    iVar2 = 3;
LAB_ram_00048c70:
    if (param_3 != 0xffff) goto LAB_ram_00048c2c;
  }
LAB_ram_00048c1c:
  iVar1 = ATT_GetMTU();
  param_3 = iVar1 - iVar2 & 0xffff;
LAB_ram_00048c2c:
  iVar1 = FUN_ram_0004c868(iVar2 + param_3 & 0xffff,param_5);
  if (iVar1 == 0) {
    return;
  }
  if (param_4 != (undefined2 *)0x0) {
    *param_4 = (short)param_3;
  }
  FUN_ram_00041bf2(iVar1,-iVar2);
  return;
}

