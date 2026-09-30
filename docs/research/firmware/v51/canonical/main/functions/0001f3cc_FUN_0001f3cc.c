/* Address: 0001f3cc; name: FUN_0001f3cc; body bytes: 76 */

undefined4 FUN_0001f3cc(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  uint local_20;
  undefined4 local_1c;
  
  iVar1 = 200000;
  local_20 = param_3;
  local_1c = param_4;
  do {
    bVar2 = iVar1 == 0;
    iVar1 = iVar1 + -1;
    if (bVar2) {
      return 0;
    }
    local_1c = CONCAT31(local_1c._1_3_,5);
    FUN_00015384(2,0x20);
    FUN_00012d10(&local_1c,1);
    FUN_00012cec(&local_20,1);
    FUN_000153e0(2,0x20);
  } while ((local_20 & 1) != 0);
  return 1;
}

