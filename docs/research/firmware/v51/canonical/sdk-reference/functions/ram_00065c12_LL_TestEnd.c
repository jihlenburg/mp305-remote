/* Address: ram:00065c12; name: LL_TestEnd; body bytes: 122 */

undefined4 LL_TestEnd(undefined1 *param_1)

{
  int iVar1;
  
  gp = 0x20004000;
  if (param_1 != (undefined1 *)0x0) {
    *param_1 = (char)DAT_ram_20001d68;
    param_1[1] = (char)((ushort)DAT_ram_20001d68 >> 8);
  }
  FUN_ram_00062262();
  iVar1 = DAT_ram_20001efc;
  DAT_ram_20001d68 = 0;
  if (*(int *)(DAT_ram_20001efc + 0x10) << 0xe < 0) {
    *(uint *)(DAT_ram_20001efc + 0x10) = *(uint *)(DAT_ram_20001efc + 0x10) & 0xfff8ffff | 0x10000;
    *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | 0x100;
    *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xfffffdff;
    *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xfffffbff;
    *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | 0x800;
  }
  return 0;
}

