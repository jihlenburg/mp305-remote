/* Address: ram:000617ca; name: FUN_ram_000617ca; body bytes: 184 */

undefined4 FUN_ram_000617ca(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  gp = 0x20004000;
  iVar2 = DAT_ram_20001e14;
  iVar4 = 0;
  while (iVar1 = iVar2, iVar1 != 0) {
    if ((*(char *)(iVar1 + 1) == *(char *)(param_1 + 1)) &&
       (iVar2 = tmos_memcmp(iVar1 + 2,param_1 + 2,6), iVar2 == 1)) goto LAB_ram_00061864;
    iVar4 = iVar1;
    iVar2 = *(int *)(iVar1 + 8);
  }
  iVar2 = FUN_ram_20000040(0xc,0x208);
  uVar3 = 0;
  if (iVar2 != 0) {
    *(undefined1 *)(iVar2 + 1) = *(undefined1 *)(param_1 + 1);
    tmos_memcpy(iVar2 + 2,param_1 + 2,6);
    iVar1 = iVar2;
    if ((DAT_ram_20001e14 != 0) && (iVar1 = DAT_ram_20001e14, iVar4 != 0)) {
      *(int *)(iVar4 + 8) = iVar2;
      iVar1 = DAT_ram_20001e14;
    }
    DAT_ram_20001e14 = iVar1;
    *(undefined4 *)(iVar2 + 8) = 0;
    DAT_ram_20001e10 = DAT_ram_20001e10 + '\x01';
LAB_ram_00061864:
    uVar3 = 1;
  }
  return uVar3;
}

