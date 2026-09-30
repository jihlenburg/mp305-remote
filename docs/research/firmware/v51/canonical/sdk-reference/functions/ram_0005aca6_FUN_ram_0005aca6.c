/* Address: ram:0005aca6; name: FUN_ram_0005aca6; body bytes: 126 */

undefined4 FUN_ram_0005aca6(int param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = *(int *)(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0x15) = 6;
  *(undefined1 *)(iVar1 + 2) = 0xc;
  *(char *)(iVar1 + 3) = (char)(undefined2)DAT_ram_20001d74;
  *(undefined1 *)(iVar1 + 4) = DAT_ram_20001d74._2_1_;
  *(char *)(iVar1 + 5) = (char)((ushort)DAT_ram_20001d74._2_2_ >> 8);
  *(undefined1 *)(iVar1 + 6) = (undefined1)DAT_ram_20001d78;
  *(undefined1 *)(iVar1 + 7) = DAT_ram_20001d78._1_1_;
  if ((*(byte *)(param_1 + 0x2d) & 0x40) == 0) {
    if ((*(byte *)(param_1 + 0x2d) & 1) != 0) {
      *(undefined1 *)(param_1 + 0x2a) = 0;
      *(undefined1 *)(param_1 + 0x2d) = 0;
      *(uint *)(param_1 + 0xa0) = *(uint *)(param_1 + 0xa0) | 0x40;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x10) = 0x3a;
  }
  *(byte *)(param_1 + 0x2d) = *(byte *)(param_1 + 0x2d) & 0x7f;
  return 0;
}

