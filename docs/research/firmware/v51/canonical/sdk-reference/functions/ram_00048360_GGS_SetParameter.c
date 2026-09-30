/* Address: ram:00048360; name: GGS_SetParameter; body bytes: 228 */

undefined4 GGS_SetParameter(undefined4 param_1,uint param_2,undefined2 *param_3)

{
  undefined1 *puVar1;
  undefined *puVar2;
  
  gp = 0x20004000;
  switch(param_1) {
  case 0:
    if (0x15 < param_2) {
      gp = 0x20004000;
      return 0x18;
    }
    tmos_memset(&DAT_ram_20001ae4,0,0x16);
    tmos_memcpy(&DAT_ram_20001ae4,param_3,param_2);
    break;
  case 1:
    if (param_2 != 2) {
      gp = 0x20004000;
      return 0x18;
    }
    DAT_ram_20001a24 = *param_3;
    break;
  case 2:
  case 3:
  case 5:
  case 8:
    gp = 0x20004000;
    return 2;
  case 4:
    if (param_2 != 8) {
      gp = 0x20004000;
      return 0x18;
    }
    FUN_ram_0006be7a(&DAT_ram_200019ac,param_3,8);
    break;
  case 6:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    puVar1 = &DAT_ram_200018e0;
    puVar2 = PTR_DAT_ram_200019a7_ram_200018d4;
    goto LAB_ram_00048404;
  case 7:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    puVar1 = &DAT_ram_20001900;
    puVar2 = PTR_DAT_ram_200019a4_ram_200018f4;
LAB_ram_00048404:
    FUN_ram_00047ea8(*(undefined1 *)param_3,puVar1,puVar2);
    break;
  case 9:
    if (param_2 != 1) {
      gp = 0x20004000;
      return 0x18;
    }
    DAT_ram_200019a5 = *(undefined1 *)param_3;
    break;
  default:
    return 2;
  }
  return 0;
}

