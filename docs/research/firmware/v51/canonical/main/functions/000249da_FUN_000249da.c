/* Address: 000249da; name: FUN_000249da; body bytes: 114 */

void FUN_000249da(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int local_20;
  
  local_20 = param_4;
  iVar3 = FUN_0003ff24(param_3);
  cVar2 = FUN_00036ec0(param_1,param_2);
  bVar1 = -cVar2;
  local_20 = CONCAT31(local_20._1_3_,bVar1);
  if (param_4 == 1) {
    uVar4 = (uint)bVar1 + iVar3;
    if (0xfe < (int)uVar4) {
      uVar4 = 0xff;
    }
  }
  else {
    if (param_4 != 2) {
      if (param_4 != 3) {
        return;
      }
      uVar4 = ((int)(short)(ushort)bVar1 * (int)(short)iVar3 & 0xffffU) >> 8;
      goto LAB_00024a14;
    }
    uVar4 = (uint)bVar1 - iVar3;
    if ((int)uVar4 < 1) {
      uVar4 = 0;
    }
  }
  uVar4 = uVar4 & 0xff;
LAB_00024a14:
  FUN_00040264(uVar4,&local_20,param_3 >> 0x18);
  if ((byte)local_20 < 0x80) {
    FUN_00027368(param_1,param_2);
  }
  else {
    FUN_0005e778();
  }
  return;
}

