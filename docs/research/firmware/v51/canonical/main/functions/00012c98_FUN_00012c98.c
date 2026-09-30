/* Address: 00012c98; name: FUN_00012c98; body bytes: 54 */

undefined8 FUN_00012c98(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined1 local_14;
  undefined3 uStack_13;
  uint local_10;
  
  if (param_1 != 0) {
    uVar2 = 0;
    _local_14 = CONCAT31((int3)((uint)param_3 >> 8),(char)param_2);
    local_10 = param_4;
    iVar1 = FUN_00016468(0x74,&local_14,1,&local_10);
    if (iVar1 == 0) {
      uVar2 = local_10 & 0xff;
    }
    return CONCAT44(1,uVar2);
  }
  uVar3 = FUN_00016a6e(&DAT_1fff8f64,DAT_1fff8f64,param_2);
  return uVar3;
}

