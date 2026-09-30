/* Address: ram:20001120; name: FUN_ram_20001120; body bytes: 1 */

/* WARNING: Removing unreachable block (ram,0x20001162) */

undefined4 FUN_ram_20001120(int param_1,int param_2,undefined1 *param_3,ushort *param_4)

{
  byte bVar1;
  ushort uVar2;
  
  gp = 0x20004000;
  if ((*(uint *)(DAT_ram_20001e88 + 0x38) >> 5 & 1) != 0) {
    gp = 0x20004000;
    return 1;
  }
  if (param_3 != (undefined1 *)0x0) {
    *param_3 = (char)(*(uint *)(DAT_ram_20001e88 + 0x30) >> 0xf);
  }
  if (param_4 != (ushort *)0x0) {
    uVar2 = (ushort)((*(uint *)(DAT_ram_20001e88 + 0x30) & 0x7fff) >> 5);
    if ((int)(*(uint *)(DAT_ram_20001e88 + 0x30) << 0x11) < 0) {
      uVar2 = uVar2 | 0xfc00;
    }
    if ((short)*param_4 != 0) {
      uVar2 = (ushort)(((int)(short)uVar2 + (int)(short)*param_4) / 2);
    }
    *param_4 = uVar2;
  }
  if ((param_2 != 0) && (*(byte *)(param_1 + 1) != 0)) {
    if ((DAT_ram_20001e9a & 0x40) == 0) {
      gp = 0x20004000;
      return 2;
    }
    bVar1 = *(byte *)(param_1 + *(byte *)(param_1 + 1) + 9);
    if ((bVar1 & 0x6f) != 1) {
      gp = 0x20004000;
      return 6;
    }
    if ((char)bVar1 < '\0') {
      gp = 0x20004000;
      return 0xe;
    }
  }
  DAT_ram_20001e9f = (byte)((uint)*(undefined4 *)(DAT_ram_20001e88 + 0x38) >> 0x1b) & 3;
  return 0;
}

