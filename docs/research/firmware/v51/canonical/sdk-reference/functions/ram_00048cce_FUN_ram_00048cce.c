/* Address: ram:00048cce; name: FUN_ram_00048cce; body bytes: 124 */

int FUN_ram_00048cce(undefined4 param_1,undefined2 *param_2)

{
  int iVar1;
  undefined2 local_20;
  undefined2 uStack_1e;
  undefined2 uStack_1c;
  undefined1 uStack_1a;
  ushort uStack_18;
  int iStack_14;
  
  gp = 0x20004000;
  iStack_14 = GATT_bm_alloc(param_1,6,*(undefined1 *)(param_2 + 2),0,0x20);
  if (iStack_14 == 0) {
    iVar1 = 0x13;
  }
  else {
    local_20 = *param_2;
    uStack_1e = param_2[1];
    uStack_1c = 2;
    uStack_1a = 0x28;
    tmos_memcpy(iStack_14,(int)param_2 + 5,*(undefined1 *)(param_2 + 2));
    uStack_18 = (ushort)*(byte *)(param_2 + 2);
    iVar1 = FUN_ram_0004367c(param_1,&local_20);
    if (iVar1 != 0) {
      FUN_ram_20000104(iStack_14);
    }
  }
  return iVar1;
}

