/* Address: ram:20000d70; name: FUN_ram_20000d70; body bytes: 1 */

undefined4 FUN_ram_20000d70(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  gp = 0x20004000;
  iVar1 = DAT_ram_20001e14;
  uStack_18 = param_1;
  uStack_14 = param_2;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if ((*(byte *)(iVar1 + 1) == (uStack_18._1_1_ & 1)) &&
       (iVar2 = tmos_memcmp(iVar1 + 2,(int)&uStack_18 + 2,6), iVar2 == 1)) break;
    iVar1 = *(int *)(iVar1 + 8);
  }
  gp = 0x20004000;
  return 1;
}

