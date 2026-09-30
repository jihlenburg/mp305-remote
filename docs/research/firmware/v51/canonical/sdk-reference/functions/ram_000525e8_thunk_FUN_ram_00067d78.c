/* Address: ram:000525e8; name: thunk_FUN_ram_00067d78; body bytes: 4 */

undefined4 thunk_FUN_ram_00067d78(byte *param_1)

{
  int iVar1;
  int iVar2;
  
  gp = 0x20004000;
  if (((DAT_ram_20001dd8 == 0) || (-1 < *(int *)(DAT_ram_20001dd8 + 0x1c) << 0x11)) &&
     (DAT_ram_20001ddc != (code *)0x0)) {
    if (DAT_ram_20001dd8 == 0) {
      iVar1 = (*DAT_ram_20001ddc)();
      if (iVar1 == 0) {
        gp = 0x20004000;
        return 3;
      }
      *(undefined2 *)(iVar1 + 0x16) = 4;
      *(undefined2 *)(iVar1 + 0x18) = 4;
      *(undefined1 *)(iVar1 + 0x4d) = 0;
      *(undefined1 *)(iVar1 + 0xb) = 1;
    }
    iVar1 = DAT_ram_20001dd8;
    if ((param_1[0xe] & 7) == 7) {
      gp = 0x20004000;
      return 0xc;
    }
    if ((*param_1 & 1) == 0) {
      if ((*(uint *)(DAT_ram_20001dd8 + 0x1c) & 2) == 0) goto LAB_ram_00067dee;
      if (*(byte *)(DAT_ram_20001dd8 + 0xb4) != param_1[1]) {
        gp = 0x20004000;
        return 0xc;
      }
      if (*(byte *)(DAT_ram_20001dd8 + 0xb5) != param_1[2]) {
        gp = 0x20004000;
        return 0xc;
      }
      iVar2 = tmos_memcmp(DAT_ram_20001dd8 + 0xb6,param_1 + 3,6);
      if (iVar2 == 1) {
        gp = 0x20004000;
        return 0xb;
      }
    }
    if ((*(uint *)(iVar1 + 0x1c) & 2) == 0) {
LAB_ram_00067dee:
      if (((*param_1 & 6) == 4) && ((DAT_ram_20001e24 & 0x10) == 0)) {
        gp = 0x20004000;
        return 0x11;
      }
      if ((*param_1 & 1) == 0) {
        *(byte *)(iVar1 + 0xb4) = param_1[1];
        *(byte *)(iVar1 + 0xb5) = param_1[2];
        tmos_memcpy(iVar1 + 0xb6,param_1 + 3,6);
      }
      *(byte *)(iVar1 + 0x82) = *param_1;
      *(undefined2 *)(iVar1 + 0x84) = *(undefined2 *)(param_1 + 10);
      *(undefined2 *)(iVar1 + 0x86) = *(undefined2 *)(param_1 + 0xc);
      *(byte *)(iVar1 + 0x83) = param_1[0xe];
      *(undefined1 *)(iVar1 + 0x7d) = 0xff;
      *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) & 0xfffffff1 | 2;
      gp = 0x20004000;
      return 0;
    }
  }
  return 0xc;
}

