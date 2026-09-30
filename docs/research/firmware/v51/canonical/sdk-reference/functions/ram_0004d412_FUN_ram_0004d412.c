/* Address: ram:0004d412; name: FUN_ram_0004d412; body bytes: 50 */

undefined4 FUN_ram_0004d412(undefined2 param_1,ushort *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  gp = 0x20004000;
  iVar1 = (*param_2 - 4) * 0xc;
  if (*(int *)(&DAT_ram_20001cd0 + iVar1) == 0) {
    uVar2 = *(undefined4 *)(param_2 + 2);
    *(undefined2 *)(&DAT_ram_20001cd6 + iVar1) = param_1;
    *(undefined4 *)(&DAT_ram_20001cd0 + iVar1) = uVar2;
    *(ushort *)(&DAT_ram_20001cd4 + iVar1) = param_2[1];
    return 0;
  }
  return 0x16;
}

