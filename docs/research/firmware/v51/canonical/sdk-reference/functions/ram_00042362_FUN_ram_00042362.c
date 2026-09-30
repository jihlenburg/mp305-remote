/* Address: ram:00042362; name: FUN_ram_00042362; body bytes: 148 */

undefined4 FUN_ram_00042362(int param_1,int param_2,undefined4 param_3,undefined1 *param_4)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    return 2;
  }
  iVar2 = 0xc0;
  uVar1 = 0x10;
  while ((*(int *)(DAT_ram_20001bf8 + iVar2) != 0 ||
         (iVar4 = tmos_start_task(uVar1 >> 4,1 << (uVar1 & 0xf) & 0xffff,param_3), iVar4 == 0))) {
    uVar1 = uVar1 + 1 & 0xff;
    iVar2 = iVar2 + 0xc;
    if (uVar1 == 0x30) {
      return 8;
    }
  }
  piVar3 = (int *)(iVar2 + DAT_ram_20001bf8);
  *piVar3 = param_1;
  piVar3[1] = param_2;
  if (param_4 == (undefined1 *)0x0) {
    gp = 0x20004000;
    return 0;
  }
  *param_4 = (char)uVar1;
  gp = 0x20004000;
  return 0;
}

