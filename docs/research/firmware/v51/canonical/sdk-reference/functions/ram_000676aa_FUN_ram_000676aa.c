/* Address: ram:000676aa; name: FUN_ram_000676aa; body bytes: 342 */

undefined4
FUN_ram_000676aa(uint param_1,undefined1 param_2,uint param_3,undefined1 *param_4,ushort *param_5,
                ushort *param_6)

{
  undefined1 uVar1;
  ushort uVar2;
  int iVar3;
  ushort uVar4;
  int iVar5;
  undefined4 uVar6;
  
  gp = 0x20004000;
  if ((((DAT_ram_20001dd8 == 0) || (uVar6 = 0xc, -1 < *(int *)(DAT_ram_20001dd8 + 0x1c) << 0x11)) &&
      (uVar6 = 0xc, DAT_ram_20001ddc != (code *)0x0)) &&
     ((uVar6 = 0x11, (param_3 & 0xfffffffa) == 0 && (uVar6 = 0xc, (param_3 & 5) != 0)))) {
    if (DAT_ram_20001dd8 == 0) {
      iVar3 = (*DAT_ram_20001ddc)();
      if (iVar3 == 0) {
        gp = 0x20004000;
        return 3;
      }
    }
    else {
      iVar3 = DAT_ram_20001dd8;
      if (*(char *)(DAT_ram_20001dd8 + 0xb) != '\0') {
        gp = 0x20004000;
        return 0xc;
      }
    }
    uVar6 = 0x12;
    if (param_1 < 4) {
      *(char *)(iVar3 + 0x4d) = (char)param_1;
      *(undefined1 *)(iVar3 + 0x10) = param_2;
      *(undefined1 *)(iVar3 + 0x20) = 0;
      iVar5 = 0;
      if ((param_3 & 1) != 0) {
        *(undefined1 *)(iVar3 + 0xf) = *param_4;
        uVar2 = *param_5;
        *(ushort *)(iVar3 + 0x16) = uVar2;
        uVar4 = *param_6;
        if (uVar2 < *param_6) {
          uVar4 = uVar2;
        }
        if (uVar2 < uVar4) {
          *(ushort *)(iVar3 + 0x18) = uVar2;
        }
        else {
          *(ushort *)(iVar3 + 0x18) = uVar4;
        }
        *(short *)(iVar3 + 0x1a) = (short)((uint)*(ushort *)(iVar3 + 0x18) * 0x55 >> 8);
        *(undefined1 *)(iVar3 + 0x20) = 1;
        iVar5 = 1;
      }
      if ((param_3 & 4) != 0) {
        uVar1 = param_4[iVar5];
        *(undefined1 *)(iVar3 + 0xf) = uVar1;
        *(undefined1 *)(iVar3 + 0x2f) = uVar1;
        uVar2 = param_5[iVar5];
        *(ushort *)(iVar3 + 0x32) = uVar2;
        uVar4 = param_6[iVar5];
        if (uVar2 < param_6[iVar5]) {
          uVar4 = uVar2;
        }
        if (uVar2 < uVar4) {
          *(ushort *)(iVar3 + 0x34) = uVar2;
        }
        else {
          *(ushort *)(iVar3 + 0x34) = uVar4;
        }
        *(short *)(iVar3 + 0x36) = (short)((uint)*(ushort *)(iVar3 + 0x34) * 0x55 >> 8);
        *(byte *)(iVar3 + 0x20) = *(byte *)(iVar3 + 0x20) | 2;
      }
      uVar6 = 0;
      *(uint *)(iVar3 + 0x1c) = *(uint *)(iVar3 + 0x1c) | 0x8000;
    }
  }
  return uVar6;
}

