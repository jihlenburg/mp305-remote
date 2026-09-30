/* Address: 0004af50; name: FUN_0004af50; body bytes: 238 */

undefined4 FUN_0004af50(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined1 auStack_28 [20];
  
  iVar1 = FUN_0004cd84(param_1,1);
  if (iVar1 == 0) {
    iVar1 = FUN_0004bc94(param_1);
    uVar2 = FUN_0004bb48();
    iVar3 = FUN_00040928();
    if ((((iVar3 == iVar1) || (iVar3 = FUN_0004093c(uVar2), iVar3 == iVar1)) ||
        (iVar3 = FUN_000408d8(uVar2), iVar3 == iVar1)) ||
       ((iVar3 = FUN_00040900(uVar2), iVar3 == iVar1 ||
        (iVar3 = FUN_000408ec(uVar2), iVar3 == iVar1)))) {
      uVar2 = FUN_0004bbb0(param_1);
      FUN_0003d9a4(auStack_28,param_1 + 0x14);
      FUN_0003db32(auStack_28,uVar2);
      iVar1 = FUN_0003db4c(param_2,param_2,auStack_28);
      if (iVar1 == 0) {
        return 0;
      }
      FUN_0004cc08(param_1,param_2,1);
      iVar1 = FUN_0004bc8c(param_1);
      while( true ) {
        if (iVar1 == 0) {
          return 1;
        }
        iVar3 = FUN_0004cd84(iVar1,1);
        if (iVar3 != 0) break;
        local_38 = *(undefined4 *)(iVar1 + 0x14);
        uStack_34 = *(undefined4 *)(iVar1 + 0x18);
        uStack_30 = *(undefined4 *)(iVar1 + 0x1c);
        uStack_2c = *(undefined4 *)(iVar1 + 0x20);
        iVar3 = FUN_0004cd84(iVar1,0x100000);
        if (iVar3 != 0) {
          uVar2 = FUN_0004bbb0(iVar1);
          FUN_0003db32(&local_38,uVar2,uVar2);
        }
        FUN_0004cc08(iVar1,&local_38,1);
        iVar3 = FUN_0003db4c(param_2,param_2,&local_38);
        if (iVar3 == 0) {
          return 0;
        }
        iVar1 = FUN_0004bc8c(iVar1);
      }
    }
  }
  return 0;
}

