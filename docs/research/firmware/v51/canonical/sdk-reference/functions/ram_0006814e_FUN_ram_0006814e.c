/* Address: ram:0006814e; name: FUN_ram_0006814e; body bytes: 98 */

undefined4 FUN_ram_0006814e(undefined4 param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  gp = 0x20004000;
  iVar2 = FUN_ram_00057ba2();
  if (iVar2 == 0) {
    uVar3 = 2;
  }
  else {
    bVar1 = *(byte *)(iVar2 + 0x16a);
    uVar3 = 0xc;
    if ((bVar1 & 4) != 0) {
      if (param_2 == 0) {
        *(byte *)(iVar2 + 0x16a) = bVar1 & 0xfe;
        uVar3 = 0;
      }
      else {
        *(byte *)(iVar2 + 0x16a) = bVar1 | 1;
        uVar3 = 0;
        if ((*(char *)(iVar2 + 0x160) == '\x7f') && (-1 < (int)(*(uint *)(iVar2 + 0xa4) << 0xb))) {
          *(undefined1 *)(iVar2 + 0x165) = 0;
          *(uint *)(iVar2 + 0xa4) = *(uint *)(iVar2 + 0xa4) | 0x100000;
        }
      }
    }
  }
  return uVar3;
}

