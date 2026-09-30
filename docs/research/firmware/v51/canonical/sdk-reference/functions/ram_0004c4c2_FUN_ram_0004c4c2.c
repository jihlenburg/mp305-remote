/* Address: ram:0004c4c2; name: FUN_ram_0004c4c2; body bytes: 90 */

void FUN_ram_0004c4c2(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  
  gp = 0x20004000;
  iVar1 = (param_1 + -4) * 0xc;
  if (((*(ushort *)(&DAT_ram_20001cd6 + iVar1) == param_2) &&
      (*(byte **)(&DAT_ram_20001cd0 + iVar1) != (byte *)0x0)) &&
     ((param_3 == 0xff || (**(byte **)(&DAT_ram_20001cd0 + iVar1) == param_3)))) {
    FUN_ram_20000104();
    *(undefined4 *)(&DAT_ram_20001cd0 + (param_1 + -4) * 0xc) = 0;
  }
  return;
}

